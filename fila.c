// ### FILA ###
#include <stdio.h>
#include <stdlib.h>

struct elementoFila {
    int num;
    struct elementoFila *prox;
};
typedef struct elementoFila ElementoFila;
ElementoFila *head = NULL;
ElementoFila *tail = NULL;

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
                // Insere elemento na fila (FIFO - First In First Out)

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

                // Remove o elemento da fila
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
    printf("   ### FILA ###\n");
    printf("1- Colocar na fila\n");
    printf("2- Remover da fila\n");
    printf("3- Mostrar toda a fila\n");
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
    ElementoFila *elemento = malloc(sizeof(ElementoFila));
    elemento->num = num;

    // Se fila vazia
    if(head == NULL) {
        head = elemento;
        tail = elemento;        
        tail->prox = NULL;        
    // Senão entra no fim da fila
    } else {        
        tail->prox = elemento;        
        tail = elemento;
        tail->prox = NULL;
    }
}

void pop() {
    if(head == NULL) {
        printf("Fila vazia!\n");

    } else {
        ElementoFila *aux;
        aux = head;
        head = head->prox;
        free(aux);
        aux = NULL;            
        printf("Elemento removido.\n");
    }
}

void show() {
    if(head == NULL) {
        printf("Fila vazia!\n");
    } else {
        ElementoFila *aux = head;

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
    if(head == NULL)
        return;

    else {
        ElementoFila *aux;
        while(head != NULL) {
            aux = head;
            head = head->prox;
            free(aux);
            aux = NULL;
        }
    }
}