#include <stdio.h>

#define TAMANHO 10
#define VAZIO -1
#define REMOVIDO -2   // marca "lapide" (tombstone) para nao quebrar buscas apos remocao

typedef struct {
    int slots[TAMANHO];
} tabelaHash;

int funcaoHash(int chave) {
    return chave % TAMANHO;
}

void inicializar(tabelaHash *t) {
    for (int i = 0; i < TAMANHO; i++)
        t->slots[i] = VAZIO;
}

// retorna 0 se inseriu, 1 se ja existia, 2 se a tabela esta cheia
int inserir(tabelaHash *t, int chave) {
    int idx = funcaoHash(chave);

    for (int cont = 0; cont < TAMANHO; cont++) {
        int pos = (idx + cont) % TAMANHO;

        if (t->slots[pos] == chave)
            return 1; // ja existe

        if (t->slots[pos] == VAZIO || t->slots[pos] == REMOVIDO) {
            t->slots[pos] = chave;
            return 0;
        }
    }
    return 2; // tabela cheia, nenhum slot livre encontrado
}

// retorna o indice onde a chave esta, ou -1 se nao encontrada
int buscar(tabelaHash *t, int chave) {
    int idx = funcaoHash(chave);

    for (int cont = 0; cont < TAMANHO; cont++) {
        int pos = (idx + cont) % TAMANHO;

        if (t->slots[pos] == VAZIO)
            return -1; // slot vazio (nunca ocupado) encerra a busca: chave nao existe

        if (t->slots[pos] == chave)
            return pos;
        // se for REMOVIDO, continua procurando -- a chave pode estar mais a frente
    }
    return -1;
}

int remover(tabelaHash *t, int chave) {
    int pos = buscar(t, chave);
    if (pos == -1) return 1;
    t->slots[pos] = REMOVIDO;
    return 0;
}

void imprimir(tabelaHash *t) {
    for (int i = 0; i < TAMANHO; i++) {
        if (t->slots[i] == VAZIO) printf("[%d] vazio\n", i);
        else if (t->slots[i] == REMOVIDO) printf("[%d] removido\n", i);
        else printf("[%d] %d\n", i, t->slots[i]);
    }
}

int main() {
    tabelaHash t;
    inicializar(&t);

    // 10 e 20 colidem (ambos hash 0); 20 deve ir pro proximo slot livre (1)
    inserir(&t, 10);
    inserir(&t, 20);
    inserir(&t, 25);
    inserir(&t, 7);
    inserir(&t, 17); // colide com 7, deve ir pro proximo slot livre

    imprimir(&t);

    printf("Busca 20: posicao %d (esperado 1)\n", buscar(&t, 20));
    printf("Busca 99: posicao %d (esperado -1)\n", buscar(&t, 99));

    remover(&t, 10);
    printf("Apos remover 10 (que estava na posicao do hash de 20), busca 20: posicao %d (esperado ainda achar, > -1)\n", buscar(&t, 20));
    printf("Busca 10 apos remover: posicao %d (esperado -1)\n", buscar(&t, 10));

    return 0;
}