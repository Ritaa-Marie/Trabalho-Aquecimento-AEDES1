#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "algoritmo_genetico.h"
#include "calculos.h"
#include "manipulacao_arquivos.h"

// funções do algoritmo genético

void gerar_populacao_inicial(Individuo *populacao, DadosEntrada *dadosEntrada){
    // intervalo definido de acordo com os pontos de entrada
    float maiorX = dadosEntrada->pontos[0].x, menorX = dadosEntrada->pontos[0].x;
    float maiorY = dadosEntrada->pontos[0].y, menorY = dadosEntrada->pontos[0].y;

    for(int i=1;i<dadosEntrada->n;i++){
        if(dadosEntrada->pontos[i].x > maiorX){
            maiorX = dadosEntrada->pontos[i].x;
        }
        if(dadosEntrada->pontos[i].x < menorX){
            menorX = dadosEntrada->pontos[i].x;
        }
        if(dadosEntrada->pontos[i].y > maiorY){
            maiorY = dadosEntrada->pontos[i].y;
        }
        if(dadosEntrada->pontos[i].y < menorY){
            menorY = dadosEntrada->pontos[i].y;
        }
    }
    
    float diferencaX = maiorX - menorX;
    float diferencaY = maiorY - menorY;

    if(diferencaX == 0.0){
        diferencaX = 1;
    }
    if(diferencaY == 0.0){
        diferencaY = 1;
    }

    float limiteA = diferencaY / diferencaX;

    for(int i=0;i<dadosEntrada->m;i++){
        float num_aleatorio = (float) rand() / RAND_MAX;
        populacao[i].a = -(limiteA) + num_aleatorio * (2 * limiteA);

        num_aleatorio = (float) rand() / RAND_MAX;
        populacao[i].b = menorY + num_aleatorio * diferencaY;
        populacao[i].fitness = NAN;
    }
}


void avaliar_individuos(DadosEntrada *dadosEntrada, Individuo *populacao){
    for(int i=0;i<dadosEntrada->m;i++){
        float erro_individual = calcular_erro_MAE_individuo(dadosEntrada, populacao, i);
        calcular_fitness(erro_individual, populacao, i);
    }
}


void selecionar_melhores_individuos(DadosEntrada *dadosEntrada, Individuo *populacao, Individuo melhores[2]){
    Individuo primeiroMelhor = populacao[0];
    Individuo segundoMelhor = populacao[0];

    float maior1 = populacao[0].fitness;
    float maior2 = populacao[0].fitness;

   for(int i=0;i<dadosEntrada->m;i++){
        if(maior1 < populacao[i].fitness){
            maior2 = maior1;
            segundoMelhor = primeiroMelhor;
            maior1 = populacao[i].fitness;
            primeiroMelhor = populacao[i];
        } else if(maior2 < populacao[i].fitness){
            maior2 = populacao[i].fitness;
            segundoMelhor = populacao[i];
        }
   }
   melhores[0] = primeiroMelhor;
   melhores[1] = segundoMelhor;
}


int selecionar_pior_individuo(DadosEntrada *dadosEntrada, Individuo *populacao){
    float menor = populacao[0].fitness;
    int posicao = 0;

    for(int i=0;i<dadosEntrada->m;i++){
        if(menor > populacao[i].fitness){
            menor = populacao[i].fitness;
            posicao = i;
        }
    }
    return posicao;
}


void crossover(Individuo melhores[2], Individuo *novoIndividuo){
    float novo_a = (melhores[0].a + melhores[1].a) / 2;
    float novo_b = (melhores[0].b + melhores[1].b) / 2;

    novoIndividuo->a = novo_a;
    novoIndividuo->b = novo_b;
    novoIndividuo->fitness = NAN;
}