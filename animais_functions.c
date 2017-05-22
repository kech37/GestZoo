/* 
 *     File:   animais_functions.c
 *    Aluno:   Carlos Filipe Sousa Pinho
 * Nº Aluno:   21220528
 *
 */

#include "util.h"

#define NOME_FICHEIRO_ANIMAIS "animais.bin"

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
    ListaAnimais->atual = ListaAnimais->head;
    while (ListaAnimais->atual != NULL) {
        if (ListaAnimais->atual->parente1 != NULL && ListaAnimais->atual->parente1->nrSerie == eliminar->nrSerie && !strcmp(ListaAnimais->atual->parente1->especie, eliminar->especie)) {
            ListaAnimais->atual->parente1 = NULL;
        }
        if (ListaAnimais->atual->parente2 != NULL && ListaAnimais->atual->parente2->nrSerie == eliminar->nrSerie && !strcmp(ListaAnimais->atual->parente2->especie, eliminar->especie)) {
            ListaAnimais->atual->parente2 = NULL;
        }
        ListaAnimais->atual = ListaAnimais->atual->prox;
    }
    free(eliminar);
    ListaAnimais->tamanho--;
    eliminar = NULL;
    return true;
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