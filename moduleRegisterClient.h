#ifndef MODULE_REGISTER_CLIENT_H
#define MODULE_REGISTER_CLIENT_H

typedef struct {
    char nome[20];
    char email[25];
    char senha[20];
    char regiao;
    int id;
} Dados;

void cadastroCliente();
void loginCliente();
int idCliente();
void perfilCliente();
void atualizarDados();

#endif

