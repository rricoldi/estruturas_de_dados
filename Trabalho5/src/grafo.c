#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"
#include "svg.h"
#include"geometria.h"

#define true 1
#define false 0
#define branco 0
#define amarelo 1
#define vermelho 2
#define infinito 2000000.0

typedef struct adjacencia {
    int vertice;
    char nomeDaRua[100];
    char ladoDireito[100];
    char ladoEsquerdo[100];
    double comprimento;
    double velocidade;
    struct adjacencia *proximo;
    double x1;
    double y1;
    double x2;
    double y2;
} Adjacencia;

typedef struct vertice {
    Adjacencia *inicio;
    char id[100];
    double x, y;
    bool ativo;
} Vertice;

typedef struct grafo {
    int numeroDeVertices;
    int numeroDeArestas;
    Vertice *arranjo;
    List *lista;
} Grafo;

Graph *criaGrafo(int numeroDeVertices) {
    Grafo *grafo = (Grafo *) malloc(sizeof(Grafo));
    grafo->numeroDeVertices = numeroDeVertices;
    grafo->numeroDeArestas = 0;
    grafo->arranjo = (Vertice *) malloc(numeroDeVertices*sizeof(Vertice));
    grafo->lista = criaLista();
    
    for(int i = 0; i<numeroDeVertices; i++) {
        grafo->arranjo[i].inicio = NULL;
        grafo->arranjo[i].ativo = true;
    }
    return grafo;
}

Adjacencia *criaAdjacencia(int noFinal, char nomeDaRua[], char ladoDireito[], char ladoEsquerdo[], double comprimento, double velocidade) {
    Adjacencia *aresta = (Adjacencia *) malloc(sizeof(Adjacencia));
    
    aresta->vertice = noFinal;
    strcpy(aresta->nomeDaRua, nomeDaRua);
    strcpy(aresta->ladoDireito, ladoDireito);
    strcpy(aresta->ladoEsquerdo, ladoEsquerdo);
    aresta->comprimento = comprimento;
    aresta->velocidade = velocidade;
    aresta->proximo = NULL;
    
    return aresta;
}

void defineInfoVertice(Graph* graph, int no, char id[], double x, double y) {
    Grafo* grafo = (Grafo*) graph;
    strcpy(grafo->arranjo[no].id, id);
    grafo->arranjo[no].x = x;
    grafo->arranjo[no].y = y;
}

Info getInfoVertice(Graph* graph, char id[]) {
    Grafo* grafo = (Grafo*) graph;
    Vertice* vertice;
    for(int i = 0; i < grafo->numeroDeVertices; i++) {
        if(strcmp(grafo->arranjo[i].id, id) == 0) {
            vertice->ativo = grafo->arranjo[i].ativo;
            strcpy(vertice->id, grafo->arranjo[i].id);
            vertice->x = grafo->arranjo[i].x;
            vertice->y = grafo->arranjo[i].y;
            
            return vertice;
        }
    }
}

double getX(Info info) {
    Vertice* vertice = (Vertice*) info;
    return vertice->x;
}

double getY(Info info) {
    Vertice* vertice = (Vertice*) info;
    return vertice->y;
}

char* getID(Info info) {
    Vertice* vertice = (Vertice*) info;
    return vertice->id;
}

int getIndiceVertice(Graph* graph, char id[]) {
    Grafo* grafo = (Grafo*) graph;
    for(int i = 0; i < grafo->numeroDeVertices; i++) {
        // printf("%s != %s      ", grafo->arranjo[i].id, id);
        if(strcmp(grafo->arranjo[i].id, id) == 0) {
            return i;
        }
    }
    return -1;
}

bool getAtivo(Info info) {
    Vertice* vertice = (Vertice*) info;
    return vertice->ativo;
}

void setLista(Graph* graph, List* lista) {
    Grafo* grafo = (Grafo*) graph;
    grafo->lista = lista;
}

List* getLista(Graph* graph) {
    Grafo* grafo = (Grafo*) graph;
    return grafo->lista;
}

void defineInfoAresta(Graph* graph, int noInicial, int noFinal, char nomeDaRua[], char ladoDireito[], char ladoEsquerdo[], double comprimento, double velocidade) {
    Grafo* grafo = (Grafo*) graph;
    Adjacencia *aresta = grafo->arranjo[noInicial].inicio;
    
    while(aresta) {
        if(aresta->vertice == noFinal){
            aresta->vertice = noFinal;
            strcpy(aresta->nomeDaRua, nomeDaRua);
            strcpy(aresta->ladoDireito, ladoDireito);
            strcpy(aresta->ladoEsquerdo, ladoEsquerdo);
            aresta->comprimento = comprimento;
            aresta->velocidade = velocidade;
            return;
        }
        aresta = aresta->proximo;
    }
    
    printf("Aresta nao encontrada\n");
}

Info getInfoAresta(Graph* graph, int noInicial, int noFinal) {
    Grafo* grafo = (Grafo*) graph;
    Adjacencia *aresta = grafo->arranjo[noInicial].inicio;
        while(aresta) {
            if(aresta->vertice == noFinal){
              return aresta;
            }
            aresta = aresta->proximo;
        }
        printf("Aresta nao encontrada\n");
        return NULL;
}

double arestaGetX1(Info info){
    Adjacencia *aresta = info;
    return aresta->x1;
}
double arestaGetY1(Info info){
    Adjacencia *aresta = info;
    return aresta->y1;
}
double arestaGetX2(Info info){
    Adjacencia *aresta = info;
    return aresta->x2;
}
double arestaGetY2(Info info){
    Adjacencia *aresta = info;
    return aresta->y2;
}
void setArestaComprimento(Info info, double comprimento){
    Adjacencia* aresta = info;
    aresta->comprimento = comprimento;
}
void setArestaVelocidade(Info info, double velocidade){
    Adjacencia* aresta = info;
    aresta->velocidade = velocidade;
}

void percorreArestas(Graph g, void (*func) (Reta*, Info, int), Reta* polig, int tamPolig){
    Grafo *graf = g;
    Vertice* aux = graf->arranjo;
    for(int i=0;i<graf->numeroDeVertices;i++){
        Adjacencia* aux2 = aux[i].inicio;
        while(aux2){
            func(polig, aux2, tamPolig);
            aux2 = aux2->proximo;
        }
    }
}

void removeAresta(Graph* graph, int noInicial, int noFinal) {
    Grafo* grafo = (Grafo*) graph;
    Adjacencia *adjacencia = grafo->arranjo[noInicial].inicio;
    Adjacencia *aux;
    while(adjacencia) {
        if(adjacencia->vertice == noFinal){
            grafo->numeroDeArestas--;
            if(grafo->arranjo[noInicial].inicio == adjacencia){
                grafo->arranjo[noInicial].inicio = adjacencia->proximo;
            } else {
                aux->proximo = adjacencia->proximo;
            }              
            free(adjacencia);
            return;
        }
        aux = adjacencia;
        adjacencia = adjacencia->proximo;        
    }

    printf("Aresta nao encontrada\n");
}

bool insereAresta(Graph* graph, int noInicial, int noFinal, char ladoDireito[], char ladoEsquerdo[], double comprimento, double velocidade, char nomeDaRua[]) {
    Grafo* grafo = (Grafo*) graph;
    if(!grafo)
        return false;
    if(noFinal < 0 || noFinal >= grafo->numeroDeVertices)
        return false;
    if(noInicial < 0 || noInicial >= grafo->numeroDeVertices)
        return false;

    Adjacencia *novo = criaAdjacencia(noFinal, nomeDaRua, ladoDireito, ladoEsquerdo, comprimento, velocidade);
    novo->x1 = grafo->arranjo[noInicial].x;
    novo->y1 = grafo->arranjo[noInicial].y;
    novo->x2 = grafo->arranjo[noFinal].x;
    novo->y2 = grafo->arranjo[noFinal].y;
    novo->proximo = grafo->arranjo[noInicial].inicio;
    grafo->arranjo[noInicial].inicio = novo;

    grafo->numeroDeArestas ++;

    return true;
}

void iniciaDijkstra(Grafo* grafo, double* distancia, int* pai, int noInicial) {
    for(int i = 0; i < grafo->numeroDeVertices; i++) {
        distancia[i] = infinito;
        pai[i] = -1;
    }
    distancia[noInicial] = 0.0;
}

void relaxaComprimento(Grafo* grafo, double* distancia, int* pai, int no1, int no2) {
    if(grafo->arranjo[no2].ativo == false)
        return;

    Adjacencia* aresta = grafo->arranjo[no1].inicio;

    while(aresta && aresta->vertice != no2) 
        aresta = aresta->proximo;

    if(aresta) {
        if(distancia[no2] > distancia[no1] + aresta->comprimento) {
            distancia[no2] = distancia[no1] + aresta->comprimento;
            pai[no2] = no1;
        }
    }
}

void relaxaVelocidade(Grafo* grafo, double* distancia, int* pai, int no1, int no2) {
    if(grafo->arranjo[no2].ativo == false)
        return;
    
    Adjacencia* aresta = grafo->arranjo[no1].inicio;

    while(aresta && aresta->vertice != no2) 
        aresta = aresta->proximo;

    if(aresta) {
        if(distancia[no2] > distancia[no1] + (aresta->velocidade)) {
            distancia[no2] = distancia[no1] + (aresta->velocidade);
            pai[no2] = no1;
        }
    }
}

bool existeAberto(Grafo* grafo, int* aberto) {
    for(int i = 0; i < grafo->numeroDeVertices; i++) {
        if(aberto[i])
            return true;
    }
    
    return false;
}

int menorDistancia(Grafo* grafo, int* aberto, double* distancia) {
    int i = 0, menor;
    
    while(i < grafo->numeroDeVertices) {
        if(aberto[i])
            break;
        i++;
    }
    
    if(i == grafo->numeroDeVertices)
        return -1;
    
    menor = i;

    for(i = i+1; i < grafo->numeroDeVertices; i++) {
        if(aberto[i] && distancia[menor] > distancia[i])
            menor = i;
    }
    return menor;
}

void auxilioDirecao(Graph graph, int *caminho, int modo, int noFinal) {
    Grafo* grafo = (Grafo*) graph;
    char *direcaoAnterior;
    int i;
    Adjacencia* aresta;
    char *direcao;
    char comando[3];
    double x, y, xInicial, yInicial;

    for(i = 0; i < grafo->numeroDeVertices - 1; i++) {
        if(caminho[i] == -1)
            continue;
        aresta = (Adjacencia*) getInfoAresta(grafo, caminho[i], caminho[i+1]);
        if(grafo->arranjo[caminho[i]].x < grafo->arranjo[caminho[i+1]].x)
            direcao = "Oeste";
        else if(grafo->arranjo[caminho[i]].x > grafo->arranjo[caminho[i+1]].x)
            direcao = "Leste";
        else if(grafo->arranjo[caminho[i]].y < grafo->arranjo[caminho[i+1]].y)
            direcao = "Norte";
        else if(grafo->arranjo[caminho[i]].y > grafo->arranjo[caminho[i+1]].y)
            direcao = "Sul";

        xInicial = grafo->arranjo[caminho[i]].x;
        yInicial = grafo->arranjo[caminho[i]].y;
        break;
    }
    x = xInicial;
    y = yInicial;

    while(1){
        if(distanciaPontos(criarPonto(x,y), criarPonto(xInicial,yInicial)) > 200)
            caminho = dijkstra(graph, retornaIndiceVertice(grafo->lista, x, y), noFinal, "removivel.svg", "removivel.txt", "black", "black", modo);
        if(x == grafo->arranjo[noFinal].x && y == grafo->arranjo[noFinal].y) {
            printf("Voce chegou ao seu destino.\n");
        }
        printf("Va para o ");
        for(i = 0; i < grafo->numeroDeVertices - 1; i++) {
            if(caminho[i] == -1)
                continue;
            aresta = (Adjacencia*) getInfoAresta(grafo, caminho[i], caminho[i+1]);
            if(x < grafo->arranjo[caminho[i+1]].x)
                direcao = "Oeste";
            else if(x > grafo->arranjo[caminho[i+1]].x)
                direcao = "Leste";
            else if(y < grafo->arranjo[caminho[i+1]].y)
                direcao = "Norte";
            else if(y > grafo->arranjo[caminho[i+1]].y)
                direcao = "Sul";

            printf("%s.\n", direcao);
            break;
        }
        scanf("%s", comando);
        if(strcmp(comando, "n") == 0) {
            y++;   
        } else if(strcmp(comando, "s") == 0) {
            x--;   
        } else if(strcmp(comando, "l") == 0) {
            y--;   
        } else if(strcmp(comando, "o") == 0) {
            x++;   
        } else if(strcmp(comando, "rr") == 0) {
            caminho = dijkstra(graph, retornaIndiceVertice(grafo->lista, x, y), noFinal, "removivel.svg", "removivel.txt", "black", "black", 2);
        } else if(strcmp(comando, "rc") == 0) {
            caminho = dijkstra(graph, retornaIndiceVertice(grafo->lista, x, y), noFinal, "removivel.svg", "removivel.txt", "black", "black", 1);
        } else if(strcmp(comando, "x") == 0) {
            remove("removivel.svg");
            remove("removivel.txt");
            return;
        }
    }

}

int* dijkstra(Graph* graph, int noInicial, int noFinal, char nomeDoArquivoSvg[], char nomeDoArquivoTxt[], char cor1[], char cor2[], int modo) {
    if(noInicial == -1 || noFinal == -1) {
        printf("Os vertices nao foram encontrados");
        exit(1);
    }

        FILE* arquivoTxt = fopen(nomeDoArquivoTxt, "a+");
        Grafo* grafo = (Grafo*) graph;
        double* distancia = (double*) malloc(grafo->numeroDeVertices*sizeof(double));
        int* caminho = (double*) malloc(grafo->numeroDeVertices*sizeof(double));
        int pai[grafo->numeroDeVertices];
        int menor, aux, i;
        char* direcao, *direcaoAnterior;
        int aberto[grafo->numeroDeVertices];
        Adjacencia* aresta;
        
        
        iniciaDijkstra(grafo, distancia, pai, noInicial);

        for(i = 0; i < grafo->numeroDeVertices; i++) 
            aberto[i] = true;

        while (existeAberto(grafo, aberto))
        {
            menor = menorDistancia(grafo, aberto, distancia);
            aberto[menor] = false;

            aresta = grafo->arranjo[menor].inicio;
            while(aresta) {
                if(modo == 2)
                    relaxaVelocidade(grafo, distancia, pai, menor, aresta->vertice);
                else
                    relaxaComprimento(grafo, distancia, pai, menor, aresta->vertice);
                    
                aresta = aresta->proximo;
            }
        }

        aux = noFinal;

        for(i = 0; i < grafo->numeroDeVertices; i++)
            caminho[i] = -1;

        i = grafo->numeroDeVertices-1;
        while(aux != -1) {
            caminho[i] = aux;
            i--;
            aux = pai[aux];
        }
            imprimirCirculo(3, grafo->arranjo[caminho[grafo->numeroDeVertices - 1]].x, grafo->arranjo[caminho[grafo->numeroDeVertices - 1]].y, "red", "black", nomeDoArquivoSvg, 2);        
            escreverNoSvg(grafo->arranjo[caminho[grafo->numeroDeVertices - 1]].x, grafo->arranjo[caminho[grafo->numeroDeVertices - 1]].y, "DESTINO", nomeDoArquivoSvg);
        for(i = 0; i < grafo->numeroDeVertices - 1; i++) {
            if(caminho[i] == -1)
                continue;

            if(modo == 1)
                imprimirLinha2(grafo->arranjo[caminho[i]].x, grafo->arranjo[caminho[i]].y, grafo->arranjo[caminho[i+1]].x, grafo->arranjo[caminho[i+1]].y, cor1, nomeDoArquivoSvg);
            else
                imprimirLinha2(grafo->arranjo[caminho[i]].x - 4, grafo->arranjo[caminho[i]].y - 4, grafo->arranjo[caminho[i+1]].x - 4, grafo->arranjo[caminho[i+1]].y - 4, cor2, nomeDoArquivoSvg);
        }


        if(modo == 1)
            fprintf(arquivoTxt, "Caminho mais curto: ");
        else
            fprintf(arquivoTxt, "Caminho mais rapido: ");


        direcaoAnterior = "direcaoAnterior";

        for(i = 0; i < grafo->numeroDeVertices - 1; i++) {
            if(caminho[i] == -1)
                continue;
            aresta = (Adjacencia*) getInfoAresta(grafo, caminho[i], caminho[i+1]);
            if(grafo->arranjo[caminho[i]].x < grafo->arranjo[caminho[i+1]].x)
                direcao = "Oeste";
            else if(grafo->arranjo[caminho[i]].x > grafo->arranjo[caminho[i+1]].x)
                direcao = "Leste";
            else if(grafo->arranjo[caminho[i]].y < grafo->arranjo[caminho[i+1]].y)
                direcao = "Norte";
            else if(grafo->arranjo[caminho[i]].y > grafo->arranjo[caminho[i+1]].y)
                direcao = "Sul";

            // printf("%s %s %d\n", direcao, direcaoAnterior, contador);
            if(direcaoAnterior == "direcaoAnterior") {
                fprintf(arquivoTxt, "Siga na direcao %s na Rua %s ", direcao, aresta->nomeDaRua);
            }
            else if(direcao != direcaoAnterior) {
                fprintf(arquivoTxt, "ate o cruzamento com a Rua %s. ", aresta->nomeDaRua);
                fprintf(arquivoTxt, "Siga na direcao %s na Rua %s ", direcao, aresta->nomeDaRua);        
            }
            
            direcaoAnterior = direcao;
        }
        if(strcmp(direcaoAnterior, "direcaoAnterior") == 0){
            fprintf(arquivoTxt, "Nao ha caminho entre esses dois pontos.\n");        
        } else {
            fprintf(arquivoTxt, ". Chegou em seu destino.\n");
        }
        fclose(arquivoTxt);

        free(distancia);

            return caminho;
}

// void imprimeGrafo(Graph* graph) {
//         Grafo* grafo = (Grafo*) graph;
//     if (grafo == NULL) {
//         printf("Grafo vazio!\n");
//         return;
//     }

//     printf("Vertices: %d. Arestas: %d.\n", grafo->numeroDeVertices, grafo->numeroDeArestas);

//     for(int i = 0; i < grafo->numeroDeVertices; i++) {
//         printf("v%d: ", i);
//         Adjacencia *adjacencia = grafo->arranjo[i].inicio;
//         while(adjacencia) {
//             printf("v%d ", adjacencia->vertice);

//             adjacencia = adjacencia->proximo;
//         }
//         printf("\n");
//     }
// }
