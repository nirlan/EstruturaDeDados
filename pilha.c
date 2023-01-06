// ### PILHA ###
#include <stdio.h>
#include <stdlib.h>

struct elementoPilha {
    int num;
    struct elementoPilha *prox;
};
typedef struct elementoPilha ElementoPilha;
ElementoPilha *top = NULL;

int menu();
void push(int num);
void show();
void pop();
void clearmem();

int main() {
    while(1) {
        int op, num, pos, c;
        op = menu();

        switch(op) {
            case 1:
                // Insere elemento na pilha (FILO - Fisrt In Last Out)

                // Recebe do usuário o novo elemento
                printf("Digite o número que deseja inserir: ");
                scanf("%9d", &num);
                // limpa o buffer do teclado
                while((c = getchar()) != '\n' && c != EOF) {}

                push(num);
                printf("Elemento inserido\n");
                printf("Pressione enter para continuar...\n");
                getchar();
                break;
            
            case 2:

                // Remove o elemento da lista
                pop();               
                printf("Pressione enter para continuar...\n");
                getchar();
                break;

            case 3:
                // Mostra os elementos da lista
                show();
                printf("Pressione enter para continuar...\n");
                getchar();
                break;

            case 4:
                // Sair
                clearmem();
                exit(0);

            default:
                // Opção inválida
                printf("Opção inválida. Por favor, digite uma opção de 1 a 4.\n");
                printf("Pressione enter para continuar...\n");
                getchar();
        }
    }
}

int menu() {
    system("clear");
    printf("   ### MENU ###\n");
    printf("   ### PILHA ###\n");
    printf("1- Empilhar\n");
    printf("2- Desempilhar\n");
    printf("3- Mostrar toda a pilha\n");
    printf("4- Sair\n\n");
    printf("Digite a opção desejada: ");
    int num;
    scanf("%2d", &num);
    // limpa o buffer do teclado
    int c;
    while((c = getchar()) != '\n' && c != EOF) {}
    return num;
}

void push(int num) {
    // Cria o novo elemento da lista
    ElementoPilha *elemento = malloc(sizeof(ElementoPilha));
    elemento->num = num;

    if(top == NULL) {
        top = elemento;
        top->prox = NULL;
    } else {
        elemento->prox = top;
        top = elemento;
    }
}

void pop() {
    if(top == NULL) {
        printf("Pilha vazia!\n");

    } else {
        ElementoPilha *aux;
        aux = top;
        top = top->prox;
        free(aux);
        aux = NULL;            
        printf("Elemento removido.\n");
    }
}

void show() {
    if(top == NULL) {
        printf("Pilha vazia!\n");
    } else {
        ElementoPilha *aux = top;

        int i = 0;
        while(aux != NULL) {
            printf("Elemento %d: %d  ", i, aux->num);
            aux = aux->prox;
            i++;
        }
        printf("\n");
    }
}

void clearmem() {
    if(top == NULL)
        return;

    else {
        ElementoPilha *aux;
        while(top != NULL) {
            aux = top;
            top = top->prox;
            free(aux);
            aux = NULL;
        }
    }
}