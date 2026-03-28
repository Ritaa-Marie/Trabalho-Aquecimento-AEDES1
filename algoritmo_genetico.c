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


void crossover(Individuo pai1, Individuo pai2, Individuo *novoIndividuoCross, float aleatoriedade){
    float novo_a, novo_b;

    if(aleatoriedade <= 0.33){
        novo_a = pai1.a;
        novo_b = pai2.b;
    }  else if(aleatoriedade <= 0.66) {
        novo_a = pai2.a;
        novo_b = pai1.b;
    } else {
        novo_a = (pai1.a + pai2.a) /2;
        novo_b = (pai1.b + pai2.b) /2;
    }
     
    novoIndividuoCross->a = novo_a;
    novoIndividuoCross->b = novo_b;
    novoIndividuoCross->fitness = NAN;
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

int evoluir_individuos(Individuo *populacao, DadosEntrada *dadosEntrada, Limites *limitesAB){
    // ordenar indivíduos
    Individuo *individuos_ordenados;
    individuos_ordenados = malloc(dadosEntrada->m * sizeof(Individuo));
    if (individuos_ordenados == NULL){
        printf("\nErro na alocação de memória para armazenar os indivíduos ordenados.\n");
        return 1;
    }
    populacao[0].fitness = 0.256;
    populacao[1].fitness = 1.456;
    populacao[2].fitness = 7.89;
    populacao[3].fitness = 7.89;
    populacao[4].fitness = 7.89;
    populacao[5].fitness = 7.89;
    populacao[6].fitness = 7.89;
    populacao[7].fitness = 0.123;
    ordenar_individuos_fitness(dadosEntrada, populacao, individuos_ordenados);

    // selecionar os 50% piores
    int num_individuosPiores = dadosEntrada->m / 2;
    int num_individuosMelhores = dadosEntrada->m - num_individuosPiores;
    printf("\npiores e melhores: %d, %d", num_individuosPiores, num_individuosMelhores);
    
    int num_individuosCross = num_individuosPiores * 0.7;
    int num_individuosMut = num_individuosPiores - num_individuosCross;
    printf("\nCross e mut: %d, %d \n", num_individuosCross, num_individuosMut);

    for(int i=0;i<num_individuosCross;i++){
        Individuo novoIndividuoCross, pai1, pai2;
        float aleatoriedade = (float) rand() / RAND_MAX;

        int posicao1, posicao2;
        do {
            posicao1 = num_individuosPiores + rand() % (dadosEntrada->m - num_individuosPiores);
            posicao2 = num_individuosPiores + rand() % (dadosEntrada->m - num_individuosPiores);
        } while(posicao1 == posicao2);
        pai1 = individuos_ordenados[posicao1];
        pai2 = individuos_ordenados[posicao2];
        crossover(pai1, pai2, &novoIndividuoCross, aleatoriedade);
        individuos_ordenados[i] = novoIndividuoCross;
    }

    int posicaoAnterior = 0;
    for(int i=num_individuosCross;i<num_individuosPiores;i++){
        Individuo novoIndividuoMut, bom;
        float aleatoriedade = (float) rand() / RAND_MAX;

        int posicao1;
        do {
            posicao1 = num_individuosPiores + rand() % (dadosEntrada->m - num_individuosPiores);
        } while(posicao1 == posicaoAnterior);
        posicaoAnterior = posicao1;
        bom = individuos_ordenados[posicao1];
        mutacao(bom, &novoIndividuoMut, aleatoriedade, limitesAB);
        individuos_ordenados[i] = novoIndividuoMut;
        printf("novo: %f %f %f\n", novoIndividuoMut.a, novoIndividuoMut.b, novoIndividuoMut.fitness);
    }

    for(int i=0;i<dadosEntrada->m;i++){
        printf("individo_ordenado: (%f %f %f)    ", individuos_ordenados[i].a, individuos_ordenados[i].b, individuos_ordenados[i].fitness);
        printf("individo_pop: (%f %f %f)\n", populacao[i].a, populacao[i].b, populacao[i].fitness);
    }
    

    return 0;
}
