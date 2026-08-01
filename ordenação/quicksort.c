#include <stdio.h>

void trocar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int particionar(int v[], int inicio, int fim) {
    int pivo = v[fim];
    int i = inicio - 1;

    for (int j = inicio; j < fim; j++) {
        if (v[j] <= pivo) {
            i++;
            trocar(&v[i], &v[j]);
        }
    }
    trocar(&v[i + 1], &v[fim]);
    return i + 1;
}

void quicksort(int v[], int inicio, int fim) {
    if (inicio < fim) {
        int p = particionar(v, inicio, fim);
        quicksort(v, inicio, p - 1);
        quicksort(v, p + 1, fim);
    }
}

void imprimir(int v[], int n) {
    for (int i = 0; i < n; i++) printf("%d ", v[i]);
    printf("\n");
}

void rodarCaso(const char *nome, int v[], int n) {
    printf("%s (antes): ", nome); imprimir(v, n);
    quicksort(v, 0, n - 1);
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