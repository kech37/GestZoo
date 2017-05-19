/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   util.h
 * Author: carlo
 *
 * Created on 29 de Abril de 2017, 18:25
 */

#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX 50

#define FICHEIRO_AREAS "areas.txt"
#define FICHEIRO_ANIMAIS_BINARIO "animais.bin"

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct AREA_t {
        char id[MAX];
        int capacidade;
        int nrAreasAdj;
        char areasAdj[3][MAX];
    } AREA;

    typedef struct ANIMAIS_t {
        int nrSerie;
        char especie[MAX];
        char nome[MAX];
        int peso;
        AREA * area;
        struct ANIMAIS_t *filho;
        struct ANIMAIS_t *prox;
    } ANIMAIS;

    struct AreasHelper {
        int tamanho;
        AREA * areas;
    };

    struct AnimaisIDGiver {
        char especie[MAX];
        int idEspecie;
    };

    struct AnimaisHelper {
        int tamanho;
        struct AnimaisIDGiver *idGiver;
        int tamanho_id;
        ANIMAIS * head;
        ANIMAIS * atual;
    };

    int contaLinhas(char *nome);
    bool iniciarVetor(struct AreasHelper * ArrayAreas);
    bool gravarFicheiroAreas(struct AreasHelper * ArrayAreas);

    AREA* procurarAreaNome(struct AreasHelper * ArrayAreas, char *nome);
    void listarArea(AREA* areasInput);
    void listarTodosAnimaisPorArea(struct AnimaisHelper * ListaAnimais, char nomeArea[]);
    void listarTodosAnimaisPorEspecie(struct AnimaisHelper * ListaAnimais, char nomeEspecie[]);
    void listarTodasAreas(struct AreasHelper * ArrayAreas);
    ANIMAIS * getAnimalByIDandEspecie(int nrSerie, char especie[], struct AnimaisHelper * ListaAnimais);
    void criarNovaArea(struct AreasHelper * ArrayAreas);
    bool eliminarArea(struct AreasHelper * ArrayAreas, struct AnimaisHelper * ListaAnimais);

    bool carregaAnimaisFicheiroTXT(char * nome, struct AreasHelper * ArrayAreas, struct AnimaisHelper * ListaAnimais);
    void listarTodosAnimais(struct AnimaisHelper * ListaAnimais);
    bool guardarAnimaisBinario(struct AnimaisHelper * ListaAnimais);
    bool leAnimaisBinario(struct AnimaisHelper * ListaAnimais, struct AreasHelper * ArrayAreas);
    bool checkAnimalinArea(struct AnimaisHelper * ListaAnimais, char area[]);

    void limparConsola();
    int apresentacaoMenu();
    void pausa();

#ifdef __cplusplus
}
#endif

#endif /* UTIL_H */

