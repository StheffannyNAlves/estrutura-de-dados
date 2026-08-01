#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int chave;
    struct no *esq;
    struct no *dir;
    int altura;
} no;

int max(int a, int b) { return a > b ? a : b; }

int altura(no *n) {
    return n == NULL ? -1 : n->altura;
}

int fatorBalanceamento(no *n) {
    return n == NULL ? 0 : altura(n->esq) - altura(n->dir);
}

no *criarNo(int chave) {
    no *novo = malloc(sizeof(no));
    novo->chave = chave;
    novo->esq = NULL;
    novo->dir = NULL;
    novo->altura = 0;
    return novo;
}

no *rotacaoDireita(no *y) {
    no *x = y->esq;
    no *t2 = x->dir;

    x->dir = y;
    y->esq = t2;

    y->altura = max(altura(y->esq), altura(y->dir)) + 1;
    x->altura = max(altura(x->esq), altura(x->dir)) + 1;

    return x;
}

no *rotacaoEsquerda(no *x) {
    no *y = x->dir;
    no *t2 = y->esq;

    y->esq = x;
    x->dir = t2;

    x->altura = max(altura(x->esq), altura(x->dir)) + 1;
    y->altura = max(altura(y->esq), altura(y->dir)) + 1;

    return y;
}

no *inserir(no *raiz, int chave) {
    if (raiz == NULL)
        return criarNo(chave);

    if (chave < raiz->chave)
        raiz->esq = inserir(raiz->esq, chave);
    else if (chave > raiz->chave)
        raiz->dir = inserir(raiz->dir, chave);
    else
        return raiz; // chave duplicada, nao insere

    raiz->altura = max(altura(raiz->esq), altura(raiz->dir)) + 1;
    int fb = fatorBalanceamento(raiz);

    // caso LL
    if (fb > 1 && chave < raiz->esq->chave)
        return rotacaoDireita(raiz);

    // caso RR
    if (fb < -1 && chave > raiz->dir->chave)
        return rotacaoEsquerda(raiz);

    // caso LR
    if (fb > 1 && chave > raiz->esq->chave) {
        raiz->esq = rotacaoEsquerda(raiz->esq);
        return rotacaoDireita(raiz);
    }

    // caso RL
    if (fb < -1 && chave < raiz->dir->chave) {
        raiz->dir = rotacaoDireita(raiz->dir);
        return rotacaoEsquerda(raiz);
    }

    return raiz;
}

void emOrdem(no *raiz) {
    if (raiz == NULL) return;
    emOrdem(raiz->esq);
    printf("%d ", raiz->chave);
    emOrdem(raiz->dir);
}

// verifica recursivamente se a arvore esta balanceada (fb entre -1 e 1 em todo no)
int estaBalanceada(no *raiz) {
    if (raiz == NULL) return 1;
    int fb = fatorBalanceamento(raiz);
    if (fb < -1 || fb > 1) return 0;
    return estaBalanceada(raiz->esq) && estaBalanceada(raiz->dir);
}

void liberar(no *raiz) {
    if (raiz == NULL) return;
    liberar(raiz->esq);
    liberar(raiz->dir);
    free(raiz);
}

void testarCaso(const char *nome, int chaves[], int n) {
    no *raiz = NULL;
    for (int i = 0; i < n; i++)
        raiz = inserir(raiz, chaves[i]);

    printf("%s -> em ordem: ", nome);
    emOrdem(raiz);
    printf("| raiz: %d | altura raiz: %d | balanceada: %s\n",
           raiz->chave, raiz->altura, estaBalanceada(raiz) ? "sim" : "nao");

    liberar(raiz);
}

int main() {
    int casoLL[] = {30, 20, 10};              // forca rotacao simples direita
    int casoRR[] = {10, 20, 30};              // forca rotacao simples esquerda
    int casoLR[] = {30, 10, 20};              // forca rotacao dupla esq-dir
    int casoRL[] = {10, 30, 20};              // forca rotacao dupla dir-esq
    int casoGrande[] = {50, 25, 75, 10, 30, 60, 90, 5, 15, 27, 35};

    testarCaso("LL", casoLL, 3);
    testarCaso("RR", casoRR, 3);
    testarCaso("LR", casoLR, 3);
    testarCaso("RL", casoRL, 3);
    testarCaso("caso maior (11 chaves)", casoGrande, 11);

    return 0;
}