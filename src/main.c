#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "moduleRegisterUser.h"
#include "moduleRegisterClient.h"
int main(){
    int opcao, idade;
    long long int contato, cpf;
    char nome[50], email[50], descricao[200], senha[20], regiao;

    acessarProfis(); //Carrega dados ao iniciar

    do{
        printf("\n--- MENU PRINCIPAL ---\n");
        printf("1. Cadastrar novo usuario\n");
        printf("2. Listar usuarios (Publico)\n");
        printf("3. Realizar Login (Admin ou Usuario)\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");

        if(scanf("%d", &opcao) != 1){
            opcao = -1;
        }
        while(getchar() != '\n'); 

        switch(opcao){
            case 1:
                printf("Digite seu nome: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';

                printf("Informe um email: ");
                fgets(email, sizeof(email), stdin);
                email[strcspn(email, "\n")] = '\0';

                printf("Defina uma senha: ");
                fgets(senha, sizeof(senha), stdin);
                senha[strcspn(senha, "\n")] = '\0';

                printf("Habilidades (descricao): ");
                fgets(descricao, sizeof(descricao), stdin);
                descricao[strcspn(descricao, "\n")] = '\0';

                printf("Qual sua idade? ");
                scanf("%d", &idade);
                
                printf("Informe seu CPF: ");
                scanf("%lld", &cpf);

                printf("Informe seu numero de contato: ");
                scanf("%lld", &contato);
                
                printf("Informe sua zona (Norte (n), Sul(s), Leste(l), Oeste(o)): ");
                scanf(" %c", &regiao);

                while(getchar() != '\n');//para evitar levar lixo para o menu

                addUsuario(senha, cpf, contato, idade, regiao, nome, email, descricao);
                break;

            case 2:
                listarUsuarios();
                break;

            case 3:
                profisLogin();
                break;

            case 0:
                cadastroProfis(); //salva antes de sair
                liberarMem();
                printf("Programa encerrado.\n");
                break;

            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while(opcao != 0);

    return 0;
}
