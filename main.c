#include <stdio.h>
#include <stdlib.h>
#include "estruturas.h"
#include "calculos.h"
#include "algoritmo_genetico.h"
#include "manipulacao_arquivos.h"


int main(){

    DadosEntrada dadosEntrada;

    int dadosApagados = apagar_dados_arquivo("output.dat");

    int leituraDados = ler_arquivo("input.dat", &dadosEntrada);
    if (leituraDados == 1){
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
    rodar_algoritmo_genetico(populacao, &dadosEntrada, &limitesAB);
     
    

    //chama as funções para rodar o algoritmo
    
    free(dadosEntrada.pontos);
    free(populacao);

    return 0;
}