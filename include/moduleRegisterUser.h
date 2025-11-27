#ifndef MODULE_REGISTER_USER
#define MODULE_REGISTER_USER

typedef struct{
  char nome[50],email[50],descricao[200];
  int id,cpf,contato,idade;
  char regiao;
}usuario;

typedef struct No{
  usuario dados;
  struct No *proximo;
}NoUsuario;


void liberarMem();
void acessarUsuarios();
void salvar_cadastros();
void adicionarUsuario(int cpf,int contato,int idade,char regiao,const char *nome,const char *email,const char *descricao);
void listarUsuarios();
void buscarPorRegiao(char regiaoBuscada);
#endif

