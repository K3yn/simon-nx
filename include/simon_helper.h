#ifndef simon_helper_H
#define simon_helper_H

u8 contMenuMain;// 
u8 contMenuModos;// 
u8 contColorM8;

int modoAudio;
int t;//
int bucleSecuencia;
int contSecuencia;
int contGameOver;//
int numAleatorio;//
int semaforoAleatorio;//
int contSemaforoSecColores; //
int contSemaforoColorOnOff;//
int vecesAleatorio;//
int contadorPlayer;//
int puntos;
int aumentaPuntos;
int incRand;
int vecesSecuencia;//

char arrayColores[99];
char color;
char chHighscore0[3];char chHighscore1[3];char chHighscore2[3];

bool semaforo;
bool modo_menuMain;
bool modo_juego;
bool selectorModo;
bool game;
bool game40;
bool game50;
bool game80;
bool modo_color_random;
bool modo_secuencia_colores;
bool modo_game_over;
bool modo_input_player;
bool game_over;
bool modo_touch;
bool modo_highScores;
bool modo_blue;
bool generaSaveGameFlag;
bool button_back;
bool activarBoton;
bool custom_wait_touch;
bool firstTime;
bool firstTimeMSC;
bool salir;

void loadIniVars();
void playSound(char color);
void turnONcolor(char color);
bool comparaStr (char entrada[],char modelo[]);
void secuenciaColores();
void fcGameOver();
void marcador();
void limpiaArrayColores();
#endif
