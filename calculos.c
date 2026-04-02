#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "manipulacao_arquivos.h"
#include "algoritmo_genetico.h"

// função para realizar os cálculos do algoritmo genético


void definir_limites_a_b(DadosEntrada *dadosEntrada, Limites *limitesAB){
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

    float centroB = 0.0f;
    float faixaB = 25.0f;

    if(diferencaX == 0.0){
        diferencaX = 1;
    }
    if(diferencaY == 0.0){
        diferencaY = 1;
    }

    float limiteA = diferencaY / diferencaX;

    limitesAB->menorX = menorX;
    limitesAB->menorY = menorY;
    limitesAB->maiorX = maiorX;
    limitesAB->maiorY = maiorY;
    limitesAB->diferencaX = diferencaX;
    limitesAB->diferencaY = diferencaY;
    limitesAB->limiteA = limiteA;
    limitesAB->menorB = centroB - faixaB;
    limitesAB->maiorB = centroB + faixaB;
    limitesAB->diferencaB = limitesAB->maiorB - limitesAB->menorB;
    
}

void definir_limites_a_b_teste(DadosEntrada *dadosEntrada, Limites *limitesAB){
    float maiorX = dadosEntrada->pontos[0].x, menorX = dadosEntrada->pontos[0].x;
    float maiorY = dadosEntrada->pontos[0].y, menorY = dadosEntrada->pontos[0].y;

    for(int i = 1; i < dadosEntrada->n; i++){
        if(dadosEntrada->pontos[i].x > maiorX) maiorX = dadosEntrada->pontos[i].x;
        if(dadosEntrada->pontos[i].x < menorX) menorX = dadosEntrada->pontos[i].x;
        if(dadosEntrada->pontos[i].y > maiorY) maiorY = dadosEntrada->pontos[i].y;
        if(dadosEntrada->pontos[i].y < menorY) menorY = dadosEntrada->pontos[i].y;
    }

    float diferencaX = maiorX - menorX;
    float diferencaY = maiorY - menorY;

    if(diferencaX == 0.0){
        diferencaX = 1.0;
    }
    if(diferencaY == 0.0){
        diferencaY = 1.0;
    } 

    float limiteA = diferencaY / diferencaX;

    limitesAB->menorA = -limiteA * 2.0f;
    limitesAB->maiorA =  limiteA * 2.0f;

    limitesAB->menorB = menorY;
    limitesAB->maiorB = maiorY;
    limitesAB->diferencaB = limitesAB->maiorB - limitesAB->menorB;

    limitesAB->menorX = menorX;
    limitesAB->maiorX = maiorX;
    limitesAB->menorY = menorY;
    limitesAB->maiorY = maiorY;
    limitesAB->diferencaX = diferencaX;
    limitesAB->diferencaY = diferencaY;
}

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
    //ordenação crescente
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

