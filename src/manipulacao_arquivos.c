#include <stdio.h>
#include <stdlib.h>
#include "manipulacao_arquivos.h"

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

    for(int i=0; i<dadosEntrada->n; i++){
        if(fscanf(arquivo, "%f %f", &dadosEntrada->pontos[i].x, &dadosEntrada->pontos[i].y) != 2){
            printf("\nErro ao ler os pontos do arquivo de entrada de dados.\n");
            fclose(arquivo);
            free(dadosEntrada->pontos);
            dadosEntrada->pontos = NULL;
            return 1;
        }
    }

    fclose(arquivo);
    return 0;
}


int gravar_arquivo(GravarDados *d){
    // permite registrar todas as informações a respeito do fitness, a e b, erro e geração
    FILE *arq = fopen("output.dat", "a");

    if(arq == NULL){
        printf("Erro ao abrir arquivo de gravar dados.");
        return 1;
    }

    fprintf(arq, "GERAÇÃO %d:  (a = %.6f, b = %f)   | ERRO: %.6f   | MELHOR FITNESS: %.6f\n", d->geracao, d->a, d->b, d->erro, d->fitness);
    fclose(arq);
    return 0;
}


int apagar_dados_arquivo(const char *nome_arquivo){
    // limpa o arquivo de gravação a cada vez que iniciar o algoritmo
    FILE *arq = fopen(nome_arquivo, "w");

    if(arq == NULL){
        printf("Erro ao limpar arquivo de gravação de dados.");
        return 1;
    }

    fclose(arq);
    return 0;
}