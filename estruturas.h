#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

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


typedef struct individuo {
    float a;
    float b;
    float fitness;
}Individuo;
 

typedef struct limites {
    float maiorX;
    float menorX;
    float maiorY;
    float menorY;
    float diferencaX;
    float diferencaY;
    float limiteA;
} Limites;

#endif /* ESTRUTURAS_H */