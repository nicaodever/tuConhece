#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define NOME_ARQUIVO "cadProfiss.txt"
#define ADMIN_EMAIL "adm"//login do administrador
#define ADMIN_SENHA "adm123"//senha do adm

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

//Variáveis globais
NoUsuario *inicioUs = NULL;
int proxID = 1;

//procedimento para cadastrar o profissional
void cadastroProfis(){  
    FILE *arquivo = fopen(NOME_ARQUIVO, "w");
    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo para escrita");
        return;
    }

    NoUsuario *atual = inicioUs;
    int cont = 0;

    while(atual != NULL){
        fprintf(arquivo, "%d;%lld;%lld;%d;%s;%s;%s;%s;%c\n", atual->dados.id, atual->dados.cpf, atual->dados.contato, atual->dados.idade, atual->dados.nome, atual->dados.email, atual->dados.senha, atual->dados.descricao, atual->dados.regiao);
        atual = atual->proximo;
        cont++;
    }

    fclose(arquivo);
    printf("\n| %d usuarios salvos |\n", cont);
}

//procedimento para acessar as informações dos usuário no arquivo (carregamento dos dados)
void acessarProfis(){
    if(inicioUs != NULL){
        liberarMem();//chamando procedimento para liberar memória
    }

    FILE *arquivo = fopen(NOME_ARQUIVO, "r");
    if(arquivo == NULL){
        printf("\nArquivo de cadastro nao encontrado (sera criado ao salvar).\n");
        return;
    }

    usuario tempUs;
    int cont = 0;
    int maiorID = 0; // Para ajustar o proxID corretamente

//lê o arquivo seguindo o padrão definindo por (;) e verificando se foi lido a qtd certa (9) de informações
    while(fscanf(arquivo, "%d;%lld;%lld;%d;%50[^;];%50[^;];%20[^;];%200[^;];%c\n", &tempUs.id, &tempUs.cpf, &tempUs.contato, &tempUs.idade, tempUs.nome, tempUs.email, tempUs.senha, tempUs.descricao, &tempUs.regiao) == 9){
        
        NoUsuario *novoNo = (NoUsuario *)malloc(sizeof(NoUsuario));//solicitando memória do sistema para criar um novo Nó
        if(novoNo == NULL) //caso não haja memória e o procedimento não trave o sistema
            break;

        novoNo->dados = tempUs;//transfere as informações da variavel tempUs para dentro do novo Nó
        novoNo->proximo = NULL;

        if(tempUs.id > maiorID){//Organiza os usuário para não repetir o id
            maiorID = tempUs.id;
        }

        if(inicioUs == NULL){//verifica se há algum profissional cadastrado
            inicioUs = novoNo;
        }else{
            NoUsuario *atual = inicioUs;//ponteiro auxiliar (atual) para organizar os nós
            while(atual->proximo != NULL){//loop que faz o ponteiro ir até o último da fila
                atual = atual->proximo;
            }
            atual->proximo = novoNo;//nó alocado no último da fila
        }
        cont++;
    }
    proxID = maiorID + 1; //incrementa o id para o próximo cadastro não repetir
    fclose(arquivo);
    printf("Dados carregados: %d usuarios.\n", cont);
}

void addUsuario(char *senha, long long int cpf, long long int contato, int idade, char regiao, const char *nome, const char *email, const char *descricao){
    NoUsuario *novoNo = (NoUsuario *)malloc(sizeof(NoUsuario));//converte o ponteiro recebido pelo malloc para do tipo NoUsuario

    if(novoNo == NULL){
        printf("Falha na alocacao.\n");
        return;
    }
    //alocando as informações no Nó
    novoNo->dados.id = proxID++;
    novoNo->dados.cpf = cpf;
    novoNo->dados.contato = contato;
    novoNo->dados.idade = idade;
    novoNo->dados.regiao = regiao;

    strncpy(novoNo->dados.nome, nome, 50); 
    novoNo->dados.nome[49] = '\0';
    strncpy(novoNo->dados.email, email, 50); 
    novoNo->dados.email[49] = '\0';
    strncpy(novoNo->dados.senha, senha, 20); 
    novoNo->dados.senha[19] = '\0';
    strncpy(novoNo->dados.descricao, descricao, 200); 
    novoNo->dados.descricao[199] = '\0';

    novoNo->proximo = NULL;//garante que o próximo nó seja NULL

    if(inicioUs == NULL){
        inicioUs = novoNo;
    }else{
        NoUsuario *atual = inicioUs;
        while(atual->proximo != NULL){//loop para caminhar nos pelos nós até chegar no último (NULL)
            atual = atual->proximo;
        }
        atual->proximo = novoNo;//alocando o novo Nó no fim da fila
    }
    printf("\nUsuario %s cadastrado com sucesso (ID: %d)\n", novoNo->dados.nome, novoNo->dados.id);
    cadastroProfis(); // Salva automaticamente após cadastrar
}

//Procedimento apenas para o adm para excluir usuario
void excluirUsuario(int id){
    NoUsuario *atual = inicioUs;
    NoUsuario *anterior = NULL;

    //Procura o usuário na lista
    while(atual != NULL && atual->dados.id != id){
        anterior = atual;
        atual = atual->proximo;
    }
    
    if(atual == NULL){// Se chegou no fim e não achou
        printf("\nErro: Usuario nao encontrado.\n");
        return;
    }

    //Se achou, verifica se é o primeiro da lista ou um do meio/fim
    if(anterior == NULL){
        inicioUs = atual->proximo;//Era o primeiro da lista
    } else {
        anterior->proximo = atual->proximo;//Era um nó do meio ou fim
    }

    printf("\nSUCESSO: Usuario '%s' (ID: %d) foi excluido.\n", atual->dados.nome, id);
    free(atual); //Libera a memória
    
    cadastroProfis(); //Atualiza o arquivo 
}

void listarUsuarios(){
    NoUsuario *atual = inicioUs;

    if(atual == NULL){
        printf("\nNenhum usuario cadastrado.\n");
        return;
    }

    printf("\n---| LISTA DE PROFISSIONAIS |---\n");
    while(atual != NULL){
        printf("ID: %d | Nome: %s | Regiao: %c | Especialidade: %s | Contato: %lld\n", atual->dados.id, atual->dados.nome, atual->dados.regiao, atual->dados.descricao, atual->dados.contato);
        atual = atual->proximo;
    }
    printf("------------------------------\n");
}

void liberarMem(){
    NoUsuario *atual = inicioUs;
    NoUsuario *proximo;

    while(atual != NULL){
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    inicioUs = NULL;
}

//Perfil do administrador
void menuAdmin(){
    int opcaoAdm, idExcluir;

    do {
        printf("\n===| PAINEL DO ADMINISTRADOR |===\n");
        printf("1. Listar todos os usuarios\n");
        printf("2. Excluir um usuario (pelo ID)\n");
        printf("0. Sair do Painel Admin\n");
        printf("Escolha: ");
        scanf("%d", &opcaoAdm);
        while(getchar() != '\n');//limpa o buffer depois do scanf

        switch(opcaoAdm){
            case 1:
                listarUsuarios();
                break;
            case 2:
                listarUsuarios(); //para ver o ID e selecionar qual será excluído
                printf("\nInforme o ID do usuario que deseja EXCLUIR: ");
                scanf("%d", &idExcluir);
                while(getchar() != '\n');
                // Confirmação simples
                printf("Tem certeza? (1-Sim / 0-Nao): ");
                int confirm;
                scanf("%d", &confirm);
                while(getchar() != '\n');

                if(confirm == 1) {
                    excluirUsuario(idExcluir);
                } else {
                    printf("Operacao cancelada.\n");
                }
                break;
            case 0:
                printf("Saindo do perfil adm\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while(opcaoAdm != 0);
}

void profisLogin(){
    char emailLogin[50], senhaLogin[20];
    int encontrado = 0;

    //getchar(); //Limpa buffer se necessário}
    printf("\n---| LOGIN |---\nEmail: ");
    fgets(emailLogin, sizeof(emailLogin), stdin);
    emailLogin[strcspn(emailLogin, "\n")] = '\0';

    printf("Senha: ");
    fgets(senhaLogin, sizeof(senhaLogin), stdin);
    senhaLogin[strcspn(senhaLogin, "\n")] = '\0';

    //Verifica se é adm
    if(strcmp(emailLogin, ADMIN_EMAIL) == 0 && strcmp(senhaLogin, ADMIN_SENHA) == 0){
        printf("\n\n>>>| BEM-VINDO ADMINISTRADOR |<<<\n");
        menuAdmin(); //Chama o menu exclusivo
        return;
    }

    //Se não for adm, verifica usuários normais
    NoUsuario *atual = inicioUs;
    while(atual != NULL){
        if(strcmp(atual->dados.email, emailLogin) == 0){
            encontrado=1;
            if(strcmp(atual->dados.senha, senhaLogin) == 0){
                printf("\n\t| Login realizado com sucesso |\n\tBem vindo(a), %s\n", atual->dados.nome);
            }else{
                printf("\n\t| Senha incorreta. Tente novamente |\n");
            }
            break;
        }
        atual = atual->proximo;
    }
    if(!encontrado){
        printf("\n>>>| Usuario nao cadastrado |<<<\n");
    }
}

int main(){
    int opcao, idade;
    long long int contato, cpf;
    char nome[50], email[50], descricao[200], senha[20], regiao;

    acessarProfis(); //Carrega dados ao iniciar

    do{
        printf("\n--- MENU PRINCIPAL ---\n");
        printf("1. Cadastrar novo usuario\n");
        printf("2. Listar usuarios (Publico)\n");
        printf("3. Realizar Login (Admin ou Usuario)\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");

        if(scanf("%d", &opcao) != 1){
            opcao = -1;
        }
        while(getchar() != '\n'); 

        switch(opcao){
            case 1:
                printf("Digite seu nome: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';

                printf("Informe um email: ");
                fgets(email, sizeof(email), stdin);
                email[strcspn(email, "\n")] = '\0';

                printf("Defina uma senha: ");
                fgets(senha, sizeof(senha), stdin);
                senha[strcspn(senha, "\n")] = '\0';

                printf("Habilidades (descricao): ");
                fgets(descricao, sizeof(descricao), stdin);
                descricao[strcspn(descricao, "\n")] = '\0';

                printf("Qual sua idade? ");
                scanf("%d", &idade);
                
                printf("Informe seu CPF: ");
                scanf("%d", &cpf);

                printf("Informe seu numero de contato: ");
                scanf("%d", &contato);
                
                printf("Informe sua zona (Norte (n), Sul(s), Leste(l), Oeste(o)): ");
                scanf(" %c", &regiao);

                while(getchar() != '\n');//para evitar levar lixo para o menu

                addUsuario(senha, cpf, contato, idade, regiao, nome, email, descricao);
                break;

            case 2:
                listarUsuarios();
                break;

            case 3:
                profisLogin();
                break;

            case 0:
                cadastroProfis(); //salva antes de sair
                liberarMem();
                printf("Programa encerrado.\n");
                break;

            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while(opcao != 0);

    return 0;
}