/* 
 *     File:   file_functions.c
 *    Aluno:   Carlos Filipe Sousa Pinho
 * Nº Aluno:   21220528
 *
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

bool iniciarVetor(struct AreasHelper * ArrayAreas) {
    FILE *f = fopen(FICHEIRO_AREAS, "r");
    int nrLinhas, i, j;
    if (f != NULL) {
        nrLinhas = contaLinhas(FICHEIRO_AREAS);
        if (nrLinhas > 0) {
            ArrayAreas->areas = malloc(sizeof (AREA) * nrLinhas);
            ArrayAreas->tamanho = nrLinhas;
            for (i = 0; i < nrLinhas; i++) {
                fscanf(f, "%49s %d %d", ArrayAreas->areas[i].id, &ArrayAreas->areas[i].capacidade, &ArrayAreas->areas[i].nrAreasAdj);
                for (j = 0; j < ArrayAreas->areas[i].nrAreasAdj; j++) {
                    fscanf(f, "%49s", ArrayAreas->areas[i].areasAdj[j]);
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

bool gravarFicheiroAreas(struct AreasHelper * bm) {
    FILE *f = fopen(FICHEIRO_AREAS, "w");
    if (f != NULL) {
        for (int i = 0; i < bm->tamanho; i++) {
            fprintf(f, "%s %d %d", bm->areas[i].id, bm->areas[i].capacidade, bm->areas[i].nrAreasAdj);
            for (int j = 0; j < bm->areas[i].nrAreasAdj; j++) {
                fprintf(f, " %s", bm->areas[i].areasAdj[j]);
            }
            if (i != bm->tamanho - 1) {
                fprintf(f, "\n");
            }
        }
        fclose(f);
        return true;
    } else {
        return false;
    }
}

bool carregaAnimaisFicheiroTXT(char * nome, struct AreasHelper * ArrayAreas, struct AnimaisHelper * ListaAnimais) {
    FILE *f = fopen(nome, "r");
    if (f != NULL) {
        int nrLinhas = contaLinhas(nome);
        if (nrLinhas > 0) {
            char aux[50];
            for (int i = 0; i < nrLinhas; i++) {
                ANIMAIS temp;
                fscanf(f, "%s %s %d %49s", temp.especie, temp.nome, &temp.peso, aux);
                temp.area = procurarAreaNome(ArrayAreas, aux);
                if (temp.area == NULL) {
                    printf("[ERRO] Area do animal %s, nao encontra.\n", temp.nome);
                } else if (!verificaCapacidadeArea(ListaAnimais, temp.area, temp.peso)) {
                    printf("[ERRO] Area %s nao tem capacidade suficiente!\n       Anima %s ignorado.\n", temp.area->id, temp.nome);
                } else {
                    temp.parente1 = NULL;
                    temp.parente2 = NULL;
                    AdicionaAnimal(ListaAnimais, temp);
                }
            }
            return true;
        } else {
            printf("[ERRO] Ficheiro vazio.\n");
            fclose(f);
            return false;
        }
    } else {
        printf("[ERRO] Ao ler o ficheiro de texto dos animais.\n");
        return false;
    }
}

bool guardarAnimaisBinario(struct AnimaisHelper * ListaAnimais) {
    FILE *f = fopen(FICHEIRO_ANIMAIS_BINARIO, "wb");
    int aux = -1;
    if (f != NULL) {
        ListaAnimais->atual = ListaAnimais->head;
        fwrite(&ListaAnimais->tamanho, sizeof (int), 1, f);
        while (ListaAnimais->atual != NULL) {
            fwrite(&ListaAnimais->atual->area->id, sizeof (char), MAX, f);
            fwrite(&ListaAnimais->atual->peso, sizeof (int), 1, f);
            fwrite(&ListaAnimais->atual->especie, sizeof (char), MAX, f);
            if (ListaAnimais->atual->parente1 == NULL) {
                fwrite(&aux, sizeof (int), 1, f);
            } else {
                fwrite(&ListaAnimais->atual->parente1->nrSerie, sizeof (int), 1, f);
            }
            if (ListaAnimais->atual->parente2 == NULL) {
                fwrite(&aux, sizeof (int), 1, f);
            } else {
                fwrite(&ListaAnimais->atual->parente2->nrSerie, sizeof (int), 1, f);
            }
            fwrite(&ListaAnimais->atual->nome, sizeof (char), MAX, f);
            ListaAnimais->atual = ListaAnimais->atual->prox;
        }
        fclose(f);
        return true;
    } else {
        printf("[ERRO] Nao foi possivel abrir o ficheiro %s.\n", FICHEIRO_ANIMAIS_BINARIO);
        return false;
    }
}

bool leAnimaisBinario(struct AnimaisHelper * ListaAnimais, struct AreasHelper * ArrayAreas) {
    FILE * f = fopen(FICHEIRO_ANIMAIS_BINARIO, "rb");
    if (f != NULL) {
        int quantos, aux_id;
        ANIMAIS temp;
        char aux[MAX];
        fread(&quantos, sizeof (int), 1, f);
        for (int i = 0; i < quantos; i++) {
            fread(&aux, sizeof (char), MAX, f);
            temp.area = procurarAreaNome(ArrayAreas, aux);
            if (temp.area == NULL) {
                printf("[ERRO] Area do animal %s, nao encontra.\n", temp.nome);
            } else {
                fread(&temp.peso, sizeof (int), 1, f);
                if (!verificaCapacidadeArea(ListaAnimais, temp.area, temp.peso)) {
                    printf("[ERRO] Area %s nao tem capacidade suficiente!\n       Anima %s ignorado.\n", temp.area->id, temp.nome);
                } else {
                    fread(&temp.especie, sizeof (char), MAX, f);
                    fread(&aux_id, sizeof (int), 1, f);
                    if (aux_id != -1) {
                        temp.parente1 = getAnimalByIDandEspecie(aux_id, temp.especie, ListaAnimais);
                    } else {
                        temp.parente1 = NULL;
                    }
                    fread(&aux_id, sizeof (int), 1, f);
                    if (aux_id != -1) {
                        temp.parente2 = getAnimalByIDandEspecie(aux_id, temp.especie, ListaAnimais);
                    } else {
                        temp.parente2 = NULL;
                    }
                    fread(&temp.nome, sizeof (char), MAX, f);
                    AdicionaAnimal(ListaAnimais, temp);
                }
            }
        }
        fclose(f);
        return true;
    } else {
        printf("[ERRO] Nao foi possivel abrir o ficheiro %s.\n", FICHEIRO_ANIMAIS_BINARIO);
        return false;
    }
}