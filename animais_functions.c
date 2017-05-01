/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "util.h"

#define NOME_FICHEIRO_ANIMAIS "animais.bin"

void init() {
    ah.animais_inicio = NULL;
    ah.animais_atual = NULL;
    ah.conta_id = 0;
    ah.tamanho = 0;
}

int setID() {
    ah.tamanho++;
    return ++ah.conta_id;
}

ANIMAIS * criaLista(ANIMAIS animal) {
    ANIMAIS *ptr = (ANIMAIS*) malloc(sizeof (ANIMAIS));
    if (NULL == ptr) {
        printf("[ERRO] Alocacao de memoria.\n");
        return NULL;
    }

    ptr->area = animal.area;
    ptr->filho = animal.filho;
    ptr->nrSerie = animal.nrSerie;
    ptr->peso = animal.peso;
    strcpy(ptr->especie, animal.especie);
    strcpy(ptr->nome, animal.nome);
    ptr->prox = NULL;

    ah.animais_inicio = ah.animais_atual = ptr;
    return ptr;
}

ANIMAIS * adicionarAnimal(ANIMAIS animal) {
    if (NULL == ah.animais_inicio) {
        return (criaLista(animal));
    }

    ANIMAIS *ptr = (ANIMAIS*) malloc(sizeof (ANIMAIS));
    if (NULL == ptr) {
        printf("[ERRO] Ao adiconar na lista.\n");
        return NULL;
    }
    ptr->area = animal.area;
    ptr->filho = animal.filho;
    ptr->nrSerie = animal.nrSerie;
    ptr->peso = animal.peso;
    strcpy(ptr->especie, animal.especie);
    strcpy(ptr->nome, animal.nome);
    ptr->prox = NULL;

    ah.animais_atual->prox = ptr;
    ah.animais_atual = ptr;

    return ptr;
}

ANIMAIS * getAnimalByID(int nrSerie, ANIMAIS ** anterior) {
    ANIMAIS *ptr = ah.animais_inicio;
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

bool eliminaNodo(int nrSerie) {
    ANIMAIS *anterior = NULL;
    ANIMAIS *eliminar = getAnimalByID(nrSerie, &anterior);
    if (eliminar == NULL) {
        return false;
    } else {
        if (anterior != NULL)
            anterior->prox = eliminar->prox;
        if (eliminar == ah.animais_atual) {
            ah.animais_atual = anterior;
        } else if (eliminar == ah.animais_inicio) {
            ah.animais_inicio = eliminar->prox;
        }
    }
    free(eliminar);
    eliminar = NULL;
    return true;
}

bool carregaAnimaisFicheiroTXT(char * nome) {
    FILE *f = fopen(nome, "r");
    if (f != NULL) {
        int nrLinhas = contaLinhas(nome);
        if (nrLinhas > 0) {
            char aux[50];
            for (int i = 0; i < nrLinhas; i++) {
                ANIMAIS temp;
                fscanf(f, "%s %s %d %s", temp.especie, temp.nome, &temp.peso, aux);
                temp.area = procurarAreaNome(&bm, aux);
                if (temp.area == NULL) {
                    printf("[ERRO] Area do animal %s, nao encontra.\n", temp.nome);
                }else{
                    temp.nrSerie = setID();
                    adicionarAnimal(temp);
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

void listarTodosAnimais() {
    ANIMAIS *ptr = ah.animais_inicio;
    while (ptr != NULL) {
        printf("%s %s %d %s\n", ptr->especie, ptr->nome, ptr->peso, ptr->area->id);
        ptr = ptr->prox;
    }
}


