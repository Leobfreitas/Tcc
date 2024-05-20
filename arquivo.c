#include "arquivo.h"

void insereTxt(char str[], char nomeArq[]){
    int i;
    for(i = 0; str[i] != '\0'; i++){
        nomeArq[i] = str[i];
    }
    nomeArq[i] = '.';
    nomeArq[i+1] = 't';
    nomeArq[i+2] = 'x';
    nomeArq[i+3] = 't';
    nomeArq[i+4] = '\0';
}

void readFileAluno(char nomeAluno[], GRAFO *g){  

    char nomeArq[200];


    insereTxt(nomeAluno, nomeArq);
    FILE *f = fopen(nomeArq, "r");

    if(f == NULL){
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    VERTICE *v = buscaVertice(g, nomeAluno);    
    VERTICE *aluno;

//    imprimeVertice(v);

    while(!feof(f)){
        ARESTA *a = malloc(sizeof(ARESTA));
        ARESTA *a2 = malloc(sizeof(ARESTA));

        a->peso = -1; a2->peso = -1;

        int relacao;

        fscanf(f, "%[^,],%[^,],%d\n", nomeArq, a->nomeDestino, &relacao);

        if(relacao == 1 || relacao == 2){
            if(relacao == 1){
                a->nivel = 3;
            }
            else{
                a->nivel = 2;
            }
            a->relacao = 3;
        }
        if(relacao == 3){
            a->nivel = 1;
            a->relacao = 2;
        }
        if(relacao == 4 || relacao == 6){
            a->relacao = 1;
        }
        if(relacao == 5){
            a->nivel = 0;
            a->relacao = -1;
        }        
        
        a->coeficienteJaccard = -1;
        a2->coeficienteJaccard = -1;

        aluno = buscaVertice(g, a->nomeDestino);

        if(!buscaAresta(aluno, nomeAluno)){
            strcpy(a2->nomeDestino, nomeAluno);
            a2->relacao = a->relacao;
            a2->nivel = a->nivel;
            insereAresta(a, v);
            insereAresta(a2, aluno);
        } else {
            a2 = buscaAresta(v, a->nomeDestino);
            if(relacao == 3){
                a2->nivel = 1;
            }
            if(relacao == 2){
                a2->nivel = 2;
            }
            if(relacao == 1){
                a2->nivel = 3;
            }                        
            if(a->relacao != a2->relacao){
                if(a2->relacao > a->relacao){
                    a2->relacao = a->relacao;

                    a2 = buscaAresta(aluno, nomeAluno);
                    a2->relacao = a->relacao;
                }
            }
        }
    }
    fclose(f);
}

void readFileVertices(char nomeArq[], GRAFO *g){
    FILE *f = fopen(nomeArq, "r");

    if(f == NULL){
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    while(!feof(f)){
        VERTICE *v = malloc(sizeof(VERTICE));

        fscanf(f, "%[^\n]\n", v->nomeVertice);
        printf("%s\n", v->nomeVertice);
        v->numVertice = g->qtdeVertices+1;
        v->listaArestas = NULL;
        g->listaVertices = insereVertice(v, g);
        g->qtdeVertices++;
    }
    fclose(f);
}

void writeGraph(GRAFO *g){
    FILE *f;

    f = fopen("Arestas.txt", "w");

    VERTICE *v, *v2;
    ARESTA *a;
    char c;
    for(v = g->listaVertices; v != NULL; v = v->prox){
        for(a = v->listaArestas; a != NULL; a = a->prox){
            v2 = buscaVertice(g, a->nomeDestino);   
            if(v2->numVertice > v->numVertice){
                if(a->relacao > 1){
                    fprintf(f, "%d;%d;Undirected;%d\n", v->numVertice, v2->numVertice, (a->peso)+1);
                }
            }
        }
    }    
    fclose(f);
}

void writeArquivoMedia(GRAFO *g){
    FILE *f;

    f = fopen("Media.txt", "w");

    VERTICE *v, *v2;
    ARESTA *a;
    char c;
    for(v = g->listaVertices; v != NULL; v = v->prox){
        for(a = v->listaArestas; a != NULL; a = a->prox){
            v2 = buscaVertice(g, a->nomeDestino);
            if(v2->numVertice > v->numVertice){
                if(a->relacao > 1){
                   fprintf(f, "%d, %d, %.2f\n", v->numVertice, v2->numVertice, a->coeficienteJaccard);
                }
            }
        }
    }    
    fclose(f);

}


/*
void readFile(char nomeArq[], GRAFO *g){
    FILE *f = fopen(nomeArq, "r");

    if(f == NULL){
        printf("Erro ao abrir o arquivo");
        return;
    }

    char str[MAX], c;

    while(!feof(f)){
        
        fscanf(f, "%c", &c);

        if(c == 'V'){
            VERTICE *vertice = malloc(sizeof(VERTICE));
            vertice->listaArestas = NULL;
            fscanf(f, ":(%[^,],%d)\n", str, &(vertice->numVertice));
            strcpy(vertice->nomeVertice, str);
            insereVertice(vertice, g);
        } else if(c == 'A'){
            VERTICE *origem, *destino;
            int numVertice, numDestino;
            ARESTA *aresta = malloc(sizeof(ARESTA));
            fscanf(f, ":(%d,%d)%d\n", &numVertice, &numDestino, &(aresta->peso));
            origem = buscaVertice(g, numVertice);
            destino = buscaVertice(g, numDestino);
            strcpy(aresta->nomeDestino, destino->nomeVertice);
            if(origem && destino){
                insereAresta(aresta, origem);
            }
            if(!(g->orientado)){
                ARESTA *invertida = malloc(sizeof(ARESTA));
                invertida->peso = aresta->peso;
                strcpy(invertida->nomeDestino, origem->nomeVertice);
                insereAresta(invertida, destino);
            }
        }
    }
}*/

