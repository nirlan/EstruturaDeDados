// ### LISTA ENCADEADA DUPLA ###
#include <stdio.h>
#include <stdlib.h>

struct elementoLista {
    int num;
    struct elementoLista *prox;
    struct elementoLista *ant;
};
typedef struct elementoLista ElementoLista;
ElementoLista *head = NULL;

int menu();
void InserirInicio(int num);
void MostrarLista();
void InserirFinal(int num);
void InserirMeio(int num, int pos);
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
                // Insere elemento no meio da lista

                // Recebe do usuário o novo elemento
                printf("Digite o número que deseja inserir na lista: ");
                scanf("%9d", &num);
                // limpa o buffer do teclado
                while((c = getchar()) != '\n' && c != EOF) {}

                printf("\nDigite a posição na lista: ");
                scanf("%5d", &pos);
                // limpa o buffer do teclado
                while((c = getchar()) != '\n' && c != EOF) {}

                InserirMeio(num, pos);
                printf("Elemento inserido\n");
                printf("Pressione enter para continuar...\n");
                getchar();
                break;

            case 4:
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

            case 5:
                // Mostra os elementos da lista
                MostrarLista();
                printf("Pressione enter para continuar...\n");
                getchar();
                break;

            case 6:
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
    printf("### LISTA ENCADEADA DUPLA ###\n");
    printf("1- Inserir no início\n");
    printf("2- Inserir no final\n");
    printf("3- Inserir no meio\n");
    printf("4- Remover elemento\n");
    printf("5- Mostrar toda a lista\n");
    printf("6- Sair\n\n");
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
        head->prox = NULL;
        head->ant = NULL;
    } else {
        elemento->prox = head;
        elemento->ant = NULL;
        head->ant = elemento;
        head = elemento;
    }
}

void MostrarLista() {
    if(head == NULL) {
        printf("Lista vazia!\n");
    } else {
        ElementoLista *elementoDeVaredura = head;

        int i = 0;
        while(elementoDeVaredura != NULL) {
            printf("Elemento %d: %d  ", i, elementoDeVaredura->num);
            elementoDeVaredura = elementoDeVaredura->prox;
            i++;
        }
        printf("\n");
    }
}

void InserirFinal(int num) {
        ElementoLista *elemento = malloc(sizeof(ElementoLista));
        elemento->prox = NULL;
        elemento->num = num;

        if(head == NULL) {
            elemento->ant = NULL;
            head = elemento;            
        } else {
            ElementoLista *elementoDeVarredura = head;

            while(elementoDeVarredura->prox != NULL)
                elementoDeVarredura = elementoDeVarredura->prox;

            elemento->ant = elementoDeVarredura;            
            elementoDeVarredura->prox = elemento;
        }
}

void InserirMeio(int num, int pos) {
    ElementoLista *elemento = malloc(sizeof(ElementoLista));
    elemento->num = num;

    // Se a lista estiver vazia, insere no head
    if(head == NULL) {
        head = elemento;
        head->prox = NULL;
        head->ant = NULL;

    // Senão se for para inserir no início
    } else if(pos == 0) {
        elemento->prox = head;
        elemento->ant = NULL;
        head = elemento;

    // Senão insere na posiçao escolhida ou no final da lista
    } else {
        ElementoLista *elementoDeVarredura = head;
        ElementoLista *elementoAux;

        int i = 0;
        while(i < pos - 1 && elementoDeVarredura->prox != NULL) {            
            elementoDeVarredura = elementoDeVarredura->prox;
            i++;
        }

        // Se a posição for maior que a lista, insere no final
        if(pos > i + 1) {
            elementoDeVarredura->prox = elemento;
            elemento->prox = NULL;
            elemento->ant = elementoDeVarredura;
        
        // Senão insere na posição escolhida
        } else {
            elementoAux = elementoDeVarredura->prox;
            elementoDeVarredura->prox = elemento;
            elemento->prox = elementoAux;
            elemento->ant = elementoDeVarredura;
        }
    }
}

void Remover(int pos) {
    if(head == NULL) {
        printf("Lista vazia!\n");
    }
    else if(pos == 0) {
        ElementoLista *elementoAux;
        elementoAux = head;
        head = head->prox;
        head->ant = NULL;
        free(elementoAux);            
    } else {
        ElementoLista *elementoDeVarredura, *elementoAux1, *elementoAux2;
        elementoDeVarredura = head;

        int i = 0;
        while(i < pos) {            
            elementoDeVarredura = elementoDeVarredura->prox;
            if(elementoDeVarredura == NULL) {
                printf("Posição inexistente!\n");
                return;
            }
            i++;
        }

        elementoAux1 = elementoDeVarredura->ant;
        elementoAux1->prox = elementoDeVarredura->prox;

        elementoAux2 = elementoDeVarredura->prox;
        elementoAux2->ant = elementoAux1;

        free(elementoDeVarredura);
        printf("Elemento removido.\n");
    }
}

void LimpaMemoria() {
    if(head == NULL)
        return;
    else {

        ElementoLista *elementoDeVarredura;
        while(head != NULL) {
            elementoDeVarredura = head;
            head = elementoDeVarredura->prox;
            free(elementoDeVarredura);
        }
    }
}