#ifndef MANIPULACAO_ARQUIVOS_H
#define MANIPULACAO_ARQUIVOS_H
#include "estruturas.h"

// todas as funções que envolvem manipulação de arquivos estarão aqui, desconsidere o retorno e os parâmetros, a ideia é apenas
// organizar o que ficará em cada módulo, no desenvolvimento esses aspectos serão resolvidos.



int ler_arquivo(const char *input, DadosEntrada *dadosEntrada);
void gravar_arquivo(GravarDados *gravarDados);
int apagar_dados_arquivo(const char *nome_arquivo);

#endif /* MANIULACAO_ARQUIVOS_H */