/* 
 *     File:   main.c
 *    Aluno:   Carlos Filipe Sousa Pinho
 * Nº Aluno:   21220528
 *
 */

#include "util.h"

int main(int argc, char** argv) {
    int op, aux, conta = 0;
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
                    }
                    pausa();
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
                    printf("<--- (9) Listagem informacao completa de um animal --->\n");
                    for (int i = 0; i < ListaAnimais.tamanho_id; i++) {
                        printf("%d - %s\n", i + 1, ListaAnimais.idGiver[i].especie);
                    }
                    printf("0 - Para cancelar\n");
                    printf("Escolha uma especie:\n");
                    scanf("%d", &aux);
                    aux--;
                    if (aux >= 0 && aux < ListaAnimais.tamanho_id) {
                        strcpy(aux_char, ListaAnimais.idGiver[aux].especie);
                        printf("\n");
                        conta = 0;
                        ListaAnimais.atual = ListaAnimais.head;
                        while (ListaAnimais.atual != NULL) {
                            if (!strcmp(ListaAnimais.atual->especie, aux_char)) {
                                printf("%d - %s\n", ListaAnimais.atual->nrSerie, ListaAnimais.atual->nome);
                                conta++;
                            }
                            ListaAnimais.atual = ListaAnimais.atual->prox;
                        }
                        printf("Escolha o ID do animal que quer ver as informacoes completas:\n");
                        scanf("%d", &aux);
                        if (aux >= 0 && aux < conta) {
                            int familia = 0;
                            printf("\n");
                            conta = 0;
                            ANIMAIS * temp = getAnimalByIDandEspecie(aux, aux_char, &ListaAnimais);
                            if (temp != NULL) {
                                limparConsola();
                                if (temp->parente1 != NULL || temp->parente2 != NULL) {
                                    if (temp->parente1 != NULL) {
                                        familia++;
                                        printf("Ascendencia #%d:\nNome: %s\n    nrSerie / Especie: %d / %s\n", familia, temp->parente1->nome, temp->parente1->nrSerie, temp->parente1->especie);
                                    }
                                    if (temp->parente2 != NULL) {
                                        familia++;
                                        printf("Ascendencia #%d\nNome: %s\n    nrSerie / Especie: %d / %s\n", familia, temp->parente2->nome, temp->parente2->nrSerie, temp->parente2->especie);
                                    }
                                }
                                if (familia == 0) {
                                    printf("<Sem ascendencia>\n");
                                }
                                familia = 0;
                                printf("\nAnimal escolhido:\n");
                                printf(" --> Nome: %s\n    nrSerie / Especie: %d / %s\n    Peso: %d\n    Area: %s\n\n", temp->nome, temp->nrSerie, temp->especie, temp->peso, temp->area->id);
                                ListaAnimais.atual = ListaAnimais.head;
                                while (ListaAnimais.atual != NULL) {
                                    if ((ListaAnimais.atual->parente1 != NULL && ListaAnimais.atual->parente1->nrSerie == temp->nrSerie && !strcmp(ListaAnimais.atual->parente1->especie, temp->especie)) || (ListaAnimais.atual->parente2 != NULL && ListaAnimais.atual->parente2->nrSerie == temp->nrSerie && !strcmp(ListaAnimais.atual->parente2->especie, temp->especie))) {
                                        familia++;
                                        printf("Descendente #%d:\n Nome: %s\n    nrSerie / Especie: %d / %s\n", familia, ListaAnimais.atual->nome, ListaAnimais.atual->nrSerie, ListaAnimais.atual->especie);
                                    }
                                    ListaAnimais.atual = ListaAnimais.atual->prox;
                                }
                                if (familia == 0) {
                                    printf("<Sem descendentes>\n");
                                }
                            } else {
                                printf("[ERRO] Animal nao existe!\n");
                            }
                        }
                    }
                    pausa();
                    break;
                case 10:
                    printf("<--- (10) Transferir animal --->\n");
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
                        conta = 0;
                        ListaAnimais.atual = ListaAnimais.head;
                        while (ListaAnimais.atual != NULL) {
                            if (!strcmp(ListaAnimais.atual->especie, aux_char)) {
                                printf("%d - %s\n", ListaAnimais.atual->nrSerie, ListaAnimais.atual->nome);
                                conta++;
                            }
                            ListaAnimais.atual = ListaAnimais.atual->prox;
                        }
                        printf("Escolha o ID do animal que quer transferir:\n");
                        scanf("%d", &aux);
                        if (aux >= 0 && aux < conta) {
                            printf("\n");
                            conta = 0;
                            ANIMAIS * temp = getAnimalByIDandEspecie(aux, aux_char, &ListaAnimais);
                            if (temp != NULL) {
                                for (int i = 0; i < temp->area->nrAreasAdj; i++) {
                                    if (verificaCapacidadeArea(&ListaAnimais, procurarAreaNome(&ArrayAreas, temp->area->areasAdj[i]), temp->peso)) {
                                        printf("%d - %s\n", i, temp->area->areasAdj[i]);
                                        conta++;
                                    }
                                }
                                if (conta == 0) {
                                    printf("[ERRO] Nao ha areas adjacentes com capacidade suficiente para o animal %s!\n", temp->nome);
                                    pausa();
                                    break;
                                } else {
                                    printf("Escolha o ID da area para que deseja transferir o animal:\n");
                                    scanf("%d", &aux);
                                    if (aux >= 0 && aux <= conta) {
                                        if (verificaCapacidadeArea(&ListaAnimais, procurarAreaNome(&ArrayAreas, temp->area->areasAdj[aux]), temp->peso)) {
                                            temp->area = procurarAreaNome(&ArrayAreas, temp->area->areasAdj[aux]);
                                        } else {
                                            printf("[ERRO] Nao e possivel realizar a transferencia!\n       A area nao tem capacidade para este anima.\n");
                                        }
                                    } else {
                                        printf("[ERRO] Opcao invalida!\n");
                                    }
                                }

                            } else {
                                printf("[ERRO] Animal nao existe!\n");
                            }
                        } else {
                            printf("[ERRO] Opcao invalida!\n");
                        }
                    } else if (aux != -1) {
                        printf("[ERRO] Opcao invalida!\n");
                    }
                    pausa();
                    break;
                case 11:
                    printf("<--- (11) Procriacao de animais --->\n");
                    for (int i = 0; i < ListaAnimais.tamanho_id; i++) {
                        printf("%d - %s\n", i + 1, ListaAnimais.idGiver[i].especie);
                    }
                    printf("0 - Para cancelar\n");
                    printf("Escolha a especie do animal que procriar:\n");
                    scanf("%d", &aux);
                    aux--;
                    if (aux >= 0 && aux < ListaAnimais.tamanho_id) {
                        conta = 0;
                        ListaAnimais.atual = ListaAnimais.head;
                        while (ListaAnimais.atual != NULL) {
                            if (!strcmp(ListaAnimais.atual->especie, ListaAnimais.idGiver[aux].especie)) {
                                conta++;
                            }
                            ListaAnimais.atual = ListaAnimais.atual->prox;
                        }
                        if (conta >= 2) {
                            ANIMAIS * temp_parente1, * temp_parente2;
                            ANIMAIS temp_filho;
                            strcpy(temp_filho.especie, ListaAnimais.idGiver[aux].especie);
                            printf("\n");
                            ListaAnimais.atual = ListaAnimais.head;
                            while (ListaAnimais.atual != NULL) {
                                if (!strcmp(ListaAnimais.atual->especie, temp_filho.especie)) {
                                    printf("%d - %s\n", ListaAnimais.atual->nrSerie, ListaAnimais.atual->nome);
                                }
                                ListaAnimais.atual = ListaAnimais.atual->prox;
                            }
                            printf("Escolha o ID do animal que sera o parente 1:\n");
                            scanf("%d", &aux);
                            temp_parente1 = getAnimalByIDandEspecie(aux, temp_filho.especie, &ListaAnimais);
                            if (temp_parente1 != NULL) {
                                printf("\n");
                                ListaAnimais.atual = ListaAnimais.head;
                                while (ListaAnimais.atual != NULL) {
                                    if (!strcmp(ListaAnimais.atual->especie, temp_filho.especie) && ListaAnimais.atual->nrSerie != temp_parente1->nrSerie) {
                                        printf("%d - %s\n", ListaAnimais.atual->nrSerie, ListaAnimais.atual->nome);
                                    }
                                    ListaAnimais.atual = ListaAnimais.atual->prox;
                                }
                                printf("Escolha o ID do animal que sera o parente 2:\n");
                                scanf("%d", &aux);
                                temp_parente2 = getAnimalByIDandEspecie(aux, temp_filho.especie, &ListaAnimais);
                                if (temp_parente2 != NULL) {
                                    temp_filho.peso = temp_parente1->peso * 0.20 + temp_parente2->peso * 0.20;
                                    for (int i = 0; i < ArrayAreas.tamanho; i++) {
                                        if (verificaCapacidadeArea(&ListaAnimais, &ArrayAreas.areas[i], temp_filho.peso)) {
                                            printf("%d - %s\n", i, ArrayAreas.areas[i].id);
                                        }
                                    }
                                    printf("Escolhe a area que desejas transferir o animal: \n(se faltar areas, e porque estas nao tem capacidade para o novo animal)\n");
                                    scanf("%d", &aux);
                                    if (aux >= 0 && aux < ArrayAreas.tamanho) {
                                        temp_filho.area = &ArrayAreas.areas[aux];
                                        printf("Indique o nome do novo animal:");
                                        scanf("%s", temp_filho.nome);
                                        temp_filho.parente1 = temp_parente1;
                                        temp_filho.parente2 = temp_parente2;
                                        if (AdicionaAnimal(&ListaAnimais, temp_filho)) {
                                            printf("[LOG] Animal procriado com sucesso!\n");
                                        } else {
                                            printf("[ERRO] Ocorreu um erro na procriacao do animal.\n");
                                        }
                                    } else if (aux != -1) {
                                        printf("[ERRO] Opcao invalida, area inexistente!\n");
                                    }
                                } else {
                                    printf("[ERRO] Nao foi encontrado esse animal parente 2!\n");
                                }
                            } else {
                                printf("[ERRO] Nao foi encontrado esse animal parente 1!\n");
                            }
                        } else {
                            printf("[ERRO] Nao ha animais suficientes para procriar!\n");
                        }
                    }
                    pausa();
                    break;
                case 12:
                    printf("<--- (12) Eliminar animal --->\n");
                    for (int i = 0; i < ListaAnimais.tamanho_id; i++) {
                        printf("%d - %s\n", i + 1, ListaAnimais.idGiver[i].especie);
                    }
                    printf("0 - Para cancelar\n");
                    printf("Escolha uma especie:\n");
                    scanf("%d", &aux);
                    aux--;
                    if (aux >= 0 && aux < ListaAnimais.tamanho_id) {
                        strcpy(aux_char, ListaAnimais.idGiver[aux].especie);
                        printf("\n");
                        conta = 0;
                        ListaAnimais.atual = ListaAnimais.head;
                        while (ListaAnimais.atual != NULL) {
                            if (!strcmp(ListaAnimais.atual->especie, aux_char)) {
                                printf("%d - %s\n", ListaAnimais.atual->nrSerie, ListaAnimais.atual->nome);
                                conta++;
                            }
                            ListaAnimais.atual = ListaAnimais.atual->prox;
                        }
                        if(conta == 0){
                            printf("[ERRO] Nao ha animais desta especie para serem eliminados!\n.");
                            pausa();
                            break;
                        }
                        printf("Escolha o ID do animal que deseja eliminar:\n");
                        scanf("%d", &aux);
                        if (aux >= 0 && aux < conta) {
                            if (eliminaNodo(aux, aux_char, &ListaAnimais)) {
                                printf("[LOG] Animal eliminado com sucesso!\n");
                            } else {
                                printf("[ERRO] Ao elimnar o animal...\n");
                            }
                        }
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

