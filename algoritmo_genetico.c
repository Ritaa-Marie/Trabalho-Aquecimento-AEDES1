#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "algoritmo_genetico.h"
#include "calculos.h"
#include "manipulacao_arquivos.h"

// funções do algoritmo genético

void gerar_populacao_inicial(Individuo *populacao, DadosEntrada *dadosEntrada, Limites *limitesAB){
    for(int i=0;i<dadosEntrada->m;i++){
        float num_aleatorio = (float) rand() / RAND_MAX;
        populacao[i].a = -(limitesAB->limiteA) + num_aleatorio * (2 * limitesAB->limiteA);

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


void crossover(Individuo pai1, Individuo pai2, Individuo *novoIndividuoCross){
    float novo_a = (pai1.a + pai2.a) / 2;
    float novo_b = (pai1.b + pai2.b) / 2;

    novoIndividuo->a = novo_a;
    novoIndividuo->b = novo_b;
    novoIndividuo->fitness = NAN;
}

void mutacao(Individuo bom, Individuo *novoIndividuoMut, float aleatoriedade, Limites *limitesAB){
    float novo_a = bom.a;
    float novo_b = bom.b;

    if(aleatoriedade <= 0.5){
        float limA = limitesAB->limiteA * 0.05;
        float mutacao = (((float) rand() / RAND_MAX) - 0.5) * limA;
        novo_a += mutacao;
    
    } else {
        float limB = limitesAB->diferencaY * 0.05;
        float mutacao = (((float) rand() / RAND_MAX) - 0.5) * limB;
        novo_b += mutacao;
            
    }

    novoIndividuoMut->a = novo_a;
    novoIndividuoMut->b = novo_b;
    novoIndividuoMut->fitness = NAN;
}

