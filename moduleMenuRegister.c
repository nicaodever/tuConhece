/* Código com centralizar removido e substituído por printf */

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>

/* Funções auxiliares (esses permanecem iguais ao que você enviou) */
void lerCPF(char *out) {
    char buf[16];
    int pos = 0;
    int digits = 0;
    char c;

    while (digits < 11) {
        c = getch();

        if (c == 13) 
            continue;

        if (c == 3) 
            exit(0);

        if (c == 8) {
            if (pos > 0) {
                if (buf[pos - 1] == '.' || buf[pos - 1] == '-') {
                    pos--;
                    printf("\b \b");
                }
                if (pos > 0) {
                    pos--;
                    digits--;
                    printf("\b \b");
                }
            }
            continue;
        }

        if (isdigit((unsigned char)c)) {
            if (digits == 3) {
                buf[pos++] = '.';
                putchar('.');
            } else if (digits == 6) {
                buf[pos++] = '.';
                putchar('.');
            } else if (digits == 9) {
                buf[pos++] = '-';
                putchar('-');
            }

            buf[pos++] = c;
            putchar(c);
            digits++;
        }
    }

    buf[pos] = '\0';
    strncpy(out, buf, 16);
    out[15] = '\0';
}
void abrirBox(const char *titulo, int altura) { /* ... código original ... */ }
void boxCursorLeft() { /* ... código original ... */ }

/* ========================= */
/*     MENU REGISTER LIMPO   */
/* ========================= */

void menuRegister(){
    char cpfStr[20], telefoneStr[20];
    int opcao, idade, tipocadastro;
    long long int contato, cpf;
    char nome[70], email[80], descricao[200], senha[20], regiao;

    system("cls || clear");

    printf("\033[1;32m+=============================================+\n\033[0m");
    printf("\033[1;32m|               TELA DE CADASTRO              |\n\033[0m");
    printf("\033[1;32m+=============================================+\n\n\033[0m");

    printf("\033[36m[1]\033[0m Cadastrar Profissional\n");
    printf("\033[36m[2]\033[0m Cadastrar Usuário Comum\n");
    printf("\033[36m[0]\033[0m Voltar\n\n");

    printf("Escolha uma opção: ");
    scanf("%d", &tipocadastro);
    while (getchar() != '\n');

    if (tipocadastro == 0) return;

    /* ----------------------------------------------------------- */
    /*                   FORMULÁRIO DE CADASTRO                    */
    /* ----------------------------------------------------------- */

    system("cls || clear");

    abrirBox("FORMULÁRIO DE CADASTRO", 14);

    boxCursorLeft();
    printf("Digite seu nome: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    boxCursorLeft();
    printf("Informe um email: ");
    fgets(email, sizeof(email), stdin);
    email[strcspn(email, "\n")] = '\0';

    boxCursorLeft();
    printf("Defina uma senha: ");
    fgets(senha, sizeof(senha), stdin);
    senha[strcspn(senha, "\n")] = '\0';

    boxCursorLeft();
    printf("Qual sua idade? ");
    scanf("%d", &idade);

    boxCursorLeft();
    printf("Informe seu CPF: ");
    lerCPF(cpfStr);

    boxCursorLeft();
    printf("Informe seu contato: ");
    scanf("%lld", &contato);

    boxCursorLeft();
    printf("\033[36mInforme sua zona (n/s/l/o):\033[0m ");
    scanf(" %c", &regiao);
    while(getchar() != '\n');

    /* ----------------------------------------------------------- */
    /*                   PROFISSIONAL                              */
    /* ----------------------------------------------------------- */

    if (tipocadastro == 1) {
        boxCursorLeft();
        printf("\033[36mHabilidades (descrição):\033[0m ");
        fgets(descricao, sizeof(descricao), stdin);
        descricao[strcspn(descricao, "\n")] = '\0';

        addUsuario(senha, cpf, contato, idade, regiao, nome, email, descricao);

        printf("\n\033[1;32mProfissional cadastrado com sucesso!\033[0m\n");
    }
    else if (tipocadastro == 2) {
        cadastroCliente(nome, email, senha, regiao);
        printf("\n\033[1;32mUsuário comum cadastrado com sucesso!\033[0m\n");
    }
    else {
        printf("\033[1;31mOpção inválida!\033[0m\n");
    }

    system("pause");
}

