#include "ELEITOR.H"
#include "CAP.H"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//funcao criar novo no
eleitor *criareleitor(int id, char *nome, int bi, int idcap, int prioridade) {
    eleitor *novo = malloc(sizeof(eleitor));
    if (novo == NULL) return NULL;

    novo->id = id;

    strncpy(novo->nome, nome, sizeof(novo->nome) - 1);
    novo->nome[sizeof(novo->nome) - 1] = '\0';

    novo->bi = bi;
    novo->idcap = idcap;
    novo->estadovoto = 0;
    novo->prioridade = prioridade;
    novo->prox = NULL;

    return novo;
}

 //funcao inserir no fim pra poder manter a ordem de chgada
  int inserireleitor(eleitor *cabecaeleitor, ListaCaps *listaCaps, int id, char *nome, int bi, int idcap, int prioridade) {
    // 1. Verifica se CAP existe
    cap *capDestino = buscarCAP(listaCaps, idcap);
    if (capDestino == NULL) {
        printf("Erro: CAP com ID %d nao existe!\n", idcap);
        return 0;
    }

    // 2. Verifica se CAP já atingiu capacidade máxima
    int capacidadeMaxima = capacidadeTotalCAP(capDestino);
    if (capDestino->eleitoresCadastrados >= capacidadeMaxima) {
        printf("Erro: CAP %d (%s) atingiu capacidade maxima de %d eleitores!\n",
               idcap, capDestino->localizacao, capacidadeMaxima);
        printf("Capacidade atual: %d/%d eleitores\n", 
               capDestino->eleitoresCadastrados, capacidadeMaxima);
        return 0;
    }

    // 3. Verifica se já existe eleitor com mesmo ID ou BI
    eleitor *aux = cabecaeleitor->prox;
    while (aux != NULL) {
        if (aux->id == id || aux->bi == bi) {
            printf("Erro: Eleitor com ID %d ou BI %d ja existe!\n", id, bi);
            return 0;
        }
        aux = aux->prox;
    }

    // 4. Cria novo eleitor
    eleitor *novo = criareleitor(id, nome, bi, idcap, prioridade);
    if (novo == NULL) {
        printf("Erro: Falha na alocacao de memoria!\n");
        return 0;
    }

    // 5. Insere na lista de eleitores (no final)
    if (cabecaeleitor->prox == NULL) {
        cabecaeleitor->prox = novo;
    } else {
        aux = cabecaeleitor->prox;
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        aux->prox = novo;
    }

    // 6. Incrementa contador de eleitores no CAP
    capDestino->eleitoresCadastrados++;

    printf("Sucesso: Eleitor %s cadastrado no CAP %d (%s)\n", 
           nome, idcap, capDestino->localizacao);
    printf("Capacidade do CAP: %d/%d eleitores\n",
           capDestino->eleitoresCadastrados, capacidadeMaxima);

    return 1;
}



// funcao buscar eleitor
eleitor *buscareleitor(eleitor *cabecaeleitor,int id){
eleitor *aux = cabecaeleitor->prox;// aux agr aponta para o primeiro no real
while(aux!=NULL){
 if(aux->id==id){
    return aux; //quer dizer encontrou o eleitor
 }
aux=aux->prox;
}
return NULL; // nao encontrou
}
// marcar voto se ainda nao votou, tds eleitores comcam com estadovoto 0
int marcarvoto(eleitor *cabecaeleitor,int id){
 eleitor *eleitor=buscareleitor(cabecaeleitor,id);
 if(eleitor==NULL){
    return 0;
 }
 if(eleitor->estadovoto==1){ 
    return 0;
 }
  eleitor->estadovoto=1;
  
  return 1;
}

void listareleitores(eleitor *cabecaeleitor) {
    eleitor *aux = cabecaeleitor->prox;  // inicia no primeiro no real

    if(aux == NULL) {
        printf("Nenhum eleitor cadastrado.\n");
        return;
    }

    printf("Lista de Eleitores:\n");
    printf("ID | Nome                 | BI       | CAP | Votou  | PRIORIDADE\n");
    printf("---------------------------------------------------\n");

    while (aux != NULL) {
        printf("%-3d | %-20s | %-8d | %1d | %s| %-1d\n ",
               aux->id,
               aux->nome,
               aux->bi,
               aux->idcap,
               aux->estadovoto ? "Sim" : "Nao",
               aux->prioridade);

        aux = aux->prox;
    }
}

int removereleitor(eleitor *cabecaeleitor, ListaCaps *listaCaps, int id) {
    if (cabecaeleitor == NULL) return 0;

    eleitor *anterior = cabecaeleitor;
    eleitor *atual = cabecaeleitor->prox;

    while (atual != NULL) {
        if (atual->id == id) {

            cap *capDoEleitor = buscarCAP(listaCaps, atual->idcap);

            // REMOVE DA FILA DO CAP
            if (capDoEleitor != NULL) {
                for (int i = 0; i < capDoEleitor->tamanhoFila; i++) {
                    if (capDoEleitor->fila[i] == atual) {
                        // desloca fila
                        for (int j = i + 1; j < capDoEleitor->tamanhoFila; j++) {
                            capDoEleitor->fila[j - 1] = capDoEleitor->fila[j];
                        }
                        capDoEleitor->fila[capDoEleitor->tamanhoFila - 1] = NULL;
                        capDoEleitor->tamanhoFila--;
                        break;
                    }
                }
                capDoEleitor->eleitoresCadastrados--;
            }

            anterior->prox = atual->prox;
            free(atual);
            return 1;
        }

        anterior = atual;
        atual = atual->prox;
    }

    return 0;
}
