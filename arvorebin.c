// ### ÁRVORE BINÁRIA ###
#include <stdio.h>
#include <stdlib.h>

struct arvoreBin {
    int num;
    struct arvoreBin *leftTwig; // Galho esquerdo - valores menores que o nó pai
    struct arvoreBin *rightTwig; // Galho direito - valores maiores que o nó pai
};
typedef struct arvoreBin Arvore;

int menu();
// Aqui é necessário receber como parâmetro um ponteiro de ponteiro pois a variável
// root não está declarada no escopo global, mas dentro da main(), e como a passagem
// do C no fundo é sempre por cópia, então é necessário passar a variável
// que armazena o endereço do endereço da variável, para que este último endereço
// possa ser alterado, por exemplo, alterando ele de NULL para um outro endereço
// quando dou malloc. Isso não seria necessário se root não tivesse necessidade de ser
// manipulado. Por exemplo, é o que ocorre nas funções show() e search(), em que
// é passado somente a variável ponteiro, pois não há modificação do ponteiro
// dentro dessas funções, somente leitura dos dados.
void push(int num, Arvore **aux);
void pop(int num);
void show(Arvore *aux);
int search(int num, Arvore *aux);
Arvore* alocar(int num);
void memClear();

int main() {
    int op, c, num;
    Arvore *root = NULL;

    while(1) {
        // Menu
        op = menu();

        switch(op) {
            case 1:
                // Insere elemento
                printf("Por favor, digite o elemento desejado: \n");
                scanf("%9d", &num);
                while((c = getchar()) != '\n' && c != EOF) {}
                push(num, &root);
                break;
            case 2:
                // Remove elemento
                pop(num);
                break;
            case 3:
                // Mostra a árvore
                show(root);
                printf("\n");
                printf("Pressione enter para continuar...\n");
                getchar();
                break;
            case 4:
                // Busca valor
                printf("Por favor, digite o elemento buscado: \n");
                scanf("%9d", &num);
                while((c = getchar()) != '\n' && c != EOF) {}
                if(search(num, root)) {
                    printf("Valor encontrado!\n");
                } else {
                    printf("Valor não encontrado\n");
                }
                printf("Pressione enter para continuar...\n");
                getchar();
                break;
            case 5:
                // Limpa a memória e sai
                memClear(&root);
                exit(0);
                break;
            default:
                printf("Opção inválida. Digite novamente.\n");
        }
    }

}

// Menu inicial
int menu() {
    system("clear");
    printf("     ### MENU ###\n");
    printf("### ÁRVORE BINÁRIA ###\n");
    printf("1- Inserir\n");
    printf("2- Remover\n");
    printf("3- Mostrar\n");
    printf("4- Buscar\n");
    printf("5- Sair\n\n");
    printf("Digite a opção desejada: ");
    int num;
    scanf("%2d", &num);
    // limpa o buffer do teclado
    int c;
    while((c = getchar()) != '\n' && c != EOF) {}
    return num;
}

// Adiciona um elemento à árvore
void push(int num, Arvore **aux) {
    
    // Se está vazio, coloca na árvore
    if(*aux == NULL) {
        *aux = alocar(num);                
        (*aux)->leftTwig = NULL;
        (*aux)->rightTwig = NULL;        
        printf("Valor adicionado: %d", (*aux)->num);
        getchar();

    } else {
        if(num < (*aux)->num){
            push(num, &(*aux)->leftTwig);
        } else {
            push(num, &(*aux)->rightTwig);
        }
    }
}

// Remove um elemento da árvore
void pop(int num) {

}

// Lista os elementos da árvore
void show(Arvore *aux) {    
    if(aux != NULL) {
        show(aux->leftTwig);                       
        printf(" %d", aux->num);
        show(aux->rightTwig); 
    }                 
}

// Busca o elemento na árvore
int search(int num, Arvore *aux) {
    if(aux == NULL) {
        return 0;
    } else {
        if(num == aux->num) {
            return 1;
        }
        else if(num < aux->num){
            search(num, aux->leftTwig);
        } else {
            search(num, aux->rightTwig);
        }
    }
}

// Aloco um elemento na memória
Arvore* alocar(int num) {
    Arvore *elemento = malloc(sizeof(Arvore));
    elemento->num = num;

    return elemento;
}

// Limpa memória
void memClear(Arvore **aux) {
    if((*aux) != NULL) {
        memClear(&(*aux)->leftTwig);
        free(*aux);
        memClear(&(*aux)->rightTwig);
    }    
}