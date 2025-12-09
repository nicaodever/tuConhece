#ifndef MODULE_REGISTER_CLIENT_H
#define MODULE_REGISTER_CLIENT_H

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
void atualizarDados();

#endif
