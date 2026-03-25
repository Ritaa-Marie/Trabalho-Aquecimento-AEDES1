#include <stdio.h>
#include <stdlib.h>
#include "algoritmo_genetico.h"
#include "manipulacao_arquivos.h"

int main(){

    DadosEntrada dadosEntrada;

    int leituraDados = ler_arquivo("input.dat", &dadosEntrada);
    if (leituraDados == 0){
        printf("%f %f", dadosEntrada.pontos[3].x, dadosEntrada.pontos[3].y); //teste
        printf("%d", dadosEntrada.n);
    } else {
        return 1;
    }

    Individuo *populacao;
    populacao = malloc(dadosEntrada.m * sizeof(Individuo));
    if(populacao == NULL){
        printf("\nErro ao alocar memória para armazenar a população inicial.\n");
        return 1;
    }

    srand(SEED);
    gerar_populacao_inicial(populacao, &dadosEntrada);

    

    //chama as funções para rodar o algoritmo
    
    free(dadosEntrada.pontos);
    free(populacao);

    return 0;
}