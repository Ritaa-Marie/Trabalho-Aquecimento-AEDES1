#ifndef CALCULOS_H
#define CALCULOS_H
#include "manipulacao_arquivos.h"
#include "algoritmo_genetico.h"

// todas as funções que envolvem cálculos estarão aqui, desconsidere o retorno e os parâmetros, a ideia é apenas
// organizar o que ficará em cada módulo, no desenvolvimento esses aspectos serão resolvidos.

float funcao_reta(float a, float b, float x);
float calcular_erro_MAE_individuo(DadosEntrada *dadosEntradaentrada, Individuo *populacao, int j);
void calcular_fitness(float erro_medio, Individuo *populacao, int j);

#endif /* CALCULOS_H */