#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

/* ---------- CORES ANSI ---------- */
#define RESET   "\033[0m"
#define CYAN    "\033[1;36m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define MAG    "\033[1;35m"
#define BOLD    "\033[1m"

/* ---------- UTIL: conta chars visíveis ignorando ANSI ---------- */
int strlenSemAnsi(const char *s) {
    int len = 0;
    const char *p = s;
    while (*p) {
        if (*p == '\033') {           // começa um código ANSI
            p++;                      // pula '\033'
            if (*p == '[') {          // sequência CSI
                p++;
                while (*p && *p != 'm') p++; // pular até 'm'
                if (*p == 'm') p++;
            }
            continue;
        }
        len++;
        p++;
    }
    return len;
}

/* ---------- UTIL: pega largura do console (Windows) ---------- */
int get_terminal_width() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns = 80; // fallback
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdout && GetConsoleScreenBufferInfo(hStdout, &csbi)) {
        columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        if (columns < 20) columns = 80; // fallback se estranho
    }
    return columns;
}


/* ---------- TYPEWRITER (imprime com efeito de digitação) ---------- */
void typewriter_center(const char *texto, int delay_ms) {
	int i = 0;
    int largura = get_terminal_width();
    int tamVis = strlenSemAnsi(texto);
    int espacos = (largura - tamVis) / 2;
    if (espacos < 0) espacos = 0;

    for (i = 0; i < espacos; i++) putchar(' ');
    const char *p = texto;
    while (*p) {
        if (*p == '\033') { 
            const char *start = p;
            putchar(*p); p++;
            if (*p == '[') {
                putchar(*p); p++;
                while (*p && *p != 'm') { putchar(*p); p++; }
                if (*p) { putchar(*p); p++; }
            }
        } else {
            putchar(*p);
            fflush(stdout);
            Sleep(delay_ms);
            p++;
        }
    }
}


void boasVindas() {
    system("cls || clear");

    int largura = get_terminal_width();

    // Top border
    char top[256];
    snprintf(top, sizeof(top), "%s%s=====================================================%s\n", CYAN, BOLD, RESET);
    // Title lines (com cor)
    char *title1 = CYAN BOLD "                BEM-VINDO AO tuConhece               " RESET "\n";
    char *title2 = CYAN "            Plataforma de Conexão entre Profissionais " RESET "\n";
    char *empty = "\n";

    
    printf(top);
    printf(title1);
    printf(title2);
    printf(top);
    printf(empty);

    // Prompt
    printf(YELLOW "Pressione qualquer tecla para iniciar o carregamento..." RESET "\n");
    
    getch();
}

