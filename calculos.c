#include <stdio.h>
#include <stdlib.h>

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