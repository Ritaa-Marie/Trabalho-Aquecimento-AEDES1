#ifndef CALCULOS_H
#define CALCULOS_H
#include "estruturas.h"

// função para realizar os cálculos e lógicas do algoritmo genético

void definir_limites_a_b(DadosEntrada *dadosEntrada, Limites *limitesAB);
float funcao_reta(float a, float b, float x);
float calcular_erro_MAE_individuo(DadosEntrada *dadosEntradaentrada, Individuo *populacao, int j);
void calcular_fitness(float erro_medio, Individuo *populacao, int j);
void ordenar_individuos_fitness(DadosEntrada *dadosEntrada, Individuo *populacao, Individuo *individuos_ordenados);

#endif /* CALCULOS_H */