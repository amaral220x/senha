#include<stdio.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>

typedef struct _RODADAS{
    char tentativa[4];
    int resposta[3];
}RODADAS_ANTERIORES;

/*--- Funções ---*/
int validar_tentativa(char c[6]);
void gerar_senha(int * senha);
void limpar(void);
void comparar(char * tentativa, int * senha, int *resposta);
void tabuleiro(int *resposta, RODADAS_ANTERIORES * rodadas_anteriores, int rodadas, int * senha);
void exibir_senha(int n, int *senha);
void imprimir_inicio(void);
void limpaTela(void);


int main(void){
    char tentativa[5];
    int senha[4] = {1,2,3,4}, resposta[3], rodadas=0;
    int i = 0;
    RODADAS_ANTERIORES rodadas_anteriores[10];
    limpaTela();
    gerar_senha(senha);
    imprimir_inicio();

    while(1){
        rodadas++;
        if(rodadas == 11){
            tabuleiro(resposta, rodadas_anteriores, rodadas, senha);
            puts("\n\t\t\tVoce perdeu!\n");
            return 0;
        }
        printf("\tDigite a sua %da tentativa.\n", rodadas);
        printf("\t");

        /*Loop para verificar a entrada*/
        while(1) {
            /* Cada tentativa de senha vai ser um loop de getchar() */
            int j = 0;
            while(1) {
            int c = getchar();
            /* Se chegamos em um \n, o usuário está submetendo uma senha */
            if(c == '\n') {
                /* Coloca um final na string */
                tentativa[j] = '\0';
                /* Sai do loop */
                break;
            }
            /* Se não foi um \n, o usuário submeteu um dígito */
            /* Salva esse dígito na string */
            tentativa[j] = c;
            /* Se chegamos ao tamanho limite da senha */
            if(j >= 4) {
                /* Termina a string com \0*/
                tentativa[4] = '\0';
                /* Se o último caractere não foi \n */
                if(c != '\n') {
                /* Então o usuário digitou mais que 4 dígitos */
                /* Limpa o buffer */
                limpar();
                /* Avisa que não pode*/
                printf("\tDigite apenas 4 digitos, por favor:\n\t");
                /* Reinicia a contagem de caracteres lidos */
                j = 0;
                continue;
                } else {
                /* Se o último caractere foi \n, não precisa mais ler nada */
                break;
                }
            }
            /* Vai pra leitura do próximo caractere */
            j++;
            }

            if(!validar_tentativa(tentativa))
            break;
        }
        printf("\nTentativa = %s\n", tentativa);
        comparar(tentativa, senha, resposta);
        for(i = 0; i<7; i++){
            if(i<4){
                rodadas_anteriores[rodadas-1].tentativa[i] = tentativa[i];
                continue;
            }
            rodadas_anteriores[rodadas-1].resposta[i-4] = resposta[i-4];
        }
        tabuleiro(resposta, rodadas_anteriores, rodadas, senha);
        if(rodadas_anteriores[rodadas-1].resposta[1] == 4){
            puts("\n\t\t\tVoce venceu!\n");
            return 0;
        }
    } 
}

int validar_tentativa(char c[6]){
    /*Verifica se todos os dígitos estão no intervalo correto e se a tentativa tem tamanho válido*/
    int i, j;
    for(i = 0; i < strlen(c); i++){
        if(c[i]=='\n'){
            c[i]='\0';
        }
    }

    for(i = 0; i<4; i++){
        if(c[i]<'1'||c[i]>'7'){ 
            printf("\tAlgum caracter esta fora do intervalo. Apenas numeros de 1 a 7, sem repeticoes, sao aceitos:\n\t");
            return 1; /*tentativa inválida*/
        }
    }
    for(i=0; i<4; i++){
        for(j=i+1; j<4; j++){
            if(c[i]==c[j]){
                printf("\tNao repita numeros, por favor:\n\t");
                return 1;
            }
        }
    }

    return 0;
}

void gerar_senha(int * senha){
    /*Gera uma senha aleatória sem dígitos repetidos*/
    int i, j;
    srand(time(NULL));
    for(i = 0; i < 4; i++){
        senha[i] = (rand()%7) + 1;
        for(j=0; j<i;j++){
            if(senha[i] == senha[j]){
                i--;
            }
        }
    }
}

void comparar(char * tentativa, int * senha, int *resposta){
    int i = 0, j = 0, pretos=0, brancos=0;
    for(i=0; i<4; i++){
        for(j=0; j<4; j++){
            if(tentativa[i]==senha[j] + '0'){
                brancos++;
            }
        }
    }
    
    for (i = 0; i < 4; i++){ /* Preencher com 1*/
        char c = senha[i]+'0';
        if(tentativa[i] ==c){
            brancos--;
            pretos++;
        }
    }
    resposta[0] = brancos;
    resposta[1] = pretos;
    resposta[2] = 4 - resposta[0] - resposta[1];
}

void limpar(void){    
    int c = 0;    
    while (getchar() != '\n' && c != EOF) {};
}

void tabuleiro(int *resposta, RODADAS_ANTERIORES * rodadas_anteriores, int rodadas, int *senha){
    /* Imprime o tabuleiro com as tentativas anteriores */
    int i;
    limpaTela();
    if(rodadas_anteriores[rodadas-1].resposta[1]==4||rodadas == 11){
        exibir_senha(1, senha);
    }
    else{
        exibir_senha(0, senha);
    }
    if(rodadas == 11) rodadas--;
    printf("\t\t\t\t\t\tbrancos\tpretos\n");
    printf("\t+--------------------------------------------------+\n");
    for(i = 0; i < rodadas; i++){
        printf("\t|#%.2d|\t", i+1);
        printf("%c\t%c\t%c\t%c\t  | %d  | %d |\n", rodadas_anteriores[i].tentativa[0], rodadas_anteriores[i].tentativa[1], rodadas_anteriores[i].tentativa[2], rodadas_anteriores[i].tentativa[3], rodadas_anteriores[i].resposta[0], rodadas_anteriores[i].resposta[1]);
    }
    printf("\t+--------------------------------------------------+\n");

    printf("\n\n");

}

void exibir_senha(int n, int *senha){
    if(n){
        printf("\n\t\t\tSENHA: %d %d %d %d\t\t   pinos\t\n", senha[0], senha[1], senha[2], senha[3]);
    }
    else{
        printf("\n\t\t\tSENHA: X X X X\t\t   pinos\t\n");
    }
}

void imprimir_inicio(void){
    printf("\t      ___           ___           ___           ___           ___     \n");
    printf("\t     /\\  \\         /\\  \\         /\\__\\         /\\__\\         /\\  \\    \n");
    printf("\t    /::\\  \\       /::\\  \\       /::|  |       /:/  /        /::\\  \\   \n");
    printf("\t   /:/\\ \\  \\     /:/\\:\\  \\     /:|:|  |      /:/__/        /:/\\:\\  \\  \n");
    printf("\t  _\\:\\~\\ \\  \\   /::\\~\\:\\  \\   /:/|:|  |__   /::\\  \\ ___   /::\\~\\:\\  \\ \n");
    printf("\t /\\ \\:\\ \\ \\__\\ /:/\\:\\ \\:\\__\\ /:/ |:| /\\__\\ /:/\\:\\  /\\__\\ /:/\\:\\ \\:\\__\\ \n");
    printf("\t \\:\\ \\:\\ \\/__/ \\:\\~\\:\\ \\/__/ \\/__|:|/:/  / \\/__\\:\\/:/  / \\/__\\:\\/:/  /\n");
    printf("\t  \\:\\ \\:\\__\\    \\:\\ \\:\\__\\       |:/:/  /       \\::/  /       \\::/  / \n");
    printf("\t   \\:\\/:/  /     \\:\\ \\/__/       |::/  /        /:/  /        /:/  /  \n");
    printf("\t    \\::/  /       \\:\\__\\         /:/  /        /:/  /        /:/  /   \n");
    printf("\t     \\/__/         \\/__/         \\/__/         \\/__/         \\/__/    \n");
    printf("\n\n");

    printf("\t+------------------------------------ REGRAS --------------------------------------+\n");
    printf("\t|\tO computador gera uma senha de quatro digitos diferentes, de 1 a 7.\t   |\n");
    printf("\t|\tO jogador tem 10 chances para adivinhar a senha gerada. Ao realizar\t   |\n");
    printf("\t|\tuma tentativa o computador retornara a quantidade de pinos pretos e\t   |\n");
    printf("\t|\tpinos brancos. Os pinos pretos indicam numero certo na posicao certa\t   |\n");
    printf("\t|\te os pinos brancos indicam numero certo na posicao errada. Nao eh dito\t   |\n");
    printf("\t|\tquais sao os numeros, cabe ao jogador descobrir. Ao esgotar o numero\t   |\n");
    printf("\t|\tde tentativas o computador revelara a senha.\t\t\t\t   |\n");
    printf("\t+----------------------------------------------------------------------------------+\n");
    printf("\n\n");

}

void limpaTela(){
     #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #elif defined(__linux__) || defined(__unix__)
        system("clear");
    #endif
}