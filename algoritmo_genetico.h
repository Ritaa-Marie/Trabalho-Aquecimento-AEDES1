#ifndef ALGORITMO_GENETICO_H
#define ALGORITMO_GENETICO_H

// todas as funções que envolvem o algoritmo genético estarão aqui, desconsidere o retorno e os parâmetros, a ideia é apenas
// organizar o que ficará em cada módulo, no desenvolvimento esses aspectos serão resolvidos.

typedef struct individuo {
    float a;
    float b;
    float fitness;
}Individuo;

void gerar_populacao_inicial();
void avaliar_individuo();
void crossover();
void mutacao();


#endif /* ALGORITMO_GENETICO_H */