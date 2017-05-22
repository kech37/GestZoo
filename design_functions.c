/* 
 *     File:   design_functions.c
 *    Aluno:   Carlos Filipe Sousa Pinho
 * Nº Aluno:   21220528
 *
 */

#include "util.h"

void limparConsola() {
    system("cls");
}

int apresentacaoMenu() {
    int op = -1;
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
        printf("        (9) Listagem informacao completa de um animal.\n");
        printf("  (10) Transferir animal.\n");
        printf("  (11) Procriacao de animais.\n");
        printf("  (12) Eliminar animal.\n");
        printf("(0) Sair.\n");
        printf("Sua opcao: ");
        scanf("%d", &op);
        if (!isdigit((op + '0'))) {
            fflush(stdin);
            op = -1;
        }
    } while (op < 0 || op > 12);
    return op;
}

void pausa() {
    printf("\n");
    system("pause");
}