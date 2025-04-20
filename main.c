#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cidades.h"

int main() {
    Estrada *e = getEstrada("Teste01.txt");

    if (e == NULL) {
        printf("Erro ao ler a estrada ou restrições no arquivo.\n");
        return 1;
    }

    printf("Comprimento total da estrada: %d\n", e->T);
    printf("Número de cidades: %d\n", e->N);
    printf("Cidades:\n");

    for (int i = 0; i < e->N; i++) {
        printf("  %d - %s\n", e->C[i].Posicao, e->C[i].Nome);
    }

    double menorVizinhanca = calcularMenorVizinhanca("Teste01.txt");
    char *C1 = cidadeMenorVizinhanca("Teste01.txt");
    printf("\nMenor vizinhança: %.2f km", menorVizinhanca);
    printf("\nNome menor vizinhança: %s", C1);

    // Libera memória
    free(e->C);
    free(e);

    return 0;
}

/*
int main() {
    int Soma = 0;
    int NumTeste = 0;

    FILE *Resposta = fopen("Resultado.txt", "w");
    Estrada *T1 = getEstrada("Teste01.txt");
    double D1 = calcularMenorVizinhanca("Teste01.txt");
    char *C1 = cidadeMenorVizinhanca("Teste01.txt");

    if (T1->T == 10) Soma++;
        NumTeste++;
    if (T1->N == 2) Soma++;
        NumTeste++;
    if (D1 == 3.5) Soma++;
        NumTeste++;
    if (strcmp(C1, "Birnin Zana")==0) Soma++;
        NumTeste++;
    
    fprintf(Resposta, "\n\nATENÇÃO: Você acertou %d de %d itens. Logo, em 2.00 pontos, sua nota foi %.2f.\n", Soma, NumTeste, 2.0 * (float)Soma/(float)NumTeste);
}
*/