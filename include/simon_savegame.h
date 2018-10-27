#ifndef simon_savegame_H
#define simon_savegame_H

#define SAVEPATH "sdmc:/switch/Simon-NX/"
#define SAVEFILE "simon_save.dat"
struct stat s;
int err;
const char* savepath;
char filename[37]; // strlen(SAVEPATH) + strlen(SAVEFILE) + 1
char linea[100];// 
char namePlayer[3][12];
u16 highscore[3];
void generaSaveGame();
int leeSaveGame();
void saveNewHighscore();
#endif
