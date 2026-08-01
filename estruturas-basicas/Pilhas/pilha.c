#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int elemento;
    struct no *prox;
} celula;

int empilhar(celula **topo, int valor) {
    celula *novo = malloc(sizeof(celula));
    if (novo == NULL) return 1;
    novo->elemento = valor;
    novo->prox = *topo;
    *topo = novo;
    return 0;
}

int desempilhar(celula **topo, int *valorRemovido) {
    if (*topo == NULL) return 1;
    celula *temp = *topo;
    *valorRemovido = temp->elemento;
    *topo = temp->prox;
    free(temp);
    return 0;
}

int pilhaVazia(celula *topo) {
    return topo == NULL ? 1 : 0;
}

void liberarPilha(celula **topo) {
    celula *temp;
    while (*topo != NULL) {
        temp = *topo;
        *topo = (*topo)->prox;
        free(temp);
    }
}

int main() {
    celula *topo = NULL;
    int valor;

    empilhar(&topo, 10);
    empilhar(&topo, 20);
    empilhar(&topo, 30);

    while (!pilhaVazia(topo)) {
        desempilhar(&topo, &valor);
        printf("Desempilhado: %d\n", valor);
    }

    empilhar(&topo, 1);
    empilhar(&topo, 2);
    liberarPilha(&topo);
    printf("topo=%p (esperado 0x0)\n", (void*)topo);
    return 0;
}