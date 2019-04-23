#include <stdio.h>
#include <stdlib.h>


// ----------------------------------------- // --------------------------------------------------- // ---------------------------------------------------------- // ----------------------------------
//INCLUINDO LISTA ENCADEADA
typedef struct dadoLista{
    int dest,peso;
}dadoLista;

typedef struct element{
    dadoLista dados;
    struct element *pNext;
}element;

typedef struct lista{
    element *pFirst;
}SLista;

int pushLista(SLista *pLista, element pElement, int nIndex){
    element *pAtual,*pAnterior,*pelement;
    pelement = malloc(sizeof(element));
    *pelement = pElement;
    int nPos;

    if(pLista->pFirst == NULL && nIndex != 0){
        printf("Index inválido.\n");
        return 0;
    }

    if(pLista->pFirst == NULL && nIndex == 0){
        pLista->pFirst = pelement;
        pLista->pFirst->pNext = NULL;
        return 1;
    }
    if(nIndex == 0){
        pelement->pNext = pLista->pFirst;
        pLista->pFirst = pelement;
        return 1;
    }

    pAtual= pLista->pFirst;
    for(nPos = 0;nPos < nIndex && pAtual != NULL;nPos++){
        pAnterior = pAtual;
        pAtual = pAtual->pNext;
    }

    if(!pAtual){
        printf("Index invalido.\n");
        return 0;
    }
    pAnterior->pNext = pelement;
    pelement->pNext = pAtual;
    return 1;
}

int popLista(SLista *pLista, element *pelement,int nIndex){
    if(pLista->pFirst == NULL){
        printf("Lista vazia.\n");
        return 0;
    }
    if(nIndex == 0){
        element *temp;
        *pelement = *(pLista->pFirst);
        temp = pLista->pFirst;
        pLista->pFirst = pLista->pFirst->pNext;
        free(temp);
        return 1;
    }

    element *pAtual,*pAnterior;
    int nPos;
    for(nPos=0;nPos < nIndex && pAtual != NULL;nPos++){
        pAnterior = pAtual;
        pAtual = pAtual->pNext;
    }

    if(!pAtual){
        printf("Index invalido.\n");
        return 0;
    }

    *pelement = *pAtual;
    pAnterior->pNext = pAtual->pNext;
    free(pAtual);

    return 1;


}

void ClearLista(SLista *pLista){
    element *pAtual,*pAnterior;
    int nPos;

    pAtual = pLista->pFirst;

    for(nPos=0; pAtual != NULL;nPos++){
        pAnterior = pAtual;
        pAtual = pAtual->pNext;
        free(pAnterior);
    }
    free(pLista);
}

void ResetLista(SLista *pLista){
    ClearLista(pLista);
    pLista =(SLista *)malloc(sizeof(SLista));
    pLista->pFirst= NULL;
}


// ----------------------------------------- // --------------------------------------------------- // ---------------------------------------------------------- // ----------------------------------
typedef struct vertice{
    SLista *listaAdj;
    int tamLista,n;
}vertice;


typedef struct Grafo{
    vertice *vertices;
}Grafo;
/*
grafo conexo
vai pegando o menor custo atual
int custo = 0;
v = origem;
while(1){
    menor = -1;
    dest = 0;
    flag = 0;
    for(i=0;i<vizinhos.length();i++){
        if(destino == vizinho[i].n){
            menor = vizinho[i];
            dest = i;
            break;
        }
        if(menor > vizinho[i]){
            k=0;
            for(k=0;k<j;k++){
                if(caminho[k] = vizinho[i].n){
                    break;
                }
            }
            if(k == j){
                menor = vizinho[i];
                dest = i;
            }
        }
    }
    if(i != vizinhos.length()){
        caminho[j] = vizinho[dest].n;
        custo = custo + menor;
        break;
    }
    if(menor == -1)
        break;
    caminho[j] = vizinho[dest].n;
    custo = custo + menor;
    v = vizinhos[dest];
    j++;
}
*/

void guloso(Grafo g,int origem, int tam,int destino){
    int j,i,flag,caminho[tam],custo = 0;
    vertice v = g.vertices[origem];
    j=1;
    flag = 0;
    caminho[0] = origem;
    while(1){
        int dest,k,menor = 2000000;
        element x;
        element backup[20];
        caminho[j] = -1;
        for(i=0;i<=v.tamLista;i++){
            popLista(v.listaAdj,&x,0);
            backup[i] = x;

            if(destino == x.dados.dest){
                menor = x.dados.peso;
                dest = x.dados.dest;
                break;
            }
            if(menor > x.dados.peso){
                for(k=0;k<j;k++){
                    if(caminho[k] == x.dados.dest ){
                        break;
                    }
                }
                if(k == j){
                    menor = x.dados.peso;
                    dest = x.dados.dest;
                }
            }
        }
        for(k=0;k<i;k++){
            pushLista(v.listaAdj,backup[k],0);
        }

        if(menor == 2000000){
             flag = 1;
             break;
        }

        if(i != v.tamLista+1){ //se quebrou antes é pq chegou no destino

            caminho[j] = dest;
            custo = custo + menor;
            j++;
            break;
        }

        caminho[j] = dest;
        custo = custo + menor;
        v = g.vertices[dest];
        j++;
    }
    //erro no caminho -> não existe solução gulosa
    if(flag == 1){
        printf("Não existe solução gulosa para o caminho de %d ate %d\n",origem,destino);
        return;
    }

    //achei o caminho
    printf("O caminho encontrdo de forma gulosa foi:\n");
    for(i=0;i<j;i++){
        printf("%d ",caminho[i]);
    }
    printf("\nE seu custo foi de: %d\n",custo);

}

int main()
{
    int qVertices,i,qArestas,origem,destino,peso;
    Grafo g;
    printf("Quantos vértices o grafo tem(max 20)?\n");
    scanf("%d",&qVertices);
    g.vertices =  malloc(qVertices * sizeof(vertice));

    for(i=0;i<qVertices;i++){
        g.vertices[i].tamLista = -1; //botando -1 eu sei que nao existe lista naquele vertice, só serao criadas listas que serão usadas
        g.vertices[i].n = i;
    }
    printf("Quantas arestas tem este grafo?\n");
    scanf("%d",&qArestas);

    for(i=0;i<qArestas;i++){
        printf("Digite a origem da aresta, o destino e seu peso(o grafo começa pelo vértice 0 e vai até o vertice %d)\n", qVertices-1);
        scanf("%d%d%d",&origem,&destino,&peso);
        dadoLista novoDado;
        novoDado.dest = destino;
        novoDado.peso = peso;
        element novoEle;
        novoEle.dados = novoDado;

        if(g.vertices[origem].tamLista == -1){
            g.vertices[origem].listaAdj = malloc(sizeof(SLista));
            g.vertices[origem].listaAdj->pFirst = NULL;
        }
        g.vertices[origem].tamLista = g.vertices[origem].tamLista + 1;
        pushLista(g.vertices[origem].listaAdj,novoEle,0);

        if(g.vertices[destino].tamLista == -1){
            g.vertices[destino].listaAdj = malloc(sizeof(SLista));
            g.vertices[destino].listaAdj->pFirst = NULL;
        }
        g.vertices[destino].tamLista = g.vertices[destino].tamLista + 1;
        pushLista(g.vertices[destino].listaAdj,novoEle,0);


    }
    printf("Digite o vertice de origem\n");
    scanf("%d",&origem);

    printf("Digite o vertice de destino\n");
    scanf("%d",&destino);


    guloso(g,origem,qArestas,destino);

    for(i=0;i<qVertices;i++){
        if(g.vertices[i].tamLista != -1)
            free(g.vertices->listaAdj);
    }
    free(g.vertices);
    return 0;
}
