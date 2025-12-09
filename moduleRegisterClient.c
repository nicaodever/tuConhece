#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "moduleRegisterClient.h"

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
  //pega a ultima posiçao no arquivo
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
  FILE *file = fopen("cliente.dat","rb");
  if(file == NULL){
    printf("Erro ao abrir arquivo para leitura!");
    return;
  }
  
  Dados data;
  int cmpEmail;
  int cmpSenha;
  //pecorre o arquivo e compara se o login esta correto
  while(fread(&data,sizeof(Dados),1,file) == 1){
    cmpEmail = strcmp(data.email,email);
    cmpSenha = strcmp(data.senha,senha);

    if(cmpEmail == 0 && cmpSenha == 0){
      printf("Usuario encontrado, segue para pagina do cliente!");
      userLog = data;
      fclose(file);
      return;
      
    }
  }  
    printf("Usuario nao encontrado ou nao cadastrado!");
    fclose(file); 
    
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
void atualizarDados(){
  // cria uma struct temporaria
  Dados temp = userLog;
  char input[100];
  int escolha = 0;
  int alterado = 0; //flag

  printf("\n|----Atualizar dados do Perfil ID: %d----\n",userLog.id);

  //menu
  while(escolha != 5){
    printf("/n0 que deseja alterar?\n");
    printf("1. Nome: %s\n",temp.nome);
    printf("2. Email: %s\n",temp.email);
    printf("3. Senha: %s\n",temp.senha);
    printf("4. Regiao: %c\n",temp.regiao);
    printf("5. Salvar e Sair\n");
    printf("Escolha: ");

    //le a escolha do usuario
    if(scanf("%d",&escolha) != 1){
      //limpa o buffer
      while(getchar() != '\n');
      escolha = 0;
      continue;
    }
    while(getchar() != '\n'); // limpa o buffer depois do scanf
    

    if(escolha >= 1 && escolha <= 4){

      if(strlen(input) > 0){
        alterado = 1;
        switch(escolha){
          case 1: 
            
            printf("\nDigite o novo nome:\n");
            while(1){
              int flag = 1;
              fgets(input,sizeof(input),stdin);
              input[strcspn(input,"\n")] = 0;
              int i;
              for(i = 0;i < strlen(input);i++){
                if(!isalpha(input[i])){
                printf("\nO nome deve conter apenas letras.\n");
                flag = 0;
                break;
                }
              }
              if(flag == 1){
                break;
              }
            }
            strcpy(temp.nome,input);
            break;
          case 2: 
            printf("\nDigite o novo email:\n");
            fgets(input,sizeof(input),stdin);
            input[strcspn(input,"\n")] = 0;
            strcpy(temp.email,input); 
            break;
          case 3: 
            printf("\nDigite a nova senha:\n");
            fgets(input,sizeof(input),stdin);
            input[strcspn(input,"\n")] = 0;
            strcpy(temp.senha,input); 
            break;
          case 4: 
            temp.regiao = input[0]; 
            printf("\nDigite apenas a inicial da regiao: Norte(n) Sul(s) Leste(l) Oeste(o)\n");
            while(1){
              input[0] = getchar();
              getchar();
              if(!isalpha(input[0])){//verifica se a entrada e uma letra
                printf("Entrada invalida. Digite apenas letras.\n");
                continue;
              }
              if(input[0] == 'n'|| input[0] == 's'|| input[0] == 'l'|| input[0] == 'o'){
                temp.regiao = input[0];
                break;
              }else{
                printf("Entrada invalida. Digite apenas as opcoes dadas.\n");
              }

            }
          temp.regiao = input[0];
          break;
        }
      }else{
        printf("Nenhuma alteracao feita neste campo.\n");
      }
    }else if(escolha == 5){
      break;
    }else{
      printf("Opçao invalida.\n");
    }
  }

  //usuario saiu, mas nao houve alteracao, apenas retorna
  if(!alterado){
    printf("\nNenhuma alteracao foi feita no perfil.\n");
    return;
  }

  FILE *fileIndex = fopen("clienteIndex.dat","rb");
  FILE *fileDados = fopen("cliente.dat","r+b");

  if(fileIndex == NULL || fileDados == NULL){
    printf("Erro ao abrir arquivos para gravacao");
    if(fileIndex) fclose(fileIndex);
    if(fileDados) fclose(fileDados);
    return;
  }

  Index idx;
  int sucesso = 0;

  while(fread(&idx ,sizeof(Index), 1, fileIndex)){
    if(idx.id == userLog.id){
      fseek(fileDados,idx.pos,SEEK_SET);

      fwrite(&temp,sizeof(Dados),1, fileDados);

      userLog = temp;

      printf("Perfil atualizado com sucesso!\n");
      sucesso = 1;
      break;
    }
  }
  fclose(fileIndex);
  fclose(fileDados);

  if(!sucesso){
    printf("\nErro: Nao foi possivel encontrar o ID para salvar.\n");
  }

}

