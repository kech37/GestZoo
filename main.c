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
    init();
    if (iniciarVetor(&bm)) {
        do {
            op = apresentacaoMenu();
            limparConsola();
            switch (op) {
                case 1:
                    printf("<--- (1) Criar nova area --->\n");
                    criarNovaArea(&bm);
                    printf("Area Criada com sucesso!\n");
                    pausa();
                    break;
                case 2:
                    printf("<--- (2) Eliminar uma area --->\n");
                    eliminarArea(&bm);
                    printf("Area Eliminada com sucesso!\n");
                    pausa();
                    break;
                case 3:
                    printf("<--- (3) Listar Area --->\n");
                    for (int i = 0; i < bm.tamanho; i++) {
                        printf("%d - %s\n", i + 1, bm.areas[i].id);
                    }
                    printf("0 - Para cancelar\n");
                    printf("Escolha o nr da area que deseja listar: ");
                    scanf("%d", &aux);
                    aux--;
                    if (aux >= 0 && aux < bm.tamanho) {
                        printf("\n");
                        listarArea(&bm.areas[aux]);
                    } else if (aux != -1) {
                        printf("[ERRO] Opcao invalida!\n");
                    }
                    pausa();
                    break;
                case 4:
                    printf("<--- (4) Listar todas as Area --->\n");
                    listarTodasAreas(&bm);
                    pausa();
                    break;
                case 5:
                    if(carregaAnimaisFicheiroTXT("animais.txt")){
                        printf("Animais carregados com sucesso!\n");
                        pausa();
                    }
                    break;
                case 8:
                    listarTodosAnimais();
                    pausa();
                    break;
            }
        } while (op > 0 && op < 9);
        gravarFicheiroAreas(&bm);
    }
    return (EXIT_SUCCESS);
}

