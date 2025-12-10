#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <string.h>

/* ---------- CORES ANSI ---------- */
#define RESET   "\033[0m"
#define CYAN    "\033[1;36m"
#define GREEN   "\033[1;32m"
#define BOLD    "\033[1m"

/* ---------- CENTRALIZAR TEXTO ---------- */
void centralizar(const char *texto) {
    int largura_terminal = 80;  // largura mais comum no CMD
    int tam = strlen(texto);
    int espacos = (largura_terminal - tam) / 2;
	int i;

    for (i = 0; i < 50; i++)
        printf("=");
}

/* ---------- TELA DE BOAS-VINDAS ---------- */
void boasVindas() {

    system("cls || clear");

    centralizar(CYAN "=====================================================\n" RESET);
    centralizar(CYAN BOLD "                BEM-VINDO AO tuConhece               \n" RESET);
    centralizar(CYAN "=====================================================\n\n" RESET);

    centralizar("Pressione qualquer tecla para iniciar...\n");
    getch();

    system("cls || clear");

    /* ---------- INICIANDO SISTEMA ---------- */
    centralizar("Inicializando sistema...\n\n");

    int largura_terminal = 80;
    int barra_total = 22; // "[" + 20 "#" + "]"
    int espacos = (largura_terminal - barra_total) / 2;
    int i;

    // centralizando início da barra
    for (i = 0; i < espacos; i++)
        printf(" ");

    printf("[");

    for (i = 0; i < 20; i++) {
        printf("#");
        fflush(stdout);
        Sleep(70);  // velocidade da animação
    }

    printf("]\n\n");

    centralizar(GREEN BOLD "Sistema carregado com sucesso.\n" RESET);
    centralizar("Bem-vindo ao tuConhece!\n\n");

    centralizar("Pressione qualquer tecla para continuar...\n");
    getch();
}

