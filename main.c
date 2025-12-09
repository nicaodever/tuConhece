#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#include "moduleRegisterUser.h"
#include "moduleRegisterClient.h"



int main(){
	setlocale(LC_ALL, "pt_BR.UTF-8");
	setlocale(LC_ALL, "Portuguese_Brazil.1252");
	setlocale(LC_ALL, "");         // permite UTF-8 no programa 
	   
    int opcao, idade, tipocadastro;
    long long int contato, cpf;
    char nome[50], email[50], descricao[200], senha[20], regiao;

	boasVindas();   
    acessarProfis(); //Carrega dados ao iniciar

do {
system("cls || clear"); // limpa tela

printf("\033[1;36m=============================================\033[0m\n");
printf("\033[1;36m                MENU PRINCIPAL               \033[0m\n");
printf("\033[1;36m=============================================\033[0m\n");

printf("\033[1;37m   [1]\033[0m Registrar-me \n");
 //printf("\033[1;37m   [2]\033[0m  Listar usuários\n");
printf("\033[1;37m   [3]\033[0m  Login\n");
printf("\033[1;37m   [0]\033[0m  Sair\n");

printf("\033[1;36m---------------------------------------------\033[0m\n");
printf("Escolha uma opção: ");

	  
	   if (scanf("%d", &opcao) != 1)
	    { opcao = -1; } 
		
		while (getchar() != '\n');


    switch (opcao) {

        case 1:


	    system("cls || clear");
	    printf("\033[1;32m--- Tela de Cadastro ---\033[0m\n\n");
	
	    printf("\033[36m[1] Cadastrar Profissional\n");
	    printf("[2] Cadastrar Usuário Comum\n");
	    printf("[0] Voltar\n\033[0m");
	    printf("\nEscolha uma opção: ");
	
	    scanf("%d", &tipocadastro);
	    while (getchar() != '\n');
	
	    if (tipocadastro == 0) break;
	
	    char nome[100], email[100], senha[50], descricao[250];
	    int idade;
	    long long cpf, contato;
	    char regiao;
	
	    system("cls || clear");
	
	    printf("\033[1;32m--- Cadastro ---\033[0m\n");
	
	    printf("\033[36mDigite seu nome: \033[0m");
	    fgets(nome, sizeof(nome), stdin);
	    nome[strcspn(nome, "\n")] = '\0';
	
	    printf("\033[36mInforme um email: \033[0m");
	    fgets(email, sizeof(email), stdin);
	    email[strcspn(email, "\n")] = '\0';
	
	    printf("\033[36mDefina uma senha: \033[0m");
	    fgets(senha, sizeof(senha), stdin);
	    senha[strcspn(senha, "\n")] = '\0';
	
	    printf("\033[36mQual sua idade? \033[0m");
	    scanf("%d", &idade);
	
	    printf("\033[36mInforme seu CPF: \033[0m");
	    scanf("%lld", &cpf);
	
	    printf("\033[36mInforme seu número de contato: \033[0m");
	    scanf("%lld", &contato);
	
	    printf("\033[36mInforme sua zona (n/s/l/o): \033[0m");
	    scanf(" %c", &regiao);
	    while (getchar() != '\n');
	
	    // -------------------------------------------
	    // CADASTRO DE PROFISSIONAL OU USUÁRIO COMUM
	    // -------------------------------------------
	
	    if (tipocadastro == 1) {
	        system("cls || clear");
	        printf("\033[1;32m--- Cadastro de Profissional ---\033[0m\n");
	
	        printf("\033[36mHabilidades (descrição): \033[0m");
	        fgets(descricao, sizeof(descricao), stdin);
	        descricao[strcspn(descricao, "\n")] = '\0';
	
	       // addProfissional(senha, cpf, contato, idade, regiao, nome, email, descricao);
	
	        printf("\n\033[1;32m? Profissional cadastrado com sucesso!\033[0m\n");
	
	    } else if (tipocadastro == 2) {
	
	        addUsuario(senha, cpf, contato, idade, regiao, nome, email, descricao);
	
	        printf("\n\033[1;32m? Usuário comum cadastrado com sucesso!\033[0m\n");
	    } 
	    else {
	        printf("\033[1;31mOpção inválida!\033[0m\n");
	    }
	
	    system("pause");
            break;

        //case 2:
            //system("cls || clear");
            //printf("\033[1;34m--- Lista de Usuários ---\033[0m\n");
            //listarUsuarios();
            //printf("\n");
            //system("pause");
            //break;

        case 3:
            system("cls || clear");
            printf("\033[1;33m--- Login ---\033[0m\n");
            profisLogin();
            printf("\n");
            system("pause");
            break;

        case 0:
            cadastroProfis();
            liberarMem();
            printf("\033[1;31mPrograma encerrado.\033[0m\n");
            break;

        default:
            printf("\033[1;31mOpção inválida. Tente novamente.\033[0m\n");
            system("pause");
    }

} while (opcao != 0);

}
