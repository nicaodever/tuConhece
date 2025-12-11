#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "moduleRegisterUser.h"

/* ----------------- CONFIGURAÇÃO DE CORES (ANSI) ----------------- */
#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define CYAN    "\033[1;36m"
#define BOLD    "\033[1m"

/* ----------------- CONSTANTES ----------------- */
#define NOME_ARQUIVO "cadProfiss.txt"
#define ADMIN_EMAIL "adm"
#define ADMIN_SENHA "adm123"
#define MAX_LINHA 1024

/* ----------------- VARIÁVEIS GLOBAIS ----------------- */
NoUsuario *inicioUs = NULL;
int proxID = 1;

/* ----------------- FUNÇÕES AUXILIARES ----------------- */
static void trim_newline(char *s) {
    if (!s) return;
    size_t n = strlen(s);
    if (n == 0) return;
    if (s[n-1] == '\n') s[n-1] = '\0';
    if (n >= 2 && s[n-2] == '\r') s[n-2] = '\0';
}

static long long str_to_ll(const char *s) {
    if (!s) return 0;
    return strtoll(s, NULL, 10);
}

/* ----------------- SALVAR PROFISSIONAIS ----------------- */
void cadastroProfis() {
    FILE *arquivo = fopen(NOME_ARQUIVO, "w");

    if (!arquivo) {
        printf(RED "Erro ao abrir o arquivo: %s\n" RESET, NOME_ARQUIVO);
        return;
    }

    NoUsuario *atual = inicioUs;
    int cont = 0;

    while (atual != NULL) {
        fprintf(arquivo, "%d;%lld;%lld;%d;%s;%s;%s;%s;%c\n",
            atual->dados.id,
            atual->dados.cpf,
            atual->dados.contato,
            atual->dados.idade,
            atual->dados.nome,
            atual->dados.email,
            atual->dados.senha,
            atual->dados.descricao,
            atual->dados.regiao
        );

        atual = atual->proximo;
        cont++;
    }

    fclose(arquivo);
    printf(GREEN "\n| %d usuarios salvos em %s |\n" RESET, cont, NOME_ARQUIVO);
}

/* ----------------- CARREGAR PROFISSIONAIS ----------------- */
void acessarProfis() {
    if (inicioUs != NULL) {
        liberarMem();
    }

    FILE *arquivo = fopen(NOME_ARQUIVO, "r");
    if (!arquivo) {
        printf(YELLOW "\nArquivo não encontrado. Será criado ao salvar.\n" RESET);
        proxID = 1;
        return;
    }

    char linha[MAX_LINHA];
    int cont = 0;
    int maiorID = 0;

    while (fgets(linha, sizeof(linha), arquivo)) {
        trim_newline(linha);
        if (strlen(linha) == 0) continue;

        char *tokens[9] = {0};
        char *p = linha;
		int i = 0;
        for (i = 0; i < 8 && p != NULL; i++) {
            char *sep = strchr(p, ';');
            if (sep) {
                *sep = '\0';
                tokens[i] = p;
                p = sep + 1;
            } else {
                tokens[i] = p;
                p = NULL;
            }
        }

        if (p) tokens[8] = p;

        usuario tempUs;
        tempUs.id = atoi(tokens[0]);
        tempUs.cpf = str_to_ll(tokens[1]);
        tempUs.contato = str_to_ll(tokens[2]);
        tempUs.idade = atoi(tokens[3]);

        strncpy(tempUs.nome, tokens[4], sizeof(tempUs.nome)-1);
        tempUs.nome[sizeof(tempUs.nome)-1] = '\0';

        strncpy(tempUs.email, tokens[5], sizeof(tempUs.email)-1);
        tempUs.email[sizeof(tempUs.email)-1] = '\0';

        strncpy(tempUs.senha, tokens[6], sizeof(tempUs.senha)-1);
        tempUs.senha[sizeof(tempUs.senha)-1] = '\0';

        strncpy(tempUs.descricao, tokens[7], sizeof(tempUs.descricao)-1);
        tempUs.descricao[sizeof(tempUs.descricao)-1] = '\0';

        tempUs.regiao = tokens[8][0];

        NoUsuario *novoNo = malloc(sizeof(NoUsuario));
        if (!novoNo) break;

        novoNo->dados = tempUs;
        novoNo->proximo = NULL;

        if (tempUs.id > maiorID) maiorID = tempUs.id;

        if (inicioUs == NULL) inicioUs = novoNo;
        else {
            NoUsuario *fim = inicioUs;
            while (fim->proximo != NULL) fim = fim->proximo;
            fim->proximo = novoNo;
        }

        cont++;
    }

    proxID = maiorID + 1;

    fclose(arquivo);
    printf(GREEN "Dados carregados: %d usuarios.\n" RESET, cont);
}

/* ----------------- ADICIONAR NOVO PROFISSIONAL ----------------- */
void addUsuario(char *senha, long long cpf, long long contato, int idade, char regiao,
                const char *nome, const char *email, const char *descricao) {

    NoUsuario *novoNo = malloc(sizeof(NoUsuario));
    if (!novoNo) {
        printf(RED "Falha na alocacao.\n" RESET);
        return;
    }

    novoNo->dados.id = proxID++;
    novoNo->dados.cpf = cpf;
    novoNo->dados.contato = contato;
    novoNo->dados.idade = idade;
    novoNo->dados.regiao = regiao;

    strncpy(novoNo->dados.nome, nome, sizeof(novoNo->dados.nome)-1);
    novoNo->dados.nome[sizeof(novoNo->dados.nome)-1] = '\0';

    strncpy(novoNo->dados.email, email, sizeof(novoNo->dados.email)-1);
    novoNo->dados.email[sizeof(novoNo->dados.email)-1] = '\0';

    strncpy(novoNo->dados.senha, senha, sizeof(novoNo->dados.senha)-1);
    novoNo->dados.senha[sizeof(novoNo->dados.senha)-1] = '\0';

    strncpy(novoNo->dados.descricao, descricao, sizeof(novoNo->dados.descricao)-1);
    novoNo->dados.descricao[sizeof(novoNo->dados.descricao)-1] = '\0';

    novoNo->proximo = NULL;

    if (inicioUs == NULL) {
        inicioUs = novoNo;
    } else {
        NoUsuario *atual = inicioUs;
        while (atual->proximo != NULL)
            atual = atual->proximo;
        atual->proximo = novoNo;
    }

    printf(GREEN "\nUsuario %s cadastrado com sucesso (ID: %d)\n" RESET, novoNo->dados.nome, novoNo->dados.id);

    cadastroProfis();
}

/* ----------------- EXCLUIR PROFISSIONAL ----------------- */
void excluirUsuario(int id) {
    NoUsuario *atual = inicioUs;
    NoUsuario *anterior = NULL;

    while (atual != NULL && atual->dados.id != id) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("\nErro: Usuario nao encontrado.\n");
        return;
    }

    if (anterior == NULL) {
        inicioUs = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

   centralizar(RED "\nUsuario '%s' (ID: %d) excluido.\n" RESET, atual->dados.nome, id);
    free(atual);
    cadastroProfis();
}

/* ----------------- LISTAR PROFISSIONAIS ----------------- */
void listarUsuarios() {
    NoUsuario *atual = inicioUs;

    if (!atual) {
        printf(YELLOW "\nNenhum usuario cadastrado.\n" RESET);
        return;
    }

    printf(CYAN BOLD "\n========== LISTA DE PROFISSIONAIS ==========\n" RESET);

    while (atual != NULL) {
        printf(BLUE "\n[ID] " RESET "%d\n", atual->dados.id);
        printf(BOLD "Nome: " RESET "%s\n", atual->dados.nome);
        printf(BOLD "Região: " RESET "%c\n", atual->dados.regiao);
        printf(BOLD "Especialidade: " RESET "%s\n", atual->dados.descricao);
        printf(BOLD "Contato: " RESET "%lld\n", atual->dados.contato);
        printf("-------------------------------------------\n");
        atual = atual->proximo;
    }
}
/* ----------------- FILTRAR POR REGIÃO ----------------- */
void buscarPorRegiao(char regiaoBuscada){
	NoUsuario *atual = inicioUs;
	int encontrou = 0;
	
	system("cls || clear");
	  
	  
	char regiao[20];
	
	regiaoBuscada = tolower(regiaoBuscada);

	switch (regiaoBuscada) {
	    case 'n':
	        strcpy(regiao, "NORTE");
	        break;
	
	    case 's':
	        strcpy(regiao, "SUL");
	        break;
	
	    case 'l':
	        strcpy(regiao, "LESTE");
	        break;
	
	    case 'o':
	        strcpy(regiao, "OESTE");
	        break;
	
	    default:
	        strcpy(regiao, "Região desconhecida");
	        break;
	}
	
	printf("\n---PROFISSIONAIS DA REGIAO %s ---\n", regiao);
	
	while(atual != NULL){
		if(atual->dados.regiao == regiaoBuscada){
			printf("ID: %d | Nome: %s | Contato: %d | Email: %s\n", 
			atual->dados.id,
			atual->dados.nome,
			atual->dados.contato,
			atual->dados.email);
		
		encontrou = 1;
		}
		
		atual = atual->proximo;
	}
	
	if(!encontrou){
		printf("Nenhum profissional encontrado nessa regiao. \n");
	}
	
	printf("-------------------------------------------\n");
}
/* ----------------- LIBERAR MEMÓRIA ----------------- */
void liberarMem() {
    NoUsuario *atual = inicioUs;
    NoUsuario *prox;

    while (atual != NULL) {
        prox = atual->proximo;
        free(atual);
        atual = prox;
    }

    inicioUs = NULL;
}

/* ----------------- MENU ADMIN ----------------- */
void menuAdmin() {
	char regiao;
    int opcaoAdm = -1;
    
  system("cls || clear");
    do {
        printf(CYAN BOLD "\n========== PAINEL DO ADMINISTRADOR ==========\n" RESET);
        printf(YELLOW "1." RESET " Listar todos os usuários\n");
        printf(YELLOW "2." RESET " Excluir um usuário (ID)\n");
        printf(YELLOW "3." RESET " Filtrar por Região\n");
        printf(YELLOW "0." RESET " Sair do painel\n");

        printf("\nEscolha: ");
        if (scanf("%d", &opcaoAdm) != 1) {
            while (getchar() != '\n');
            opcaoAdm = -1;
            printf(RED "Entrada inválida!\n" RESET);
            continue;
        }
        while (getchar() != '\n');

        if (opcaoAdm == 1) listarUsuarios();

        else if (opcaoAdm == 2) {
            int id;
            listarUsuarios();
            printf("\nID a excluir: ");
            scanf("%d", &id);
            while (getchar() != '\n');

            excluirUsuario(id);
        }
        else if(opcaoAdm == 3){
        	    
             	printf("Escolha uma região(n/s/l/o): ");
    			scanf("%c", &regiao);
			    buscarPorRegiao(regiao);  

		}
        
		printf(YELLOW "\nPressione ENTER para continuar..." RESET);
        getchar();

    } while (opcaoAdm != 0);
}

/* ----------------- MENU PROFISSIONAL ----------------- */
void menuProfissional() {
    int op;
    char regiao;
    do {
        printf(CYAN BOLD "\n========== ÁREA DO PROFISSIONAL ==========\n" RESET);
        printf(YELLOW "1." RESET " Cadastrar Profissional\n");
        printf(YELLOW "2." RESET " Listar Profissionais\n");
        printf(YELLOW "3." RESET " Filtrar por Região\n");
        printf(YELLOW "0." RESET " Sair\n");

        printf("\nEscolha: ");
        if (scanf("%d", &op) != 1) {
            while (getchar() != '\n');
            op = -1;
            continue;
        }
        while (getchar() != '\n');
  switch(op) {

            case 1: {
                char nome[50], email[50], senha[20], descricao[100];
                long long cpf, contato;
                int idade;
                char regiao;

                printf("\nNome: ");
                fgets(nome, sizeof(nome), stdin); trim_newline(nome);

                printf("Email: ");
                fgets(email, sizeof(email), stdin); trim_newline(email);

                printf("Senha: ");
                fgets(senha, sizeof(senha), stdin); trim_newline(senha);

                printf("CPF: ");
                scanf("%lld", &cpf); while(getchar()!='\n');

                printf("Contato: ");
                scanf("%lld", &contato); while(getchar()!='\n');

                printf("Idade: ");
                scanf("%d", &idade); while(getchar()!='\n');

                printf("Região (A-Z): ");
                scanf("%c", &regiao); while(getchar()!='\n');

                printf("Descricao: ");
                fgets(descricao, sizeof(descricao), stdin); trim_newline(descricao);
                
        addUsuario(senha, cpf, contato, idade, regiao, nome, email, descricao);
                break;
            }

            case 2:
                listarUsuarios();
                break;
                
             case 3:
             	printf("Escolha uma região(n/s/l/o): ");
    			scanf("%c", &regiao);
			    buscarPorRegiao(regiao);  

            case 0:
                printf(RED "\nVoltando...\n" RESET);
                break;

            default:
                printf(RED "Opção inválida!\n" RESET);
        }

        printf(YELLOW "\nPressione ENTER para continuar..." RESET);
        getchar();

    } while(op != 0);
}



/* ----------------- LOGIN ----------------- */
void profisLogin() {
    char emailLogin[50];
    char senhaLogin[20];
    int encontrado = 0;

    centralizar(CYAN BOLD "========== LOGIN ==========\n" RESET);
    
	boxCursorLeft();
    printf("Email: ");
    fgets(emailLogin, sizeof(emailLogin), stdin);
    trim_newline(emailLogin);
	boxCursorLeft();
    printf("Senha: ");
    fgets(senhaLogin, sizeof(senhaLogin), stdin);
    trim_newline(senhaLogin);

    if (strcmp(emailLogin, ADMIN_EMAIL) == 0 &&
        strcmp(senhaLogin, ADMIN_SENHA) == 0) {

        centralizar(GREEN "\nBem-vindo, ADMIN!\n" RESET);
        menuAdmin();
        return;
    }
    NoUsuario *atual = inicioUs;
    while (atual != NULL) {
        if (strcmp(atual->dados.email, emailLogin) == 0) {
            encontrado = 1;

            if (strcmp(atual->dados.senha, senhaLogin) == 0) {
                centralizar(GREEN "\nLogin realizado com sucesso!\nBem vindo(a), %s\n" RESET, atual->dados.nome);

                menuProfissional();  // CHAMA O MENU PROFISSIONAL

            } else {
                printf(RED "\nSenha incorreta!\n" RESET);
            }
            break;
        }
        atual = atual->proximo;
    }

    if (!encontrado) {
        centralizar(YELLOW "\nUsuário não encontrado!\n" RESET);
    }
}
