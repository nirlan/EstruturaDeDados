// ### LISTA ENCADEADA DUPLA CIRCULAR ###
#include <stdio.h>
#include <stdlib.h>

struct elementoLista {
    int num;
    struct elementoLista *prox;
    struct elementoLista *ant;
};
typedef struct elementoLista ElementoLista;
ElementoLista *head = NULL;
ElementoLista *tail = NULL;
ElementoLista *aux = NULL;

int menu();
void InserirInicio(int num);
void MostrarLista();
void InserirFinal(int num);
void Remover(int pos);
void LimpaMemoria();

int main() {
    while(1) {
        int op, num, pos, c;
        op = menu();

        switch(op) {
            case 1:
                // Insere elemento no início da lista

                // Recebe do usuário o novo elemento
                printf("Digite o número que deseja inserir na lista: ");
                scanf("%9d", &num);
                // limpa o buffer do teclado
                while((c = getchar()) != '\n' && c != EOF) {}

                InserirInicio(num);
                printf("Elemento inserido\n");
                printf("Pressione enter para continuar...\n");
                getchar();
                break;

            case 2:
                // Insere elemento no final da lista
                // Recebe do usuário o novo elemento
                printf("Digite o número que deseja inserir na lista: ");
                scanf("%9d", &num);
                // limpa o buffer do teclado
                while((c = getchar()) != '\n' && c != EOF) {}

                InserirFinal(num);
                printf("Elemento inserido\n");
                printf("Pressione enter para continuar...\n");
                getchar();
                break;
            
            case 3:
                // Remove o elemento da lista

                // Recebe do usuário o elemento
                printf("Digite a posição do elemento: ");
                scanf("%5d", &pos);
                // limpa o buffer do teclado
                while((c = getchar()) != '\n' && c != EOF) {}

                Remover(pos);                
                printf("Pressione enter para continuar...\n");
                getchar();
                break;

            case 4:
                // Mostra os elementos da lista
                MostrarLista();
                printf("Pressione enter para continuar...\n");
                getchar();
                break;

            case 5:
                // Sair
                LimpaMemoria();
                exit(0);

            default:
                // Opção inválida
                printf("Opção inválida. Por favor, digite uma opção de 1 a 6.\n");
                printf("Pressione enter para continuar...\n");
                getchar();
        }
    }
}

int menu() {
    system("clear");
    printf("         ### MENU ###\n");
    printf("### LISTA ENCADEADA DUPLA CIRCULAR ###\n");
    printf("1- Inserir no início\n");
    printf("2- Inserir no final\n");    
    printf("3- Remover elemento\n");
    printf("4- Mostrar toda a lista\n");
    printf("5- Sair\n\n");
    printf("Digite a opção desejada: ");
    int num;
    scanf("%2d", &num);
    // limpa o buffer do teclado
    int c;
    while((c = getchar()) != '\n' && c != EOF) {}
    return num;
}

void InserirInicio(int num) {
    // Cria o novo elemento da lista
    ElementoLista *elemento = malloc(sizeof(ElementoLista));
    elemento->num = num;

   if(head == NULL) {
        head = elemento;
        tail = elemento;
        
        elemento->prox = head;
        elemento->ant = head;
        
    } else {
        elemento->prox = head;
        head->ant = elemento;

        head = elemento;

        head->ant = tail;
        tail->prox = head;
    }
}

void InserirFinal(int num) {
        ElementoLista *elemento = malloc(sizeof(ElementoLista));
        elemento->num = num;

        if(head == NULL) {
            head = elemento;
            tail = elemento;
            
            elemento->prox = head;
            elemento->ant = head;

        } else {
            // Quando vc olha para o abismo, o abismo olha para vc
            tail->prox = elemento;
            elemento->ant = tail;

            tail = elemento;

            tail->prox = head;
            head->ant = tail;
        }
}

void MostrarLista() {
    if(head == NULL) {
        printf("Lista vazia!\n");
    } else {
        aux = head;

        int i = 0;
        do {
            printf("Elemento %d: %d  ", i, aux->num);
            aux = aux->prox;            
            i++;
        } while (aux != head);
        printf("\n");
    }
}

void Remover(int pos) {
    if(head == NULL) {        
        printf("Lista vazia!\n");        

    } else {

        // Se a posição do elemento é 0
        if(pos == 0) {
            aux = head;

        } else {
            int i = 0;
            aux = head;
            do {
                aux = aux->prox;
                i++;
            } while(i < pos && aux != head);            
        }                

        // Se a lista possui apenas um elemento
        if(head == tail) {                      
            free(head);
            aux = NULL; 
            head = NULL;
            printf("ponteiro aux: %p\n", aux);
            printf("Elemento removido\n");
        
        // Se a lista possui mais de um elemento
        } else {
            // Se o elemento é o primeiro da lista
            if(aux == head) {
                head = aux->prox;
                head->ant = tail;
                tail->prox = head;

                free(aux);
                aux = NULL;

                printf("Elemento removido\n");
            }
            // Se o elemento é o último da lista
            else if(aux == tail) {
                tail = aux->ant;
                tail->prox = head;
                head->ant = tail;

                free(aux);
                aux = NULL;  

                printf("Elemento removido\n");              

            // O elemento está no meio da lista
            } else {
                aux->ant->prox = aux->prox;
                aux->prox->ant = aux->ant;

                free(aux);
                aux = NULL;
            }            
        }
    }
}

void LimpaMemoria() {
    if(head == NULL)
        return;
    else {
        ElementoLista *elementoDeVarredura;
        while(head != tail) {
            elementoDeVarredura = head;
            head = elementoDeVarredura->prox;
            free(elementoDeVarredura);
            elementoDeVarredura = NULL;
        }
        free(head);
        head = NULL;
    }
}