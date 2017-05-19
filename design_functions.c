/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "util.h"

void limparConsola() {
    system("cls");
}

int apresentacaoMenu() {
    int op;
    do {
        limparConsola();
        printf("-> Menu areas\n");
        printf("  (1) Adicionar area.\n");
        printf("  (2) Eliminar area.\n");
        printf("  (3) Listar uma area.\n");
        printf("  (4) Listar todas as areas.\n");
        printf("-> Menu animais\n");
        printf("  (5) Carregar animais ficheiro txt.\n");
        printf("    -> Listagem de animais.\n");
        printf("        (6) Listar por especie.\n");
        printf("        (7) Listar por area.\n");
        printf("        (8) Listar completa.\n");
        printf("  (9) Transferir animal.\n");
        printf("  (10) Procriacao de animais.\n");
        printf("(0) Sair.\n");
        printf("Sua opcao: ");
        scanf("%d", &op);
    } while (op < 0 || op > 13);
    return op;
}

void pausa() {
    printf("\n");
    system("pause");
}