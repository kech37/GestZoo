/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "util.h"

void limparConsola() {
#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
    system("clear");
#endif

#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#endif
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
        printf("  (6) Eliminar area.\n");
        printf("  (7) Listar uma area.\n");
        printf("  (8) Listar todos os animais.\n");
        printf("(0) Sair.\n");
        printf("Sua opcao: ");
        scanf("%d", &op);
    } while (op < 0 || op > 8);
    return op;
}

void pausa() {
    printf("\n");
    system("pause");
}