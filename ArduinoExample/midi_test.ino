#include "Frogger.h"
#include "MsPackman.h"
#include "Arkanoid.h"

FroggerPlayer player1;
MsPackmanPlayer player2;
ArkanoidThemePlayer player3;

void Player1EndMusic() { delay(2000); player2.play(2, 1); }
void Player2EndMusic() { delay(2000); player3.play(6, 2); }
void Player3EndMusic() { delay(2000); player1.play(2, 1); }

void setup() 
{
    player3.begin();

    player1.setOnEndMusic(Player1EndMusic);
    player2.setOnEndMusic(Player2EndMusic);
    player3.setOnEndMusic(Player3EndMusic);
    
    player1.play(2, 1);
}

void loop() 
{
         if (player1.isPlaying()) player1.update();
    else if (player2.isPlaying()) player2.update();
    else if (player3.isPlaying()) player3.update();
}
