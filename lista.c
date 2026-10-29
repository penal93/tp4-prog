#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* coloque demais includes aqui */

/* ------------------- Nao altere estas structs ------------------------- */
struct nodo {
    int chave;
    struct nodo *prox;
};

struct lista {
    struct nodo *ini;
    struct nodo *ptr; /* ponteiro para algum nodo da lista (iterador) */
    int tamanho;

};
/* ---------------------------------------------------------------------- */

struct lista *lista_cria (){
    struct lista *novaLista = malloc (sizeof(struct lista));

    if (!novaLista)
        return NULL;

    memset (novaLista, 0, sizeof(struct lista));

    return novaLista;
}

void lista_destroi (struct lista **lista){
    if (lista_vazia(*lista))
        return;

    struct nodo *atual = (*lista)->ini;
    
    for (int i = 0; i < (*lista)->tamanho; i++){
        struct nodo *prox = atual->prox;
        free(atual);
        atual = NULL;
        atual = prox;
    }

    free(*lista);
    (*lista) = NULL;
}

int lista_insere_inicio (struct lista *lista, int chave){
    struct nodo *novoElemento = malloc (sizeof(struct nodo));

    if (!novoElemento)
        return 0;

    novoElemento->chave = chave;
    
    if (lista->tamanho == 0)
        novoElemento->prox = NULL;
    
    else 
        novoElemento->prox = lista->ini;

    lista->ini = novoElemento;
    lista->tamanho ++;

    return 1;
}

int lista_insere_fim (struct lista *lista, int chave){
    struct nodo *novoElemento = malloc (sizeof(struct nodo));

    if (!novoElemento)
        return 0;

    lista_inicia_iterador(lista);
    for (int i = 0; i < lista->tamanho; i++)
        lista_incrementa_iterador(lista, &chave);

    novoElemento->chave = chave;
    novoElemento->prox = NULL;
    
    lista->ptr->prox = novoElemento;
    lista->tamanho ++;

    return 1;
}

int lista_insere_ordenado (struct lista *lista, int chave){
    struct nodo *atual = lista->ini;
    struct nodo *ant = NULL;

    while (atual->chave < chave){
        ant = atual;
        atual = atual->prox;
    }

    struct nodo *novoElemento = malloc (sizeof(struct nodo));

    if (!novoElemento)
        return 0;

    ant->prox = novoElemento;
    novoElemento->prox = atual;

    return 1;
}

int lista_remove_inicio (struct lista *lista, int *chave){
    if (!lista_tamanho(lista))
        return 0;

    *chave = lista->ini->chave;

    struct nodo *removido = lista->ini;
    lista->ini = lista->ini->prox;

    free(removido);
    removido = NULL;

    return 1;
}

int lista_remove_fim (struct lista *lista, int *chave){
    if (!lista_tamanho(lista))
        return 0;

    lista_inicia_iterador(lista);
    for (int i = 0; i < lista->tamanho - 1; i++)
        lista_incrementa_iterador(lista, chave);

    *chave = lista->ptr->prox->chave;
    free(lista->ptr->prox);
    lista->ptr->prox = NULL;

    return 1;
}

int lista_remove_ordenado (struct lista *lista, int chave){
    if (lista_vazia(lista))
        return 0;

    struct nodo *atual = lista->ini;
    struct nodo *ant = NULL;

    while (atual->chave != chave){
        ant = atual;
        atual = atual->prox;
    }
        
    ant->prox = atual->prox;
    free(atual);
    atual = NULL;

    return 1;
}

int lista_vazia (struct lista *lista){
    if (lista->tamanho == 0)
        return 1;

    return 0;
}

int lista_tamanho (struct lista *lista){
    return lista->tamanho;
}

int lista_pertence (struct lista *lista, int chave){
    struct nodo *atual = lista->ini;

    while (atual != NULL){
        if (atual->chave == chave)
            return 1;

        atual = atual->prox;
    }

    return 0;
}

void lista_inicia_iterador (struct lista *lista){
    lista->ptr = lista->ini;
}

int lista_incrementa_iterador (struct lista *lista, int *chave){
    *chave = lista->ptr->chave;

    if (!lista->ptr->prox)
        return 0;

    lista->ptr = lista->ptr->prox;

    return 1;
}
