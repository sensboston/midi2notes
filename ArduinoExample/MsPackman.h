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

    class MsPackmanPlayer {
	public:
		void begin(int startPin = 12) {
			for (int i=0; i<2;i++) {
    			ledcSetup(i*2, 2000, 8);
    			ledcAttachPin(startPin+i, i*2);
			}
        }
        void play(int8_t tempo, int8_t octShift) {
            musicTempo = tempo;
            octaveShift = octShift;
            for (int i=0; i<2; i++) { idx[i] = ms[i] = 0; doPlay[i] = true; }
        }
		void update() {
			for (int i=0; i<2; i++) {
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
        void pause() { for (int i=0; i<2; i++) { doPlay[i]=false; ledcWrite(i*2, 0); } }
        void resume() { for (int i=0; i<2; i++) doPlay[i]=true; }
        bool isPlaying() { 
            for (int i=0; i<2; i++) if (doPlay[i]) return true; 
            return false;
        }
        void setOnEndMusic(PLAYER_CALLBACK *callback) { pEndMusic = callback; }
	private:
        int idx[2];
        unsigned long ms[2];
        bool doPlay[2];
        int8_t musicTempo = 2;
        int8_t octaveShift = 0;
        PLAYER_CALLBACK *pEndMusic = NULL;
		Note ch_1[105] PROGMEM = {
{ NOTE_G, 3, 188 },{ NOTE_B, 3, 92 },{ NOTE_C, 4, 92 },{ NOTE_Cs, 4, 92 },{ NOTE_D, 4, 188 },
{ NOTE_Cs, 4, 92 },{ NOTE_D, 4, 188 },{ NOTE_B, 3, 92 },{ NOTE_D, 4, 92 },{ NOTE_E, 4, 92 },
{ NOTE_F, 4, 188 },{ NOTE_E, 4, 92 },{ NOTE_F, 4, 188 },{ NOTE_B, 4, 92 },{ NOTE_A, 4, 92 },
{ NOTE_G, 4, 92 },{ NOTE_F, 4, 92 },{ NOTE_E, 4, 92 },{ NOTE_F, 4, 188 },{ NOTE_A, 3, 44 },
{ NOTE_B, 3, 44 },{ NOTE_C, 4, 572 },{ NOTE_G, 3, 188 },{ NOTE_E, 4, 92 },{ NOTE_F, 4, 92 },
{ NOTE_Fs, 4, 92 },{ NOTE_G, 4, 92 },{ NOTE_C, 4, 92 },{ NOTE_D, 4, 92 },{ NOTE_Eb, 4, 92 },
{ NOTE_E, 4, 92 },{ NOTE_C, 4, 92 },{ NOTE_E, 4, 92 },{ NOTE_C, 4, 92 },{ NOTE_G, 3, 188 },
{ NOTE_E, 3, 92 },{ NOTE_F, 3, 92 },{ NOTE_Fs, 3, 92 },{ NOTE_G, 3, 380 },{ NOTE_Bb, 3, 380 },
{ NOTE_B, 3, 572 },{ NOTE_F, 3, 188 },{ NOTE_F, 4, 92 },{ NOTE_E, 4, 92 },{ NOTE_B, 3, 92 },
{ NOTE_C, 4, 92 },{ NOTE_E, 4, 92 },{ NOTE_D, 4, 92 },{ NOTE_Bb, 3, 92 },{ NOTE_B, 3, 92 },
{ NOTE_D, 4, 92 },{ NOTE_F, 4, 92 },{ NOTE_A, 4, 92 },{ NOTE_G, 4, 188 },{ NOTE_F, 4, 92 },
{ NOTE_D, 4, 92 },{ NOTE_B, 3, 92 },{ NOTE_A, 3, 380 },{ NOTE_G, 3, 380 },{ NOTE_C, 4, 92 },
{ NOTE_D, 4, 92 },{ NOTE_Eb, 4, 92 },{ NOTE_E, 4, 92 },{ NOTE_A, 3, 92 },{ NOTE_Bb, 3, 92 },
{ NOTE_B, 3, 92 },{ NOTE_D, 4, 92 },{ NOTE_E, 4, 92 },{ NOTE_F, 4, 92 },{ NOTE_Fs, 4, 92 },
{ NOTE_G, 4, 92 },{ NOTE_C, 4, 92 },{ NOTE_D, 4, 92 },{ NOTE_Eb, 4, 92 },{ NOTE_E, 4, 92 },
{ NOTE_C, 4, 92 },{ NOTE_E, 4, 92 },{ NOTE_C, 4, 92 },{ NOTE_G, 3, 284 },{ NOTE_Fs, 3, 92 },
{ NOTE_G, 3, 92 },{ NOTE_A, 3, 380 },{ NOTE_Gs, 3, 380 },{ NOTE_A, 3, 684 },{ NOTE_F, 4, 92 },
{ NOTE_E, 4, 92 },{ NOTE_D, 4, 92 },{ NOTE_C, 4, 188 },{ NOTE_D, 4, 92 },{ NOTE_E, 4, 188 },
{ NOTE_E, 4, 92 },{ NOTE_D, 4, 92 },{ NOTE_C, 4, 92 },{ NOTE_G, 3, 188 },{ NOTE_C, 3, 92 },
{ NOTE_D, 3, 92 },{ NOTE_A, 3, 92 },{ NOTE_G, 3, 380 },{ NOTE_B, 3, 92 },{ NOTE_F, 4, 92 },
{ NOTE_A, 3, 92 },{ NOTE_B, 3, 92 },{ NOTE_C, 4, 188 },{ NOTE_G, 3, 140 },{ NOTE_C, 4, 140 } 
};

		Note ch_2[82] PROGMEM = {
{ NOTE_B, 2, 64 },{ NOTE_Bb, 2, 64 },{ NOTE_Bb, 2, 64 },{ NOTE_A, 2, 64 },{ NOTE_A, 2, 64 },
{ NOTE_Gs, 2, 64 },{ NOTE_G, 2, 64 },{ NOTE_F, 2, 64 },{ NOTE_E, 2, 64 },{ NOTE_Eb, 2, 64 },
{ NOTE_D, 2, 64 },{ NOTE_D, 2, 64 },{ NOTE_Cs, 2, 64 },{ NOTE_C, 2, 64 },{ NOTE_G, 1, 256 },
{ NOTE_G, 1, 128 },{ NOTE_G, 1, 96 },{ NOTE_A, 1, 48 },{ NOTE_B, 1, 48 },{ NOTE_C, 2, 128 },
{ NOTE_E, 2, 128 },{ NOTE_G, 1, 128 },{ NOTE_E, 2, 128 },{ NOTE_C, 2, 128 },{ NOTE_E, 2, 128 },
{ NOTE_G, 1, 128 },{ NOTE_E, 2, 128 },{ NOTE_C, 2, 128 },{ NOTE_E, 2, 128 },{ NOTE_G, 1, 128 },
{ NOTE_E, 2, 128 },{ NOTE_E, 2, 128 },{ NOTE_G, 2, 128 },{ NOTE_Eb, 2, 128 },{ NOTE_Fs, 2, 128 },
{ NOTE_D, 2, 128 },{ NOTE_F, 2, 128 },{ NOTE_G, 1, 128 },{ NOTE_F, 2, 128 },{ NOTE_D, 2, 128 },
{ NOTE_F, 2, 128 },{ NOTE_G, 1, 128 },{ NOTE_F, 2, 128 },{ NOTE_D, 2, 128 },{ NOTE_F, 2, 128 },
{ NOTE_G, 1, 128 },{ NOTE_F, 2, 128 },{ NOTE_F, 2, 128 },{ NOTE_D, 2, 128 },{ NOTE_E, 2, 96 },
{ NOTE_F, 2, 96 },{ NOTE_Fs, 2, 96 },{ NOTE_G, 2, 96 },{ NOTE_G, 2, 96 },{ NOTE_E, 2, 96 },
{ NOTE_D, 2, 96 },{ NOTE_G, 1, 96 },{ NOTE_C, 2, 128 },{ NOTE_E, 2, 128 },{ NOTE_G, 1, 128 },
{ NOTE_E, 2, 128 },{ NOTE_C, 2, 128 },{ NOTE_E, 2, 128 },{ NOTE_G, 1, 128 },{ NOTE_E, 2, 128 },
{ NOTE_A, 1, 128 },{ NOTE_F, 2, 128 },{ NOTE_E, 2, 128 },{ NOTE_Cs, 2, 128 },{ NOTE_D, 2, 128 },
{ NOTE_B, 1, 128 },{ NOTE_A, 1, 128 },{ NOTE_G, 1, 128 },{ NOTE_F, 1, 128 },{ NOTE_F, 2, 128 },
{ NOTE_E, 2, 128 },{ NOTE_F, 1, 128 },{ NOTE_F, 2, 128 },{ NOTE_F, 2, 128 },{ NOTE_C, 2, 128 },
{ NOTE_G, 1, 128 },{ NOTE_C, 2, 128 } };

		Note* music[2] = {ch_1,ch_2};
		int len[2] = {ARRAY_LENGTH(ch_1),ARRAY_LENGTH(ch_2)};
};

