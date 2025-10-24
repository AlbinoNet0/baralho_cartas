#ifndef MAO_H
#define MAO_H

typedef struct CARTA CARTA;
typedef struct MAO MAO;

MAO* criarMao();
void adicionaCartaMao(MAO* mao, CARTA* nova, int i);
void exibirMao(MAO* maoExibida);
char* naipeCarta(MAO* mao, int posicao);
char* valorCarta(MAO* mao, int posicao);
int getQuantidadeJogos(MAO * player);
CARTA* getCarta(MAO* player, int posicao);
void setCarta(MAO* player, int posicao, CARTA* carta);
void liberarMao(MAO* mao);
void quaseNaipeIgual(MAO* mao);
void jogoNaipeIgual(MAO* mao);
void quaseNaipeDiferente(MAO* mao);
void jogoNaipeDiferente(MAO* mao);
void resetarStatusMao(MAO* mao);

#endif