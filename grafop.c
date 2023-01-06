// ### GRAFO COM LISTA DE ADJACÊNCIAS ###
// ### com implementação de busca em PROFUNDIDADE ###
// ### depth-first search (DFS) ###
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
struct stack {
    int vertice;
    struct stack *prox;
} *top = NULL;
typedef struct stack STACK;

Grafo* CriarGrafo(int totalVertices);
void AdicionarAresta(Grafo* grafo, int origem, int destino);
void MostrarGrafo(Grafo *grafo);
void BuscaProfundidade(Grafo *Vizinhos, int v, int marcado[]);
void push(int vertice);
void pop();
void ClearMem(Grafo *grafo);

int main() {
    int c, origem;
    int marcado[NUMERO_VERTICES] = { 0 };

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
    BuscaProfundidade(grafoTeste, origem, marcado);
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
// a busca em profundidade e um vetor para marcar com '1' os vértices visitados
void BuscaProfundidade(Grafo *Vizinhos, int v, int marcado[]) {
    int w;
    ListaVizinhos *aux = NULL;
    
    // Marco o vértice de origem como visitado (VISITADO == EMPILHADO)
    marcado[v] = 1;
    printf("\nElemento empilhado: V%d", v);

    // Empilho o vértice de origem
    push(v);

    // Pego o head da minha lista encadeada do vértice de origem
    aux = Vizinhos->ListaAdj[v];
    while(aux != NULL) {

        // Mantem o vértice que estou visitando da lista encadeada atual
        w = aux->vertice;

        // Verifica se o vértice w já foi visitado ou não
        if(marcado[w] != 1) {

            // Se não foi visitado, vou chamar recursivamente BuscaProfundidade
            // para localizar vértices ainda não visitados
            BuscaProfundidade(Vizinhos, w, marcado);
        }

        // Passo para o próximo elemento da minha lista de varredura
        aux = aux->prox;
    }
    // Desempilho
    pop();
}

void push(int vertice) {    
    STACK *elemento = malloc(sizeof(STACK));
    elemento->vertice = vertice;

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
        STACK *aux;
        aux = top;
        top = top->prox;
        printf("\nElemento removido: V%d", aux->vertice);
        free(aux);
        aux = NULL;                    
    }
}