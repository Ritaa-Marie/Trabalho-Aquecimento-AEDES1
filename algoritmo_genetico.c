#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "algoritmo_genetico.h"
#include "calculos.h"
#include "manipulacao_arquivos.h"


void gerar_populacao_inicial(Individuo *populacao, DadosEntrada *dadosEntrada, Limites *limitesAB){
    for(int i=0;i<dadosEntrada->m;i++){
        float num_aleatorio = (float) rand() / RAND_MAX;
        populacao[i].a = -(limitesAB->limiteA) + num_aleatorio * (2 * limitesAB->limiteA);

        num_aleatorio = (float) rand() / RAND_MAX;
        populacao[i].b = limitesAB->menorB + num_aleatorio * limitesAB->diferencaB;
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
    novoIndividuoCross->a = 0;
    novoIndividuoCross->b = 0;
    novoIndividuoCross->fitness = 0;

    if(aleatoriedade <= 0.5){
        novo_a = pai1.a;
        novo_b = pai2.b;
    }  else {
        novo_a = pai2.a;
        novo_b = pai1.b;
    }
     
    novoIndividuoCross->a = novo_a;
    novoIndividuoCross->b = novo_b;
    novoIndividuoCross->fitness = NAN;
}


void mutacao(Individuo bom, Individuo *novoIndividuoMut, float aleatoriedade, Limites *limitesAB){
    float novo_a = bom.a;
    float novo_b = bom.b;
    novoIndividuoMut->a = 0;
    novoIndividuoMut->b = 0;
    novoIndividuoMut->fitness = 0;

    if(aleatoriedade <= 0.5f){
        float limA = (limitesAB->maiorA - limitesAB->menorA);
        float mutacaoA = (((float) rand() / RAND_MAX) - 0.5f) * limA * 0.1f;
        novo_a += mutacaoA;

        if(novo_a < limitesAB->menorA){
            novo_a = limitesAB->menorA;
        } 
        if(novo_a > limitesAB->maiorA){
            novo_a = limitesAB->maiorA;
        } 

    } else {
        float limB = limitesAB->diferencaB;
        float mutacaoB = (((float) rand() / RAND_MAX) - 0.5f) * limB * 0.1f;
        novo_b += mutacaoB;

        if(novo_b < limitesAB->menorB){
            novo_b = limitesAB->menorB;
        } 
        if(novo_b > limitesAB->maiorB){
            novo_b = limitesAB->maiorB;
        } 
    }

    novoIndividuoMut->a = novo_a;
    novoIndividuoMut->b = novo_b;
    novoIndividuoMut->fitness = NAN;
}


int evoluir_individuos(DadosEntrada *dadosEntrada, Limites *limitesAB, Individuo *individuos_ordenados, Individuo *nova_pop){
    // selecionar os 50% piores
    int num_individuosPiores = dadosEntrada->m / 2;
    int num_individuosCross = (int)(num_individuosPiores * 0.3f);

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
        nova_pop[i] = novoIndividuoCross;
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
        nova_pop[i] = novoIndividuoMut;
    }

    for(int i=num_individuosPiores;i<dadosEntrada->m;i++){
        nova_pop[i] = individuos_ordenados[i];
        nova_pop[i].fitness = NAN;
    }
    return 0;
}

int rodar_algoritmo_genetico(Individuo *populacao, DadosEntrada *dadosEntrada, Limites *limitesAB, Individuo *individuos_ordenados, Individuo *nova_pop){
    for(int i=0;i<dadosEntrada->G;i++){
        avaliar_individuos(dadosEntrada, populacao);
        ordenar_individuos_fitness(dadosEntrada, populacao, individuos_ordenados);
        
        // gravar dados no arquivo
        int melhor = dadosEntrada->m - 1;
        GravarDados gravarDados;
        gravarDados.geracao = i + 1;
        gravarDados.a = individuos_ordenados[melhor].a;
        gravarDados.b = individuos_ordenados[melhor].b;
        gravarDados.fitness = individuos_ordenados[melhor].fitness;
        if(individuos_ordenados[melhor].fitness > 0){
            gravarDados.erro = (1.0f / individuos_ordenados[melhor].fitness) -1.0f;
        } else {
            gravarDados.erro = INFINITY;
        }
        
        gravar_arquivo(&gravarDados);
        printf("\nMelhor %d: (%f %f %f)\n", i+1,
            individuos_ordenados[melhor].a,
            individuos_ordenados[melhor].b,
            individuos_ordenados[melhor].fitness);
        int evoluiu = evoluir_individuos(dadosEntrada, limitesAB, individuos_ordenados, nova_pop);
        if (evoluiu == 1){
            return 1;
        }

        for(int j=0;j<dadosEntrada->m;j++){
            populacao[j] = nova_pop[j];
        }
    }
    return 0;
}
