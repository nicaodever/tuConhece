#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

void centralizar(const char *texto) {
    int largura_terminal = 80; // largura padrão do CMD
    int tam = strlen(texto);
    int espacos = (largura_terminal - tam) / 2;
    int i;

    for (i = 0; i < espacos; i++)
        printf(" ");
    printf("%s", texto);
}

void boasVindas() {
    int i;

    system("cls || clear");

    centralizar("\033[1;36m=============================================\033[0m\n");
    centralizar("\033[1;36m              BEM-VINDO AO tuConhece         \033[0m\n");
    centralizar("\033[1;36m=============================================\033[0m\n\n");

    centralizar("Pressione qualquer tecla para iniciar o carregamento...\n");
    getch();

    system("cls || clear");

    centralizar("Inicializando tuConhece...\n\n");

    // Centraliza o começo da barra
    int largura_terminal = 80;
    int barra_total = 22; // "[" + 20 "#" + "]"
    int espacos = (largura_terminal - barra_total) / 2;

    for (i = 0; i < espacos; i++)
        printf(" ");

    printf("[");
    for (i = 0; i < 20; i++) {
        printf("#");
        fflush(stdout);
        Sleep(70);
    }
    printf("]\n\n");

    centralizar("\033[1;32mSistema carregado com sucesso.\033[0m\n");
    centralizar("Bem-vindo ao tuConhece!\n\n");

    centralizar("Pressione qualquer tecla para continuar...\n");
    getch();
}

