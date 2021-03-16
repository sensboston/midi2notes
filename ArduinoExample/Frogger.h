#ifndef _NOTE_H
#define _NOTE_H
typedef struct Note {
	note_t name;
	int8_t octave;
	int duration;
};
#define ARRAY_LENGTH(a) (sizeof(a)/sizeof(a[0]))
typedef void (PLAYER_CALLBACK)();
#endif 

    class FroggerPlayer {
    private:
        int len[2] = { ARRAY_LENGTH(ch_1),ARRAY_LENGTH(ch_2) }; 
        Note* music[ARRAY_LENGTH(len)] = { ch_1,ch_2 };
	public:
		void begin(int startPin = 12) {
			for (int i=0; i<ARRAY_LENGTH(len);i++) {
    			ledcSetup(i*2, 2000, 8);
    			ledcAttachPin(startPin+i, i*2);
			}
        }
        void play(int8_t tempo, int8_t octShift) {
            musicTempo = tempo;
            octaveShift = octShift;
            for (int i=0; i<ARRAY_LENGTH(len); i++) { idx[i] = ms[i] = 0; doPlay[i] = true; }
        }
		void update() {
			for (int i=0; i<ARRAY_LENGTH(len); i++) {
				if (doPlay[i] && millis()-ms[i] >= music[i][idx[i]].duration*musicTempo) {
                    ms[i]=millis();
                    if (idx[i]++ < len[i]-1) {
                        if (music[i][idx[i]].name == NOTE_MAX) ledcWrite(i*2, 0);
                        else ledcWriteNote(i*2, music[i][idx[i]].name, music[i][idx[i]].octave+octaveShift);
				    }
                    else {
                        ledcWrite(i*2, 0);
                        doPlay[i] = false;
                    }
				}
			}
            if (!isPlaying() && pEndMusic) (*pEndMusic)();
		}
        void pause() { for (int i=0; i<ARRAY_LENGTH(len); i++) { doPlay[i]=false; ledcWrite(i*2, 0); } }
        void resume() { for (int i=0; i<ARRAY_LENGTH(len); i++) doPlay[i]=true; }
        bool isPlaying() { 
            for (int i=0; i<ARRAY_LENGTH(len); i++) if (doPlay[i]) return true; 
            return false;
        }
        void setOnEndMusic(PLAYER_CALLBACK *callback) { pEndMusic = callback; }
	private:
        int idx[ARRAY_LENGTH(len)];
        unsigned long ms[ARRAY_LENGTH(len)];
        bool doPlay[ARRAY_LENGTH(len)];
        int8_t musicTempo = 2;
        int8_t octaveShift = 0;
        PLAYER_CALLBACK *pEndMusic = NULL;
		Note ch_1[368] PROGMEM = {
{ NOTE_Cs, 4, 179 },{ NOTE_Bb, 3, 90 },{ NOTE_Fs, 3, 89 },{ NOTE_Fs, 4, 179 },{ NOTE_F, 4, 90 },
{ NOTE_Eb, 4, 90 },{ NOTE_Cs, 4, 179 },{ NOTE_Fs, 4, 89 },{ NOTE_Bb, 3, 90 },{ NOTE_Cs, 4, 90 },
{ NOTE_Gs, 3, 358 },{ NOTE_Cs, 4, 90 },{ NOTE_Cs, 4, 89 },{ NOTE_Cs, 4, 90 },{ NOTE_Cs, 4, 89 },
{ NOTE_Bb, 3, 90 },{ NOTE_Gs, 3, 90 },{ NOTE_Fs, 3, 179 },{ NOTE_Fs, 4, 89 },{ NOTE_Fs, 4, 90 },
{ NOTE_Fs, 4, 90 },{ NOTE_Gs, 4, 89 },{ NOTE_Fs, 4, 90 },{ NOTE_F, 4, 89 },{ NOTE_Eb, 4, 90 },
{ NOTE_Cs, 4, 90 },{ NOTE_Bb, 3, 179 },{ NOTE_Bb, 3, 89 },{ NOTE_Fs, 4, 180 },{ NOTE_Bb, 3, 179 },
{ NOTE_Cs, 4, 89 },{ NOTE_Gs, 3, 717 },{ NOTE_Bb, 3, 90 },{ NOTE_Bb, 3, 89 },{ NOTE_B, 3, 90 },
{ NOTE_Cs, 4, 90 },{ NOTE_Eb, 4, 89 },{ NOTE_F, 4, 90 },{ NOTE_Eb, 4, 806 },{ NOTE_B, 3, 90 },
{ NOTE_B, 3, 89 },{ NOTE_Cs, 4, 90 },{ NOTE_Eb, 4, 179 },{ NOTE_F, 4, 90 },{ NOTE_Fs, 4, 89 },
{ NOTE_F, 4, 628 },{ NOTE_Cs, 4, 179 },{ NOTE_Fs, 4, 358 },{ NOTE_F, 4, 179 },{ NOTE_Eb, 4, 90 },
{ NOTE_Cs, 4, 90 },{ NOTE_F, 4, 179 },{ NOTE_Eb, 4, 358 },{ NOTE_Eb, 4, 179 },{ NOTE_Cs, 4, 180 },
{ NOTE_Gs, 4, 179 },{ NOTE_Fs, 4, 179 },{ NOTE_F, 4, 179 },{ NOTE_Fs, 4, 717 },{ NOTE_Fs, 4, 90 },
{ NOTE_Fs, 4, 89 },{ NOTE_Gs, 4, 90 },{ NOTE_Bb, 4, 89 },{ NOTE_Fs, 4, 90 },{ NOTE_Bb, 4, 90 },
{ NOTE_Gs, 4, 89 },{ NOTE_Cs, 4, 90 },{ NOTE_Fs, 4, 89 },{ NOTE_Fs, 4, 90 },{ NOTE_Gs, 4, 90 },
{ NOTE_Bb, 4, 89 },{ NOTE_Fs, 4, 179 },{ NOTE_F, 4, 90 },{ NOTE_Cs, 4, 90 },{ NOTE_Fs, 4, 89 },
{ NOTE_Fs, 4, 90 },{ NOTE_Gs, 4, 89 },{ NOTE_Bb, 4, 90 },{ NOTE_B, 4, 90 },{ NOTE_Bb, 4, 89 },
{ NOTE_Gs, 4, 90 },{ NOTE_Fs, 4, 89 },{ NOTE_F, 4, 90 },{ NOTE_Cs, 4, 90 },{ NOTE_Eb, 4, 89 },
{ NOTE_F, 4, 90 },{ NOTE_Fs, 4, 179 },{ NOTE_Fs, 4, 179 },{ NOTE_Eb, 4, 90 },{ NOTE_F, 4, 89 },
{ NOTE_Eb, 4, 90 },{ NOTE_Cs, 4, 90 },{ NOTE_Eb, 4, 89 },{ NOTE_F, 4, 90 },{ NOTE_Fs, 4, 179 },
{ NOTE_Cs, 4, 90 },{ NOTE_Eb, 4, 89 },{ NOTE_Cs, 4, 90 },{ NOTE_B, 3, 89 },{ NOTE_Bb, 3, 180 },
{ NOTE_Cs, 4, 179 },{ NOTE_Eb, 4, 89 },{ NOTE_F, 4, 90 },{ NOTE_Eb, 4, 90 },{ NOTE_Cs, 4, 89 },
{ NOTE_Eb, 4, 90 },{ NOTE_F, 4, 89 },{ NOTE_Fs, 4, 90 },{ NOTE_Eb, 4, 90 },{ NOTE_Cs, 4, 89 },
{ NOTE_Fs, 4, 90 },{ NOTE_F, 4, 89 },{ NOTE_Gs, 4, 90 },{ NOTE_Fs, 4, 179 },{ NOTE_Fs, 4, 807 },
{ NOTE_F, 3, 89 },{ NOTE_Bb, 3, 179 },{ NOTE_Bb, 3, 90 },{ NOTE_Cs, 4, 90 },{ NOTE_F, 4, 268 },
{ NOTE_F, 3, 90 },{ NOTE_A, 3, 90 },{ NOTE_F, 3, 89 },{ NOTE_A, 3, 90 },{ NOTE_C, 4, 89 },
{ NOTE_Eb, 4, 269 },{ NOTE_F, 3, 90 },{ NOTE_A, 3, 179 },{ NOTE_A, 3, 90 },{ NOTE_C, 4, 89 },
{ NOTE_Eb, 4, 269 },{ NOTE_F, 3, 90 },{ NOTE_Bb, 3, 89 },{ NOTE_F, 3, 90 },{ NOTE_Bb, 3, 89 },
{ NOTE_Cs, 4, 90 },{ NOTE_F, 4, 269 },{ NOTE_F, 3, 89 },{ NOTE_Bb, 3, 180 },{ NOTE_Bb, 3, 89 },
{ NOTE_Cs, 4, 90 },{ NOTE_F, 4, 269 },{ NOTE_F, 3, 89 },{ NOTE_A, 3, 90 },{ NOTE_F, 3, 89 },
{ NOTE_A, 3, 90 },{ NOTE_C, 4, 90 },{ NOTE_Eb, 4, 268 },{ NOTE_Eb, 4, 90 },{ NOTE_Eb, 4, 90 },
{ NOTE_Eb, 4, 89 },{ NOTE_F, 4, 90 },{ NOTE_Eb, 4, 89 },{ NOTE_Cs, 4, 90 },{ NOTE_Cs, 4, 90 },
{ NOTE_Eb, 4, 89 },{ NOTE_Cs, 4, 90 },{ NOTE_C, 4, 89 },{ NOTE_C, 4, 90 },{ NOTE_Cs, 4, 90 },
{ NOTE_Eb, 4, 89 },{ NOTE_F, 4, 359 },{ NOTE_Eb, 4, 89 },{ NOTE_Cs, 4, 90 },{ NOTE_C, 4, 89 },
{ NOTE_F, 3, 180 },{ NOTE_A, 3, 89 },{ NOTE_Bb, 3, 627 },{ NOTE_C, 4, 180 },{ NOTE_D, 4, 89 },
{ NOTE_E, 4, 90 },{ NOTE_F, 4, 179 },{ NOTE_A, 4, 90 },{ NOTE_G, 4, 89 },{ NOTE_F, 4, 179 },
{ NOTE_C, 4, 90 },{ NOTE_F, 4, 90 },{ NOTE_E, 4, 89 },{ NOTE_C, 4, 269 },{ NOTE_F, 3, 90 },
{ NOTE_G, 3, 89 },{ NOTE_A, 3, 90 },{ NOTE_G, 3, 89 },{ NOTE_Bb, 3, 90 },{ NOTE_A, 3, 90 },
{ NOTE_G, 3, 89 },{ NOTE_F, 3, 90 },{ NOTE_Bb, 3, 89 },{ NOTE_C, 4, 90 },{ NOTE_D, 4, 90 },
{ NOTE_C, 4, 89 },{ NOTE_Eb, 4, 90 },{ NOTE_D, 4, 89 },{ NOTE_C, 4, 90 },{ NOTE_Bb, 3, 90 },
{ NOTE_A, 3, 89 },{ NOTE_C, 4, 90 },{ NOTE_F, 3, 89 },{ NOTE_A, 3, 90 },{ NOTE_C, 3, 90 },
{ NOTE_F, 3, 89 },{ NOTE_A, 2, 90 },{ NOTE_C, 3, 89 },{ NOTE_E, 3, 90 },{ NOTE_C, 3, 90 },
{ NOTE_G, 3, 89 },{ NOTE_E, 3, 90 },{ NOTE_C, 4, 89 },{ NOTE_G, 3, 90 },{ NOTE_E, 4, 90 },
{ NOTE_C, 4, 89 },{ NOTE_F, 4, 90 },{ NOTE_C, 4, 89 },{ NOTE_F, 3, 90 },{ NOTE_C, 3, 90 },
{ NOTE_F, 2, 89 },{ NOTE_C, 2, 90 },{ NOTE_F, 1, 89 },{ NOTE_C, 1, 90 },{ NOTE_Bb, 0, 90 },
{ NOTE_F, 1, 89 },{ NOTE_Bb, 1, 90 },{ NOTE_F, 2, 89 },{ NOTE_Bb, 2, 90 },{ NOTE_F, 3, 90 },
{ NOTE_Bb, 3, 89 },{ NOTE_F, 4, 90 },{ NOTE_Bb, 4, 89 },{ NOTE_D, 5, 90 },{ NOTE_F, 5, 90 },
{ NOTE_Bb, 5, 89 },{ NOTE_F, 5, 90 },{ NOTE_D, 5, 89 },{ NOTE_Bb, 4, 90 },{ NOTE_F, 4, 90 },
{ NOTE_E, 4, 89 },{ NOTE_D, 4, 90 },{ NOTE_C, 4, 89 },{ NOTE_D, 4, 90 },{ NOTE_E, 4, 90 },
{ NOTE_F, 4, 89 },{ NOTE_G, 4, 90 },{ NOTE_Bb, 4, 89 },{ NOTE_A, 4, 90 },{ NOTE_G, 4, 90 },
{ NOTE_F, 4, 89 },{ NOTE_D, 4, 90 },{ NOTE_C, 4, 89 },{ NOTE_A, 3, 90 },{ NOTE_G, 3, 90 },
{ NOTE_F, 3, 89 },{ NOTE_Bb, 3, 90 },{ NOTE_C, 4, 89 },{ NOTE_D, 4, 90 },{ NOTE_E, 4, 90 },
{ NOTE_F, 4, 89 },{ NOTE_G, 4, 90 },{ NOTE_F, 4, 89 },{ NOTE_D, 4, 90 },{ NOTE_E, 4, 90 },
{ NOTE_D, 4, 89 },{ NOTE_C, 4, 90 },{ NOTE_Bb, 3, 89 },{ NOTE_A, 3, 90 },{ NOTE_G, 3, 90 },
{ NOTE_D, 3, 89 },{ NOTE_E, 3, 90 },{ NOTE_F, 3, 358 },{ NOTE_Cs, 4, 179 },{ NOTE_Eb, 4, 90 },
{ NOTE_F, 4, 90 },{ NOTE_Fs, 4, 179 },{ NOTE_Bb, 4, 89 },{ NOTE_Gs, 4, 90 },{ NOTE_Fs, 4, 179 },
{ NOTE_Cs, 4, 90 },{ NOTE_Fs, 4, 89 },{ NOTE_F, 4, 90 },{ NOTE_Cs, 4, 269 },{ NOTE_Fs, 3, 89 },
{ NOTE_Gs, 3, 90 },{ NOTE_Bb, 3, 90 },{ NOTE_Gs, 3, 89 },{ NOTE_B, 3, 90 },{ NOTE_Bb, 3, 89 },
{ NOTE_Gs, 3, 90 },{ NOTE_Fs, 3, 90 },{ NOTE_B, 3, 89 },{ NOTE_Cs, 4, 90 },{ NOTE_Eb, 4, 89 },
{ NOTE_Cs, 4, 90 },{ NOTE_E, 4, 90 },{ NOTE_Eb, 4, 89 },{ NOTE_Cs, 4, 90 },{ NOTE_B, 3, 89 },
{ NOTE_Bb, 3, 90 },{ NOTE_Cs, 4, 90 },{ NOTE_Fs, 3, 89 },{ NOTE_Bb, 3, 90 },{ NOTE_Cs, 3, 89 },
{ NOTE_Fs, 3, 90 },{ NOTE_Bb, 2, 90 },{ NOTE_Cs, 3, 89 },{ NOTE_F, 3, 90 },{ NOTE_Cs, 3, 89 },
{ NOTE_Gs, 3, 90 },{ NOTE_F, 3, 90 },{ NOTE_Cs, 4, 89 },{ NOTE_Gs, 3, 90 },{ NOTE_F, 4, 89 },
{ NOTE_Cs, 4, 90 },{ NOTE_Fs, 4, 90 },{ NOTE_Cs, 4, 89 },{ NOTE_Fs, 3, 90 },{ NOTE_Cs, 3, 89 },
{ NOTE_Fs, 2, 90 },{ NOTE_Cs, 2, 90 },{ NOTE_Fs, 1, 89 },{ NOTE_Cs, 1, 90 },{ NOTE_B, 0, 89 },
{ NOTE_Fs, 1, 90 },{ NOTE_B, 1, 90 },{ NOTE_Fs, 2, 89 },{ NOTE_B, 2, 90 },{ NOTE_Fs, 3, 89 },
{ NOTE_B, 3, 90 },{ NOTE_Fs, 4, 90 },{ NOTE_B, 4, 89 },{ NOTE_Eb, 5, 90 },{ NOTE_Fs, 5, 89 },
{ NOTE_C, -1, 90 },{ NOTE_Fs, 5, 90 },{ NOTE_Eb, 5, 89 },{ NOTE_B, 4, 90 },{ NOTE_Fs, 4, 89 },
{ NOTE_F, 4, 90 },{ NOTE_Eb, 4, 90 },{ NOTE_Cs, 4, 89 },{ NOTE_Eb, 4, 90 },{ NOTE_F, 4, 89 },
{ NOTE_Fs, 4, 90 },{ NOTE_Gs, 4, 90 },{ NOTE_B, 4, 89 },{ NOTE_Bb, 4, 90 },{ NOTE_Gs, 4, 89 },
{ NOTE_Fs, 4, 90 },{ NOTE_Eb, 4, 90 },{ NOTE_Cs, 4, 89 },{ NOTE_Bb, 3, 90 },{ NOTE_Gs, 3, 89 },
{ NOTE_Fs, 3, 90 },{ NOTE_B, 3, 90 },{ NOTE_Cs, 4, 89 },{ NOTE_Eb, 4, 90 },{ NOTE_F, 4, 89 },
{ NOTE_Fs, 4, 90 },{ NOTE_Gs, 4, 90 },{ NOTE_Fs, 4, 89 },{ NOTE_Eb, 4, 90 },{ NOTE_F, 4, 89 },
{ NOTE_Eb, 4, 90 },{ NOTE_Cs, 4, 90 },{ NOTE_B, 3, 89 },{ NOTE_Bb, 3, 90 },{ NOTE_Gs, 3, 89 },
{ NOTE_Eb, 3, 90 },{ NOTE_F, 3, 90 },{ NOTE_Fs, 3, 358 } };

		Note ch_2[396] PROGMEM = {
{ NOTE_Fs, 2, 358 },{ NOTE_Eb, 2, 359 },{ NOTE_Cs, 2, 358 },{ NOTE_F, 2, 179 },{ NOTE_Eb, 2, 90 },
{ NOTE_F, 2, 89 },{ NOTE_Fs, 2, 90 },{ NOTE_Bb, 2, 90 },{ NOTE_Cs, 2, 89 },{ NOTE_Bb, 2, 90 },
{ NOTE_Fs, 2, 89 },{ NOTE_Bb, 2, 90 },{ NOTE_Cs, 2, 90 },{ NOTE_Bb, 2, 89 },{ NOTE_Fs, 2, 90 },
{ NOTE_B, 2, 89 },{ NOTE_Eb, 2, 90 },{ NOTE_B, 2, 90 },{ NOTE_Fs, 2, 89 },{ NOTE_B, 2, 90 },
{ NOTE_Eb, 2, 89 },{ NOTE_B, 2, 90 },{ NOTE_Fs, 2, 90 },{ NOTE_Bb, 2, 89 },{ NOTE_Cs, 2, 90 },
{ NOTE_Bb, 2, 89 },{ NOTE_Fs, 2, 90 },{ NOTE_Bb, 2, 90 },{ NOTE_Cs, 2, 89 },{ NOTE_Bb, 2, 90 },
{ NOTE_F, 2, 89 },{ NOTE_Gs, 2, 90 },{ NOTE_Cs, 2, 90 },{ NOTE_Gs, 2, 89 },{ NOTE_Eb, 2, 90 },
{ NOTE_Gs, 2, 89 },{ NOTE_F, 2, 90 },{ NOTE_Gs, 2, 90 },{ NOTE_Fs, 2, 89 },{ NOTE_Bb, 2, 90 },
{ NOTE_Cs, 2, 89 },{ NOTE_Bb, 2, 90 },{ NOTE_Fs, 2, 90 },{ NOTE_Bb, 2, 89 },{ NOTE_Cs, 2, 90 },
{ NOTE_Bb, 2, 89 },{ NOTE_Fs, 2, 90 },{ NOTE_B, 2, 90 },{ NOTE_Eb, 2, 89 },{ NOTE_B, 2, 90 },
{ NOTE_Fs, 2, 89 },{ NOTE_B, 2, 90 },{ NOTE_Eb, 2, 90 },{ NOTE_B, 2, 89 },{ NOTE_Fs, 2, 90 },
{ NOTE_B, 2, 89 },{ NOTE_Eb, 2, 90 },{ NOTE_B, 2, 90 },{ NOTE_Fs, 2, 89 },{ NOTE_B, 2, 90 },
{ NOTE_Eb, 2, 89 },{ NOTE_B, 2, 90 },{ NOTE_Gs, 2, 90 },{ NOTE_Cs, 3, 89 },{ NOTE_Cs, 2, 90 },
{ NOTE_Cs, 3, 89 },{ NOTE_Gs, 2, 90 },{ NOTE_Cs, 3, 90 },{ NOTE_Cs, 2, 89 },{ NOTE_Cs, 3, 90 },
{ NOTE_Fs, 2, 89 },{ NOTE_Bb, 2, 90 },{ NOTE_Cs, 2, 90 },{ NOTE_Bb, 2, 89 },{ NOTE_Fs, 2, 90 },
{ NOTE_Bb, 2, 89 },{ NOTE_Cs, 2, 90 },{ NOTE_Bb, 2, 90 },{ NOTE_Fs, 2, 89 },{ NOTE_B, 2, 90 },
{ NOTE_Eb, 2, 89 },{ NOTE_B, 2, 90 },{ NOTE_Fs, 2, 90 },{ NOTE_B, 2, 89 },{ NOTE_Eb, 2, 90 },
{ NOTE_B, 2, 89 },{ NOTE_F, 2, 90 },{ NOTE_B, 2, 90 },{ NOTE_Cs, 2, 89 },{ NOTE_B, 2, 90 },
{ NOTE_F, 2, 89 },{ NOTE_B, 2, 90 },{ NOTE_Cs, 2, 90 },{ NOTE_B, 2, 89 },{ NOTE_Fs, 2, 90 },
{ NOTE_Bb, 2, 89 },{ NOTE_Cs, 2, 90 },{ NOTE_Bb, 2, 90 },{ NOTE_Fs, 2, 89 },{ NOTE_Bb, 2, 90 },
{ NOTE_Cs, 2, 89 },{ NOTE_Bb, 2, 90 },{ NOTE_Fs, 2, 90 },{ NOTE_Bb, 2, 89 },{ NOTE_Cs, 2, 90 },
{ NOTE_Bb, 2, 89 },{ NOTE_Fs, 2, 90 },{ NOTE_Bb, 2, 90 },{ NOTE_Cs, 2, 89 },{ NOTE_Bb, 2, 90 },
{ NOTE_Fs, 2, 89 },{ NOTE_Bb, 2, 90 },{ NOTE_Cs, 2, 90 },{ NOTE_Bb, 2, 89 },{ NOTE_Fs, 2, 90 },
{ NOTE_Bb, 2, 89 },{ NOTE_Gs, 2, 90 },{ NOTE_Cs, 2, 90 },{ NOTE_Fs, 2, 89 },{ NOTE_Bb, 2, 90 },
{ NOTE_Cs, 2, 89 },{ NOTE_Bb, 2, 90 },{ NOTE_Fs, 2, 90 },{ NOTE_B, 2, 89 },{ NOTE_Eb, 2, 90 },
{ NOTE_B, 2, 89 },{ NOTE_F, 2, 90 },{ NOTE_Cs, 3, 90 },{ NOTE_Cs, 2, 89 },{ NOTE_Cs, 3, 90 },
{ NOTE_Fs, 2, 89 },{ NOTE_Bb, 2, 90 },{ NOTE_Cs, 2, 90 },{ NOTE_Bb, 2, 89 },{ NOTE_Fs, 2, 90 },
{ NOTE_B, 2, 89 },{ NOTE_Eb, 2, 90 },{ NOTE_B, 2, 90 },{ NOTE_Fs, 2, 89 },{ NOTE_B, 2, 90 },
{ NOTE_Eb, 2, 89 },{ NOTE_B, 2, 90 },{ NOTE_Fs, 2, 90 },{ NOTE_Bb, 2, 89 },{ NOTE_Cs, 2, 90 },
{ NOTE_Bb, 2, 89 },{ NOTE_Fs, 2, 90 },{ NOTE_Bb, 2, 90 },{ NOTE_Cs, 2, 89 },{ NOTE_Bb, 2, 90 },
{ NOTE_Fs, 2, 89 },{ NOTE_B, 2, 90 },{ NOTE_Eb, 2, 90 },{ NOTE_B, 2, 89 },{ NOTE_Fs, 2, 90 },
{ NOTE_B, 2, 89 },{ NOTE_Eb, 2, 90 },{ NOTE_B, 2, 90 },{ NOTE_F, 2, 89 },{ NOTE_B, 2, 90 },
{ NOTE_Cs, 2, 89 },{ NOTE_B, 2, 90 },{ NOTE_Fs, 2, 90 },{ NOTE_Bb, 2, 89 },{ NOTE_Cs, 2, 90 },
{ NOTE_Bb, 2, 89 },{ NOTE_Bb, 2, 180 },{ NOTE_Bb, 2, 179 },{ NOTE_Bb, 2, 179 },{ NOTE_Bb, 2, 179 },
{ NOTE_Bb, 2, 179 },{ NOTE_Bb, 2, 180 },{ NOTE_Bb, 2, 179 },{ NOTE_Bb, 2, 179 },{ NOTE_F, 2, 179 },
{ NOTE_F, 2, 179 },{ NOTE_F, 2, 180 },{ NOTE_F, 2, 179 },{ NOTE_F, 2, 179 },{ NOTE_F, 2, 179 },
{ NOTE_F, 2, 179 },{ NOTE_F, 2, 180 },{ NOTE_Bb, 2, 179 },{ NOTE_Bb, 2, 179 },{ NOTE_Bb, 2, 179 },
{ NOTE_Bb, 2, 179 },{ NOTE_Bb, 2, 180 },{ NOTE_Bb, 2, 179 },{ NOTE_Bb, 2, 179 },{ NOTE_Bb, 2, 179 },
{ NOTE_F, 2, 179 },{ NOTE_F, 2, 180 },{ NOTE_F, 2, 179 },{ NOTE_F, 2, 179 },{ NOTE_Eb, 2, 358 },
{ NOTE_Eb, 2, 359 },{ NOTE_F, 2, 358 },{ NOTE_F, 2, 359 },{ NOTE_Eb, 2, 358 },{ NOTE_F, 2, 358 },
{ NOTE_Bb, 2, 807 },{ NOTE_D, 2, 358 },{ NOTE_C, 2, 359 },{ NOTE_E, 2, 179 },{ NOTE_D, 2, 89 },
{ NOTE_E, 2, 90 },{ NOTE_F, 2, 90 },{ NOTE_A, 2, 89 },{ NOTE_C, 2, 90 },{ NOTE_A, 2, 89 },
{ NOTE_F, 2, 90 },{ NOTE_A, 2, 90 },{ NOTE_C, 2, 89 },{ NOTE_A, 2, 90 },{ NOTE_F, 2, 89 },
{ NOTE_Bb, 2, 90 },{ NOTE_D, 2, 90 },{ NOTE_Bb, 2, 89 },{ NOTE_F, 2, 90 },{ NOTE_Bb, 2, 89 },
{ NOTE_D, 2, 90 },{ NOTE_Bb, 2, 90 },{ NOTE_F, 2, 89 },{ NOTE_A, 2, 90 },{ NOTE_C, 2, 89 },
{ NOTE_A, 2, 90 },{ NOTE_F, 2, 90 },{ NOTE_A, 2, 89 },{ NOTE_C, 2, 90 },{ NOTE_A, 2, 89 },
{ NOTE_E, 2, 90 },{ NOTE_G, 2, 90 },{ NOTE_C, 2, 89 },{ NOTE_G, 2, 90 },{ NOTE_D, 2, 89 },
{ NOTE_G, 2, 90 },{ NOTE_E, 2, 90 },{ NOTE_G, 2, 89 },{ NOTE_F, 2, 90 },{ NOTE_A, 2, 89 },
{ NOTE_C, 2, 90 },{ NOTE_A, 2, 90 },{ NOTE_F, 2, 89 },{ NOTE_A, 2, 90 },{ NOTE_C, 2, 89 },
{ NOTE_A, 2, 90 },{ NOTE_F, 2, 90 },{ NOTE_Bb, 2, 89 },{ NOTE_D, 2, 90 },{ NOTE_Bb, 2, 89 },
{ NOTE_F, 2, 90 },{ NOTE_Bb, 2, 90 },{ NOTE_D, 2, 89 },{ NOTE_Bb, 2, 90 },{ NOTE_F, 2, 89 },
{ NOTE_Bb, 2, 90 },{ NOTE_D, 2, 90 },{ NOTE_Bb, 2, 89 },{ NOTE_F, 2, 90 },{ NOTE_Bb, 2, 89 },
{ NOTE_D, 2, 90 },{ NOTE_Bb, 2, 90 },{ NOTE_G, 2, 89 },{ NOTE_C, 3, 90 },{ NOTE_C, 2, 89 },
{ NOTE_C, 3, 90 },{ NOTE_G, 2, 90 },{ NOTE_C, 3, 89 },{ NOTE_C, 2, 90 },{ NOTE_C, 3, 89 },
{ NOTE_F, 2, 90 },{ NOTE_A, 2, 90 },{ NOTE_C, 2, 89 },{ NOTE_A, 2, 90 },{ NOTE_F, 2, 89 },
{ NOTE_A, 2, 90 },{ NOTE_C, 2, 90 },{ NOTE_A, 2, 89 },{ NOTE_F, 2, 90 },{ NOTE_Bb, 2, 89 },
{ NOTE_D, 2, 90 },{ NOTE_Bb, 2, 90 },{ NOTE_F, 2, 89 },{ NOTE_Bb, 2, 90 },{ NOTE_D, 2, 89 },
{ NOTE_Bb, 2, 90 },{ NOTE_E, 2, 90 },{ NOTE_Bb, 2, 89 },{ NOTE_C, 2, 90 },{ NOTE_Bb, 2, 89 },
{ NOTE_E, 2, 90 },{ NOTE_Bb, 2, 90 },{ NOTE_C, 2, 89 },{ NOTE_Bb, 2, 90 },{ NOTE_F, 2, 89 },
{ NOTE_A, 2, 90 },{ NOTE_C, 2, 90 },{ NOTE_A, 2, 89 },{ NOTE_Fs, 2, 359 },{ NOTE_Eb, 2, 358 },
{ NOTE_Cs, 2, 358 },{ NOTE_F, 2, 180 },{ NOTE_Eb, 2, 89 },{ NOTE_F, 2, 90 },{ NOTE_Fs, 2, 89 },
{ NOTE_Bb, 2, 90 },{ NOTE_Cs, 2, 90 },{ NOTE_Bb, 2, 89 },{ NOTE_Fs, 2, 90 },{ NOTE_Bb, 2, 89 },
{ NOTE_Cs, 2, 90 },{ NOTE_Bb, 2, 90 },{ NOTE_Fs, 2, 89 },{ NOTE_B, 2, 90 },{ NOTE_Eb, 2, 89 },
{ NOTE_B, 2, 90 },{ NOTE_Fs, 2, 90 },{ NOTE_B, 2, 89 },{ NOTE_Eb, 2, 90 },{ NOTE_B, 2, 89 },
{ NOTE_Fs, 2, 90 },{ NOTE_Bb, 2, 90 },{ NOTE_Cs, 2, 89 },{ NOTE_Bb, 2, 90 },{ NOTE_Fs, 2, 89 },
{ NOTE_Bb, 2, 90 },{ NOTE_Cs, 2, 90 },{ NOTE_Bb, 2, 89 },{ NOTE_F, 2, 90 },{ NOTE_Gs, 2, 89 },
{ NOTE_Cs, 2, 90 },{ NOTE_Gs, 2, 90 },{ NOTE_Eb, 2, 89 },{ NOTE_Gs, 2, 90 },{ NOTE_F, 2, 89 },
{ NOTE_Gs, 2, 90 },{ NOTE_Fs, 2, 90 },{ NOTE_Bb, 2, 89 },{ NOTE_Cs, 2, 90 },{ NOTE_Bb, 2, 89 },
{ NOTE_Fs, 2, 90 },{ NOTE_Bb, 2, 90 },{ NOTE_Cs, 2, 89 },{ NOTE_Bb, 2, 90 },{ NOTE_Fs, 2, 89 },
{ NOTE_B, 2, 90 },{ NOTE_Eb, 2, 90 },{ NOTE_B, 2, 89 },{ NOTE_Fs, 2, 90 },{ NOTE_B, 2, 89 },
{ NOTE_Eb, 2, 90 },{ NOTE_B, 2, 90 },{ NOTE_Fs, 2, 89 },{ NOTE_B, 2, 90 },{ NOTE_Eb, 2, 89 },
{ NOTE_B, 2, 90 },{ NOTE_Fs, 2, 90 },{ NOTE_B, 2, 89 },{ NOTE_Eb, 2, 90 },{ NOTE_B, 2, 89 },
{ NOTE_Gs, 2, 90 },{ NOTE_Cs, 3, 90 },{ NOTE_Cs, 2, 89 },{ NOTE_Cs, 3, 90 },{ NOTE_Gs, 2, 89 },
{ NOTE_Cs, 3, 90 },{ NOTE_Cs, 2, 90 },{ NOTE_Cs, 3, 89 },{ NOTE_Fs, 2, 90 },{ NOTE_Bb, 2, 89 },
{ NOTE_Cs, 2, 90 },{ NOTE_Bb, 2, 90 },{ NOTE_Fs, 2, 89 },{ NOTE_Bb, 2, 90 },{ NOTE_Cs, 2, 89 },
{ NOTE_Bb, 2, 90 },{ NOTE_Fs, 2, 90 },{ NOTE_B, 2, 89 },{ NOTE_Eb, 2, 90 },{ NOTE_B, 2, 89 },
{ NOTE_Fs, 2, 90 },{ NOTE_B, 2, 90 },{ NOTE_Eb, 2, 89 },{ NOTE_B, 2, 90 },{ NOTE_F, 2, 89 },
{ NOTE_B, 2, 90 },{ NOTE_Cs, 2, 90 },{ NOTE_B, 2, 89 },{ NOTE_F, 2, 90 },{ NOTE_B, 2, 89 },
{ NOTE_Cs, 2, 90 },{ NOTE_B, 2, 90 },{ NOTE_Fs, 2, 89 },{ NOTE_Bb, 2, 90 },{ NOTE_Cs, 2, 89 },
{ NOTE_Bb, 2, 90 } };

};

