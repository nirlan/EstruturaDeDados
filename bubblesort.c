#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void BubbleSort(int vet[]);

#define TAMANHOVETOR 100000

int main() {
    double tempo_inicio = time(NULL);
    int vet[TAMANHOVETOR] = {0}; 

    // Gera a semente aleatória
    srand(time(NULL));

    // Insere os dados no vetor
    for(int i = 0; i < TAMANHOVETOR; i++) {

        // Gera os valores aleatórios de 0 a 99
        vet[i] = rand() % 10000;
    }

    printf("Vetor não ordenado: \n");
    for(int i = 0; i < TAMANHOVETOR; i++) {
        printf("%d\n", vet[i]);
    }

    BubbleSort(vet);

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

// Dois laços for com uma condicional e um swap com uma variável auxiliar
void BubbleSort(int vet[]) {
    int aux;
    for(int n = 1; n <= TAMANHOVETOR; n++) {
        for(int i = 0; i < (TAMANHOVETOR - 1); i++) {
            if(vet[i] > vet[i + 1]) {
                aux = vet[i];
                vet[i] = vet[i + 1];
                vet[i + 1] = aux;
            }
        }
    }
}