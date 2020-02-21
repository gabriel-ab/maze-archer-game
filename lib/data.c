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
Mapa LoadMapa(const char *endereco){
    Mapa fase = { 0 };
    
    FILE *arquivo = fopen(endereco,"r");

    fscanf(arquivo,"inicio %f %f\n", &fase.inicio.x, &fase.inicio.y);
    fscanf(arquivo,"fim %f %f\n", &fase.fim.x, &fase.fim.y);

    fscanf(arquivo,"paredes %i\n", &fase.n_paredes);
    for( int i = 0; i < fase.n_paredes; i++){
        fscanf(arquivo,"%f %f %f %f\n", &fase.parede[i].x, &fase.parede[i].y, &fase.parede[i].width, &fase.parede[i].height);
    }
    fscanf(arquivo,"pisos %i\n", &fase.n_pisos);
    for( int i = 0; i < fase.n_pisos; i++){
        fscanf(arquivo,"%f %f %f %f\n", &fase.piso[i].x, &fase.piso[i].y, &fase.piso[i].width, &fase.piso[i].height);
    }
    fscanf(arquivo,"inimigos %i\n", &fase.n_inimigos);
    for (int i = 0; i < fase.n_inimigos; i++)
    {
        fase.inimigo[i] = inimigoContructor();
        fscanf(arquivo,"%f %f\n", &fase.inimigo[i].posicao.x, &fase.inimigo[i].posicao.y);
    }
    fscanf(arquivo,"vidas %i\n", &fase.n_vidas);
    for( int i = 0; i < fase.n_vidas; i++){
        fscanf(arquivo,"%f %f\n", &fase.vida[i].posicao.x, &fase.vida[i].posicao.y);
    }
    fscanf(arquivo,"flechas %i\n", &fase.n_flechas);
    for( int i = 0; i < fase.n_flechas; i++){
        fscanf(arquivo,"%f %f\n", &fase.flecha[i].posicao.x, &fase.flecha[i].posicao.y);
    }
    fclose(arquivo);
    return fase;
}