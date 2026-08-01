#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int chave;
    struct no *esq;
    struct no *dir;
} no;

no *criarNo(int chave) {
    no *novo = malloc(sizeof(no));
    novo->chave = chave;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

no *inserir(no *raiz, int chave) {
    if (raiz == NULL)
        return criarNo(chave);

    if (chave < raiz->chave)
        raiz->esq = inserir(raiz->esq, chave);
    else if (chave > raiz->chave)
        raiz->dir = inserir(raiz->dir, chave);
    // se for igual, nao insere duplicado

    return raiz;
}

int buscar(no *raiz, int chave) {
    if (raiz == NULL) return 0;
    if (chave == raiz->chave) return 1;
    if (chave < raiz->chave) return buscar(raiz->esq, chave);
    return buscar(raiz->dir, chave);
}

// encontra o menor valor de uma subarvore (usado na remocao com 2 filhos)
no *encontrarMinimo(no *raiz) {
    while (raiz->esq != NULL)
        raiz = raiz->esq;
    return raiz;
}

no *remover(no *raiz, int chave) {
    if (raiz == NULL) return NULL;

    if (chave < raiz->chave) {
        raiz->esq = remover(raiz->esq, chave);
    } else if (chave > raiz->chave) {
        raiz->dir = remover(raiz->dir, chave);
    } else {
        // achou o no a remover

        // caso 1: folha (nenhum filho)
        if (raiz->esq == NULL && raiz->dir == NULL) {
            free(raiz);
            return NULL;
        }

        // caso 2: um filho so -- substitui o no pelo filho que existe
        if (raiz->esq == NULL) {
            no *temp = raiz->dir;
            free(raiz);
            return temp;
        }
        if (raiz->dir == NULL) {
            no *temp = raiz->esq;
            free(raiz);
            return temp;
        }

        // caso 3: dois filhos, pega o sucessor (menor da subarvore direita),
        // copia o valor dele pra esse no, e remove o sucessor da subarvore direita
        no *sucessor = encontrarMinimo(raiz->dir);
        raiz->chave = sucessor->chave;
        raiz->dir = remover(raiz->dir, sucessor->chave);
    }
    return raiz;
}

void emOrdem(no *raiz) {
    if (raiz == NULL) return;
    emOrdem(raiz->esq);
    printf("%d ", raiz->chave);
    emOrdem(raiz->dir);
}

int altura(no *raiz) {
    if (raiz == NULL) return -1;
    int e = altura(raiz->esq);
    int d = altura(raiz->dir);
    return (e > d ? e : d) + 1;
}

void liberar(no *raiz) {
    if (raiz == NULL) return;
    liberar(raiz->esq);
    liberar(raiz->dir);
    free(raiz);
}

int main() {
    no *raiz = NULL;
    int valores[] = {50, 30, 70, 20, 40, 60, 80, 10, 25};
    int n = sizeof(valores) / sizeof(valores[0]);

    for (int i = 0; i < n; i++)
        raiz = inserir(raiz, valores[i]);

    printf("Em ordem: "); emOrdem(raiz); printf("\n");
    printf("Altura: %d\n", altura(raiz));

    printf("Busca 40: %d (esperado 1)\n", buscar(raiz, 40));
    printf("Busca 99: %d (esperado 0)\n", buscar(raiz, 99));

    // caso 1: remover folha (10, nao tem filhos)
    raiz = remover(raiz, 10);
    printf("Apos remover 10 (folha): "); emOrdem(raiz); printf("\n");

    // caso 2: remover no com 1 filho (20, so tem o 25 como filho direito agora)
    raiz = remover(raiz, 20);
    printf("Apos remover 20 (1 filho): "); emOrdem(raiz); printf("\n");

    // caso 3: remover no com 2 filhos (30, tem 25 e 40)
    raiz = remover(raiz, 30);
    printf("Apos remover 30 (2 filhos): "); emOrdem(raiz); printf("\n");

    // remover a raiz (50), que tambem tem 2 filhos
    raiz = remover(raiz, 50);
    printf("Apos remover raiz (50, 2 filhos): "); emOrdem(raiz); printf("\n");

    liberar(raiz);
    return 0;
}