#include <stdio.h>
#include <stdlib.h>
#include "baralho/baralho.h"
#include "mao/mao.h"

int main() {
    BARALHO* trinca = criarBaralho();
    if(trinca == NULL) {
        exit(1);
    } else distribuirCartas(trinca, 2, 9);

    int opcao_selecionar = 0, opcCarta, 
    jog1, jog2;
    char opcao;

    jog1 = jogos(trinca, 0);
    jog2 = jogos(trinca, 1);
    while(1) {
        if(getCartaDoTopo(trinca) == 1)  {
            printf("MAIS CARTAS\n");
            system("pause");
            maisCarta(trinca);
        }
        // INTERFACE JOGADOR
        exibirMaoJogador(trinca, 0);
        exibirCartaNaMesa(trinca);
        loop:
        printf("[1]PEGAR DO BARALHO\n[2]PEGAR DA MESA\n");
        printf("QUAL OPCAO: ");
        scanf("%d", &opcao_selecionar);

        switch (opcao_selecionar) {
        case 1:
            // PEGAR CARTA DO BARALHO
            verCartaTopo(trinca);
            printf("\nPEGAR CARTA[S/N]: ");
            scanf(" %c", &opcao);
            switch (opcao) {
            case 'S':
            case 's':
            printf("QUAL CARTA(NUMERO): ");
            scanf("%d", &opcCarta);
            trocarCarta(trinca, opcCarta, "TOPO", 0);
            break;

            case 'N':
            case 'n':
            trocarCarta(trinca, 1, "NAO", 0);
                break;
            
            default:
                break;
            }
   
            system("pause");
            system("cls");
            break;

        // PEGAR MESA
        case 2:
            printf("\nDESISTIR[S/N]: ");
            scanf(" %c", &opcao);
            switch (opcao) {
            case 'N':
            case 'n':
            if(getCartaDaMesa(trinca) == 1) {
                system("cls");
                printf("SEM CARTA NA MESA\n");
                goto loop;
            }
            printf("QUAL CARTA(NUMERO): ");
            scanf("%d", &opcCarta);
            trocarCarta(trinca, opcCarta, "MESA", 0);
            break;

            case 'S':
            case 's':
            system("cls");
            goto loop;
                break;
            
            default:
                break;
            }
            system("pause");
            system("cls");
            break;
        default:
            break;
        }

        verificaJogo(trinca, 0);
        jog1 = jogos(trinca, 0);
        if(jog1 == 3) break;

        printf("\n=== VEZ DO BOT ===\n");
        bot(trinca);
        system("pause");
        system("cls");

        verificaJogo(trinca, 0);
        jog2 = jogos(trinca, 1);

        if(jog1 == 3 || jog2 == 3) {
            break;
        }
    }

    if(jog1 == 3) {
        printf("VOCE VENCEU!\n");
    }

    if(jog2 == 3) {
        printf("VOCE PERDEU!\n");
    }

    liberarMemoriaJogo(trinca);
    return 0;
}