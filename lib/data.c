#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "data.h"
#include "define.h"
#include "tela.h"


void save() {
	
	FILE *ponteiro_arquivo;

	ponteiro_arquivo = fopen("save/save.txt", "w");

	fprintf(ponteiro_arquivo, "fase_atual:%d\n", telaAtual);
	fprintf(ponteiro_arquivo, "vida_maxima_xala:%d\n", vida_maxima_xala);
	fprintf(ponteiro_arquivo, "quantidade_maxima_flechas:%d", quantidade_maxima_flechas);

	fclose(ponteiro_arquivo);

	printf("Dados gravados com sucesso!\n");
}

int load() {
	FILE *ponteiro_arquivo;
    ponteiro_arquivo = fopen("save/save.txt", "r");

    char data[50];
    while (fgets(data, sizeof data, ponteiro_arquivo) != NULL) {

        if(strncmp(data, "fase_atual", strlen("fase_atual")) == 0) {

            strtok(data,":");
            telaAtual = atoi(strtok(NULL," "));
        }

        if(strncmp(data, "vida_maxima_xala", strlen("vida_maxima_xala")) == 0) {
            strtok(data,":");
            vida_maxima_xala = atoi(strtok(NULL," "));
        }

        if(strncmp(data, "quantidade_maxima_flechas", strlen("quantidade_maxima_flechas")) == 0) {
            strtok(data,":");
            quantidade_maxima_flechas = atoi(strtok(NULL," "));
        }
        
    }
	printf("%d", telaAtual);
          
    fclose(ponteiro_arquivo);

	return telaAtual;
}
