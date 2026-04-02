#ifndef ALGORITMO_GENETICO_H
#define ALGORITMO_GENETICO_H
#include "estruturas.h"
#define SEED 73

// funções do algoritmo genético

void gerar_populacao_inicial(Individuo *populacao, DadosEntrada *dadosEntrada, Limites *limitesAB);
void avaliar_individuos(DadosEntrada *dadosEntrada, Individuo *populacao);
void crossover(Individuo pai1, Individuo pai2, Individuo *novoIndividuoCross, float aleatoriedade);
void mutacao(Individuo bom, Individuo *novoIndividuoMut, float aleatoriedade, Limites *limitesAB);
void evoluir_individuos(DadosEntrada *dadosEntrada, Limites *limitesAB, Individuo *individuos_ordenados, Individuo *nova_pop);
void rodar_algoritmo_genetico(Individuo *populacao, DadosEntrada *dadosEntrada, Limites *limitesAB, Individuo *individuos_ordenados, Individuo *nova_pop);


#endif /* ALGORITMO_GENETICO_H */