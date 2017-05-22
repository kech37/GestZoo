/* 
 *     File:   areas_functions.c
 *    Aluno:   Carlos Filipe Sousa Pinho
 * Nº Aluno:   21220528
 *
 */

#include "util.h"

bool verificaCapacidadeArea(struct AnimaisHelper * ListaAnimais, AREA * area, int peso_adicionar) {
    int total = 0;
    ANIMAIS * temp = ListaAnimais->head;
    while (temp != NULL) {
        if (!strcmp(temp->area->id, area->id)) {
            total += temp->peso;
        }
        temp = temp->prox;
    }
    if ((total + peso_adicionar) > area->capacidade) {
        return false;
    } else {
        return true;
    }
}

AREA * procurarAreaNome(struct AreasHelper * ArrayAreas, char *nome) {
    for (int i = 0; i < ArrayAreas->tamanho; i++) {
        if (!strcmp(ArrayAreas->areas[i].id, nome)) {
            return &ArrayAreas->areas[i];
        }
    }
    return NULL;
}

void listarArea(AREA* areasInput) {
    if (areasInput != NULL) {
        printf("%10s\t%5d\t%5d", areasInput->id, areasInput->capacidade, areasInput->nrAreasAdj);
        for (int j = 0; j < areasInput->nrAreasAdj; j++) {
            printf("\t%10s", areasInput->areasAdj[j]);
        }
        printf("\n");
    } else {
        printf("[ERRO] Area nao encontra.\n");
    }
}

void listarTodasAreas(struct AreasHelper * ArrayAreas) {
    for (int i = 0; i < ArrayAreas->tamanho; i++) {
        listarArea(&ArrayAreas->areas[i]);
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

void criarNovaArea(struct AreasHelper * ArrayAreas) {
    char id[50];
    int flag = 0, op;
    ArrayAreas->areas = realloc(ArrayAreas->areas, sizeof (AREA) * ArrayAreas->tamanho + 1);
    ArrayAreas->tamanho++;
    printf("Indique o ID da nova area: ");
    do {
        scanf("%49s", id);
        if (procurarAreaNome(ArrayAreas, id) != NULL) {
            printf("[ERRO] Esse ID ja estar a ser utilizado, escolha outro!\n");
        } else {
            flag = 1;
            strcpy(ArrayAreas->areas[ArrayAreas->tamanho - 1].id, id);
        }
    } while (flag == 0);
    printf("Indique a capacidade da area: ");
    do {
        scanf("%d", &ArrayAreas->areas[ArrayAreas->tamanho - 1].capacidade);
        if (ArrayAreas->areas[ArrayAreas->tamanho - 1].capacidade <= 0) {
            printf("[ERRO] Capacidade tem que ser maior que zero!\n");
        }
    } while (ArrayAreas->areas[ArrayAreas->tamanho - 1].capacidade <= 0);
    ArrayAreas->areas[ArrayAreas->tamanho - 1].nrAreasAdj = 0;
    for (int i = 1; i <= ArrayAreas->tamanho - 1; i++) {
        printf("%d - %s\n", i, ArrayAreas->areas[i - 1].id);
    }
    printf("0 - Para terminar\n");
    do {
        printf("Indique o nr da area que deseja adicionar: ");
        scanf("%d", &op);
        if (op > 0 && op < ArrayAreas->tamanho) {
            if (ArrayAreas->areas[op - 1].nrAreasAdj < 3) {
                if (!verificaAdjacentes(&ArrayAreas->areas[ArrayAreas->tamanho - 1], ArrayAreas->areas[op - 1].id)) {
                    strcpy(ArrayAreas->areas[ArrayAreas->tamanho - 1].areasAdj[ArrayAreas->areas[ArrayAreas->tamanho - 1].nrAreasAdj], ArrayAreas->areas[op - 1].id);
                    ArrayAreas->areas[ArrayAreas->tamanho - 1].nrAreasAdj++;
                    strcpy(ArrayAreas->areas[op - 1].areasAdj[ArrayAreas->areas[op - 1].nrAreasAdj], ArrayAreas->areas[ArrayAreas->tamanho - 1].id);
                    ArrayAreas->areas[op - 1].nrAreasAdj++;
                    printf("Area %s adiciona.\n", ArrayAreas->areas[op - 1].id);
                } else {
                    printf("[ERRO] Essa area ja e adjacente!\n");
                }
            } else {
                printf("[ERRO] A area escolhida ja tem 3 areas adjacentes!\n");
            }
        } else if (op != 0) {
            printf("[ERRO] Coloque um nr de uma area valida.\n");
        }
    } while (op != 0 && ArrayAreas->areas[ArrayAreas->tamanho - 1].nrAreasAdj < 3);
}

bool eliminarArea(struct AreasHelper * ArrayAreas, struct AnimaisHelper * ListaAnimais) {
    int op;
    for (int i = 1; i <= ArrayAreas->tamanho; i++) {
        printf("%d - %s\n", i, ArrayAreas->areas[i - 1].id);
    }
    printf("0 - Para cancelar\n");
    printf("Indique o nr da area que deseja eliminar: ");
    do {
        scanf("%d", &op);
        if (op < 0 || op > ArrayAreas->tamanho) {
            printf("[ERRO] Escolha um nr de uma area valido.\n");
        }
    } while (op < 0 || op > ArrayAreas->tamanho);
    if (op != 0) {
        if (!checkAnimalinArea(ListaAnimais, ArrayAreas->areas[op - 1].id)) {
            AREA *temp = malloc(sizeof (AREA) * ArrayAreas->tamanho);
            for (int i = 0; i < ArrayAreas->tamanho; i++) {
                strcpy(temp[i].id, ArrayAreas->areas[i].id);
                temp[i].capacidade = ArrayAreas->areas[i].capacidade;
                temp[i].nrAreasAdj = ArrayAreas->areas[i].nrAreasAdj;
                for (int j = 0; j < ArrayAreas->areas[i].nrAreasAdj; j++) {
                    strcpy(temp[i].areasAdj[j], ArrayAreas->areas[i].areasAdj[j]);
                }
            }
            free(ArrayAreas->areas);
            ArrayAreas->areas = malloc(sizeof (AREA) * ArrayAreas->tamanho - 1);
            for (int i = 0, j = 0; i < ArrayAreas->tamanho; i++) {
                if (i != (op - 1)) {
                    strcpy(ArrayAreas->areas[j].id, temp[i].id);
                    ArrayAreas->areas[j].capacidade = temp[i].capacidade;
                    ArrayAreas->areas[j].nrAreasAdj = 0;
                    for (int k = 0; k < temp[i].nrAreasAdj; k++) {
                        if (strcmp(temp[i].areasAdj[k], temp[op - 1].id)) {
                            strcpy(ArrayAreas->areas[j].areasAdj[ArrayAreas->areas[j].nrAreasAdj], temp[i].areasAdj[k]);
                            ArrayAreas->areas[j].nrAreasAdj++;
                        }
                    }
                    j++;
                }
            }
            ArrayAreas->tamanho--;
            free(temp);
            return true;
        } else {
            printf("[ERRO] Esta area encontra-se com animais, mova-os primeiro antes de eliminar a area!\n");
        }
    }
    return false;
}