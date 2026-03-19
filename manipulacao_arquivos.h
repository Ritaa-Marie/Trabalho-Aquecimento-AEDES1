#ifndef MANIPULACAO_ARQUIVOS_H
#define MANIPULACAO_ARQUIVOS_H

// todas as funções que envolvem manipulação de arquivos estarão aqui, desconsidere o retorno e os parâmetros, a ideia é apenas
// organizar o que ficará em cada módulo, no desenvolvimento esses aspectos serão resolvidos.

typedef struct ponto{
    float x;
    float y;
} Ponto;

typedef struct dadosEntrada{
    int m;
    int n;
    int G;
    Ponto *pontos ;
} DadosEntrada;

void ler_arquivo();
void gravar_arquivo();

#endif /* MANIULACAO_ARQUIVOS_H */