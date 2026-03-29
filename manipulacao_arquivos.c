#include <stdio.h>
#include <stdlib.h>
#include "manipulacao_arquivos.h"

// funções para manipular todas as interações com arquivos


int ler_arquivo(const char *input, DadosEntrada *dadosEntrada){
    // permite extrair todos os dados do input.dat e armazenar em variáveis para serem utilizados
    // n m G (n = quantidade de pontos; m = tamanho da população; G = número de gerações)
    // x1 y1 (pontos)

    FILE *arquivo;
    arquivo = fopen(input, "r");
    if(arquivo == NULL){
        printf("\nErro ao abrir o arquivo de entrada de dados.\n");
        return 1;
    }

    if(fscanf(arquivo, "%d %d %d", &dadosEntrada->n, &dadosEntrada->m, &dadosEntrada->G) != 3 || 
     dadosEntrada->n <= 0 || dadosEntrada->m <= 0 || dadosEntrada->G <= 0){
        printf("\nErro ao ler a primeira linha do arquivo de entrada de dados.\n");
        fclose(arquivo);
        return 1;
    }
    

    dadosEntrada->pontos = malloc(dadosEntrada->n * sizeof(Ponto));
    if(dadosEntrada->pontos == NULL){
        printf("\nErro ao alocar memória para armazenar os pontos da entrada de dados.\n");
        fclose(arquivo);
        return 1;
    }


    int pontos_lidos = 0;
    for(int i=0; i<dadosEntrada->n; i++){
        if(fscanf(arquivo, "%f %f", &dadosEntrada->pontos[i].x, &dadosEntrada->pontos[i].y) == 2){
            pontos_lidos += 1;
        }
    }

    if(dadosEntrada->n != pontos_lidos){
        printf("\nErro ao ler os pontos do arquivo de entrada de dados.\n");
        fclose(arquivo);
        free(dadosEntrada->pontos);
        dadosEntrada->pontos = NULL;
        return 1;
    } 


    fclose(arquivo);
    return 0;
}


void gravar_arquivo(GravarDados *d){
    // permite registrar todas as informações a respeito do fitness, a e b, erro e geração
    FILE *arq = fopen("output.dat", "a");
    fprintf(arq, "GERAÇÃO %d:  (a = %f, b = %f)   | ERRO: %f   | MELHOR FITNESS: %f\n", d->geracao, d->a, d->b, d->erro, d->fitness);
    fclose(arq);
}