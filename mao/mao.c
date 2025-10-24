#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mao.h"
#include "../carta/carta.h"

typedef struct MAO {
    CARTA* mao_player[9];
    int numero_de_jogos;
} MAO;

MAO* criarMao() {
    MAO* mao = (MAO*)malloc(sizeof(MAO));
    if (mao == NULL) {
        printf("ERRO DE ALOCACAO DE MAO\n");
        exit(1);
    }

    for (int i = 0; i < 9; i++)
        mao->mao_player[i] = NULL;

    mao->numero_de_jogos = 0;
    return mao;
}

void adicionaCartaMao(MAO* mao, CARTA* nova, int i) {
    mao->mao_player[i] = nova;
}

void exibirMao(MAO* maoExibida) {
    for (int i = 0; i < 9; i++) {
        if (maoExibida->mao_player[i] != NULL) {
            printf("NAIPE: %s\n", getNaipe(maoExibida->mao_player[i]));
            printf("VALOR: %s\n", getValor(maoExibida->mao_player[i]));
        }
    }
    printf("\n");
}

char* naipeCarta(MAO* mao, int posicao) {
    return getNaipe(mao->mao_player[posicao]);
}
char* valorCarta(MAO* mao, int posicao) {
    return getValor(mao->mao_player[posicao]);
}

int getQuantidadeJogos(MAO * player){
    return player->numero_de_jogos;
}

CARTA * getCarta(MAO* player, int posicao) {
    return player->mao_player[posicao];
}

void setCarta(MAO* player, int posicao, CARTA* carta) {
    player->mao_player[posicao] = carta;
}

void quaseNaipeIgual(MAO* mao) {
    CARTA *c1;
    CARTA *c2;

    int v1, v2;
    for(int i = 0; i < 9; i++) {
        for(int j = i + 1; j < 9; j++) {
            c1 = mao->mao_player[i];
            c2 = mao->mao_player[j];

            if(strcmp(getNaipe(c1), getNaipe(c2)) == 0) {
                v1 = converteEmNumero(getValor(c1));
                v2 = converteEmNumero(getValor(c2));
                if(v1 + 1 == v2 || v2 + 1 == v1) {
                    if(getUsada(c1) == 0) setUsada(c1, 2);
                    if(getUsada(c2) == 0) setUsada(c2, 2);
                }
            }
        }
    }
}

void jogoNaipeIgual(MAO* mao) {
    CARTA *c1;
    CARTA *c2;
    CARTA *c3;

    int v1, v2, v3, temp;

    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            for(int k = 0; k < 9; k++) {
                c1 = mao->mao_player[i];
                c2 = mao->mao_player[j];
                c3 = mao->mao_player[k];

                if(strcmp(getNaipe(c1), getNaipe(c2)) == 0 && strcmp(getNaipe(c2), getNaipe(c3)) == 0) {
                    v1 = converteEmNumero(getValor(c1));
                    v2 = converteEmNumero(getValor(c2));
                    v3 = converteEmNumero(getValor(c3));

                    if (v1 > v2) { temp = v1; v1 = v2; v2 = temp; }
                    if (v1 > v3) { temp = v1; v1 = v3; v3 = temp; }
                    if (v2 > v3) { temp = v2; v2 = v3; v3 = temp; }

                     if (v2 == v1 + 1 && v3 == v2 + 1) {
                         if ( ((getUsada(c1) == 0) || (getUsada(c1) == 2)) &&
                              ((getUsada(c2) == 0) || (getUsada(c2) == 2)) &&
                              ((getUsada(c3) == 0) || (getUsada(c3) == 2)) ) {
                                mao->numero_de_jogos++;
                                setUsada(c1, 1);
                                setUsada(c2, 1);
                                setUsada(c3, 1);
                            }
                    }
                }
            }
        }
    }
}

void quaseNaipeDiferente(MAO* mao) {
    CARTA *c1;
    CARTA *c2;

    for(int i = 0; i < 9; i++) {
        for(int j = i + 1; j < 9; j++) {
            c1 = mao->mao_player[i];
            c2 = mao->mao_player[j];

            if(strcmp(getNaipe(c1), getNaipe(c2)) != 0) {
                if(strcmp(getValor(c1), getValor(c2)) == 0) {
                    if(getUsada(c1) == 0) setUsada(c1, 2);
                    if(getUsada(c2) == 0) setUsada(c2, 2);
                }
            }
        }
    }
}


void jogoNaipeDiferente(MAO* mao) {
    CARTA *c1;
    CARTA *c2;
    CARTA *c3;

    int v1, v2, v3, temp;

    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            for(int k = 0; k < 9; k++) {
                c1 = mao->mao_player[i];
                c2 = mao->mao_player[j];
                c3 = mao->mao_player[k];

                if(strcmp(getNaipe(c1), getNaipe(c2)) != 0 && 
                   strcmp(getNaipe(c1), getNaipe(c3)) != 0 &&
                   strcmp(getNaipe(c2), getNaipe(c3)) != 0) {
                    v1 = converteEmNumero(getValor(c1));
                    v2 = converteEmNumero(getValor(c2));
                    v3 = converteEmNumero(getValor(c3));

                     if (v1 == v2 && v2 == v3) {
                        if ( ((getUsada(c1) == 0) || (getUsada(c1) == 2)) &&
                             ((getUsada(c2) == 0) || (getUsada(c2) == 2)) &&
                             ((getUsada(c3) == 0) || (getUsada(c3) == 2)) ) {
                                mao->numero_de_jogos++;
                                setUsada(c1, 1);
                                setUsada(c2, 1);
                                setUsada(c3, 1);
                            }
                    }

                }
            }
        }
    }
}

void liberarMao(MAO* mao) {
    if (mao == NULL)
        return;

    for (int i = 0; i < 9; i++) {
        if (mao->mao_player[i] != NULL) {
            free(mao->mao_player[i]);
            mao->mao_player[i] = NULL;
        }
    }

    free(mao);
}

void resetarStatusMao(MAO* mao) {
    if (mao == NULL) return;
    mao->numero_de_jogos = 0;
    for (int i = 0; i < 9; i++) {
        CARTA* c = getCarta(mao, i);
        if (c != NULL) {
            setUsada(c, 0);
        }
    }
}