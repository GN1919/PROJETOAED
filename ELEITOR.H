#ifndef ELEITOR_H
#define ELEITOR_H


#include <stdio.h>
#include "CAP.H"
typedef struct eleitor{
int id;
char nome[50];
int bi;
int idcap;
int estadovoto;
 int prioridade;  // 1 idoso | 2 deficiente | 3 gravida e 0 normal
struct eleitor *prox;

}eleitor;

eleitor *criareleitor(int id,char *nome,int bi,int idcap,int prioridade);
int inserireleitor(eleitor *cabecaeleitor,ListaCaps *listaCaps,int id,char *nome,int bi,int idcap,int prioridade);
void listareleitores(eleitor *cabecaeleitor);
int marcarvoto(eleitor *cabecaeleitor,int id); 
eleitor *buscareleitor(eleitor *cabecaeleitor,int id); 
int removereleitor(eleitor *cabecaeleitor,ListaCaps *listaCaps, int id);



#endif

