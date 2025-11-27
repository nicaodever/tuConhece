#ifndef MODULE_REGISTER_CLIENT_H
#define MODULE_REGISTER_CLIENT_H

typedef struct{
  char nome[20],email[25],senha[9],regiao;
  int idade,id;
}Dados;

void cadastroCliente(char *nome,char *email,char *senha,char regiao,int idade);

int loginCliente(char *email,char *senha);


#endif
