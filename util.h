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

    struct BlocoMemoria {
        int tamanho;
        AREA * areas;
    };

    struct BlocoMemoria bm;

    struct AnimaisHelper {
        int conta_id;
        int tamanho;
        ANIMAIS * animais_inicio;
        ANIMAIS * animais_atual;
    };

    struct AnimaisHelper ah;

    int contaLinhas(char *nome);
    bool iniciarVetor(struct BlocoMemoria * bm);
    bool gravarFicheiroAreas(struct BlocoMemoria * bm);

    AREA* procurarAreaNome(struct BlocoMemoria * bm, char *nome);
    void listarArea(AREA* areasInput);
    void listarTodasAreas(struct BlocoMemoria * bm);
    void criarNovaArea(struct BlocoMemoria * bm);
    void eliminarArea(struct BlocoMemoria * bm);

    void init();
    bool carregaAnimaisFicheiroTXT(char * nome);
    void listarTodosAnimais();

    void limparConsola();
    int apresentacaoMenu();
    void pausa();

#ifdef __cplusplus
}
#endif

#endif /* UTIL_H */

