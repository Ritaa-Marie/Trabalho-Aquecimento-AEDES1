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

    if(aleatoriedade <= 0.5){
        novo_a = pai1.a;
        novo_b = pai2.b;
    }  else if(aleatoriedade > 0.5) {
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
    
    if(aleatoriedade <= 0.5){
        float limA = limitesAB->limiteA * 0.3;
        float mutacao = (((float) rand() / RAND_MAX) - 0.5) * limA;
        novo_a += mutacao;
    
    } else {
        float limB = limitesAB->diferencaB * 0.5;
        float mutacao = (((float) rand() / RAND_MAX) - 0.5) * limB;
        novo_b += mutacao;
            
    }

    novoIndividuoMut->a = novo_a;
    novoIndividuoMut->b = novo_b;
    novoIndividuoMut->fitness = NAN;
}

void mutacaoT(Individuo bom, Individuo *novoIndividuoMut, float aleatoriedade, Limites *limitesAB){
    float novo_a = bom.a;
    float novo_b = bom.b;

    novoIndividuoMut->a = bom.a;
    novoIndividuoMut->b = bom.b;

    if(aleatoriedade < 0.5f){
        float rangeA = (limitesAB->maiorA - limitesAB->menorA);
        float mutacaoA = (((float) rand() / RAND_MAX) - 0.5f) * rangeA * 0.1f;
        novo_a += mutacaoA;

        if(novo_a < limitesAB->menorA){
            novo_a = limitesAB->menorA;
        } 
        if(novo_a > limitesAB->maiorA){
            novo_a = limitesAB->maiorA;
        } 

    } else {
        float rangeB = limitesAB->diferencaB;
        float mutacaoB = (((float) rand() / RAND_MAX) - 0.5f) * rangeB * 0.1f;
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


int evoluir_individuos(Individuo *populacao, DadosEntrada *dadosEntrada, Limites *limitesAB, Individuo *individuos_ordenados, Individuo *nova_pop){
    // selecionar os 50% piores
    int num_individuosPiores = dadosEntrada->m / 2;
    int num_individuosMelhores = dadosEntrada->m - num_individuosPiores;
    
    int num_individuosCross = num_individuosPiores * 0.3;
    int num_individuosMut = num_individuosPiores - num_individuosCross;

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
        mutacaoT(bom, &novoIndividuoMut, aleatoriedade, limitesAB);
        nova_pop[i] = novoIndividuoMut;
    }

    for(int i=num_individuosPiores;i<dadosEntrada->m;i++){
        nova_pop[i] = individuos_ordenados[i];
        nova_pop[i].fitness = NAN;
    }
    return 0;
}

int rodar_algoritmo_genetico(Individuo *populacao, DadosEntrada *dadosEntrada, Limites *limitesAB){
    for(int i=0;i<dadosEntrada->G;i++){
        avaliar_individuos(dadosEntrada, populacao);

        // ordenar indivíduos
        Individuo *individuos_ordenados;
        individuos_ordenados = malloc(dadosEntrada->m * sizeof(Individuo));
        if (individuos_ordenados == NULL){
            printf("\nErro na alocação de memória para armazenar os indivíduos ordenados.\n");
            return 1;
        }
    
        ordenar_individuos_fitness(dadosEntrada, populacao, individuos_ordenados);
        int melhor = dadosEntrada->m - 1;

        Individuo *nova_pop;
        nova_pop = malloc(dadosEntrada->m * sizeof(Individuo));
        
        GravarDados gravarDados;
        gravarDados.geracao = i + 1;
        gravarDados.a = individuos_ordenados[melhor].a;
        gravarDados.b = individuos_ordenados[melhor].b;
        gravarDados.fitness = individuos_ordenados[melhor].fitness;
        gravarDados.erro = (1 / individuos_ordenados[melhor].fitness) -1;
        gravar_arquivo(&gravarDados);
        printf("\nMelhor %d: (%f %f %f)\n", i+1,
            individuos_ordenados[melhor].a,
            individuos_ordenados[melhor].b,
            individuos_ordenados[melhor].fitness);
        int evoluiu = evoluir_individuos(populacao, dadosEntrada, limitesAB, individuos_ordenados, nova_pop);
        if (evoluiu == 1){
            return 1;
        }

        for(int i=0;i<dadosEntrada->m;i++){
            populacao[i] = nova_pop[i];
        }
        free(individuos_ordenados);

    }
    return 0;
}


int evoluir_individuos1(Individuo *populacao, DadosEntrada *dadosEntrada, Limites *limitesAB, Individuo *individuos_ordenados, Individuo *nova_pop){
    // deixando só os 2 melhores na evolução
    int num_individuosPiores = dadosEntrada->m - 2;
    int metade_pop = dadosEntrada->m /2;
    
    int num_individuosCross = num_individuosPiores * 0.3;
    int num_individuosMut = num_individuosPiores - num_individuosCross;

    for(int i=0;i<num_individuosCross;i++){
        Individuo novoIndividuoCross, pai1, pai2;
        float aleatoriedade = (float) rand() / RAND_MAX;

        int posicao1, posicao2;
        do {
            posicao1 = metade_pop + rand() % (dadosEntrada->m - metade_pop);
            posicao2 = metade_pop + rand() % (dadosEntrada->m - metade_pop);
        } while(posicao1 == posicao2);
        pai1 = individuos_ordenados[posicao1];
        pai2 = individuos_ordenados[posicao2];
        crossover(pai1, pai2, &novoIndividuoCross, aleatoriedade);
        nova_pop[i] = novoIndividuoCross;
    }

    int posicaoAnterior = -1;
    for(int i=num_individuosCross;i<num_individuosPiores;i++){
        Individuo novoIndividuoMut, bom;
        float aleatoriedade = (float) rand() / RAND_MAX;

        int posicao1;
        do {
            posicao1 = metade_pop + rand() % (dadosEntrada->m - metade_pop);
        } while(posicao1 == posicaoAnterior);
        posicaoAnterior = posicao1;
        bom = individuos_ordenados[posicao1];
        mutacao(bom, &novoIndividuoMut, aleatoriedade, limitesAB);
        nova_pop[i] = novoIndividuoMut;
    }

    nova_pop[dadosEntrada->m -1] = individuos_ordenados[dadosEntrada->m -1];
    nova_pop[dadosEntrada->m -1].fitness = NAN;
    nova_pop[dadosEntrada->m -2] = individuos_ordenados[dadosEntrada->m -2];
    nova_pop[dadosEntrada->m -2].fitness = NAN;
    return 0;
}
