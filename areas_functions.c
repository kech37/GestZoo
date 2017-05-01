/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "util.h"

AREA* procurarAreaNome(struct BlocoMemoria * bm, char *nome) {
    for (int i = 0; i < bm->tamanho; i++) {
        if (!strcmp(bm->areas[i].id, nome)) {
            return &bm->areas[i];
        }
    }
    return NULL;
}

void listarArea(AREA* areasInput) {
    if (areasInput != NULL) {
        printf("%s %d %d", areasInput->id, areasInput->capacidade, areasInput->nrAreasAdj);
        for (int j = 0; j < areasInput->nrAreasAdj; j++) {
            printf(" %s", areasInput->areasAdj[j]);
        }
        printf("\n");
    } else {
        printf("[ERRO] Area nao encontra.\n");
    }
}

void listarTodasAreas(struct BlocoMemoria * bm) {
    for (int i = 0; i < bm->tamanho; i++) {
        listarArea(&bm->areas[i]);
    }
}

int verificaAdjacentes(AREA *a, char *nome) {
    for (int i = 0; i < a->nrAreasAdj; i++) {
        if (!strcmp(a->areasAdj[i], nome)) {
            return 1;
        }
    }
    return 0;
}

void criarNovaArea(struct BlocoMemoria * bm) {
    char id[50];
    int flag = 0, op;
    bm->areas = realloc(bm->areas, sizeof (AREA) * bm->tamanho + 1);
    bm->tamanho++;
    printf("Indique o ID da nova area: ");
    do {
        scanf("%49s", id);
        if (procurarAreaNome(bm, id) != NULL) {
            printf("[ERRO] Esse ID ja estar a ser utilizado, escolha outro!\n");
        } else {
            flag = 1;
            strcpy(bm->areas[bm->tamanho - 1].id, id);
        }
    } while (flag == 0);
    printf("Indique a capacidade da area: ");
    do {
        scanf("%d", &bm->areas[bm->tamanho - 1].capacidade);
        if (bm->areas[bm->tamanho - 1].capacidade <= 0) {
            printf("[ERRO] Capacidade tem que ser maior que zero!\n");
        }
    } while (bm->areas[bm->tamanho - 1].capacidade <= 0);
    bm->areas[bm->tamanho - 1].nrAreasAdj = 0;
    for (int i = 1; i <= bm->tamanho - 1; i++) {
        printf("%d - %s\n", i, bm->areas[i - 1].id);
    }
    printf("0 - Para terminar\n");
    do {
        printf("Indique o nr da area que deseja adicionar: ");
        scanf("%d", &op);
        if (op > 0 && op < bm->tamanho) {
            if (bm->areas[op - 1].nrAreasAdj < 3) {
                if (!verificaAdjacentes(&bm->areas[bm->tamanho - 1], bm->areas[op - 1].id)) {
                    strcpy(bm->areas[bm->tamanho - 1].areasAdj[bm->areas[bm->tamanho - 1].nrAreasAdj], bm->areas[op - 1].id);
                    bm->areas[bm->tamanho - 1].nrAreasAdj++;
                    strcpy(bm->areas[op - 1].areasAdj[bm->areas[op - 1].nrAreasAdj], bm->areas[bm->tamanho - 1].id);
                    bm->areas[op - 1].nrAreasAdj++;
                    printf("Area %s adiciona.\n", bm->areas[op - 1].id);
                }else{
                    printf("[ERRO] Essa area ja e adjacente!\n");
                }
            } else {
                printf("[ERRO] A area escolhida ja tem 3 areas adjacentes!\n");
            }
        } else if (op != 0) {
            printf("[ERRO] Coloque um nr de uma area valida.\n");
        }
    } while (op != 0 && bm->areas[bm->tamanho - 1].nrAreasAdj < 3);
}

void eliminarArea(struct BlocoMemoria * bm) {
    //TODO VERIFICAR SE A AREA TEM ANIMAIS, ANTES DE ELIMINAR
    int op;
    for (int i = 1; i <= bm->tamanho; i++) {
        printf("%d - %s\n", i, bm->areas[i - 1].id);
    }
    printf("0 - Para cancelar\n");
    printf("Indique o nr da area que deseja eliminar: ");
    do {
        scanf("%d", &op);
        if (op < 0 || op > bm->tamanho) {
            printf("[ERRO] Escolha um nr de uma area valido.\n");
        }
    } while (op < 0 || op > bm->tamanho);
    if (op != 0) {
        AREA *temp = malloc(sizeof (AREA) * bm->tamanho);
        for (int i = 0; i < bm->tamanho; i++) {
            strcpy(temp[i].id, bm->areas[i].id);
            temp[i].capacidade = bm->areas[i].capacidade;
            temp[i].nrAreasAdj = bm->areas[i].nrAreasAdj;
            for (int j = 0; j < bm->areas[i].nrAreasAdj; j++) {
                strcpy(temp[i].areasAdj[j], bm->areas[i].areasAdj[j]);
            }
        }
        free(bm->areas);
        bm->areas = malloc(sizeof (AREA) * bm->tamanho - 1);
        for (int i = 0, j = 0; i < bm->tamanho; i++) {
            if (i != (op - 1)) {
                strcpy(bm->areas[j].id, temp[i].id);
                bm->areas[j].capacidade = temp[i].capacidade;
                bm->areas[j].nrAreasAdj = 0;
                for (int k = 0; k < temp[i].nrAreasAdj; k++) {
                    if (strcmp(temp[i].areasAdj[k], temp[op - 1].id)) {
                        strcpy(bm->areas[j].areasAdj[bm->areas[j].nrAreasAdj], temp[i].areasAdj[k]);
                        bm->areas[j].nrAreasAdj++;
                    }
                }
                j++;
            }
        }
        bm->tamanho--;
        free(temp);
    }
}