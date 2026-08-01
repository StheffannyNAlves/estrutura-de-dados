#include <stdio.h>
#include <stdlib.h>

#define TAMANHO 10

typedef struct no {
    int chave;
    struct no *prox;
} celula;

typedef struct {
    celula *buckets[TAMANHO];
} tabelaHash;

int funcaoHash(int chave) {
    return chave % TAMANHO;
}

void inicializar(tabelaHash *t) {
    for (int i = 0; i < TAMANHO; i++)
        t->buckets[i] = NULL;
}

int inserir(tabelaHash *t, int chave) {
    int idx = funcaoHash(chave);

    // evita duplicata
    celula *atual = t->buckets[idx];
    while (atual != NULL) {
        if (atual->chave == chave) return 1; // ja existe
        atual = atual->prox;
    }

    celula *novo = malloc(sizeof(celula));
    if (novo == NULL) return 2; // falha de alocacao
    novo->chave = chave;
    novo->prox = t->buckets[idx];
    t->buckets[idx] = novo;
    return 0;
}

int buscar(tabelaHash *t, int chave) {
    int idx = funcaoHash(chave);
    celula *atual = t->buckets[idx];
    while (atual != NULL) {
        if (atual->chave == chave) return 1;
        atual = atual->prox;
    }
    return 0;
}

int remover(tabelaHash *t, int chave) {
    int idx = funcaoHash(chave);
    celula *atual = t->buckets[idx];
    celula *anterior = NULL;

    while (atual != NULL && atual->chave != chave) {
        anterior = atual;
        atual = atual->prox;
    }
    if (atual == NULL) return 1; // nao encontrado

    if (anterior == NULL)
        t->buckets[idx] = atual->prox;
    else
        anterior->prox = atual->prox;

    free(atual);
    return 0;
}

void imprimir(tabelaHash *t) {
    for (int i = 0; i < TAMANHO; i++) {
        printf("bucket %d: ", i);
        celula *atual = t->buckets[i];
        while (atual != NULL) {
            printf("%d -> ", atual->chave);
            atual = atual->prox;
        }
        printf("NULL\n");
    }
}

void liberar(tabelaHash *t) {
    for (int i = 0; i < TAMANHO; i++) {
        celula *atual = t->buckets[i];
        while (atual != NULL) {
            celula *temp = atual;
            atual = atual->prox;
            free(temp);
        }
        t->buckets[i] = NULL;
    }
}

int main() {
    tabelaHash t;
    inicializar(&t);

    inserir(&t, 10);
    inserir(&t, 20);
    inserir(&t, 25);
    inserir(&t, 7);
    inserir(&t, 17); // colide com 7 (17%10==7%10)

    imprimir(&t);

    printf("Busca 20: %d (esperado 1)\n", buscar(&t, 20));
    printf("Busca 99: %d (esperado 0)\n", buscar(&t, 99));

    remover(&t, 20);
    printf("Apos remover 20, busca 20: %d (esperado 0)\n", buscar(&t, 20));
    printf("Bucket 0 apos remocao: ");
    celula *a = t.buckets[0];
    while (a != NULL) { printf("%d -> ", a->chave); a = a->prox; }
    printf("NULL (esperado so 10)\n");

    printf("Inserir 10 de novo (duplicata): %d (esperado 1)\n", inserir(&t, 10));

    liberar(&t);
    return 0;
}