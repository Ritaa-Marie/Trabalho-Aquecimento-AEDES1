#include <stdio.h>
#include <stdlib.h>
#include "algoritmo_genetico.h"
#include "manipulacao_arquivos.h"

int main(){

    DadosEntrada dadosEntrada;

    int leituraDados = ler_arquivo("input.dat", &dadosEntrada);
    if (leituraDados == 0){
        printf("%f %f", dadosEntrada.pontos[3].x, dadosEntrada.pontos[3].y); //teste
        printf("%d", dadosEntrada.n);
        return 0;
    } else {
        return 1;
    }
    
    // alocação dinâmica do vetor da população
    //chama as funções para rodar o algoritmo
    
    free(dadosEntrada.pontos);
    return 0;
}