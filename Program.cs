using System;
using System.Text;
using System.Collections.Generic;
using System.Linq;
using System.IO;
using MidiParser;

namespace midi2notes
{
    class Program
    {
        enum note_t
        {
            NOTE_C, NOTE_Cs, NOTE_D, NOTE_Eb, NOTE_E, NOTE_F, NOTE_Fs, NOTE_G, NOTE_Gs, NOTE_A, NOTE_Bb, NOTE_B, NOTE_MAX
        };

        const string classSrc =
@"#ifndef _NOTE_H
#define _NOTE_H
typedef struct Note {{
	note_t name;
	int8_t octave;
	int duration;
}};
#define ARRAY_LENGTH(a) (sizeof(a)/sizeof(a[0]))
typedef void (PLAYER_CALLBACK)();
#endif 

    class {1}Player {{
	public:
		void begin(int startPin = 12) {{
			for (int i=0; i<{0};i++) {{
    			ledcSetup(i*2, 2000, 8);
    			ledcAttachPin(startPin+i, i*2);
			}}
        }}
        void play(int8_t tempo, int8_t octShift) {{
            musicTempo = tempo;
            octaveShift = octShift;
            for (int i=0; i<{0}; i++) {{ idx[i] = ms[i] = 0; doPlay[i] = true; }}
        }}
		void update() {{
			for (int i=0; i<{0}; i++) {{
				if (doPlay[i] && millis()-ms[i] >= music[i][idx[i]].duration*musicTempo) {{
                    ms[i]=millis();
                    if (idx[i]++ < len[i]-1) {{
                        if (music[i][idx[i]].name == NOTE_MAX) ledcWrite(i*2, 0);
                        else ledcWriteNote(i*2, music[i][idx[i]].name, music[i][idx[i]].octave+octaveShift);
				    }}
                    else {{
                        ledcWrite(i*2, 0);
                        doPlay[i] = false;
                    }}
				}}
			}}
            if (!isPlaying() && pEndMusic) (*pEndMusic)();
		}}
        void pause() {{ for (int i=0; i<{0}; i++) {{ doPlay[i]=false; ledcWrite(i*2, 0); }} }}
        void resume() {{ for (int i=0; i<{0}; i++) doPlay[i]=true; }}
        bool isPlaying() {{ 
            for (int i=0; i<{0}; i++) if (doPlay[i]) return true; 
            return false;
        }}
        void setOnEndMusic(PLAYER_CALLBACK *callback) {{ pEndMusic = callback; }}
	private:
        int idx[{0}];
        unsigned long ms[{0}];
        bool doPlay[{0}];
        int8_t musicTempo = 2;
        int8_t octaveShift = 0;
        PLAYER_CALLBACK *pEndMusic = NULL;
";

        class Note
        {
            public note_t Value { get; set; }
            public int Octave { get; set; }
            public int Duration { get; set; }
            public int StartTime { get; set; }
            public Note(note_t val, byte octave, int duration = 48) { Value = val; Octave = octave; Duration = duration; }
            public Note(int noteNumber, int startTime)
            {
                Value = (note_t) (noteNumber % (Enum.GetNames(typeof(note_t)).Length-1));
                Octave = (noteNumber / (Enum.GetNames(typeof(note_t)).Length-1)) - 2;
                StartTime = startTime;
                Duration = 48;
            }
        }

        class ChannelNotes
        {
            public List<Note> Notes;
            public int Channel { get; set; }
            public ChannelNotes(int chan)
            {
                Channel = chan;
                Notes = new List<Note>();
            }
            public void AddNote(bool noteOn, int noteNumber, int time)
            {
                if (noteOn) Notes.Add(new Note(noteNumber, time));
                else
                {
                    var noteDuration = time-Notes.Last().StartTime;
                    if (noteDuration > 1000)
                    {
                        Notes.Last().Duration = 48;
                        Notes.Add(new Note(note_t.NOTE_MAX, 0, noteDuration - 48));
                    }
                    else Notes.Last().Duration = time - Notes.Last().StartTime;
                }
            }
        }

        static void Main(string[] args)
        {
            List<ChannelNotes> music = new List<ChannelNotes>();

            if (args.Length == 0 || !File.Exists(args[0])) return;
            var midiFile = new MidiFile(args[0]);

            foreach (var track in midiFile.Tracks)
            {
                foreach (var midiEvent in track.MidiEvents)
                {
                    if (midiEvent.MidiEventType == MidiEventType.NoteOn || midiEvent.MidiEventType == MidiEventType.NoteOff)
                    {
                        ChannelNotes channel = music.FirstOrDefault(c => c.Channel == midiEvent.Channel);
                        if (channel == null)
                        {
                            channel = new ChannelNotes(midiEvent.Channel);
                            music.Add(channel);
                        }
                        channel.AddNote(midiEvent.MidiEventType == MidiEventType.NoteOn, midiEvent.Note, midiEvent.Time);
                    }

                }
            }

            var sb = new StringBuilder(string.Format(classSrc, music.Count, Path.GetFileNameWithoutExtension(args[0])));
            int num = 0;
            foreach (var chan in music)
            {
                num++;
                sb.AppendLine($"\t\tNote ch_{num}[{chan.Notes.Count}] PROGMEM = {{");
                int i = 0;
                foreach (var note in chan.Notes)
                {
                    sb.Append($"{{ {note.Value}, {note.Octave}, {note.Duration} }},");
                    i += 18;
                    if (i > 80)
                    {
                        i = 0;
                        sb.AppendLine();
                    }
                }
                sb.Replace(',', ' ', sb.Length-4, 4);
                sb.AppendLine("};\n");
            }

            sb.Append($"\t\tNote* music[{music.Count}] = {{");
            for (int i = 1; i <= music.Count; i++) sb.Append($"ch_{i},");
            sb.Remove(sb.Length - 1, 1);
            sb.AppendLine("};");

            sb.Append($"\t\tint len[{music.Count}] = {{");
            for (int i = 1; i <= music.Count; i++) sb.Append($"ARRAY_LENGTH(ch_{i}),");
            sb.Remove(sb.Length - 1, 1);
            sb.AppendLine("};");
            sb.AppendLine("};");
            Console.WriteLine(sb);
        }
    }
}
