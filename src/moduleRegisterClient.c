#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "moduleRegisterClient.h"

static Dados userLog;

void cadastroCliente(char *nome,char *email,char *senha,char regiao,int idade){
  FILE *file = fopen("cliente.txt","a");
  int novoId = idCliente();
  if(file == NULL){
    printf("Erro ao abrir arquivo para escrita!");
     return;
  }
  
  Dados data;
  strcpy(data.nome ,nome);
  strcpy(data.email,email);
  strcpy(data.senha ,senha);
  data.regiao = regiao;
  data.idade = idade;
  data.id = novoId;

  fwrite(&data,sizeof(Dados),1,file);
  fclose(file);
}

// gerador de id
int idCliente(){
  FILE *file;
  int ultimo_id = 0;

  file = fopen("idCliente.txt","r");
  if(file != NULL){
    if(fscanf(file, "%d", &ultimo_id) != 1){
      ultimo_id = 0;
    }
    fclose(file);
  }

  int proximo_id = ultimo_id + 1;

  file = fopen("idCliente.txt","r");

  if(file == NULL){
    printf("Nao foi possivel abrir o arquivo");
    return proximo_id;
  }

  fprintf(file,"%d",proximo_id);
  fclose(file);
  return proximo_id;
}

// 
int loginCliente(char *email,char *senha){
  FILE *file = fopen("cliente.txt","r");
  if(file == NULL){
    printf("Erro ao abrir arquivo para leitura!");
  }
  
  Dados data;
  int cmpEmail;
  int cmpSenha;
  
  while(fread(&data,sizeof(Dados),1,file) == 1){
    cmpEmail = strcmp(data.email,email);
    cmpSenha = strcmp(data.senha,senha);

    if(cmpEmail == 0 && cmpSenha == 0){
      printf("Usuario encontrado, segue para pagina do cliente!");
      userLog = data;
      fclose(file);
      return 1;
    }
  }  
    printf("Usuario nao encontrado ou nao cadastrado!");
    fclose(file); 
    return 0;
}

void perfilCliente(){
  printf("\n|----Dados do Perfil----|\n");
  printf("|  Nome: %s\n  ",userLog.name);
  printf("|  Email: %s\n  ",userLog.email);
  printf("|  Idade: %d\n  ",userLog.idade);
  printf("|  Regiao: %c\n  ",userLog.regiao);
  printf("|  Senha: %s\n  ",userLog.regiao);
  printf("|-----------------------|\n");
}

void atualizarDados(){

}

