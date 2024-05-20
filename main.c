#include "arquivo.h"

int main(){
    GRAFO *g = inicializaGrafo();
    int cont = 0;
    VERTICE *v;
    readFileVertices("Vertices.txt", g);
    int i = 0;
    for(v = g->listaVertices; v != NULL; v = v->prox){
        readFileAluno(v->nomeVertice, g);
    }
    calculaPesoArestas(g);
    calculaCoefJaccard(g);
    calculaMediaArestas(g);
    imprimeGrafo(g);
    printf("\n[%d]\n", calculaPontesLocais(g));
    printf("%d\n", uniao(buscaVertice(g, "0"), buscaVertice(g, "1")));
    printf("%d\n", intersecao(buscaVertice(g, "0"), buscaVertice(g, "1")));
    writeGraph(g);
    writeArquivoMedia(g);
    contaArestas(g);
    return 0;
}