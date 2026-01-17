#ifndef CAP_H
#define CAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "ELEITOR.H"
#define MAX_ELEITORES_FILA 100 // tamanho mximo da fila do CAP
#define MAX_CAPS 4

typedef struct cap cap; // forward declaration do CAP

typedef struct ListaCaps {
    cap *caps;       // ponteiro para array de CAPs
    int numCAPs;     // número atual de CAPs cadastrados
    int capacidade;  // capacidade máxima do array
} ListaCaps;

typedef struct cap {
    int idCAP;                          
    char localizacao[50];            
    int numUrnas;                     
    int maxEleitoresPorUrna;          // quantidade máxima de eleitores por urna
    int tamanhoFila; // qtd de eleitores
       int eleitoresCadastrados;
    eleitor *fila[MAX_ELEITORES_FILA];    // fila sequencial de ponteiros para eleitores
     
  
   
} cap;





// Funcao criarnovocap
void inicializarListaCaps(ListaCaps *lista,int capacidade);
cap criarCAP(int idCAP, const char *localizacao, int numUrnas, int maxEleitoresPorUrna);
void inicializarFila(cap *c);
int filaVazia(cap *c);
int filaCheia(cap *c);
int enfileirar(cap *c, eleitor *e);
eleitor *desenfileirar(cap *c);
void listarFila(cap *c);
void listarCAPS(ListaCaps *lista); 
int inserirCAP(ListaCaps *lista, cap novo);
cap *buscarCAP(ListaCaps *lista, int id);
int capacidadeTotalCAP(cap *c);
void liberarListaCaps(ListaCaps *lista);
#endif
