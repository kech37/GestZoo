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
    int op, aux, limite_superior = 0;
    char aux_char[MAX];
    struct AreasHelper ArrayAreas;
    struct AnimaisHelper ListaAnimais;
    ListaAnimais.head = ListaAnimais.atual = NULL;
    ListaAnimais.tamanho = 0;
    ListaAnimais.tamanho_id = 0;
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
                    if (eliminarArea(&ArrayAreas, &ListaAnimais)) {
                        printf("Area Eliminada com sucesso!\n");
                    }
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
                case 6:
                    printf("<--- (6) Listagem por especie de animais --->\n");
                    for (int i = 0; i < ListaAnimais.tamanho_id; i++) {
                        printf("%d - %s\n", i + 1, ListaAnimais.idGiver[i].especie);
                    }
                    printf("0 - Para cancelar\n");
                    printf("Escolha uma especie:\n");
                    scanf("%d", &aux);
                    aux--;
                    if (aux >= 0 && aux < ListaAnimais.tamanho_id) {
                        printf("\n");
                        listarTodosAnimaisPorEspecie(&ListaAnimais, ListaAnimais.idGiver[aux].especie);
                    } else if (aux != -1) {
                        printf("[ERRO] Opcao invalida!\n");
                    }
                    pausa();
                    break;
                case 7:
                    printf("<--- (7) Listagem de animais por area --->\n");
                    for (int i = 0; i < ArrayAreas.tamanho; i++) {
                        printf("%d - %s\n", i + 1, ArrayAreas.areas[i].id);
                    }
                    printf("0 - Para cancelar\n");
                    printf("Escolha uma area: ");
                    scanf("%d", &aux);
                    aux--;
                    if (aux >= 0 && aux < ArrayAreas.tamanho) {
                        printf("\n");
                        listarTodosAnimaisPorArea(&ListaAnimais, ArrayAreas.areas[aux].id);
                    } else if (aux != -1) {
                        printf("[ERRO] Opcao invalida!\n");
                    }
                    pausa();
                    break;
                case 8:
                    printf("<--- (8) Listagem completa de animais --->\n");
                    listarTodosAnimais(&ListaAnimais);
                    pausa();
                    break;
                case 9:
                    printf("<--- (9) Transferir animal --->\n");
                    for (int i = 0; i < ListaAnimais.tamanho_id; i++) {
                        printf("%d - %s\n", i + 1, ListaAnimais.idGiver[i].especie);
                    }
                    printf("0 - Para cancelar\n");
                    printf("Escolha a especie do animal que quer transferir:\n");
                    scanf("%d", &aux);
                    aux--;
                    if (aux >= 0 && aux < ListaAnimais.tamanho_id) {
                        strcpy(aux_char, ListaAnimais.idGiver[aux].especie);
                        printf("\n");
                        ListaAnimais.atual = ListaAnimais.head;
                        while (ListaAnimais.atual != NULL) {
                            if (!strcmp(ListaAnimais.atual->especie, aux_char)) {
                                printf("%d - %s\n", ListaAnimais.atual->nrSerie, ListaAnimais.atual->nome);
                                limite_superior++;
                            }
                            ListaAnimais.atual = ListaAnimais.atual->prox;
                        }
                        printf("Escolha o ID do animal que quer transferir:\n");
                        scanf("%d", &aux);
                        if (aux >= 0 && aux < limite_superior) {
                            printf("\n");
                            limite_superior = 0;
                            ANIMAIS * temp = getAnimalByIDandEspecie(aux, aux_char, &ListaAnimais);
                            if (temp != NULL) {
                                for (int i = 0; i < temp->area->nrAreasAdj; i++) {
                                    printf("%d - %s\n", i, temp->area->areasAdj[i]);
                                    limite_superior++;
                                }
                                printf("Escolha o ID da area para que deseja transferir o animal:\n");
                                scanf("%d", &aux);
                                if (aux >= 0 && aux < limite_superior) {
                                    temp->area = procurarAreaNome(&ArrayAreas, temp->area->areasAdj[aux]);
                                } else {
                                    printf("[ERRO] Opcao invalida!\n");
                                }
                            }
                        } else {
                            printf("[ERRO] Opcao invalida!\n");
                        }
                    } else if (aux != -1) {
                        printf("[ERRO] Opcao invalida!\n");
                    }
                    pausa();
                    break;
            }
        } while (op > 0 && op < 14);
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

