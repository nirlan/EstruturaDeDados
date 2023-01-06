#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHOVETOR 10

int buscaSequencial(int vet[], int buscado);

int main() {
    int vet[TAMANHOVETOR] = { 0 };
    int buscado, achou;

    // Gera semente
    srand(time(NULL));

    // Povoa o vetor com valores aleatórios
    for(int i = 0; i < TAMANHOVETOR; i++) {
        vet[i] = rand() % 1000;
    }

    // Imprime na tela o vetor gerado
    printf("Vetor gerado:\n");
    for(int i = 0; i < TAMANHOVETOR; i++) {
        printf("%d\n", vet[i]);
    }

    // Solicita ao usuário que digite um valor
    printf("Escolha um valor para buscar:\n");
    scanf("%3d", &buscado);

    achou = buscaSequencial(vet, buscado);
   
    // Se achou, imprime na tela a posição do valor no vetor
    if(achou) {
        printf("O valor foi encontrado na posição %d\n", achou);
    } else {
        printf("O valor não foi encontrado.\n");
    }
    

    printf("Pressione 'Enter' para continuar...");
    getchar();
    return 0;
}

// Função que procura sequencialmente em cada valor do vetor comparando com
// o valor buscado
int buscaSequencial(int vet[], int buscado) {
    for(int i = 0; i < TAMANHOVETOR; i++) {
        if(vet[i] == buscado) {
            return ++i;
        }        
    }

    return 0;
}