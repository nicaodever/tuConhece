#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#include "moduleRegisterUser.h"
#include "moduleRegisterClient.h"

int main(){
	 system("mode con: cols=50 lines=40");
    setlocale(LC_ALL, "pt_BR.UTF-8");
    setlocale(LC_ALL, "Portuguese_Brazil.1252");
    setlocale(LC_ALL, "");

    int opcao, idade, tipocadastro;
    long long int contato, cpf;
    char nome[50], email[50], descricao[200], senha[20], regiao;

    boasVindas();
    acessarProfis(); // Carrega dados ao iniciar

    do {
        system("cls || clear");

        printf("\033[1;36m=============================================\n\033[0m");
        printf("\033[1;36m            Não tem login? Registre-se        \n\033[0m");
        printf("\033[1;36m=============================================\n\n\033[0m");

        printf("\033[1;37m[1]\033[0m Registrar-me\n");
        printf("\033[1;37m[2]\033[0m Login\n");
        printf("\033[1;37m[0]\033[0m Sair\n");

        printf("\033[1;36m---------------------------------------------\n\033[0m");
        printf("Escolha uma opção: ");

        if (scanf("%d", &opcao) != 1) {
            opcao = -1;
        }
        while (getchar() != '\n');

        switch (opcao) {
            case 1:
                menuRegister();
                break;

            case 2:
                system("cls || clear");
                printf("\033[1;33m+==============================================+\033[0m\n");
                printf("\033[1;33m|                 SELECIONAR LOGIN             |\033[0m\n");
                printf("\033[1;33m+==============================================+\033[0m\n\n");

                printf("\033[1;37m[1]\033[0m Login de Profissionais/Admin\n");
                printf("\033[1;37m[2]\033[0m Login de Clientes\n");
                printf("\033[1;37m[0]\033[0m Voltar\n\n");

                printf("Escolha uma opção: ");
                int tipoLogin;
                scanf("%d", &tipoLogin);
                while (getchar() != '\n');

                switch (tipoLogin) {
                    case 1:
                        system("cls || clear");
                        printf("\033[1;33m--- Login de Profissionais/Admin ---\033[0m\n\n");
                        profisLogin();
                        printf("\n");
                        system("pause");
                        break;

                    case 2:
                        system("cls || clear");
                        printf("\033[1;33m--- Login de Clientes ---\033[0m\n\n");

                        char emailLogin[50];
                        char senhaLogin[20];

                       printf("Email: ");
					   fgets(emailLogin, sizeof(emailLogin), stdin);
						emailLogin[strcspn(emailLogin, "\n")] = 0;

						printf("Senha: ");
						fgets(senhaLogin, sizeof(senhaLogin), stdin);
						senhaLogin[strcspn(senhaLogin, "\n")] = 0;

						loginCliente(emailLogin, senhaLogin);

                        printf("\n");
                        system("pause");
                        break;

                    case 0:
                        break;

                    default:
                        printf("\033[1;31mOpção inválida! Tente novamente.\033[0m\n");
                        system("pause");
                        break;
                }
                break;

            case 0:
                liberarMem();
                printf("\033[1;31mPrograma encerrado.\033[0m\n");
                break;

            default:
                printf("\033[1;31mOpção inválida. Tente novamente.\033[0m\n");
                system("pause");
        }

    } while (opcao != 0);
}
