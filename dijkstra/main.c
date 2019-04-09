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


//INCLUINDO FILA

typedef struct nodo{
    vertice dados;
    struct nodo *pNext;
}Snodo;

typedef struct fila{
    Snodo *pFirst;
    Snodo *pLast;
}Sfila;

void push(Sfila *pFila,vertice *dados){
    Snodo *pNovo;
    pNovo = (Snodo*)malloc(sizeof(Snodo));
    if(!pNovo){
        printf("Erro alocando memo.\n");
        return;
    }
    pNovo->dados = *dados;
    pNovo->pNext = NULL;

    if(pFila->pLast != NULL)
        pFila->pLast->pNext = pNovo;
    else
        pFila->pFirst = pNovo;

    pFila->pLast = pNovo;
}

int pop(Sfila *pFila,vertice *dados){
    if(pFila->pFirst == NULL){
        printf("Lista vazia.\n");
        return 0;
    }

    Snodo *pNodo;

    pNodo = pFila->pFirst;
    *dados = pFila->pFirst->dados;
    pFila->pFirst= pFila->pFirst->pNext;

    if(pFila->pFirst == NULL)
        pFila->pLast = NULL;

    free(pNodo);
    return 1;
}

/*void imprimeFila(Sfila *pFila){
    element *pelement;
    if(pFila->pFirst == NULL){
        printf("Fila vazia.\n");
        return;
    }

    for(pelement = pFila->pFirst;pelement != NULL;pelement = pelement->pNext){
        printf("Nome: %s\t Idade:%d\n",pelement->dados.nome,pelement->dados.idade);
    }
}*/

void Clear(Sfila *pFila){
    Snodo *pNodo,*pAnt;
    int flag=0;
    if(pFila->pFirst == NULL)
        return;
    for(pNodo = pFila->pFirst;pNodo != NULL;pNodo = pNodo->pNext){
        if(flag)
            free(pAnt);
        pAnt = pNodo;
        flag = 1;
    }
    if(flag)
        free(pAnt);

}

Sfila *Reset(Sfila *pFila){
    Clear(pFila);

    free(pFila);
    pFila =(Sfila *) malloc(sizeof(Sfila));
    if(!pFila){
        printf("Erro alocando memo.\n");
        return;
    }

    pFila->pFirst = NULL;
    pFila->pLast = NULL;

    return pFila;
}

// ----------------------------------------- // --------------------------------------------------- // ---------------------------------------------------------- // -----------------------------------

/*construir um grafo ponderado --> CHECK
zerar tamLista de ad --> CHECK
ler os pesos das arestas --> CHECK
dijkstra:
  vetor d(distancia) que contem as distancias da origem até cada vértice --> CHECK
  vetor od que contem a origem --> CHECK
  inicializa tudo como infinito --> CHECK
  seta d[origem] = 0 --> CHECK
  começa o algo(v = origem): --> CHECK
    expande v ->    --> CHECK
        pega todas as ligações e compara a menor distancia: --> CHECK
            vizinho = v.vizinhos;   --> CHECK
            j=0;    --> CHECK
            while(vizinho != null){ --> CHECK
                Nó valores[] = (endVizinho, d[v] + custo(v,vizinho));   --> CHECK
                if(d[vizinho] > d[v] + custo(v,vizinho))    --> CHECK
                    d[vizinho] = d[v] + custo(v,vizinho));  --> CHECK
                j++;    --> CHECK
            }   --> CHECK
            sort(valores);--> CHECK
            for(i=0;i<j;i++){   --> CHECK
                fila.insert(valores[i]);    --> CHECK
            }   --> CHECK
            começa o algo de novo   --> CHECK
*/



typedef struct Grafo{
    vertice *vertices;
}Grafo;


void dijkstra(Grafo g,int origem,int tam,int f){
    int i,*d,*od;//od é a origem da distancia, pra saber qual o caminho de verdade
    Sfila *pFila;
    pFila =(Sfila *) malloc(sizeof(Sfila));
     if(!pFila){
        printf("Erro alocando memo.\n");
        return;
    }
    pFila->pFirst = NULL;
    pFila->pLast = NULL;

    d = malloc(sizeof(int)*tam);
    od = malloc(sizeof(int)*tam);
    for(i=0;i<tam;i++){
        d[i] = 2147483646;
    }
    d[origem] = 0;

    push(pFila,&g.vertices[origem]);

    while(pFila->pFirst != NULL){
        vertice rPop;
        pop(pFila,&rPop);
        i = 0;  //aqui o i vai ter a quantidade de vizinhos
        element *aux;
        dadoLista vetorPOrdenar[g.vertices[rPop.n].tamLista + 1],auxDado;

        if(g.vertices[rPop.n].tamLista != -1){
            for(aux = g.vertices[rPop.n].listaAdj->pFirst; aux != NULL; aux = aux->pNext){ //percorre os vizinhos
                vetorPOrdenar[i] = aux->dados;
                i++;
                if(d[aux->dados.dest] > d[rPop.n] + aux->dados.peso){ //aux representa uma aresta, destino é numero do vizinho, peso é peso(lol) da aresta(lol²)
                    d[aux->dados.dest] = d[rPop.n] + aux->dados.peso;
                    od[aux->dados.dest] = rPop.n;
                }
            }
            //ordenar vetor
            int j;
            if(i >= 2){
                int k;
                //bubble
                for(j=0;j<i;j++){
                    for(k=0;k<j-1;k++){
                        if(vetorPOrdenar[k].peso > vetorPOrdenar[k+1].peso){
                            auxDado = vetorPOrdenar[k];
                            vetorPOrdenar[k] = vetorPOrdenar[k+1];
                            vetorPOrdenar[k+1] = auxDado;
                        }
                    }
                }
            }
            //ordenado
            for(j=0;j<i;j++){
                push(pFila,&g.vertices[vetorPOrdenar[j].dest]);
            }
        }
    }
    //ja tem os menores valores em d
    printf("O custo do menor caminho do vertice %d ate o vertice %d e: %d.\n",origem,f,d[f]);
    free(d);
    free(od);
    free(pFila);
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
        printf("Digite a origem da aresta, o destino e seu peso(o grafo começa pelo vértice 0 e vai até o vertice %d pesos não podem ser negativos)\n", qVertices-1);
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
    }
    printf("Digite o vertice de origem para o calculo de menor caminho(pelo algoritmo de dijkstra)\n");
    scanf("%d",&origem);

    printf("Digite o vertice de destino para o calculo de menor caminho(pelo algoritmo de dijkstra)\n");
    scanf("%d",&destino);


    dijkstra(g,origem,qVertices,destino);
    for(i=0;i<qVertices;i++){
        if(g.vertices[i].tamLista != -1)
            free(g.vertices->listaAdj);
    }
    free(g.vertices);
    return 0;
}
