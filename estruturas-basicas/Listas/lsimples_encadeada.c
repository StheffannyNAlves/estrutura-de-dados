#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int elemento;
    struct no *prox;
} celula;

int inserirInicio(celula **ini, int valor) {
    celula *novo = malloc(sizeof(celula));
    if (novo == NULL) return 1;
    novo->elemento = valor;
    novo->prox = *ini;
    *ini = novo;
    return 0;
}

int inserirFim(celula **ini, int valor) {
    celula *novo = malloc(sizeof(celula));
    if (novo == NULL) return 1;
    novo->elemento = valor;
    novo->prox = NULL;

    if (*ini == NULL) {
        *ini = novo;
        return 0;
    }
    celula *atual = *ini;
    while (atual->prox != NULL) atual = atual->prox;
    atual->prox = novo;
    return 0;
}

// remove a primeira ocorrencia do valor. Retorna 0 se removeu, 1 se nao achou.
int removerValor(celula **ini, int valor) {
    celula *atual = *ini;
    celula *anterior = NULL;

    while (atual != NULL && atual->elemento != valor) {
        anterior = atual;
        atual = atual->prox;
    }
    if (atual == NULL) return 1;

    if (anterior == NULL)
        *ini = atual->prox;
    else
        anterior->prox = atual->prox;

    free(atual);
    return 0;
}

int buscar(celula *ini, int valor) {
    celula *atual = ini;
    while (atual != NULL) {
        if (atual->elemento == valor) return 1;
        atual = atual->prox;
    }
    return 0;
}

void imprimirLista(celula *ini) {
    celula *atual = ini;
    while (atual != NULL) {
        printf("%d ", atual->elemento);
        atual = atual->prox;
    }
    printf("\n");
}

void liberarLista(celula **ini) {
    celula *temp;
    while (*ini != NULL) {
        temp = *ini;
        *ini = (*ini)->prox;
        free(temp);
    }
}

int main() {
    celula *ini = NULL;

    inserirFim(&ini, 10);
    inserirFim(&ini, 20);
    inserirFim(&ini, 30);
    inserirInicio(&ini, 5);
    printf("Lista: "); imprimirLista(ini);

    removerValor(&ini, 20);
    printf("Apos remover 20: "); imprimirLista(ini);

    printf("Busca 30: %d (esperado 1)\n", buscar(ini, 30));
    printf("Busca 99: %d (esperado 0)\n", buscar(ini, 99));

    liberarLista(&ini);
    printf("ini=%p (esperado 0x0)\n", (void*)ini);
    return 0;
}