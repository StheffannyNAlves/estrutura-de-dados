#include <stdio.h>
#include <stdlib.h>

#define T 3               
#define MAX_CHAVES (2 * T - 1)
#define MAX_FILHOS (2 * T)

typedef struct no {
    int chaves[MAX_CHAVES];
    struct no *filhos[MAX_FILHOS];
    int n;                
    int folha;            // 1 se for folha, 0 caso contrario
} no;

no *criarNo(int folha) {
    no *novo = malloc(sizeof(no));
    novo->n = 0;
    novo->folha = folha;
    for (int i = 0; i < MAX_FILHOS; i++) novo->filhos[i] = NULL;
    return novo;
}

void dividirFilho(no *pai, int i) {
    no *cheio = pai->filhos[i];
    no *novo = criarNo(cheio->folha);
    novo->n = T - 1;

    for (int j = 0; j < T - 1; j++)
        novo->chaves[j] = cheio->chaves[j + T];

    if (!cheio->folha) {
        for (int j = 0; j < T; j++)
            novo->filhos[j] = cheio->filhos[j + T];
    }
    cheio->n = T - 1;

    for (int j = pai->n; j >= i + 1; j--)
        pai->filhos[j + 1] = pai->filhos[j];
    pai->filhos[i + 1] = novo;

    for (int j = pai->n - 1; j >= i; j--)
        pai->chaves[j + 1] = pai->chaves[j];
    pai->chaves[i] = cheio->chaves[T - 1];
    pai->n++;
}

void inserirNaoCheio(no *n, int chave) {
    int i = n->n - 1;

    if (n->folha) {
        while (i >= 0 && chave < n->chaves[i]) {
            n->chaves[i + 1] = n->chaves[i];
            i--;
        }
        n->chaves[i + 1] = chave;
        n->n++;
    } else {
        while (i >= 0 && chave < n->chaves[i]) i--;
        i++;
        if (n->filhos[i]->n == MAX_CHAVES) {
            dividirFilho(n, i);
            if (chave > n->chaves[i]) i++;
        }
        inserirNaoCheio(n->filhos[i], chave);
    }
}

no *inserir(no *raiz, int chave) {
    if (raiz->n == MAX_CHAVES) {
        no *novaRaiz = criarNo(0);
        novaRaiz->filhos[0] = raiz;
        dividirFilho(novaRaiz, 0);
        inserirNaoCheio(novaRaiz, chave);
        return novaRaiz;
    }
    inserirNaoCheio(raiz, chave);
    return raiz;
}

int buscar(no *n, int chave) {
    if (n == NULL) return 0;
    int i = 0;
    while (i < n->n && chave > n->chaves[i]) i++;
    if (i < n->n && chave == n->chaves[i]) return 1;
    if (n->folha) return 0;
    return buscar(n->filhos[i], chave);
}

void emOrdem(no *n) {
    if (n == NULL) return;
    int i;
    for (i = 0; i < n->n; i++) {
        if (!n->folha) emOrdem(n->filhos[i]);
        printf("%d ", n->chaves[i]);
    }
    if (!n->folha) emOrdem(n->filhos[i]);
}

void liberar(no *n) {
    if (n == NULL) return;
    if (!n->folha) {
        for (int i = 0; i <= n->n; i++)
            liberar(n->filhos[i]);
    }
    free(n);
}

int main() {
    no *raiz = criarNo(1);
    // valores que forcam split de folha e depois split de raiz (t=3 -> estoura em 5 chaves)
    int chaves[] = {10, 20, 5, 6, 12, 30, 7, 17, 3, 25, 1, 40, 15};
    int n = sizeof(chaves) / sizeof(chaves[0]);

    for (int i = 0; i < n; i++)
        raiz = inserir(raiz, chaves[i]);

    printf("Em ordem: ");
    emOrdem(raiz);
    printf("\n");

    printf("Busca 17: %d (esperado 1)\n", buscar(raiz, 17));
    printf("Busca 99: %d (esperado 0)\n", buscar(raiz, 99));
    printf("Raiz tem %d chave(s), folha: %s (esperado nao-folha, ja que estourou)\n",
           raiz->n, raiz->folha ? "sim" : "nao");

    liberar(raiz);
    return 0;
}