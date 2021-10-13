#include<stdio.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>

/*--- Funções ---*/
int validar_tentativa(char c[6]);
void gerar_senha(int * senha);
void comparar(char * tentativa, int * senha, int *resposta);

char keyboard[BUFSIZ]; /*Variável usada pra limpar o buffer de entrada*/ 

int main(void){
    /*--- Declaração de variáveis ---*/
    char tentativa[6], c;
    int senha[4], resposta[3], rodadas=0;
    int i = 0;
    gerar_senha(senha); /*Gerando a senha*/
    /*--- Início do jogo ---*/
    while(1){
        rodadas++;
        if(rodadas == 11){
            puts("Você perdeu!");
            return 0;
        }
        printf("Rodada %d.\n",rodadas);
        puts("Insira sua tentativa.");
        while(1){ /*Loop para verificar entrada, terminará quando a entrada for válida*/
            fgets(tentativa, 6, stdin);
            setbuf(stdin,keyboard);/*Limpando o buffer de entrada*/
            if(!validar_tentativa(tentativa)){ /*Validando a tentativa, se validar vai entrar nesse if e quebrar o laço while*/
                break;
            }
        }
        //printf("Tentativa = %s\n", tentativa);
        comparar(tentativa, senha, resposta);/*Compara a entrada com a senha.*/
        printf("Pinos Brancos = %d", resposta[0]);/*Imprime os pinos brancos*/
        printf("Pinos Pretos = %d", resposta[1]);/*Imprime os pinos pretos*/
        printf("Vazio = %d", resposta[2]);/*Imprime os espaços vazios*/
        if(resposta[1] == 4){ /*Se todos os pinos forem pretos*/
            printf("\nVocê venceu!!");
            return 0;
        }
    } 
}

int validar_tentativa(char c[6]){
    /*Verifica se todos os dígitos estão no intervalo correto e se a tentativa tem tamanho válido*/
    int i;
    for(i = 0; i < strlen(c); i++){
        if(c[i]=='\n')
            c[i]='\0';
    }
    if((strlen(c))!=4){
        printf("Tamanho invalido. Digite somente 4 digitos: ");
        return 1;
    }
    
    for(i = 0; i<4; i++){
        if(c[i]<'1'||c[i]>'7'){ 
            printf("Algum numero esta fora do intervalo. Digite valores validos: ");
            return 1; /*tentativa inválida*/
        }
    }
    return 0;
}

void gerar_senha(int * senha){
    /*Gera uma senha aleatória sem dígitos repetidos*/
    srand(time(NULL));
    /*int varBreak = 0;*/
    int i, j;
    for(i = 0; i < 4; i++){
        senha[i] = (rand()%7) + 1;
        for(j=0; j<i;j++){
            if(senha[i] == senha[j]){
                i--;
                /*
                varBreak = 1;
                break
                */
            }
        }
        /*if(varBreak == 1){
            varBreak = 0;
            continue;
        }*/
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