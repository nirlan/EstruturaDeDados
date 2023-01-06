// ### GRAFO COM LISTA DE ADJACÊNCIAS ###
// ### com implementação de busca em LARGURA ###
// ### breadth-first search (BFS) ###
#include <stdio.h>
#include <stdlib.h>

#define NUMERO_VERTICES 6

struct listaVizinhos {
    int vertice;
    struct listaVizinhos *prox;
};
typedef struct listaVizinhos ListaVizinhos;

struct grafo {
    int totalVertices;
    // Vetor com os endereços do head para cada uma das listas encadeadas
    // Cada vértice tem uma lista encadeada de vértices vizinhos associada
    struct listaVizinhos **ListaAdj;
};
typedef struct grafo Grafo;

// Stack (pilha) de vértices a serem visitados
struct queue {
    int vertice;
    struct queue *prox;
} *head, *tail = NULL;
typedef struct queue QUEUE;

Grafo* CriarGrafo(int totalVertices);
void AdicionarAresta(Grafo* grafo, int origem, int destino);
void MostrarGrafo(Grafo *grafo);
void BuscaLargura(Grafo *Vizinhos, int v, int marcado[], int distancia[]);
void push(int vertice);
int pop();
void ClearMem(Grafo *grafo);

int main() {
    int c, origem;
    int distancia[NUMERO_VERTICES], marcado[NUMERO_VERTICES] = { 0 };

    Grafo *grafoTeste = CriarGrafo(6);
    AdicionarAresta(grafoTeste, 0, 1);
    AdicionarAresta(grafoTeste, 0, 2);
    AdicionarAresta(grafoTeste, 1, 3);
    AdicionarAresta(grafoTeste, 2, 3);
    AdicionarAresta(grafoTeste, 3, 4);
    AdicionarAresta(grafoTeste, 3, 5);

    MostrarGrafo(grafoTeste);

    printf("\nEscolha um vértice para iniciar a busca:\n");
    scanf("%1d", &origem);
    while(((c = getchar() != '\n' && c != EOF))) {}

    printf("\nVértices visitados do grafo, iniciando em V%d\n", origem);
    BuscaLargura(grafoTeste, origem, marcado, distancia);
    printf("\n\n");

    ClearMem(grafoTeste);

    printf("Pressione enter para continuar...");
    getchar();
    return 0;
}

// Cria os vértices do grafo
Grafo* CriarGrafo(int totalVertices) {
    Grafo *grafo = malloc(sizeof(Grafo));
    grafo->totalVertices = totalVertices;
    grafo->ListaAdj = malloc(totalVertices*sizeof(ListaVizinhos*));
    for(int i = 0; i < totalVertices; i++) {
        grafo->ListaAdj[i] = NULL;
    }
    return grafo;
}

// Cria as arestas do grafo
void AdicionarAresta(Grafo* grafo, int origem, int destino) {
    
    // Aresta da origem para o destino
    ListaVizinhos *aresta = malloc(sizeof(ListaVizinhos));
    aresta->vertice = destino;
    aresta->prox = grafo->ListaAdj[origem];
    grafo->ListaAdj[origem] = aresta;

    // Aresta do destino para a origem
    aresta = malloc(sizeof(ListaVizinhos));
    aresta->vertice = origem;
    aresta->prox = grafo->ListaAdj[destino];
    grafo->ListaAdj[destino] = aresta;
}

void MostrarGrafo(Grafo *grafo) {    
    for(int i = 0; i < grafo->totalVertices; i++) {
        printf("Vértice %d:\n", i);
        ListaVizinhos *aux;
        aux = grafo->ListaAdj[i];        
        while(aux != NULL) {            
            printf("%d -> ", aux->vertice);            
            aux = aux->prox;
        }
        printf("\n");
    }
}

void ClearMem(Grafo *grafo) {
    for(int i = grafo->totalVertices; i >= 0 ; i--) {        
        ListaVizinhos *aux, *varredura;
        varredura = grafo->ListaAdj[i];        
        while(varredura != NULL) {                        
            aux = varredura;
            varredura = aux->prox;
            free(aux);
            aux = NULL;
        }              
    }
    free(grafo->ListaAdj);
    grafo->ListaAdj = NULL;
    free(grafo);
    grafo = NULL;
}

// Recebe como parâmetros o grafo, um vértice de origem onde se iniciará
// a busca em largura e um vetor para marcar com '1' os vértices visitados
void BuscaLargura(Grafo *Vizinhos, int v, int marcado[], int distancia[]) {
    int w, v_removido;
    ListaVizinhos *aux = NULL;
    
    // Marco o vértice de origem como visitado (VISITADO == ENFILEIRADO)
    marcado[v] = 1;

    // Distância de v para ele mesmo é 0
    distancia[v] = 0;    

    // Enfileiro o vértice de origem
    push(v);

    // Pega o head da lista encadeada do vértice de origem    
    while(head != NULL) {

        // Remove um vértice da fila
        v_removido = pop();
        aux = Vizinhos->ListaAdj[v_removido];

        // Laço para varrer a lista de vizinhos de um vértice
        for(int i = 0; i < NUMERO_VERTICES; i++) {            
            while(aux != NULL) {
                w = aux->vertice;

                // Se o vértice w não estiver marcado, calcular a distancia em
                // relação a origem e inseri-lo na fila para visitar seus 
                // vizinhos depois
                if(marcado[w] == 0) {
                    printf(" V%d\t", w);
                    marcado[w] = 1;
                    distancia[w] = distancia[v_removido] + 1;
                    push(w);
                }

                // Próximo vértice adjacente a v
                aux = aux->prox;
            }            
        }
    }

    printf("\nDistâncias:\n");        
    for(int i = 0; i < NUMERO_VERTICES; i++) {
        printf(" %d\t", distancia[i]);
    }   
}

void push(int vertice) {
    // Cria o novo elemento da lista
    QUEUE *elemento = malloc(sizeof(QUEUE));
    elemento->vertice = vertice;

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
     printf("\nElemento enfileirado: V%d\n", vertice);
}

int pop() {
    if(head == NULL) {
        printf("Fila vazia!\n");
        return 0;
    } else {        
        QUEUE *aux;
        aux = head;
        head = head->prox;        
        int v = aux->vertice;
        free(aux);
        aux = NULL;            
        printf("\nElemento removido: V%d\n", v);
        return v;
    }
}