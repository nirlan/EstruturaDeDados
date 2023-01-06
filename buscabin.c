#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int buscaBinaria(int vet[], int p, int u, int buscado);
void quickSort(int vet[], int p, int u);
int particao(int vet[], int p, int u);
void troca(int vet[], int i, int j);

#define TAMANHOVETOR 10

int main() {
    int vet[TAMANHOVETOR] = { 0 };
    int achou, buscado;

    srand(time(NULL));

    // Gera um vetor com números aleatórios
    for(int i = 0; i < TAMANHOVETOR; i++) {
        vet[i] = rand() % 1000;
    }

    printf("Vetor gerado:\n");
    for(int i = 0; i < TAMANHOVETOR; i++) {
        printf("%d\n", vet[i]);
    }

    // Ordena o vetor
    quickSort(vet, 0, TAMANHOVETOR-1);

    printf("Vetor ordenado:\n");
    for(int i = 0; i < TAMANHOVETOR; i++) {
        printf("%d\n", vet[i]);
    }

    printf("Digite o valor buscado:\n");
    scanf("%3d", &buscado);

    // Busca binária pelo valor 'buscado'
    achou = buscaBinaria(vet, 0, TAMANHOVETOR-1, buscado);

    if(achou) {
        printf("O valor foi encontrado na posição %d\n", achou);
    } else {
        printf("O valor não foi encontrado.\n");
    }

    return 0;
}

// Algoritmo de busca binária (recursivo)
int buscaBinaria(int vet[], int p, int u, int buscado) {

    if(p <= u) {
        int m;
        m = (p + u)/2;

        if(vet[m] == buscado) {
            return m + 1;
        } else {
            if(buscado < vet[m]){
                buscaBinaria(vet, p, m - 1, buscado);
            } else {
                buscaBinaria(vet, m + 1, u, buscado);
            }
        }
    } else {
        return 0;
    }
}

// Algoritmo de ordenação do vetor
void quickSort(int vet[], int p, int u) {
    int m;
    if(p < u) {
        m = particao(vet, p, u);
        quickSort(vet, p, m); // lado esquerdo do vetor
        quickSort(vet, m + 1, u); // lado direito do vetor
    }
}

// Calcula o elemento do meio do vetor - o pivot
int particao(int vet[], int p, int u) {
    int pivot, pivot_pos, i, j;

    pivot_pos = (p + u) / 2;
    pivot = vet[pivot_pos];

    i = p - 1; // varredura esquerda
    j = u + 1; // varredura direita

    // Enquanto a varredura direita e esquerda não se encontrarem, vai sendo buscado valores
    // para serem trocados
    while(i < j) {

        // Testa o lado direito
        do {

            j--; // começa do final do vetor e vai em direção ao meio dele
        } while(vet[j] > pivot);

        // Testa o lado esquerdo
         do {

            i++; // começa do início do vetor e vai em direção ao meio dele
        } while(vet[i] < pivot);

        if(i < j)
            troca(vet, i, j);
    }
    return j;
}

void troca(int vet[], int i, int j) {
    int aux;
    aux = vet[i];
    vet[i] = vet[j];
    vet[j] = aux;
}