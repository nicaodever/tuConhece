#ifndef MODULE_REGISTER_USER_H
#define MODULE_REGISTER_USER_H

#include <stddef.h>


typedef struct{
  char nome[50];
  char email[50];
  char descricao[200];
  char senha[20];
  

  long long int cpf, contato; //para caber mais digitos
  
  
  int id, idade;
  char regiao;
} usuario;

typedef struct No{
  usuario dados;
  struct No *proximo;
} NoUsuario;

extern NoUsuario *inicioUs;
extern int proxID;

void liberarMem();
void acessarProfis();
void cadastroProfis();
void profisLogin();
void addUsuario(const char *senha, long long int cpf, long long int contato, int idade, char regiao, const char *nome, const char *email, const char *descricao);
void listarUsuarios();
void excluirUsuario(int id); 
void menuAdmin();
#endif

