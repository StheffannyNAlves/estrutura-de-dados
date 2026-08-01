#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int elemento;
    struct no *prox;
    struct no *ant;
} celula;

int inserirInicio(celula **ini, celula **fim, int valor) {
    celula *novo = malloc(sizeof(celula));
    if (novo == NULL) return 1;
    novo->elemento = valor;
    novo->ant = NULL;
    novo->prox = *ini;

    if (*ini != NULL)
        (*ini)->ant = novo;
    else
        *fim = novo;

    *ini = novo;
    return 0;
}

int inserirFim(celula **ini, celula **fim, int valor) {
    celula *novo = malloc(sizeof(celula));
    if (novo == NULL) return 1;
    novo->elemento = valor;
    novo->prox = NULL;
    novo->ant = *fim;

    if (*fim != NULL)
        (*fim)->prox = novo;
    else
        *ini = novo;

    *fim = novo;
    return 0;
}

// remove a primeira ocorrencia do valor. Retorna 0 se removeu, 1 se nao achou.
int removerValor(celula **ini, celula **fim, int valor) {
    celula *atual = *ini;
    while (atual != NULL && atual->elemento != valor)
        atual = atual->prox;

    if (atual == NULL) return 1;

    if (atual->ant != NULL)
        atual->ant->prox = atual->prox;
    else
        *ini = atual->prox;

    if (atual->prox != NULL)
        atual->prox->ant = atual->ant;
    else
        *fim = atual->ant;

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

void imprimirFrente(celula *ini) {
    celula *atual = ini;
    while (atual != NULL) {
        printf("%d ", atual->elemento);
        atual = atual->prox;
    }
    printf("\n");
}

void imprimirTras(celula *fim) {
    celula *atual = fim;
    while (atual != NULL) {
        printf("%d ", atual->elemento);
        atual = atual->ant;
    }
    printf("\n");
}

void liberarLista(celula **ini, celula **fim) {
    celula *temp;
    while (*ini != NULL) {
        temp = *ini;
        *ini = (*ini)->prox;
        free(temp);
    }
    *fim = NULL;
}

int main() {
    celula *ini = NULL, *fim = NULL;

    inserirFim(&ini, &fim, 10);
    inserirFim(&ini, &fim, 20);
    inserirFim(&ini, &fim, 30);
    inserirInicio(&ini, &fim, 5);

    printf("Frente->tras:  "); imprimirFrente(ini);
    printf("Tras->frente:  "); imprimirTras(fim);

    removerValor(&ini, &fim, 20);
    printf("Apos remover 20 (frente->tras): "); imprimirFrente(ini);
    printf("Apos remover 20 (tras->frente): "); imprimirTras(fim);

    removerValor(&ini, &fim, 5);  // remove o primeiro
    printf("Apos remover 5 (o primeiro): "); imprimirFrente(ini);

    removerValor(&ini, &fim, 30); // remove o ultimo
    printf("Apos remover 30 (o ultimo): "); imprimirFrente(ini);

    printf("Busca 10: %d (esperado 1)\n", buscar(ini, 10));

    liberarLista(&ini, &fim);
    printf("ini=%p fim=%p (esperado ambos 0x0)\n", (void*)ini, (void*)fim);
    return 0;
}