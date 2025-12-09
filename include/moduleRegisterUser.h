#ifndef MODULE_REGISTER_USER
#define MODULE_REGISTER_USER


typedef struct{
  char nome[50], email[50], descricao[200], senha[20];
  long long int cpf, contato; //para caber mais digitos
  int id, idade;
  char regiao;
} usuario;

typedef struct No{
  usuario dados;
  struct No *proximo;
} NoUsuario;

void liberarMem();
void acessarProfis();
void cadastroProfis();
void profisLogin();
void addUsuario(char *senha, long long int cpf, long long int contato, int idade, char regiao, const char *nome, const char *email, const char *descricao);
void listarUsuarios();
void excluirUsuario(int id); 
void menuAdmin();
#endif

