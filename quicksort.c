#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void quickSort(int vet[], int p, int u);
int particao(int vet[], int p, int u);
void troca(int vet[], int i, int j);

#define TAMANHOVETOR 100000

int main() {
    double tempo_inicio = time(NULL);
    int vet[TAMANHOVETOR] = {0};

    // Gera a semente aleatória
    srand(time(NULL));

    // Insere os dados no vetor
    for(int i = 0; i < TAMANHOVETOR; i++) {

        // Gera os valores aleatórios
        vet[i] = rand() % 10000;
    }

    printf("Vetor não ordenado: \n");
    for(int i = 0; i < TAMANHOVETOR; i++) {
        printf("%d\n", vet[i]);
    }


    quickSort(vet, 0, TAMANHOVETOR - 1);

    printf("Vetor ordenado:\n");
    for(int i = 0; i < TAMANHOVETOR; i++) {
        printf("%d\n", vet[i]);
    }

    double tempo_fim = time(NULL);
    printf("\nTempo de execução %lf segundos\n", tempo_fim - tempo_inicio);

    printf("Pressione qualquer tecla para continuar...");
    getchar();

    return 0;
}

// Função recursiva que recebe o vetor, e a primeira e a última posição dele
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