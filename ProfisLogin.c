#include "utils.h"
#include <stdio.h>

/* ----------------- MENU DO PROFISSIONAL ----------------- */
void menuProfissional() {
    int op;

    do {
        printf(CYAN BOLD "\n========== ÁREA DO PROFISSIONAL ==========\n" RESET);
        printf(YELLOW "1." RESET " Cadastrar Profissional\n");
        printf(YELLOW "2." RESET " Listar Profissionais\n");
        printf(YELLOW "0." RESET " Sair\n");

        printf("\nEscolha: ");
        if (scanf("%d", &op) != 1) {
            while (getchar() != '\n');
            op = -1;
            continue;
        }
        while (getchar() != '\n');

        switch(op) {

            case 1: {
                char nome[50], email[50], senha[20], descricao[100];
                long long cpf, contato;
                int idade;
                char regiao;

                printf("\nNome: ");
                fgets(nome, sizeof(nome), stdin); trim_newline(nome);

                printf("Email: ");
                fgets(email, sizeof(email), stdin); trim_newline(email);

                printf("Senha: ");
                fgets(senha, sizeof(senha), stdin); trim_newline(senha);

                printf("CPF: ");
                scanf("%lld", &cpf); while(getchar()!='\n');

                printf("Contato: ");
                scanf("%lld", &contato); while(getchar()!='\n');

                printf("Idade: ");
                scanf("%d", &idade); while(getchar()!='\n');

                printf("Região (A-Z): ");
                scanf("%c", &regiao); while(getchar()!='\n');

                printf("Descricao: ");
                fgets(descricao, sizeof(descricao), stdin); trim_newline(descricao);

                addUsuario(senha, cpf, contato, idade, regiao, nome, email, descricao);
                break;
            }

            case 2:
                listarUsuarios();
                break;

            case 0:
                printf(RED "\nVoltando...\n" RESET);
                break;

            default:
                printf(RED "Opção inválida!\n" RESET);
        }

        printf(YELLOW "\nPressione ENTER para continuar..." RESET);
        getchar();

    } while(op != 0);
}

