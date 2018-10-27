#include <stdio.h>
#include <string.h>
#include <switch.h>
#include <dirent.h>
#include <sys/stat.h> 
#include "simon_savegame.h"


void generaSaveGame(){
	FILE* save = fopen(filename, "wb");
	
	if (save)
	{ 

		highscore[0]=5;
		highscore[1]=4;
		highscore[2]=3;
		strcpy(namePlayer[0],"Pauline");
		strcpy(namePlayer[1],"Bowser");
		strcpy(namePlayer[2],"Tatanga");
		
		fwrite(highscore, sizeof(u16), 3, save);
		fwrite(namePlayer, sizeof(u64),4, save);
		fclose(save);
	}
}
int leeSaveGame(){

	savepath = SAVEPATH;
	int t;
	int err = stat(SAVEPATH, &s);
	if(err == -1)
	{
		savepath = "./";
	}
	else if(!S_ISDIR(s.st_mode))
	{
		savepath = "./";
	}
	sprintf(filename, "%s%s", savepath, SAVEFILE);
	FILE* save = fopen(filename, "rb");

	if (save)
	{
		fread(highscore, sizeof(u16), 3, save);
		fread(namePlayer, sizeof(u64), 4, save);
		fclose(save);
	}
	else
	{
	t=1;
	}

	return t;
}
void saveNewHighscore(){
		
		FILE* save = fopen(filename, "wb");
		if (save)
		{ 
			fwrite(highscore, sizeof(u16), 3, save);
			fwrite(namePlayer, sizeof(u64), 4, save);
		}
}
