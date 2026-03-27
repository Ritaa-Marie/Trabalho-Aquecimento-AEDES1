#ifndef ALGORITMO_GENETICO_H
#define ALGORITMO_GENETICO_H
#include "estruturas.h"
#define SEED 73

// todas as funções que envolvem o algoritmo genético estarão aqui, desconsidere o retorno e os parâmetros, a ideia é apenas
// organizar o que ficará em cada módulo, no desenvolvimento esses aspectos serão resolvidos.


void gerar_populacao_inicial(Individuo *populacao, DadosEntrada *dadosEntrada, Limites *limitesAB);
void avaliar_individuos(DadosEntrada *dadosEntrada, Individuo *populacao);
void crossover(Individuo melhores[2], Individuo *novoIndividuo);
void mutacao();
void algoritmo_gene();


#endif /* ALGORITMO_GENETICO_H */