//SISTEMA DE CADASTRO
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "moduleRegisterUser.h"
#define NOME_ARQUIVO "cadastro_profissional.txt"


//Variáveis globais
NoUsuario *inicioUs=NULL; //Ponteiro para o bloco de cada usuário
int proxID=1; //Para controlar o cadastro de cada usuario



void salvar_cadastros(){  //procedimento salvar os cadastros no arquivo
    FILE *arquivo = fopen(NOME_ARQUIVO, "w");
    if(arquivo==NULL){
        printf("Erro ao abrir o arquivo para escrita");
        return;
    }

    NoUsuario *atual = inicioUs; //Faz com que a variavel global não perca a referencia do inicio 
    int cont = 0;

    while(atual != NULL){   //repetição para acessar os elementos da lista encadeada
        fprintf(arquivo, "%d;%d;%d;%d;%s;%s;%s;%c\n", atual->dados.id, atual->dados.cpf, atual->dados.contato, atual->dados.idade, atual->dados.nome, atual->dados.email, atual->dados.descricao, atual->dados.regiao);
        atual=atual->proximo;   //avança na lista encadeada para o próximo usuário
        cont++;
    }

    fclose(arquivo);
    printf("\n%d usuarios salvos no arquivo.\n", cont);
}

void acessarUsuarios(){
    //chamando o procedimento para liberar memória antes de carregar o arquivo
    if(inicioUs!=NULL){
        liberarMem();//chamando a função para abrir espaço na memória
    }

    FILE *arquivo = fopen(NOME_ARQUIVO, "r"); //Leitura do arquivo

    if(arquivo==NULL){
        printf("\nArquivo nao econtrado.\n");
        return;
    }

    usuario tempUs; //variavel temporaria
    int cont=0;

    while(fscanf(arquivo, "%d;%d;%d;%d;%c;%50[^;];%50[^;];%200[^\n]\n", &tempUs.id, &tempUs.cpf, &tempUs.contato, &tempUs.idade, tempUs.nome, tempUs.email, tempUs.descricao, tempUs.regiao)==8){
        //Aloca um novo Nó usando MALLOC
        NoUsuario *novoNo = (NoUsuario *)malloc(sizeof(NoUsuario));
        if(novoNo==NULL){
            printf("Falha na alocacao de memoria");
            break;
        }

        novoNo->dados=tempUs; //copia os dados
        novoNo->proximo=NULL;

        //Atuliza o novo usuário (id)
        if(tempUs.id>=proxID){
            proxID=tempUs.id + 1;
        }

        //Insere na lista (no final)
        if(inicioUs==NULL){
            inicioUs=novoNo;
        }else{
            NoUsuario *atual=inicioUs;
            while(atual->proximo!=NULL){
                atual=atual->proximo;
            }
            atual->proximo=novoNo;
        }
        cont++;
    }
    fclose(arquivo);
    printf("Dados de usuarios carregados (%d usuarios). Proximo ID a ser usado: %d.\n", cont, proxID);
}

void adicionarUsuario(int cpf, int contato, int idade, char regiao, const char *nome, const char *email, const char *descricao){
    //Alocação de memória dinâmica (MALLOC)
    NoUsuario *novoNo = (NoUsuario *)malloc(sizeof(NoUsuario));

    if(novoNo==NULL){
        printf("Falha na alocacao para o novo usuario.\n");
        return;
    }

    //Preenchimento dos Dados
    novoNo->dados.id=proxID++;
    novoNo->dados.cpf=cpf;
    novoNo->dados.contato=contato;
    novoNo->dados.idade=idade;
    novoNo->dados.regiao=regiao;

    strncpy(novoNo->dados.nome, nome, 50);
    novoNo->dados.nome[50]='\0';
    strncpy(novoNo->dados.email, email, 50);
    novoNo->dados.email[50]='\0';
    strncpy(novoNo->dados.descricao, descricao, 200);
    novoNo->dados.descricao[200]='\0';
    novoNo->dados.regiao=regiao;

    novoNo->proximo=NULL;//garantindo que o último da fila seja NULL

    //Inserção na lista (no final)
    if(inicioUs==NULL){
        inicioUs=novoNo;
    }else{
        NoUsuario *atual = inicioUs;
        while(atual->proximo!=NULL){
            atual=atual->proximo;
        }
        atual->proximo=novoNo;
    }
    printf("\nUsuario %s cadastrado com sucesso", novoNo->dados.nome);
}

void listarUsuarios(){
    NoUsuario *atual = inicioUs;

    if(atual==NULL){
        printf("\nNenhum usuario cadastrado.\n");
        return;
    }

    printf("\n--- LISTA DE USUARIOS ---\n");
    while(atual!=NULL){
        printf("ID: %d | Nome: %s | email: %s| Contato: %d\n", atual->dados.id, atual->dados.nome, atual->dados.email, atual->dados.contato);
        atual=atual->proximo;
    }
    printf("------------------------\n");
}

void buscarPorRegiao(char regiaoBuscada){
	NoUsuario *atual = inicioUs;
	int encontrou = 0;
	
	printf("\n---PROFISSIONAIS DA REGIAO %c ---\n", regiaoBuscada);
	
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

void liberarMem(){
    NoUsuario *atual = inicioUs;
    NoUsuario *proximo;

    while(atual!=NULL){
        proximo=atual->proximo;
        free(atual);    //Libera memoria alocada pelo Malloc
        atual=proximo;
    }
    inicioUs=NULL;
    printf("\nMemoria de todos os usuarios liberada com sucesso.\n");
}
