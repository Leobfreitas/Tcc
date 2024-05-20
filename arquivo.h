#ifndef ARQUIVO_H
#define ARQUIVO_H

#include "grafo.h"

void insereTxt(char str[], char nomeArq[]);

void readFileAluno(char nomeAluno[], GRAFO *g);

void readFileVertices(char nomeArq[], GRAFO *g);

void readFiles(char nomeArq[], GRAFO *g);

void writeGraph(GRAFO *g);

void writeArquivoMedia(GRAFO *g);

#endif