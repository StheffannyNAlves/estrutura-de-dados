#include <stdio.h>
#include <stdlib.h>

void mesclar(int v[], int inicio, int meio, int fim) {
    int n1 = meio - inicio + 1;
    int n2 = fim - meio;

    int *esq = malloc(n1 * sizeof(int));
    int *dir = malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++) esq[i] = v[inicio + i];
    for (int j = 0; j < n2; j++) dir[j] = v[meio + 1 + j];

    int i = 0, j = 0, k = inicio;
    while (i < n1 && j < n2) {
        if (esq[i] <= dir[j])
            v[k++] = esq[i++];
        else
            v[k++] = dir[j++];
    }
    while (i < n1) v[k++] = esq[i++];
    while (j < n2) v[k++] = dir[j++];

    free(esq);
    free(dir);
}

void mergesort(int v[], int inicio, int fim) {
    if (inicio < fim) {
        int meio = inicio + (fim - inicio) / 2;
        mergesort(v, inicio, meio);
        mergesort(v, meio + 1, fim);
        mesclar(v, inicio, meio, fim);
    }
}

void imprimir(int v[], int n) {
    for (int i = 0; i < n; i++) printf("%d ", v[i]);
    printf("\n");
}

void rodarCaso(const char *nome, int v[], int n) {
    printf("%s (antes): ", nome); imprimir(v, n);
    if (n > 0) mergesort(v, 0, n - 1);
    printf("%s (depois): ", nome); imprimir(v, n);
}

int main() {
    int *v0 = NULL;
    int v1[] = {42};
    int v2[] = {1, 2, 3, 4, 5};
    int v3[] = {5, 4, 3, 2, 1};
    int v4[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};

    rodarCaso("vazio", v0, 0);
    rodarCaso("um elemento", v1, 1);
    rodarCaso("ja ordenado", v2, 5);
    rodarCaso("ordem reversa", v3, 5);
    rodarCaso("com duplicados", v4, 10);

    return 0;
}