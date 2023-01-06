// ### HASH com endereçamento em cadeia ###
#include <stdio.h>
#include <stdlib.h>

#define TAMANHO_VETOR 10

struct hashLista {
    int chave;
    struct hashLista *prox;
};
typedef struct hashLista HashLista;

struct tabela {
    int Tamanho;
    HashLista **ListaChave;
};
typedef struct tabela Tabela;
Tabela *TabelaHash = NULL;

int menu();
int FuncaoHashing(int num);
void InserirHash(Tabela *TabelaHash, int num, int pos);
void MostrarHash(Tabela *TabelaHash);
void RemoverHash(Tabela *TabelaHash, int num, int pos);
void Buscar(Tabela *TabelaHash, int num, int pos);
void clearMem(Tabela *TabelaHash);

int main() {
    int op, c, num, pos;
    TabelaHash = malloc(sizeof(Tabela));
    TabelaHash->Tamanho = TAMANHO_VETOR;
    TabelaHash->ListaChave = malloc(TAMANHO_VETOR * sizeof(HashLista*));

    for(int i = 0; i < TAMANHO_VETOR; i++) {
        TabelaHash->ListaChave[i] = NULL;
    }

    while(1) {
        op = menu();
        switch(op) {
            case 1:
                printf("Digite o número desejado: ");
                scanf("%d", &num);
                while((c = getchar()) != '\n' && c != EOF) {}
                pos = FuncaoHashing(num);
                printf("Inserindo na posição %d da tabela...\n", pos);
                InserirHash(TabelaHash, num, pos);
                getchar();
                break;
            case 2:
                printf("Digite o número desejado: ");
                scanf("%d", &num);
                while((c = getchar()) != '\n' && c != EOF) {}                
                pos = FuncaoHashing(num);
                printf("Removendo da posição %d da tabela...\n", pos);
                RemoverHash(TabelaHash, num, pos);
                getchar();
                break;
            case 3:
                // Mostra os elementos da HashLista
                MostrarHash(TabelaHash);
                printf("Pressione enter para continuar...\n");
                getchar();                
                break;
            case 4:
                printf("Digite o número desejado: ");
                scanf("%d", &num);
                while((c = getchar()) != '\n' && c != EOF) {}                
                pos = FuncaoHashing(num);
                printf("Buscando %d na tabela...\n", num);
                Buscar(TabelaHash, num, pos);
                getchar(); 
                break;
            case 5:
                printf("Saindo...");
                clearMem(TabelaHash);
                getchar();
                exit(0);
                break;
            default:
                // Opção inválida
                printf("Opção inválida. Por favor, digite uma opção de 1 a 4.\n");
                printf("Pressione enter para continuar...\n");
                getchar();
        }
    }

}

int menu(){
    system("clear");
    printf("### MENU ###\n");
    printf("### HASH ###\n");
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

void InserirHash(Tabela *TabelaHash, int num, int pos) {
    HashLista *elemento = malloc(sizeof(HashLista));
        elemento->chave = num;
        elemento->prox = TabelaHash->ListaChave[pos];
        TabelaHash->ListaChave[pos] = elemento;
}

void MostrarHash(Tabela *TabelaHash) {
    for(int i = 0; i < TAMANHO_VETOR; i++) {
        HashLista *aux = TabelaHash->ListaChave[i];
        printf("Posição %d\n", i);
        while(aux != NULL) {
            printf("Chave: %d\t", aux->chave);
            aux = aux->prox;
        }
        printf("\n");
    }
}

void RemoverHash(Tabela *TabelaHash, int num, int pos) {
    HashLista *aux = TabelaHash->ListaChave[pos];
    HashLista *ant = NULL;

    if(aux == NULL) {
        printf("Número não encontrado...");
    } else {
        while(aux->chave != num && aux->prox != NULL) {
            ant = aux;
            aux = aux->prox;
        }
        if(aux->chave != num) {
            printf("Número não encontrado...\n");
        } else if(aux != TabelaHash->ListaChave[pos]){
            ant->prox = aux->prox;
            free(aux);
            aux = NULL;
        } else {
            aux = TabelaHash->ListaChave[pos];
            TabelaHash->ListaChave[pos] = TabelaHash->ListaChave[pos]->prox;
            free(aux);
            aux = NULL;            
        }
    }
}

void Buscar(Tabela *TabelaHash, int num, int pos) {
    HashLista *aux = TabelaHash->ListaChave[pos];
    HashLista *ant = NULL;

    if(aux == NULL) {
        printf("Número não encontrado...");
    } else {
        int i = 0;
        while(aux->chave != num && aux->prox != NULL) {
            ant = aux;
            aux = aux->prox;
            i++;
        }
        if(aux->chave != num) {
            printf("Número não encontrado...\n");
        } else {
            printf("Número encontrado na posição %d ", pos);                        
            printf("lista %d\n", i);
        }
    }
}

// Calcula a posição na tabela através de uma função de hashing
// com método da divisão
int FuncaoHashing(int num) {    
    return (num % TAMANHO_VETOR);
}

void clearMem(Tabela *TabelaHash) {    
    int i = 0;
    HashLista *aux = NULL;
    while(i < TAMANHO_VETOR) {
        HashLista *elemento = TabelaHash->ListaChave[i];
        while(elemento != NULL) {
            aux = elemento;
            elemento = elemento->prox;
            free(aux);
            aux = NULL;
        }
        i++;
    }
    free(TabelaHash->ListaChave);
    TabelaHash->ListaChave = NULL;
    free(TabelaHash);
    TabelaHash = NULL;
}