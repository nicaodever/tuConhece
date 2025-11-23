#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
  char nome[20], email[25],senha[9],regiao;
  int idade,id; 
}Dados;


void cadastroCliente(char *nome,char *email,char *senha,char regiao,int idade){
  FILE *file = fopen("cliente.txt","w");
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
  //data.id = id;

  fwrite(&data,sizeof(Dados),1,file);
  fclose(file);
}


int loginCliente(char *email,char *senha){
  FILE *file = fopen("cliente.txt","r");
  if(file == NULL){
    printf("Erro ao abrir arquivo para leitura!");
      
  }
  
  Dados data;
  strcpy(data.email , email);
  strcpy(data.senha, senha);
  
  
  while(fread(&data,sizeof(Dados),1,file) == 1){
    int cmpEmail = strcmp(data.email,email);
    int cmpSenha = strcmp(data.senha,senha);

    if(cmpEmail == 0 && cmpSenha == 0){
      printf("Usuario encontrado, segue para pagina do cliente!");
      return 1;
      break;
    }else{
      printf("Usuario nao encontrado ou nao cadastrado!");
      return 0;
      break;
    }  

    
    fclose(file); 
  }
}


