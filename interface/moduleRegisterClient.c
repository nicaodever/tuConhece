#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "moduleRegisterClient.h"

/* ======= ESTILIZAÇÃO ======= */
#define RESET   "\033[0m"
#define VERDE   "\033[1;32m"
#define AMARELO "\033[1;33m"
#define VERMELHO "\033[1;31m"
#define CIANO   "\033[1;36m"
#define AZUL    "\033[1;34m"
#define BOLD    "\033[1m"

#define CLIENT_ARQ "clientes.txt"

/* ======= ESTRUTURA NA MEMÓRIA ======= */
static Dados clientes[500];
static int totalClientes = 0;

/* ======= FUNÇÃO INTERNA PARA LIMPAR \n ======= */
static void trim(char *s) {
    s[strcspn(s, "\n")] = 0;
}

/* ======= CARREGAR CLIENTES ======= */
static void carregarClientes() {
    FILE *f = fopen(CLIENT_ARQ, "r");
    if (!f) return;

    totalClientes = 0;

    while (fscanf(f, "%d;%19[^;];%24[^;];%19[^;];%c\n",
                  &clientes[totalClientes].id,
                  clientes[totalClientes].nome,
                  clientes[totalClientes].email,
                  clientes[totalClientes].senha,
                  &clientes[totalClientes].regiao) == 5) {
        totalClientes++;
    }

    fclose(f);
}

/* ======= SALVAR CLIENTES ======= */
static void salvarClientes() {
    FILE *f = fopen(CLIENT_ARQ, "w");
    if (!f) return;

    int i;
    for (i = 0; i < totalClientes; i++) {
        fprintf(f, "%d;%s;%s;%s;%c\n",
                clientes[i].id,
                clientes[i].nome,
                clientes[i].email,
                clientes[i].senha,
                clientes[i].regiao);
    }

    fclose(f);
}

/* ======= GERAR ID ======= */
int idCliente() {
    if (totalClientes == 0) return 1;
    return clientes[totalClientes - 1].id + 1;
}

/* ======= CADASTRO ======= */
void cadastroCliente() {
    carregarClientes();

    Dados novo;

    system("clear||cls");
    printf(CIANO BOLD "\n====== CADASTRO DO CLIENTE ======\n" RESET);

    novo.id = idCliente();

    printf("Nome: ");
    fgets(novo.nome, sizeof(novo.nome), stdin);
    trim(novo.nome);

    printf("Email: ");
    fgets(novo.email, sizeof(novo.email), stdin);
    trim(novo.email);

    printf("Senha: ");
    fgets(novo.senha, sizeof(novo.senha), stdin);
    trim(novo.senha);

    printf("Região (N/S/L/O): ");
    scanf("%c", &novo.regiao);
    getchar();

    clientes[totalClientes++] = novo;
    salvarClientes();

    printf(VERDE "\nCliente cadastrado com sucesso! ID: %d\n" RESET, novo.id);
    printf(AMARELO "Pressione ENTER para continuar..." RESET);
    getchar();
}

/* ======= LOGIN CLIENTE ======= */
void loginCliente() {
    carregarClientes();

    char email[50], senha[50];

    system("clear||cls");
    printf(CIANO BOLD "\n====== LOGIN DO CLIENTE ======\n" RESET);

    printf("Email: ");
    fgets(email, sizeof(email), stdin);
    trim(email);

    printf("Senha: ");
    fgets(senha, sizeof(senha), stdin);
    trim(senha);

    int i;
    for (i = 0; i < totalClientes; i++) {
        if (strcmp(email, clientes[i].email) == 0) {

            if (strcmp(senha, clientes[i].senha) == 0) {
                printf(VERDE "\nBem-vindo(a), %s!\n" RESET, clientes[i].nome);
            } else {
                printf(VERMELHO "\nSenha incorreta!\n" RESET);
            }

            printf(AMARELO "\nPressione ENTER para continuar..." RESET);
            getchar();
            return;
        }
    }
    
    
    printf(VERMELHO "\nCliente não encontrado!\n" RESET);
    printf(AMARELO "Pressione ENTER para continuar..." RESET);
    getchar();
}

/* ======= PERFIL DO CLIENTE (OPCIONAL) ======= */
void perfilCliente() {
    printf(AMARELO "\nPerfil do cliente será implementado futuramente...\n" RESET);
}

/* ======= ATUALIZAR DADOS (OPCIONAL) ======= */
void atualizarDados() {
    printf(AMARELO "\nAtualização de dados será implementada futuramente...\n" RESET);
}

