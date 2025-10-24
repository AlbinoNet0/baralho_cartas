#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "baralho.h"
#include "../carta/carta.h"
#include "../mao/mao.h"

typedef struct BARALHO {
    CARTA* topo_baralho;
    CARTA* encima_mesa;
    MAO* players[2];
} BARALHO;

BARALHO* criarBaralho() {
    BARALHO* baralho = (BARALHO*)malloc(sizeof(BARALHO));
    srand(time(NULL));

    if (baralho == NULL) {
        printf("ERRO DE ALOCACAO\n");
        exit(1);
    }

    baralho->topo_baralho = NULL;
    baralho->encima_mesa = NULL;

    for (int i = 0; i < 104; i++) {
        baralho->topo_baralho = criarCarta(baralho->topo_baralho, rand());
    }

    return baralho;
}

void porNaMesa(BARALHO* baralho) {
    baralho->encima_mesa = baralho->topo_baralho;
    baralho->topo_baralho = proximaCarta(baralho->topo_baralho);
}

void distribuirCartas(BARALHO* baralho, int qtd_players, int qtd_cartas) {
    for (int i = 0; i < qtd_players; i++) {
        baralho->players[i] = criarMao();
        for (int j = 0; j < qtd_cartas; j++) {
            CARTA* carta = baralho->topo_baralho;
            baralho->topo_baralho = proximaCarta(baralho->topo_baralho);
            adicionaCartaMao(baralho->players[i], carta, j);
        }
    }
}

void exibirMaoJogador(BARALHO* baralho, int qual_jogador) {
    for(int i = 0; i < 9; i++) {
        printf("%d | ", i + 1);
        printf("%s | ", naipeCarta(baralho->players[qual_jogador], i));
        printf("%s\n", valorCarta(baralho->players[qual_jogador], i));
    }
}

void exibirCartaNaMesa(BARALHO * baralho){
    if(baralho->encima_mesa == NULL) {
        printf("=================\n");
        printf("SEM CARTA NA MESA\n");
        printf("=================\n");
        return;
    }
    printf("=================\n");
    printf("  CARTA NA MESA\n");
    printf("=================\n");
    printf("NAIPE: %s\n", getNaipe(baralho->encima_mesa));
    printf("VALOR: %s\n", getValor(baralho->encima_mesa));
    printf("=================\n");
}

CARTA* desempilharCarta(BARALHO * baralho){
    CARTA * carta = baralho->topo_baralho;
    baralho->topo_baralho = proximaCarta(baralho->topo_baralho);
    return carta;
}

int jogos(BARALHO * baralho, int player) {
    return getQuantidadeJogos(baralho->players[player]);
}

void verCartaTopo(BARALHO * baralho) {
    printf("=================\n");
    printf("  CARTA DO TOPO\n");
    printf("=================\n");
    printf("NAIPE: %s\n", getNaipe(baralho->topo_baralho));
    printf("VALOR: %s\n", getValor(baralho->topo_baralho));
    printf("=================\n");
}

void trocarCarta(BARALHO* baralho, int posicao, char* operacao, int jogador) {
    CARTA* carta;
    posicao--;

    if(strcmp("TOPO", operacao) == 0) {
        CARTA* nova_carta = desempilharCarta(baralho);

        CARTA* carta_descartada = getCarta(baralho->players[jogador], posicao);
        setCarta(baralho->players[jogador], posicao, nova_carta);
        baralho->encima_mesa = carta_descartada; 
    }

    else if(strcmp("MESA", operacao) == 0) {
        if(baralho->encima_mesa == NULL) {
            printf("MESA VAZIA\n");
        } else {
            carta = getCarta(baralho->players[jogador], posicao);
            setCarta(baralho->players[jogador], posicao, baralho->encima_mesa);
            baralho->encima_mesa = carta;
        }
    }  else {
        CARTA* carta_descartada = getCarta(baralho->players[jogador], posicao);
        CARTA* nova_carta_topo = desempilharCarta(baralho); 

        carta = desempilharCarta(baralho); 
        if(baralho->encima_mesa != NULL) {
            baralho->encima_mesa = getCarta(baralho->players[jogador], posicao);
        }
        baralho->encima_mesa = carta;
    }
}

void liberarMemoriaJogo(BARALHO *baralho) {
    if (baralho == NULL)
        return;
    CARTA *atual = baralho->topo_baralho;
    while (atual != NULL) {
        CARTA *prox = proximaCarta(atual);
        free(atual);
        atual = prox;
    }

    if (baralho->encima_mesa != NULL)
        free(baralho->encima_mesa);
    for (int i = 0; i < 2; i++) {
        if (baralho->players[i] != NULL)
            liberarMao(baralho->players[i]);
    }

    free(baralho);
}

void verificaJogo(BARALHO* baralho, int j) {
    
    for(int i = 0; i < 2; i++) {
        resetarStatusMao(baralho->players[i]);
        
        quaseNaipeDiferente(baralho->players[i]);
        quaseNaipeIgual(baralho->players[i]);
        jogoNaipeDiferente(baralho->players[i]);
        jogoNaipeIgual(baralho->players[i]);
        
        if(j == 1)
        printf("\nNUMERO JOGOS JOGADOR %d: %d\n", i + 1, jogos(baralho, i));
    }
}

CARTA* getCartaTopo(BARALHO* baralho) {
    if (baralho == NULL) return NULL;
    return baralho->topo_baralho;
}

CARTA* getCartaMesa(BARALHO* baralho) {
    if (baralho == NULL) return NULL;
    return baralho->encima_mesa;
}

int simularJogos(MAO* mao, CARTA* novaCarta, int posSubstituir, CARTA** cartaAntiga) {
    CARTA* original = getCarta(mao, posSubstituir); 
    *cartaAntiga = original; 

    setCarta(mao, posSubstituir, novaCarta);
    resetarStatusMao(mao); 
    quaseNaipeDiferente(mao);
    quaseNaipeIgual(mao);
    jogoNaipeDiferente(mao);
    jogoNaipeIgual(mao);

    int jogosResultantes = getQuantidadeJogos(mao); 
    setCarta(mao, posSubstituir, original); 

    return jogosResultantes;
}

void bot(BARALHO* baralho) {
    MAO* maoBot = baralho->players[1]; 
    CARTA* cartaMesa = getCartaMesa(baralho); 
    CARTA* cartaTopo = getCartaTopo(baralho); 
    
    int jogosOriginais = 0;
    int melhorIndiceMesa = -1;
    int maxJogosMesa = -1;
    int melhorIndiceTopo = -1;
    int maxJogosTopo = -1;

    resetarStatusMao(maoBot);
    quaseNaipeDiferente(maoBot);
    quaseNaipeIgual(maoBot);
    jogoNaipeDiferente(maoBot);
    jogoNaipeIgual(maoBot);
    jogosOriginais = getQuantidadeJogos(maoBot);

    if (cartaMesa != NULL) { 
        for (int i = 0; i < 9; i++) {
            CARTA* cartaAntiga;
            int jogos = simularJogos(maoBot, cartaMesa, i, &cartaAntiga);

            if (jogos > maxJogosMesa) {
                maxJogosMesa = jogos;
                melhorIndiceMesa = i;
            }
        }
    }

    if (cartaTopo != NULL) { 
        for (int i = 0; i < 9; i++) {
            CARTA* cartaAntiga;
            int jogos = simularJogos(maoBot, cartaTopo, i, &cartaAntiga);

            if (jogos > maxJogosTopo) {
                maxJogosTopo = jogos;
                melhorIndiceTopo = i;
            }
        }
    }

    int decisaoIndice = -1;
    char* operacao = "TOPO";
    
    if (maxJogosMesa > jogosOriginais) {
        decisaoIndice = melhorIndiceMesa;
        operacao = "MESA";
    } else if (maxJogosTopo > jogosOriginais) {
        decisaoIndice = melhorIndiceTopo;
        operacao = "TOPO";
    }

if (decisaoIndice == -1) {
    operacao = "TOPO";
    
    resetarStatusMao(maoBot); 
    quaseNaipeDiferente(maoBot);
    quaseNaipeIgual(maoBot);
    jogoNaipeDiferente(maoBot);
    jogoNaipeIgual(maoBot);

    int piorIndice = -1;
    
    for (int i = 0; i < 9; i++) {
        CARTA* c = getCarta(maoBot, i);
        if (c != NULL) {
            int status = getUsada(c); 
            if (status == 0) {
                piorIndice = i;
                break; 
            }
        }
    }
    
    decisaoIndice = piorIndice;

    if (decisaoIndice == -1) {
        printf("AVISO BOT: Todas as cartas estao marcadas como jogo/quase-jogo. Descartando a ultima carta da mao.\n");
   
        decisaoIndice = 8; 
    }
}
    trocarCarta(baralho, decisaoIndice + 1, operacao, 1);
    CARTA* descartada = getCartaMesa(baralho);
    if (descartada != NULL) { 
        printf("\nBOT descartou: %s de %s\n", getValor(descartada), getNaipe(descartada));
    }
}

int getCartaDoTopo(BARALHO* baralho) {
    if(baralho->topo_baralho == NULL) return 1;
    else return 0;
}

int getCartaDaMesa(BARALHO* baralho) {
    if(baralho->encima_mesa == NULL) {
        return 1;
    }

    return 0;
}

void maisCarta(BARALHO * baralho) {
     for (int i = 0; i < 20; i++) {
        baralho->topo_baralho = criarCarta(baralho->topo_baralho, rand());
    }
}