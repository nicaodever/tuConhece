#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "moduleRegisterClient.h"


typedef struct{
  int id;
  long pos;
}Index;

typedef struct{
  char nome[20],email[25],senha[9],regiao;
  int id;
}Dados;

void cadastroCliente(char *nome,char *email,char *senha,char regiao);
void loginCliente(char *email,char *senha);
int idCliente();
void perfilCliente();
static Dados userLog;


void cadastroCliente(char *nome,char *email,char *senha,char regiao){
  //gera um novo id
  int novoId = idCliente();
  
  //abre o arquivo cliente
  FILE *file = fopen("cliente.txt","ab+");
    
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

  FILE *fileIndex = fopen("clienteIndex.txt","ab");
  if(fileIndex == NULL){
    printf("Erro ao abrir o arquivo de indice para escrita");
    return;
  }
  
  Index idx;
  idx.id = novoId;
  idx.pos = posicao_registro;

  fwrite(&idx,sizeof(Index),1,fileIndex);
  fclose(fileIndex);

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

  file = fopen("idCliente.txt","w");

  if(file == NULL){
    printf("Nao foi possivel abrir o arquivo");
    return proximo_id;
  }

  fprintf(file,"%d",proximo_id);
  fclose(file);
  return proximo_id;
}

// 
void loginCliente(char *email,char *senha){
  FILE *file = fopen("cliente.txt","rb");
  if(file == NULL){
    printf("Erro ao abrir arquivo para leitura!");
    return;
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
/*
void atualizarDados(){


}*/

int main(){
  char nome[] = "Emaniel ";
  char email[] = "emanie@";
  char regiao = 'r';
  char senha[] = "1234";
  char nome1[] = "jsoa ";
  char email1[] = "jsiaj2";
  char regiao1 = 's';
  char senha1[] = "1234";
  char nome2[] = "ganis ";
  char email2[] = "ganis21";
  char regiao2 = 'a';
  char senha2[] = "1234";

  printf("comecou");
  cadastroCliente(nome,email,senha,regiao);
  cadastroCliente(nome1,email1,senha1,regiao1);
  cadastroCliente(nome2,email2,senha2,regiao2);
  loginCliente(email,senha);
  perfilCliente();
  
  loginCliente(email1,senha1);
  perfilCliente();
  
  loginCliente(email2,senha2);
  perfilCliente();

  return 0;
}
