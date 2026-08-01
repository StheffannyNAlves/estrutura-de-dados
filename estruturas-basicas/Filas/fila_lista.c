// fila com lista
#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int elemento;
    struct no *prox;
} celula;


int enfileirar(celula **fim, int valor, celula **ini) {
    celula *novo = malloc(sizeof(celula));


    if (novo == NULL){
        return 1;
    }
    novo->elemento = valor;
    novo->prox = NULL;

    if (*fim != NULL)
        (*fim)->prox = novo;
    else
        *ini = novo;

    *fim = novo;
    return 0;

}

int desenfileirar(celula **ini, celula **fim, int *valorRemvoido){
    if (*ini == NULL){
        return 1;
    }

    celula *temp = *ini;
    *valorRemvoido = temp->elemento;
    *ini = temp->prox;
    free(temp);
    if (*ini == NULL){
        *fim = NULL;
    }
    return 0;
}

int filaVazia(celula *ini){
    if (ini == NULL){
        return 1;
    }
    else{
        return 0;
    }
    
}

void liberarFila(celula **ini, celula **fim){
    celula *temp;

    while (*ini != NULL){
        temp = *ini;
        *ini = (*ini)->prox;
        free(temp);
    }

    *fim = NULL;
}

int main() {
    celula *ini = NULL, *fim = NULL;
    int valor;

    enfileirar(&fim, 10, &ini);
    enfileirar(&fim, 20, &ini);
    enfileirar(&fim, 30, &ini);

    while (!filaVazia(ini)) {
        desenfileirar(&ini, &fim, &valor);
        printf("Removido: %d\n", valor);
    }
    if (filaVazia(ini)) {
      printf("Fila vazia.\n");
    } else {
        printf("Fila possui elementos.\n");
    }

    enfileirar(&fim, 5, &ini);
    enfileirar(&fim, 2, &ini);
    enfileirar(&fim, 3, &ini);
    liberarFila(&ini, &fim);
    return 0;
}