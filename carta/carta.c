#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "carta.h"

typedef struct CARTA {
    char naipe[8];
    char valor[3];
    int usada;
    struct CARTA* proximo;
} CARTA;

char* naipes[] = {"ESPADAS", "PAUS   ", "OUROS  ", "COPAS  "};
char* valores[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};

CARTA* criarCarta(CARTA* proxima, int numero_sorte) {
    CARTA* nova = (CARTA*)malloc(sizeof(CARTA));
    if (nova == NULL) {
        printf("ERRO DE ALOCACAO DE CARTA\n");
        exit(1);
    }

    int n = numero_sorte % 4;
    int v = numero_sorte % 13;

    strcpy(nova->naipe, naipes[n]);
    strcpy(nova->valor, valores[v]);
    nova->usada = 0;
    nova->proximo = proxima;

    return nova;
}

CARTA* proximaCarta(CARTA* atualCarta) {
    return atualCarta->proximo;
}

char* getNaipe(CARTA* atualCarta) {
    return atualCarta->naipe;
}

char* getValor(CARTA* atualCarta) {
    return atualCarta->valor;
}

int getUsada(CARTA* carta) {
    return carta->usada;
}

void setUsada(CARTA* carta, int usada) {
    carta->usada = usada;
}

int converteEmNumero(char* valor) {
    if (strcmp(valor, "A") == 0) return 1;
    if (strcmp(valor, "J") == 0) return 11;
    if (strcmp(valor, "Q") == 0) return 12;
    if (strcmp(valor, "K") == 0) return 13;
    int numero = atoi(valor); 
    if (numero >= 2 && numero <= 10)
        return numero;

    return -1;
}

CARTA* duplicarCarta(CARTA* original) {
    if (original == NULL) {
        return NULL;
    }

    CARTA* copia = (CARTA*)malloc(sizeof(CARTA));
    if (copia == NULL) {
        printf("ERRO DE ALOCACAO PARA DUPLICAR CARTA\n");
        exit(1);
    }

    strcpy(copia->naipe, original->naipe);
    strcpy(copia->valor, original->valor);
    copia->usada = original->usada;
    copia->proximo = NULL;

    return copia;
}