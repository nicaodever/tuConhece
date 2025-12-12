#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "moduleRegisterClient.h"


/* ----------------- CONFIGURAÇÃO DE CORES (ANSI) ----------------- */
#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define CYAN    "\033[1;36m"
#define BOLD    "\033[1m"

static Dados userLog;


void cadastroCliente(char *nome,char *email,char *senha,char regiao){
  //gera um novo id
  int novoId = idCliente();
  
  //abre o arquivo cliente
  FILE *file = fopen("cliente.dat","ab+");
    
  if(file == NULL){
    printf("Erro ao abrir arquivo para escrita!");
     return;
  }
  //pega a ultima posiÃ§ao no arquivo
  fseek(file,0,SEEK_END);
  long posicao_registro = ftell(file);
  //preenche a struct
  Dados data;
  strcpy(data.nome ,nome);
  strcpy(data.email,email);
  strcpy(data.senha ,senha);
  data.regiao = regiao;
  data.id = novoId;

  //escreve no arquivo e fecha
  fwrite(&data,sizeof(Dados),1,file);
  fclose(file);
  //abre file para guardar id e pos
  FILE *fileIndex = fopen("clienteIndex.dat","ab");
  if(fileIndex == NULL){
    printf("Erro ao abrir o arquivo de indice para escrita");
    return;
  }
  //cria struct do indice  
  Index idx;
  idx.id = novoId;
  idx.pos = posicao_registro;
  //escreve no arquivo index
  fwrite(&idx,sizeof(Index),1,fileIndex);
  fclose(fileIndex);
	printf("Cadastrado com sucesso");
}

// gerador de id
int idCliente(){
  FILE *file  = fopen("cliente.dat","rb");
  Dados data_temp;
  long tam_file;
  //se o arquivo nao existir, id deve ser 1
  if(file == NULL){
    return 1;
  }
  //vai para o final do arquivo e mede o tamanho total
  fseek(file,0,SEEK_END);
  tam_file = ftell(file);

  //se o arquivo estiver vazio, id deve ser 1
  if(tam_file == 0){
    fclose(file);
    return 1;
  }
  //verifica se arquivo nao esta corrompido
  if(tam_file % sizeof(Dados) != 0){
    printf("Erro: Arquivo corrompido ou incompleto.");
    fclose(file);
    return 1;
  }
  //volta o para a ultima struct
  fseek(file, -(long)sizeof(Dados), SEEK_CUR);
  //le o ultimo registro para obter id  
  if(fread(&data_temp,sizeof(Dados),1,file) != 1){
    printf("Erro de leitura do ultimo registro.");
    fclose(file);
    return 1;
  }
  fclose(file);

  return data_temp.id + 1;
}

//valida o login 
void loginCliente(char *email,char *senha){
    // remover quebra de linha
    email[strcspn(email, "\n")] = 0;
    senha[strcspn(senha, "\n")] = 0;

    FILE *file = fopen("cliente.dat","rb");
    if(file == NULL){
        printf("Erro ao abrir arquivo para leitura!");
        return;
    }

    Dados data;
    while (fread(&data, sizeof(Dados), 1, file) == 1) {

        if(strcmp(data.email, email) == 0 && strcmp(data.senha, senha) == 0){
            printf("Usuario encontrado!");
            userLog = data;
            fclose(file);
            menuCliente();
            return;
        }
    }
    printf("Usuario nao encontrado!");
    fclose(file);
}
/* ----------------- MENU Cliente ----------------- */
void menuCliente() {
    int op;
    char regiao;
    do {
        printf(CYAN BOLD "\n========== ÁREA DO Cliente ==========\n" RESET);
        printf(YELLOW "1." RESET " Listar Profissionais\n");
        printf(YELLOW "2." RESET " Filtrar por Região\n");
        printf(YELLOW "3." RESET " Entender meu problema\n");
        printf(YELLOW "4." RESET " Visualizar perfil\n");
         printf(YELLOW "5." RESET " Atualizar perfil\n");
        printf(YELLOW "0." RESET " Sair\n");

        printf("\nEscolha: ");
        if (scanf("%d", &op) != 1) {
            while (getchar() != '\n');
            op = -1;
            continue;
        }
        while (getchar() != '\n');
  switch(op) {

            case 1:
                listarUsuarios();
                break;
                
             case 2:
			 	
             	printf("Escolha uma região(n/s/l/o): ");
    			scanf("%c", &regiao);
			    buscarPorRegiao(regiao);
				break;  
            case 3: 
               moduleDiagnostico();
               break;
               
            case 4: 
				perfilCliente();
				break;   
            case 5:
            	atualizarDados();
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
void perfilCliente(){
  printf("\n|----Dados do Perfil----|\n");
  printf("|  Id: %d\n",userLog.id);
  printf("|  Nome: %s\n",userLog.nome);
  printf("|  Email: %s\n",userLog.email);
  printf("|  Regiao: %c\n",userLog.regiao);
  printf("|  Senha: %s\n",userLog.senha);
  printf("|-----------------------|\n");
}
//atualiza os dados do cliente logado
void atualizarDados() {
    Dados temp = userLog;
    char input[100];
    int escolha = 0;
    int alterado = 0;

    system("cls || clear");

    printf("\033[1;36m+--------------------------------------------------------------+\n");
    printf("|           ATUALIZAR DADOS DO PERFIL (ID: %d)                |\n", userLog.id);
    printf("+--------------------------------------------------------------+\033[0m\n");

    while (escolha != 5) {

        printf("\n\033[1;33mO que deseja alterar?\033[0m\n");
        printf("\033[1;32m1.\033[0m Nome   : %s\n", temp.nome);
        printf("\033[1;32m2.\033[0m Email  : %s\n", temp.email);
        printf("\033[1;32m3.\033[0m Senha  : %s\n", temp.senha);
        printf("\033[1;32m4.\033[0m Regiao : %c\n", temp.regiao);
        printf("\033[1;32m5.\033[0m Salvar e Sair\n");
        printf("Escolha: ");

        if (scanf("%d", &escolha) != 1) {
            while (getchar() != '\n');
            escolha = 0;
            continue;
        }
        while (getchar() != '\n');

        switch (escolha) {
            case 1:
                alterado = 1;
                printf("\nDigite o novo nome:\n");
                while (1) {
                    int valido = 1;
                    fgets(input, sizeof(input), stdin);
                    input[strcspn(input, "\n")] = 0;
					int i = 0;
                    for (i = 0; i < strlen(input); i++) {
                        if (!isalpha(input[i])) {
                            printf("O nome deve conter apenas letras.\n");
                            valido = 0;
                            break;
                        }
                    }
                    if (valido) break;
                }
                strcpy(temp.nome, input);
                break;

            case 2:
                alterado = 1;
                printf("\nDigite o novo email:\n");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = 0;
                strcpy(temp.email, input);
                break;

            case 3:
                alterado = 1;
                printf("\nDigite a nova senha:\n");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = 0;
                strcpy(temp.senha, input);
                break;

            case 4:
                alterado = 1;
                printf("\nDigite a inicial da região (n/s/l/o): ");
                while (1) {
                    input[0] = getchar();
                    getchar();

                    if (!isalpha(input[0])) {
                        printf("Entrada inválida. Digite apenas letras.\n");
                        continue;
                    }

                    if (input[0]=='n' || input[0]=='s' || input[0]=='l' || input[0]=='o') {
                        temp.regiao = input[0];
                        break;
                    } else {
                        printf("Entrada inválida. Use apenas n/s/l/o.\n");
                    }
                }
                break;

            case 5:
                break;

            default:
                printf("\033[1;31mOpção inválida!\033[0m\n");
        }
    }

    // Se nada foi alterado
    if (!alterado) {
        printf("\n\033[1;33mNenhuma alteração foi feita no perfil.\033[0m\n");
        return;
    }

    FILE *fileIndex = fopen("clienteIndex.dat","rb");
    FILE *fileDados = fopen("cliente.dat","r+b");

    if(!fileIndex || !fileDados){
        printf("\033[1;31mErro ao abrir os arquivos!\033[0m\n");
        if(fileIndex) fclose(fileIndex);
        if(fileDados) fclose(fileDados);
        return;
    }

    Index idx;
    int sucesso = 0;

    while (fread(&idx, sizeof(Index), 1, fileIndex)) {
        if (idx.id == userLog.id) {
            fseek(fileDados, idx.pos, SEEK_SET);
            fwrite(&temp, sizeof(Dados), 1, fileDados);
            userLog = temp;

            printf("\n\033[1;32mPerfil atualizado com sucesso!\033[0m\n");

            sucesso = 1;
            break;
        }
    }

    fclose(fileIndex);
    fclose(fileDados);

    if (!sucesso) {
        printf("\033[1;31mErro: ID não encontrado para salvar.\033[0m\n");
    }
}

