#ifndef simon_helper_H
#define simon_helper_H

u8 contMenuMain;// usada en el menu main para controlar la posicion
u8 contMenuModos;// usada en el menu selector level para controlar la seleccion y posicion del nivel

int modoAudio;
int t;//variable utilizada para debug
int bucleSecuencia;
int contSecuencia;
int contGameOver;// utilizada en game over
int numAleatorio;// numero que se genera para seleccionar el color aleatorio
int semaforoAleatorio;// Utilizado para controlar la puesta y retirada del color_on del color correspondiente
int contSemaforoSecColores; // Se utiliza para entrar o salir de la secuencia de colores
int contSemaforoColorOnOff;// Se utiliza en secuencia de colores para apagar o encender el color
int vecesAleatorio;// Contando las veces aleatorias, podemos utilizarla para que vaya rellenando el array cada vez que genera un aleatorio
int contadorPlayer;// se utilizara para saber las veces que ha pulsado el jugador cuando este en su secuencia de introduccion de colores
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
