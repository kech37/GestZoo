/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "util.h"

#define NOME_FICHEIRO_ANIMAIS "animais.bin"

bool criaLista(struct AnimaisHelper * ListaAnimais, ANIMAIS animal) {
    ANIMAIS * temp = malloc(sizeof (ANIMAIS));
    if (temp == NULL) {
        printf("[ERRO] Alocacao de memoria.\n");
        return false;
    }
    temp->area = animal.area;
    temp->filho = animal.filho;
    temp->nrSerie = animal.nrSerie;
    temp->peso = animal.peso;
    strcpy(temp->especie, animal.especie);
    strcpy(temp->nome, animal.nome);
    temp->prox = NULL;

    ListaAnimais->tamanho++;

    ListaAnimais->head = ListaAnimais->atual = temp;

    return true;
}

bool AdicionaAnimal(struct AnimaisHelper * ListaAnimais, ANIMAIS animal) {
    if (ListaAnimais->head == NULL) {
        return (criaLista(ListaAnimais, animal));
    } else {
        ANIMAIS * temp = malloc(sizeof (ANIMAIS));
        if (temp == NULL) {
            printf("[ERRO] Alocacao de memoria.\n");
            return false;
        }
        temp->area = animal.area;
        temp->filho = animal.filho;
        temp->nrSerie = animal.nrSerie;
        temp->peso = animal.peso;
        strcpy(temp->especie, animal.especie);
        strcpy(temp->nome, animal.nome);
        temp->prox = NULL;

        ListaAnimais->tamanho++;

        ListaAnimais->atual->prox = temp;
        ListaAnimais->atual = temp;

        return true;
    }
}

void listaAnimal(ANIMAIS * animal) {
    if (animal != NULL) {
        printf("%s %s %d %s\n", animal->especie, animal->nome, animal->peso, animal->area->id);
    } else {
        printf("Ponteiro ANIMAIS NULL.\n");
    }
}

void listarTodosAnimais(struct AnimaisHelper * ListaAnimais) {
    ANIMAIS *temp = ListaAnimais->head;
    while (temp != NULL) {
        listaAnimal(temp);
        temp = temp->prox;
    }
}

ANIMAIS * getAnimalByID(int nrSerie, ANIMAIS ** anterior, struct AnimaisHelper * ListaAnimais) {
    ANIMAIS *ptr = ListaAnimais->head;
    ANIMAIS *temp = NULL;
    bool encontrei = false;
    while (ptr != NULL) {
        if (ptr->nrSerie == nrSerie) {
            encontrei = true;
            break;
        } else {
            temp = ptr;
            ptr = ptr->prox;
        }
    }
    if (encontrei == true) {
        if (anterior)
            *anterior = temp;
        return ptr;
    } else {
        return NULL;
    }
}

bool eliminaNodo(int nrSerie, struct AnimaisHelper * ListaAnimais) {
    ANIMAIS *anterior = NULL;
    ANIMAIS *eliminar = getAnimalByID(nrSerie, &anterior, ListaAnimais);
    if (eliminar == NULL) {
        return false;
    } else {
        if (anterior != NULL)
            anterior->prox = eliminar->prox;
        if (eliminar == ListaAnimais->atual) {
            ListaAnimais->atual = anterior;
        } else if (eliminar == ListaAnimais->head) {
            ListaAnimais->head = eliminar->prox;
        }
    }
    free(eliminar);
    ListaAnimais->tamanho--;
    eliminar = NULL;
    return true;
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
                } else {
                    temp.nrSerie = 0;
                    temp.filho = NULL;
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
    if (f != NULL) {
        ListaAnimais->atual = ListaAnimais->head;
        fwrite(&ListaAnimais->tamanho, sizeof (int), 1, f);
        while (ListaAnimais->atual != NULL) {
            fwrite(&ListaAnimais->atual->area->id, sizeof (char), MAX, f);
            fwrite(&ListaAnimais->atual->especie, sizeof (char), MAX, f);
            //            fwrite(&ListaAnimais->atual->filho->especie, sizeof(char), MAX, f);
            //            fwrite(&ListaAnimais->atual->filho->nrSerie, sizeof(int), 1, f);
            fwrite(&ListaAnimais->atual->nome, sizeof (char), MAX, f);
            fwrite(&ListaAnimais->atual->nrSerie, sizeof (int), 1, f);
            fwrite(&ListaAnimais->atual->peso, sizeof (int), 1, f);
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
        int quantos;
        ANIMAIS temp;
        char aux[MAX];
        fread(&quantos, sizeof (int), 1, f);
        for (int i = 0; i < quantos; i++) {
            fread(&aux, sizeof (char), MAX, f);
            temp.area = procurarAreaNome(ArrayAreas, aux);
            if (temp.area == NULL) {
                printf("[ERRO] Area do animal %s, nao encontra.\n", temp.nome);
            } else {
                fread(&temp.especie, sizeof (char), MAX, f);
                //            fwrite(ListaAnimais->atual->filho->especie, sizeof(char), MAX, f);
                //            fwrite(ListaAnimais->atual->filho->nrSerie, sizeof(int), 1, f);
                fread(&temp.nome, sizeof (char), MAX, f);
                fread(&temp.nrSerie, sizeof (int), 1, f);
                fread(&temp.peso, sizeof (int), 1, f);
                temp.filho = NULL;
                AdicionaAnimal(ListaAnimais, temp);
            }
        }
        fclose(f);
        return true;
    } else {
        printf("[ERRO] Nao foi possivel abrir o ficheiro %s.\n", FICHEIRO_ANIMAIS_BINARIO);
        return false;
    }
}
