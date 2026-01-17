#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CAP.H"

// Inicializa a lista sequencial de CAPs
void inicializarListaCaps(ListaCaps *lista, int capacidade) {
    lista->caps = malloc(capacidade * sizeof(cap));
    if (lista->caps == NULL) {
        printf("Erro: Falha ao alocar memoria para CAPs\n");
        exit(1);
    }

    lista->numCAPs = 0;
    lista->capacidade = capacidade;

    for (int i = 0; i < capacidade; i++) {
        lista->caps[i].idCAP = -1;
        lista->caps[i].eleitoresCadastrados = 0;
        inicializarFila(&lista->caps[i]);
    }
}

void liberarListaCaps(ListaCaps *lista) {
    free(lista->caps);
    lista->caps = NULL;
    lista->numCAPs = 0;
    lista->capacidade = 0;
}

// Cria um CAP
cap criarCAP(int idCAP, const char *localizacao, int numUrnas, int maxEleitoresPorUrna) {
    cap novo;
    novo.idCAP = idCAP;

    strncpy(novo.localizacao, localizacao, sizeof(novo.localizacao) - 1);
    novo.localizacao[sizeof(novo.localizacao) - 1] = '\0';

    novo.numUrnas = numUrnas;
    novo.maxEleitoresPorUrna = maxEleitoresPorUrna;
    novo.eleitoresCadastrados = 0;

    inicializarFila(&novo);
    return novo;
}

// Insere um CAP na lista
int inserirCAP(ListaCaps *lista, cap novo) {
    if (lista->numCAPs >= lista->capacidade) {
        printf("Erro: Limite maximo de CAPs atingido (%d)\n", lista->capacidade);
        return 0;
    }

    for (int i = 0; i < lista->numCAPs; i++) {
        if (lista->caps[i].idCAP == novo.idCAP) {
            printf("Erro: Ja existe um CAP com ID %d\n", novo.idCAP);
            return 0;
        }
    }

    lista->caps[lista->numCAPs++] = novo;
    return 1;
}

// Busca um CAP
cap *buscarCAP(ListaCaps *lista, int id) {
    for (int i = 0; i < lista->numCAPs; i++) {
        if (lista->caps[i].idCAP == id) {
            return &lista->caps[i];
        }
    }
    return NULL;
}

// Capacidade total
int capacidadeTotalCAP(cap *c) {
    if (c == NULL) return 0;
    return c->numUrnas * c->maxEleitoresPorUrna;
}
