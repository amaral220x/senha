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
void tabuleiro(int *resposta, RODADAS_ANTERIORES * rodadass, int rodadas, int * senha);
void exibir_senha(int n, int *senha);
void imprimir_inicio(void);


int main(void){
    char tentativa[6], c;
    int senha[4] = {1,2,3,4}, resposta[3], rodadas=0, matriz_respostas[10][6];
    int i = 0;
    RODADAS_ANTERIORES rodadass[10];
    gerar_senha(senha);
    imprimir_inicio();

    while(1){
        rodadas++;
        if(rodadas == 11){
            tabuleiro(resposta, rodadass, rodadas, senha);
            puts("\n\t\t\tVocê perdeu!\n");
            return 0;
        }
        //printf("\n");
        printf("\tDigite a sua %dª tentativa.\n", rodadas);
        printf("\t");
        while(1){ /*Loop para verificar entrada*/
            fgets(tentativa, 6, stdin);
            printf("\t**Tecle enter para continuar**\n");
            printf("\t");
            setbuf(stdin, NULL);
            limpar();
            if(!validar_tentativa(tentativa)){
                break;
            }
        }
        printf("\nTentativa = %s\n", tentativa);
        comparar(tentativa, senha, resposta);
        for(i = 0; i<7; i++){
            if(i<4){
                rodadass[rodadas-1].tentativa[i] = tentativa[i];
                continue;
            }
            rodadass[rodadas-1].resposta[i-4] = resposta[i-4];
        }
        tabuleiro(resposta, rodadass, rodadas, senha);
        if(rodadass[rodadas-1].resposta[1] == 4){
            puts("\n\t\t\tVocê venceu!\n");
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
    if((strlen(c))>4||strlen(c)<4){
        printf("\tTamanho invalido. Digite somente 4 digitos: ");
        return 1;
    }
    for(i = 0; i<4; i++){
        if(c[i]<'1'||c[i]>'7'){ 
            printf("\tAlgum numero esta fora do intervalo. Digite valores validos: ");
            return 1; /*tentativa inválida*/
        }
    }
    for(i=0; i<4; i++){
        for(j=i+1; j<4; j++){
            if(c[i]==c[j]){
                printf("\tNao repita numeros, por favor: ");
                return 1;
            }
        }
    }

    return 0;
}

void gerar_senha(int * senha){
    /*Gera uma senha aleatória sem dígitos repetidos*/
    srand(time(NULL));
    int i, j;
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
    int i = 0, j = 0, pretos=0, brancos=0, nada=0;
    for(i=0; i<4; i++){
        for(j=0; j<4; j++){
            if(tentativa[i]==senha[j] + '0'){
                brancos++;
            }
        }
    }
    
    for (i = 0; i < 4; i++){ // Preencher com 1
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

void limpar (void){    
    while (getchar() != '\n' );
}

void tabuleiro(int *resposta, RODADAS_ANTERIORES * rodadass, int rodadas, int *senha){
    /* Imprime o tabuleiro com as tentativas anteriores */
    system("clear");
    int i;
    if(rodadass[rodadas-1].resposta[1]==4||rodadas == 11){
        exibir_senha(1, senha);
    }
    else{
        exibir_senha(0, senha);
    }
    if(rodadas == 11) rodadas--;
    printf("\t\t\t\t\t\tbrancos\tpretos\n");
    printf("\t+-------------------------------------------------+\n");
    for(i = 0; i < rodadas; i++){
        printf("\t|#%.2d|\t", i+1);
        printf("%c\t%c\t%c\t%c\t| %d  |  %d |\n", rodadass[i].tentativa[0], rodadass[i].tentativa[1], rodadass[i].tentativa[2], rodadass[i].tentativa[3], rodadass[i].resposta[0], rodadass[i].resposta[1]);
    }
    printf("\t+-------------------------------------------------+\n");

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