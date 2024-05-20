#include "grafo.h"

void imprimeAresta(ARESTA *a){
    if(a->relacao != 1){
        printf("Peso: %d\n", a->peso);
        printf("Coeficiente de Jaccard: %.2f\n", a->coeficienteJaccard);
        printf("Media: %.2f\n", a->media);
        printf("Vertice destino: %s\n", a->nomeDestino);  
//        if(a->relacao == 1){
//            printf("Relacao: Conhecido\n");    
//        }  
        if(a->relacao == 2){
            printf("Relacao: Colega\n");    
        }  
        if(a->relacao == 3){
            printf("Relacao: Amizade\n");    
        }  
        if(a->relacao == -1){
            printf("Relacao: Conflito\n");    
        }             
        printf("\n"); 
    }
}

void imprimeVertice(VERTICE *v){
    printf("Vertice: %s\n", v->nomeVertice);
    //printf("Numero Vertice: %d\n\n", v->numVertice);
    printf("ARESTAS:\n");
    for(ARESTA *a = v->listaArestas; a != NULL; a = a->prox){
        imprimeAresta(a);
    }
    printf("\n\n");
}

void imprimeGrafo(GRAFO *g){
    if(g->orientado){
        printf("O grafo eh orientado.\n");
    } else{
        printf("O grafo nao eh orientado.\n");
    }
    for(VERTICE *v = g->listaVertices; v != NULL; v = v->prox){
        imprimeVertice(v);
    }
}

GRAFO* inicializaGrafo(){
    GRAFO *g = malloc(sizeof(GRAFO));
    g->listaVertices = NULL;
    g->orientado = 0;
    g->qtdeVertices = 0;
    return g;
}

VERTICE* insereVertice(VERTICE *v, GRAFO *g){
    v->prox = NULL;
    if(g->listaVertices == NULL){
        g->listaVertices = v;
    } else{
        VERTICE *corredor;
        for(corredor = g->listaVertices; corredor->prox != NULL; corredor = corredor->prox);
        corredor->prox = v;
    }
    return g->listaVertices;
}

ARESTA* insereAresta(ARESTA *a, VERTICE *v){
    a->prox = NULL;
    if(v->listaArestas == NULL){
        v->listaArestas = a;
    } else{
        ARESTA *corredor;
        for(corredor = v->listaArestas; corredor->prox != NULL; corredor = corredor->prox);
        corredor->prox = a;
    }
    return v->listaArestas;
}

VERTICE *buscaVertice(GRAFO *g, char nomeVertice[]){
    VERTICE *corredor;
    for(corredor = g->listaVertices; corredor != NULL; corredor = corredor->prox){
        if(strcmp(nomeVertice, corredor->nomeVertice) == 0){
            return corredor;
        }
    }
    return NULL;
}

ARESTA* buscaAresta(VERTICE *v, char nomeDestino[]){
    ARESTA *corredor;
    for(corredor = v->listaArestas; corredor != NULL; corredor = corredor->prox){
        if(strcmp(nomeDestino, corredor->nomeDestino) == 0){
            return corredor;
        }
    }
    return NULL;
}

int calculaPeso(int a, int b){
    if(a == -1 || b == -1){
        return 0;
    }
    if(a > 2 && b > 2){
        return 1;
    } else{
        return 0;
    }
}

float calculaMedia(int a, int b){
    int c;
    c = a+b;
    return (float) c/2;
}

//AQUI
void calculaPesoArestas(GRAFO *g){
    VERTICE *v, *v2;
    ARESTA *a, *a2;
    int peso;
    for(v = g->listaVertices; v != NULL; v = v->prox){
        for(a = v->listaArestas; a != NULL; a = a->prox){
            v2 = buscaVertice(g, a->nomeDestino);
            if(v2->numVertice > v->numVertice){
                a2 = buscaAresta(v2, v->nomeVertice);
                peso = calculaPeso(a->relacao, a2->relacao);
                a->peso = peso;
                a2->peso = peso;
            }
        }
    }
}

//AQUI
int vizinhoComum(VERTICE *v1, VERTICE *v2, GRAFO *g){
    ARESTA *a, *a2;
    VERTICE *aux, *aux2;
    for(a = v1->listaArestas; a != NULL; a = a->prox){
        if(a->relacao > 1){
            aux = buscaVertice(g, a->nomeDestino);
            if(aux != v2){
                for(a2 = v2->listaArestas; a2 != NULL; a2 = a2->prox){
                    if(a2->relacao > 1){                        
                        aux2 = buscaVertice(g, a2->nomeDestino);
                        if(aux == aux2){
                            return 1;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

//AQUI
int calculaPontesLocais(GRAFO *g){
    VERTICE *v, *v2;
    ARESTA *a;
    int pontes = 0;
    for(v = g->listaVertices; v != NULL; v = v->prox){
        for(a = v->listaArestas; a != NULL; a = a->prox){
            if(a->relacao > 1){
                v2 = buscaVertice(g, a->nomeDestino);
                if(v2->numVertice > v->numVertice){
                    if(!vizinhoComum(v, v2, g)){
                        pontes++;
                    }
                }
            }
        }
    }
    return pontes;
}

int uniao(VERTICE *v1, VERTICE *v2){
    ARESTA *corredor;
    ARESTA *aux;
    int cont = 0;
    for(corredor = v1->listaArestas; corredor != NULL; corredor = corredor->prox){
        if(corredor->relacao > 1){
            if(strcmp(corredor->nomeDestino, v2->nomeVertice) != 0){
                cont++;
            }
        }
    }
    int i = 0;
    for(corredor = v2->listaArestas; corredor != NULL; corredor = corredor->prox){
        if(corredor->relacao > 1){
            if(strcmp(corredor->nomeDestino, v1->nomeVertice) != 0){
                aux = buscaAresta(v1, corredor->nomeDestino);
                if(aux->relacao < 2 || aux == NULL){
                    //printf("%s  ", corredor->nomeDestino);
                    cont++;
                }
            }
        }
    }
    return cont;
}

int intersecao(VERTICE *v1, VERTICE *v2){
    ARESTA *corredor;
    ARESTA *aux;
    int cont = 0;
    for(corredor = v1->listaArestas; corredor != NULL; corredor = corredor->prox){
        if(corredor->relacao > 1){
            aux = buscaAresta(v2, corredor->nomeDestino);
            if(aux && aux->relacao > 1){
                cont++;
            }
        }
    }
    return cont;
}

void calculaCoefJaccard(GRAFO *g){
    VERTICE *v, *v2;
    ARESTA *a;
    int un, inters;
    for(v = g->listaVertices; v != NULL; v = v->prox){
        for(a = v->listaArestas; a != NULL; a = a->prox){
            v2 = buscaVertice(g, a->nomeDestino);
            if(a->relacao > 1){
                un = uniao(v, v2);
                inters = intersecao(v, v2);
                a->coeficienteJaccard = (float)inters/(float)un;
            }
        }
    }
}

void calculaMediaArestas(GRAFO *g){
    VERTICE *v, *v2;
    ARESTA *a, *a2;
    float media;
    for(v = g->listaVertices; v != NULL; v = v->prox){
        for(a = v->listaArestas; a != NULL; a = a->prox){
            v2 = buscaVertice(g, a->nomeDestino);
            if(v2->numVertice > v->numVertice){
                a2 = buscaAresta(v2, v->nomeVertice);
                media = calculaMedia(a->nivel, a2->nivel);
                a->media = media;
                a2->media = media;
            }
        }
    }
}

void contaArestas(GRAFO *g){
    VERTICE *v, *v2;
    ARESTA *a;
    int lv1 = 0, lv2 = 0, lv3 = 0, lv4 = 0, lv5 = 0;
    for(v = g->listaVertices; v != NULL; v = v->prox){
        for(a = v->listaArestas; a != NULL; a = a->prox){
            if(a->relacao > 1){
                v2 = buscaVertice(g, a->nomeDestino);
                if(v->numVertice < v2->numVertice){
                    if(a->coeficienteJaccard <= 0.2){
                        lv1++;
                    } else if(a->coeficienteJaccard > 0.2 && a->coeficienteJaccard <= 0.4){
                        lv2++;
                    } else if(a->coeficienteJaccard > 0.4 && a->coeficienteJaccard <= 0.6){
                        lv3++;
                    } else if(a->coeficienteJaccard > 0.6 && a->coeficienteJaccard <= 0.8){
                        lv4++;
                    } else if(a->coeficienteJaccard > 0.8 && a->coeficienteJaccard <= 1.0){
                        lv5++;
                    }
                }
            }
        }
    }   
    printf("%d %d %d %d %d\n", lv1, lv2, lv3, lv4, lv5);
}