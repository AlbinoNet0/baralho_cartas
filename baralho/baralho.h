#ifndef BARALHO_H
#define BARALHO_H

#include "../carta/carta.h"
#include "../mao/mao.h"

typedef struct BARALHO BARALHO;

BARALHO* criarBaralho();
void distribuirCartas(BARALHO* baralho, int qtd_players, int qtd_cartas);
void exibirMaoJogador(BARALHO* baralho, int qual_jogador);
void exibirCartaNaMesa(BARALHO * baralho);
CARTA* desempilharCarta(BARALHO * baralho);
int jogos(BARALHO * baralho, int player);
void verCartaTopo(BARALHO * baralho);
void trocarCarta(BARALHO* baralho, int posicao, char* operacao, int jogador);
void liberarMemoriaJogo(BARALHO *baralho);
void verificaJogo(BARALHO* baralho, int j);
void bot(BARALHO* baralho);
int getCartaDoTopo(BARALHO* baralho);
void maisCarta(BARALHO * baralho);
int getCartaDaMesa(BARALHO* baralho);

#endif
