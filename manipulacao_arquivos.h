#ifndef MANIPULACAO_ARQUIVOS_H
#define MANIPULACAO_ARQUIVOS_H

// todas as funções que envolvem manipulação de arquivos estarão aqui, desconsidere o retorno e os parâmetros, a ideia é apenas
// organizar o que ficará em cada módulo, no desenvolvimento esses aspectos serão resolvidos.

typedef struct ponto{
    float x;
    float y;
} Ponto;

typedef struct dadosEntrada{
    int n;
    int m;
    int G;
    Ponto *pontos;
} DadosEntrada;

int ler_arquivo(const char *input, DadosEntrada *dadosEntrada);
void gravar_arquivo(const char *output);

#endif /* MANIULACAO_ARQUIVOS_H */