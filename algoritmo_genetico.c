#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "algoritmo_genetico.h"
#include "calculos.h"
#include "manipulacao_arquivos.h"

// funções do algoritmo genético

void gerar_populacao_inicial(Individuo *populacao, DadosEntrada *dadosEntrada, Limites *limitesAB){
    float limiteA = limitesAB->diferencaY / limitesAB->diferencaX;

    for(int i=0;i<dadosEntrada->m;i++){
        float num_aleatorio = (float) rand() / RAND_MAX;
        populacao[i].a = -(limiteA) + num_aleatorio * (2 * limiteA);

        num_aleatorio = (float) rand() / RAND_MAX;
        populacao[i].b = limitesAB->menorY + num_aleatorio * limitesAB->diferencaY;
        populacao[i].fitness = NAN;
    }
}


void avaliar_individuos(DadosEntrada *dadosEntrada, Individuo *populacao){
    for(int i=0;i<dadosEntrada->m;i++){
        float erro_individual = calcular_erro_MAE_individuo(dadosEntrada, populacao, i);
        calcular_fitness(erro_individual, populacao, i);
    }
}


void crossover(Individuo melhores[2], Individuo *novoIndividuo){
    float novo_a = (melhores[0].a + melhores[1].a) / 2;
    float novo_b = (melhores[0].b + melhores[1].b) / 2;

    novoIndividuo->a = novo_a;
    novoIndividuo->b = novo_b;
    novoIndividuo->fitness = NAN;
}