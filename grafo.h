#ifndef GRAFO_H
#define GRAFO_H

#define MAX 250

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct aresta{
    int peso;
    char nomeDestino[MAX];
    int relacao;
    float coeficienteJaccard;
    float media;
    int nivel;
    struct aresta *prox;
} typedef ARESTA;

struct vertice{
    char nomeVertice[MAX];
    int numVertice;
    ARESTA *listaArestas;
    struct vertice *prox;
} typedef VERTICE;

struct grafo{
    VERTICE *listaVertices;
    int orientado;
    int qtdeVertices;
} typedef GRAFO;

void imprimeAresta(ARESTA *a);

void imprimeVertice(VERTICE *v);

void imprimeGrafo(GRAFO *g);

GRAFO* inicializaGrafo();

VERTICE* insereVertice(VERTICE *v, GRAFO *g);

ARESTA* insereAresta(ARESTA *a, VERTICE *v);

VERTICE* buscaVertice(GRAFO *g, char nomeVertice[]);

ARESTA* buscaAresta(VERTICE *v, char nomeDestino[]);

void atualizaAresta(ARESTA *a, ARESTA *a2);

int calculaPeso(int a, int b);

int calculaPeso(int a, int b);

void calculaPesoArestas(GRAFO *g);

int vizinhoComum(VERTICE *v1, VERTICE *v2, GRAFO *g);

int calculaPontesLocais(GRAFO *g);

int uniao(VERTICE *v1, VERTICE *v2);

int intersecao(VERTICE *v1, VERTICE *v2);

void calculaCoefJaccard(GRAFO *g);

void calculaMediaArestas(GRAFO *g);

void contaArestas(GRAFO *g);

#endif