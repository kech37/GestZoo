/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "util.h"

int contaLinhas(char *nome) {
    FILE *f = fopen(nome, "r");
    int ch = 0, linhas = 0;
    if (f != NULL) {
        linhas++;
        while ((ch = fgetc(f)) != EOF) {
            if (ch == '\n')
                linhas++;
        }
        fclose(f);
        return linhas;
    } else {
        return 0;
    }
}

bool iniciarVetor(struct BlocoMemoria * bm) {
    FILE *f = fopen(FICHEIRO_AREAS, "r");
    int nrLinhas, i, j;
    if (f != NULL) {
        nrLinhas = contaLinhas(FICHEIRO_AREAS);
        if (nrLinhas > 0) {
            bm->areas = malloc(sizeof (AREA) * nrLinhas);
            bm->tamanho = nrLinhas;
            for (i = 0; i < nrLinhas; i++) {
                fscanf(f, "%49s %d %d", bm->areas[i].id, &bm->areas[i].capacidade, &bm->areas[i].nrAreasAdj);
                for (j = 0; j < bm->areas[i].nrAreasAdj; j++) {
                    fscanf(f, "%49s", bm->areas[i].areasAdj[j]);
                }
            }
        } else {
            printf("[ERRO] Ficheiro %s nao contem informacao!\n", FICHEIRO_AREAS);
        }
        fclose(f);
        return true;
    } else {
        printf("[ERRO] Ficheiro %s nao existe, logo o programa nao pode correr!\n", FICHEIRO_AREAS);
        return false;
    }
}

bool gravarFicheiroAreas(struct BlocoMemoria * bm){
    FILE *f = fopen(FICHEIRO_AREAS, "w");
    if(f != NULL){
        for(int i = 0; i < bm->tamanho; i++){
            fprintf(f, "%s %d %d", bm->areas[i].id, bm->areas[i].capacidade, bm->areas[i].nrAreasAdj);
            for(int j = 0; j < bm->areas[i].nrAreasAdj; j++){
                fprintf(f, " %s", bm->areas[i].areasAdj[j]);
            }
            if(i != bm->tamanho-1){
                fprintf(f, "\n");
            }
        }
        fclose(f);
        return true;
    }else{
        return false;
    }
}