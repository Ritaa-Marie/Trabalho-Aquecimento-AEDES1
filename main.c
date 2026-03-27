#include <stdio.h>
#include <stdlib.h>
#include "estruturas.h"
#include "calculos.h"
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
    Limites limitesAB;
    definir_limites_a_b(&dadosEntrada, &limitesAB);
    gerar_populacao_inicial(populacao, &dadosEntrada, &limitesAB);
    for(int i=0;i<dadosEntrada.m;i++){
        printf("%f %f\n", populacao[i].a, populacao[i].b);
    }
    printf("teste");
    printf("%d\n", rand());
    printf("%d\n", rand());

    

    //chama as funções para rodar o algoritmo
    
    free(dadosEntrada.pontos);
    free(populacao);

    return 0;
}