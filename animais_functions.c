/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "util.h"

#define NOME_FICHEIRO_ANIMAIS "animais.bin"

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

int animalIDGiver(struct AnimaisHelper * ListaAnimais, char nomeEspecie[]) {
    if (ListaAnimais->tamanho_id == 0) {
        ListaAnimais->idGiver = malloc(sizeof (struct AnimaisIDGiver));
        ListaAnimais->idGiver[ListaAnimais->tamanho_id].idEspecie = 0;
        strcpy(ListaAnimais->idGiver[ListaAnimais->tamanho_id].especie, nomeEspecie);
        ListaAnimais->tamanho_id++;
        return ListaAnimais->idGiver[0].idEspecie;
    } else {
        for (int i = 0; i < ListaAnimais->tamanho_id; i++) {
            if (!strcmp(ListaAnimais->idGiver[i].especie, nomeEspecie)) {
                ListaAnimais->idGiver[i].idEspecie++;
                return ListaAnimais->idGiver[i].idEspecie;
            }
        }
        ListaAnimais->tamanho_id++;
        ListaAnimais->idGiver = realloc(ListaAnimais->idGiver, sizeof (struct AnimaisIDGiver) * ListaAnimais->tamanho_id);
        strcpy(ListaAnimais->idGiver[ListaAnimais->tamanho_id - 1].especie, nomeEspecie);
        ListaAnimais->idGiver[ListaAnimais->tamanho_id - 1].idEspecie = 0;
        return ListaAnimais->idGiver[ListaAnimais->tamanho_id - 1].idEspecie;
    }
}

bool criaLista(struct AnimaisHelper * ListaAnimais, ANIMAIS animal) {
    ANIMAIS * temp = malloc(sizeof (ANIMAIS));
    if (temp == NULL) {
        printf("[ERRO] Alocacao de memoria.\n");
        return false;
    }
    temp->area = animal.area;
    temp->parente1 = animal.parente1;
    temp->parente2 = animal.parente2;
    temp->nrSerie = animalIDGiver(ListaAnimais, animal.especie);
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
        temp->parente1 = animal.parente1;
        temp->parente2 = animal.parente2;
        temp->nrSerie = animalIDGiver(ListaAnimais, animal.especie);
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
        printf("%3d\t%20s\t%10s\t%5d\t%10s\n", animal->nrSerie, animal->nome, animal->especie, animal->peso, animal->area->id);
    } else {
        printf("Ponteiro ANIMAIS NULL.\n");
    }
}

void listarTodosAnimaisPorArea(struct AnimaisHelper * ListaAnimais, char nomeArea[]) {
    ANIMAIS *temp = ListaAnimais->head;
    while (temp != NULL) {
        if (!strcmp(temp->area->id, nomeArea)) {
            listaAnimal(temp);
        }
        temp = temp->prox;
    }
}

void listarTodosAnimaisPorEspecie(struct AnimaisHelper * ListaAnimais, char nomeEspecie[]) {
    ANIMAIS *temp = ListaAnimais->head;
    while (temp != NULL) {
        if (!strcmp(temp->especie, nomeEspecie)) {
            listaAnimal(temp);
        }
        temp = temp->prox;
    }
}

void listarTodosAnimais(struct AnimaisHelper * ListaAnimais) {
    ANIMAIS *temp = ListaAnimais->head;
    while (temp != NULL) {
        listaAnimal(temp);
        temp = temp->prox;
    }
}

ANIMAIS * getAnimalByIDandEspecie(int nrSerie, char especie[], struct AnimaisHelper * ListaAnimais) {
    ListaAnimais->atual = ListaAnimais->head;
    while (ListaAnimais->atual != NULL) {
        if (ListaAnimais->atual->nrSerie == nrSerie && !strcmp(ListaAnimais->atual->especie, especie)) {
            return ListaAnimais->atual;
        }
        ListaAnimais->atual = ListaAnimais->atual->prox;
    }
    return NULL;
}

ANIMAIS * getToEliminateAnimalByIDeEspecie(int nrSerie, char especie[], ANIMAIS ** anterior, struct AnimaisHelper * ListaAnimais) {
    ANIMAIS *ptr = ListaAnimais->head;
    ANIMAIS *temp = NULL;
    bool encontrei = false;
    while (ptr != NULL) {
        if (ptr->nrSerie == nrSerie && !strcmp(ptr->especie, especie)) {
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

bool eliminaNodo(int nrSerie, char especie[], struct AnimaisHelper * ListaAnimais) {
    ANIMAIS *anterior = NULL;
    ANIMAIS *eliminar = getToEliminateAnimalByIDeEspecie(nrSerie, especie, &anterior, ListaAnimais);
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

bool checkAnimalinArea(struct AnimaisHelper * ListaAnimais, char area[]) {
    ListaAnimais->atual = ListaAnimais->head;
    while (ListaAnimais->atual != NULL) {
        if (!strcmp(ListaAnimais->atual->area->id, area)) {
            return true;
        }
        ListaAnimais->atual = ListaAnimais->atual->prox;
    }
    return false;
}