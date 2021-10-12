#include<stdio.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>

/*--- Funções ---*/
int validar_tentativa(char c[6]);
void gerar_senha(int * senha);
void clear(void);
void comparar(char * tentativa, int * senha, int *resposta);


int main(void){
    char tentativa[6], c;
    int senha[4] = {1,2,3,4}, resposta[3], rodadas=0;
    int i = 0;
    gerar_senha(senha);
    while(1){
        rodadas++;
        if(rodadas == 11){
            printf("\nVocê perdeu!");
            return 0;
        }
        printf("\n");
        while(1){ /*Loop para verificar entrada*/
        
            fgets(tentativa, 6, stdin);
            printf("**Tecle enter para continuar**");
            clear();
            if(!validar_tentativa(tentativa)){
                break;
            }
        }
        printf("\nTentativa = %s\n", tentativa);
        comparar(tentativa, senha, resposta);
        printf("\nPinos Brancos = %d", resposta[0]);
        printf("\nPinos Pretos = %d", resposta[1]);
        printf("\nVazio = %d", resposta[2]);
        if(resposta[1] == 4){
            printf("\nVocê venceu!!");
            return 0;
        }
    } 
}

int validar_tentativa(char c[6]){
    /*Verifica se todos os dígitos estão no intervalo correto e se a tentativa tem tamanho válido*/
    int i;
    if((strlen(c))>5){
        printf("Tamanho invalido. Digite somente 4 digitos: ");
        return 1;
    }
    else{
        for(i = 0; i < strlen(c); i++){
                if(c[i]=='\n'){
                    c[i]='\0';
                }
            }
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

void clear (void){    
    while (getchar() != '\n' );
}