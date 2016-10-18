#include <stdio.h>
#include <stdlib.h>

void imprimirResultado(int matrizJogo[9], int pontos[3]){
    switch(checarVitoria(matrizJogo)){
        case -1:
            printf("Voce ganhou.\n\n");
            pontos[0]++;
            break;
        case 1:
            printf("Voce perdeu.\n\n");
            pontos[1]++;
            break;
        case 0:
            printf("Velha.\n\n");
            pontos[2]++;
            break;
    }
}

char imprimirChar(int i){
    switch(i){
        case -1:
            return 'X';
        case 0:
            return ' ';
        case 1:
            return 'O';
    }
}

void imprimirJogo(int matrizJogo[9]){
    system("cls");
    printf("|%c|%c|%c|\n",imprimirChar(matrizJogo[0]),imprimirChar(matrizJogo[1]),imprimirChar(matrizJogo[2]));
    printf(" - - -\n");
    printf("|%c|%c|%c|\n",imprimirChar(matrizJogo[3]),imprimirChar(matrizJogo[4]),imprimirChar(matrizJogo[5]));
    printf(" - - -\n");
    printf("|%c|%c|%c|\n",imprimirChar(matrizJogo[6]),imprimirChar(matrizJogo[7]),imprimirChar(matrizJogo[8]));
}

int checarVitoria(int matrizJogo[9]){
    int wins[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};//Lista de casos de vitórias.
    int i;
    for(i=0;i<8;i++){
        if(matrizJogo[wins[i][0]] != 0 && matrizJogo[wins[i][0]] == matrizJogo[wins[i][1]] && matrizJogo[wins[i][0]] == matrizJogo[wins[i][2]])
            return matrizJogo[wins[i][0]];
    }
    return 0;
}

int minimax(int matrizJogo[9], int jogador){

    int ganhador = checarVitoria(matrizJogo);
    if(ganhador != 0)
        return ganhador*jogador;//Checa se chegou até a profundidade máxima da arvore de possibilidades.

    int move = -1;
    int score = -2;
    int i;
    for(i=0;i<9;i++){
        if(matrizJogo[i] == 0) {
            matrizJogo[i] = jogador;
            int thisScore = -minimax(matrizJogo, jogador*-1);
            if(thisScore > score){
                score = thisScore;
                move = i;
            }
            matrizJogo[i] = 0;//retorna estado anterior do tabuleiro.
        }
    }
    if(move == -1)
        return 0;
    return score;
}

void vezBot(int matrizJogo[9]){
    int move = -1;
    int score = -2;
    int i;
    for(i=0;i<9;i++){
        if(matrizJogo[i] == 0){
            matrizJogo[i] = 1;
            int tempScore = -minimax(matrizJogo, -1);
            matrizJogo[i] = 0;
            if(tempScore > score){
                score = tempScore;
                move = i;
            }
        }
    }
    matrizJogo[move] = 1;
}

void vezJogador(int matrizJogo[9]){
    int move=0;
    int i=0;
    printf("Sua vez.\n");
    for(i=0;i<1;i++){
        printf("Digite a posicao que deseja jogar: ");
        scanf("%d", &move);
        if(move < 1 || move > 9 || matrizJogo[move-1] != 0){
            printf("Jogue em outra posicao.\n");
            i--;
        }
    }
    matrizJogo[move-1] = -1;
}

int main(){
    int matrizJogo[9] = {0,0,0,0,0,0,0,0,0};
    int vez;
    int i=0;
    int pontos[3] = {0,0,0};
    int run=1;
    int jogada=0;
    while(run == 1){
        for(i=0;i<1;i++){
            printf("Deseja jogar primeiro?\n1-Sim.\n2-Nao.\n");
            scanf("%d", &vez);
            if(!(vez == 1 || vez == 2)){
                system("cls");
                i--;
            }
        }
        for(i=0;i<9;i++){
            imprimirJogo(matrizJogo);
            if(vez == 1){
                vezJogador(matrizJogo);
                vez=2;
                jogada++;
            }
            else if(vez == 2){
                if(jogada == 0){
                    matrizJogo[4]=1;
                    jogada++;
                    vez=1;
                }
                else if(jogada > 0){
                    vezBot(matrizJogo);
                    vez=1;
                    jogada++;
                }
            }
            imprimirJogo(matrizJogo);
            if(checarVitoria(matrizJogo) != 0)
                break;
        }
        imprimirJogo(matrizJogo);
        imprimirResultado(matrizJogo, pontos);
        printf("---Placar---\nVoce: %d.\nBOT: %d.\nVelha: %d.\n\n", pontos[0], pontos[1], pontos[2]);
        for(i=0;i<1;i++){
            printf("Jogar novamente?\n1-Sim\n2-Nao\n");
            scanf("%d", &run);
            if(run < 1 || run > 2)
                i--;
                system("cls");
        }
        for(i=0;i<9;i++)
            matrizJogo[i]=0;
        jogada=0;
    }
    return 0;
}
