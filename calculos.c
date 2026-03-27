#include <stdio.h>
#include <stdlib.h>
#include "manipulacao_arquivos.h"
#include "algoritmo_genetico.h"

// função para realizar os cálculos do algoritmo genético
float funcao_reta(float a, float b, float x){
    float y = (a * x) + b;
    return y;
}


float calcular_erro_MAE_individuo(DadosEntrada *dadosEntrada, Individuo *populacao, int j){
    float a = populacao[j].a;
    float b = populacao[j].b;

    float erro_total = 0.0;

    for(int i=0;i<dadosEntrada->n;i++){
        float y_funcao = funcao_reta(a, b, dadosEntrada->pontos[i].x);
        float erro = y_funcao - dadosEntrada->pontos[i].y;

        if(erro < 0){
            erro *= -1;
        }

        erro_total += erro;
    }

    float media_erro_reta = erro_total / dadosEntrada->n;
    return media_erro_reta;
}


void calcular_fitness(float erro_medio, Individuo *populacao, int j){
    float fit = 1.0f / (1.0f + erro_medio);
    populacao[j].fitness = fit;
}


void ordenar_individuos_fitness(DadosEntrada *dadosEntrada, Individuo *populacao, Individuo *individuos_ordenados){
    for(int i=0;i<dadosEntrada->m;i++){
        individuos_ordenados[i] = populacao[i];
    }

    for(int i=0;i<dadosEntrada->m - 1;i++){
        for(int j=0;j<dadosEntrada->m - 1 - i;j++){
            if(individuos_ordenados[j].fitness > individuos_ordenados[j+1].fitness){
                Individuo ordenar = individuos_ordenados[j];
                individuos_ordenados[j] = individuos_ordenados[j+1];
                individuos_ordenados[j+1] = ordenar;
            }
        }
    }
}

