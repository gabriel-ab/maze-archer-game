#include <stdlib.h>
#include <stdio.h>
#include "data.h"


void save(int faseAtual) {
	
	FILE *ponteiro_arquivo;

	ponteiro_arquivo = fopen("save/save.txt", "w");

	fprintf(ponteiro_arquivo, "%d", faseAtual);

	fclose(ponteiro_arquivo);

	printf("Dados gravados com sucesso!\n");
}

int load() {
	
	FILE *ponteiro_arquivo;
	
	ponteiro_arquivo = fopen("save/save.txt", "r");

	int telaAtual = 1;

	while (!feof (ponteiro_arquivo))
	{  
		fscanf (ponteiro_arquivo, "%i", &telaAtual);  
	}

	fclose(ponteiro_arquivo);

	return telaAtual;
}
