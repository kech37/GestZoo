/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: carlo
 *
 * Created on 29 de Abril de 2017, 18:25
 */

#include "util.h"

int main(int argc, char** argv) {
    int op, aux;
    struct AreasHelper ArrayAreas;
    struct AnimaisHelper ListaAnimais;
    ListaAnimais.head = ListaAnimais.atual = NULL;
    ListaAnimais.tamanho = 0;
    if (iniciarVetor(&ArrayAreas)) {
        if (!leAnimaisBinario(&ListaAnimais, &ArrayAreas)) {
            printf("[ERRO] Lista animais nao foi carregada.\n");
            pausa();
        }
        do {
            op = apresentacaoMenu();
            limparConsola();
            switch (op) {
                case 1:
                    printf("<--- (1) Criar nova area --->\n");
                    criarNovaArea(&ArrayAreas);
                    printf("Area Criada com sucesso!\n");
                    pausa();
                    break;
                case 2:
                    printf("<--- (2) Eliminar uma area --->\n");
                    eliminarArea(&ArrayAreas);
                    printf("Area Eliminada com sucesso!\n");
                    pausa();
                    break;
                case 3:
                    printf("<--- (3) Listar Area --->\n");
                    for (int i = 0; i < ArrayAreas.tamanho; i++) {
                        printf("%d - %s\n", i + 1, ArrayAreas.areas[i].id);
                    }
                    printf("0 - Para cancelar\n");
                    printf("Escolha o nr da area que deseja listar: ");
                    scanf("%d", &aux);
                    aux--;
                    if (aux >= 0 && aux < ArrayAreas.tamanho) {
                        printf("\n");
                        listarArea(&ArrayAreas.areas[aux]);
                    } else if (aux != -1) {
                        printf("[ERRO] Opcao invalida!\n");
                    }
                    pausa();
                    break;
                case 4:
                    printf("<--- (4) Listar todas as Area --->\n");
                    listarTodasAreas(&ArrayAreas);
                    pausa();
                    break;
                case 5:
                    printf("<--- (5) Carregar animais por ficheiro texto --->\n");
                    if (carregaAnimaisFicheiroTXT("animais.txt", &ArrayAreas, &ListaAnimais)) {
                        printf("Animais carregados com sucesso!\n");
                        pausa();
                    }
                    break;
                case 8:
                    printf("<--- (8) Listar todas os Animais --->\n");
                    listarTodosAnimais(&ListaAnimais);
                    pausa();
                    break;
            }
        } while (op > 0 && op < 9);
        if (!gravarFicheiroAreas(&ArrayAreas)) {
            printf("[ERRO] Array areas nao foi guardado.\n");
            pausa();
        }
        if (!guardarAnimaisBinario(&ListaAnimais)) {
            printf("[ERRO] Lista animais nao foi guardada.\n");
            pausa();
        }
    } else {
        pausa();
    }
    return (EXIT_SUCCESS);
}

