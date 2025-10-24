#ifndef CARTA_H
#define CARTA_H

typedef struct CARTA CARTA;

CARTA* criarCarta(CARTA* proxima, int numero_sorte);
CARTA* proximaCarta(CARTA* atualCarta);
char* getNaipe(CARTA* atualCarta);
char* getValor(CARTA* atualCarta);
int converteEmNumero(char* valor);
int getUsada(CARTA* carta);
void setUsada(CARTA* carta, int usada);
CARTA* duplicarCarta(CARTA* original);

#endif