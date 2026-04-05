#ifndef MANIPULACAO_ARQUIVOS_H
#define MANIPULACAO_ARQUIVOS_H
#include "estruturas.h"

// funções para manipular todas as interações com arquivos

int ler_arquivo(const char *input, DadosEntrada *dadosEntrada);
int gravar_arquivo(GravarDados *gravarDados);
int apagar_dados_arquivo(const char *nome_arquivo);

#endif /* MANIULACAO_ARQUIVOS_H */