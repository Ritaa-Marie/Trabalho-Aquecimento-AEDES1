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

    // ordenar indivíduos
        Individuo *individuos_ordenados;
        individuos_ordenados = malloc(dadosEntrada.m * sizeof(Individuo));
        if (individuos_ordenados == NULL){
            printf("\nErro na alocação de memória para armazenar os indivíduos ordenados.\n");
            return 1;
        }

        Individuo *nova_pop;
        nova_pop = malloc(dadosEntrada.m * sizeof(Individuo));

        if(nova_pop == NULL){
            printf("\nErro na alocação de memória para armazenar a nova população.\n");
            return 1;
        }
    rodar_algoritmo_genetico(populacao, &dadosEntrada, &limitesAB, individuos_ordenados, nova_pop);
     
    
    free(dadosEntrada.pontos);
    free(populacao);
    free(individuos_ordenados);
    free(nova_pop);

    return 0;
}