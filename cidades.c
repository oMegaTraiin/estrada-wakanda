#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cidades.h"

void swap(Cidade *a, Cidade *b);
int partition(Cidade *V, int inf, int sup);
void quickSort(Cidade *V, int inf, int sup);

Estrada *getEstrada(const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) return NULL;

    int T, N;

    if (fscanf(arquivo, "%d", &T) != 1) return NULL;
    if (fscanf(arquivo, "%d", &N) != 1) return NULL;

    // Verifica restrições
    if (T < 3 || T > 1000000 || N < 2 || N > 10000) {
        fclose(arquivo);
        return NULL;
    }

    // Aloca memoria para a struct estrada;
    Estrada *estrada = malloc(sizeof(Estrada));
    if (estrada == NULL) {
        fclose(arquivo);
        return NULL;
    }

    // Aloca memoria para a struct cidade;
    estrada->T = T;
    estrada->N = N;
    estrada->C = malloc(sizeof(Cidade) * N);
    if (estrada->C == NULL) {
        free(estrada);
        fclose(arquivo);
        return NULL;
    }

    // Lê os dados das cidades
    for (int i = 0; i < N; i++) {
        int pos;
        char nome[256];
        
        if (fscanf(arquivo, "%d %[^\n]", &pos, nome) != 2) {
            free(estrada->C);
            free(estrada);
            fclose(arquivo);
            // printf("Erro: Ler cidade\n"); // Debug
            return NULL;
        }

        // Verifica restrições de posição;
        if (pos <= 0 || pos >= T) {
            free(estrada->C);
            free(estrada);
            fclose(arquivo);
            //printf("Erro: Restrição de posição\n"); // Debug
            return NULL;
        }

        // Verifica se a posição já foi usada
        for (int j = 0; j < i; j++) {
            if (estrada->C[j].Posicao == pos) {
                free(estrada->C);
                free(estrada);
                fclose(arquivo);
                //printf("Erro: Posição já foi utilizada\n"); // Debug
                return NULL;
            }
        }

        estrada->C[i].Posicao = pos;
        strcpy(estrada->C[i].Nome, nome);
    }

    fclose(arquivo);
    return estrada;
}

double calcularMenorVizinhanca(const char *nomeArquivo) {
    Estrada *estrada = getEstrada(nomeArquivo);
    if (estrada == NULL) {
        return -1;  // Se houver erro ao obter a estrada;
    }

    // Ordena as cidades pela posição;
    quickSort(estrada->C, 0, estrada->N - 1);

    double menor = estrada->T;

    // Calcula a vizinhança para cada cidade;
    for (int i = 0; i < estrada->N; i++) {
        double vizinhanca;

        if (i == 0) {
            vizinhanca = (estrada->C[i].Posicao + estrada->C[i + 1].Posicao) / 2.0;
        } else if (i == estrada->N - 1) {
            double anterior = (estrada->C[i].Posicao + estrada->C[i - 1].Posicao) / 2.0;
            vizinhanca = estrada->T - anterior;
        } else {
            double anterior = (estrada->C[i].Posicao + estrada->C[i - 1].Posicao) / 2.0;
            double proxima = (estrada->C[i].Posicao + estrada->C[i + 1].Posicao) / 2.0;
            vizinhanca = proxima - anterior;
        }

        if (vizinhanca < menor) menor = vizinhanca;
    }

    free(estrada->C);
    free(estrada);

    return menor;
}

char *cidadeMenorVizinhanca(const char *nomeArquivo) {
    Estrada *estrada = getEstrada(nomeArquivo);
    if (estrada == NULL) return NULL;

    quickSort(estrada->C, 0, estrada->N - 1);

    double menor = estrada->T;
    int indice = -1;

    for (int i = 0; i < estrada->N; i++) {
        double vizinhanca;
        if (i == 0) {
            vizinhanca = (estrada->C[i].Posicao + estrada->C[i + 1].Posicao) / 2.0;
        } else if (i == estrada->N - 1) {
            double anterior = (estrada->C[i].Posicao + estrada->C[i - 1].Posicao) / 2.0;
            vizinhanca = estrada->T - anterior;
        } else {
            double anterior = (estrada->C[i].Posicao + estrada->C[i - 1].Posicao) / 2.0;
            double proxima = (estrada->C[i].Posicao + estrada->C[i + 1].Posicao) / 2.0;
            vizinhanca = proxima - anterior;
        }

        if (vizinhanca < menor) {
            menor = vizinhanca;
            indice = i;
        }
    }

    if (indice == -1) return NULL;

    // Retornar cópia do nome
    char *nomeCidade = malloc(strlen(estrada->C[indice].Nome) + 1);
    if (nomeCidade) {
        strcpy(nomeCidade, estrada->C[indice].Nome);
    }

    free(estrada->C);
    free(estrada);

    return nomeCidade;
}


// Função de quicksort;

void swap(Cidade *a, Cidade *b) {
    Cidade temp = *a;
    *a = *b;
    *b = temp;
}

int partition(Cidade *V, int inf, int sup) {
    int Pivot = V[(inf + sup) / 2].Posicao;
    int i = inf;
    int j = sup;

    while (i <= j) {
        while (V[i].Posicao < Pivot) i++;
        while (V[j].Posicao > Pivot) j--;

        if (i <= j) {
            swap(&V[i], &V[j]);
            i++;
            j--;
        }
    }
    return i;
}

void quickSort(Cidade *V, int inf, int sup) {
    if (inf < sup) {
        int p = partition(V, inf, sup);
        quickSort(V, inf, p - 1);
        quickSort(V, p, sup);
    }
}

