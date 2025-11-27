#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "moduleRegisterUser.h"
#include "moduleRegisterClient.h"
int main(){
    int opcao, idade, cpf, contato;
    char nome[50], email[50], descricao[200], regiao;

    acessarUsuarios();

    do{
        printf("\n--- MENU DE CADASTRO ---\n");
        printf("1. Cadastrar novo usuario\n");
        printf("2. Listar usuarios\n");
        printf("3. Salvar dados em arquivo\n");
        printf("0. Sair (Salvar dados e liberar memoria)\n");
        printf("Escolha uma opcao: ");

        if(scanf("%d", &opcao)!=1){ //Lê a opção e limpa o buffer
            opcao=-1; //caso ele leia um número define como invalida e limpa o buffer
        }
        while(getchar()!='\n');

        switch(opcao){
            case 1:
                printf("Informe o nome:");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")]='\0'; //remove o enter e adiciona o final da string

                printf("Informe o email:");
                fgets(email, sizeof(email), stdin);
                email[strcspn(email, "\n")]='\0';

                printf("Informe uma descricao concisa:");
                fgets(descricao, sizeof(descricao), stdin);
                descricao[strcspn(descricao, "\n")]='\0';

                printf("Qual sua idade?");
                scanf("%d", &idade);
                
                printf("Informe seu CPF:");
                scanf("%d", &cpf);

                printf("Informe seu numero de contato:");
                scanf("%d", &contato);
                getchar();  //limpando o buffer
                printf("Informe sua zona com apenas uma letra(Norte (n), Sul(s), Leste(l), Oeste(o)):");
                scanf("%c", &regiao);

                adicionarUsuario(cpf, contato, idade, regiao, nome, email, descricao);
                break;
            case 2:
                listarUsuarios();
                break;
            case 3:
                salvar_cadastros();
                break;
            case 0:
                salvar_cadastros();
                liberarMem();
                printf("Programa encerrado.\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    }while(opcao!=0);

    return 0;
}
