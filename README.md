# senha
Jogo Senha implementado em C para o trabalho de Comp I.

O jogo Senha consiste em uma senha de 4 digitos entre 1 e 7, não repetidos e gerados aleatoriamente.
O jogador tenta uma senha e o programa responde com pinos pretos, brancos ou espaços vazios. Pinos pretos indicam cor certa no lugar certo, brancos são cor certa em posição errada e vazio são cores erradas. Os pinos não indicam qual cor, isso faz parte do que o jogador tem que descobrir. São 10 tentativas que se esgotadas levam ao Game Over e mostram a senha.

Entrada:
	As tentativas são armazenadas no vetor de char tentativa que possui 6 caracteres disponiveis. Como os valores são char, então precisamos de 4 casas para os números, 1 casa para o caractere \0 que indica fim da string e mais uma para armazenar algo a mais que o usuario digitar, pois se ele digitar mais de 4 caracteres iremos pedir uma entrada valida. (veja [Verificando tentativas](#verificando-tentativas))

#Funções:

O jogo conta com a função main, funções de bibliotecas externas e funções criadas para o jogo. São elas:

### Verificando tentativas
#### int verificar_intervalo(char c[6])

Essa função recebe um vetor de char, que é a entrada do teclado, as tentativas. Nela testamos se a tentativa possui mais de 4 digitos ou digitos fora do intervalos correto: 1 a 7 seguindo a tabela ASCII.

### Gerando a senha
#### void gerar_senha(int * senha)

A senha é gerada aleatoriamente, usando as bibliotecas stdlib, com as funções srand para gerar uma semente e rand para gerar um numero aleatorio, e time, para usarmos sempre uma semente diferente em srand, usando sradn(time(NULL)).
Após gerar o número precisamos dele no intervalo correto, 1 a 7, então dividimos o número gerado por 7, ficando com um valor no intervalo entre 0 e 6, e somamos 1, tirando o 0 e acrescentando o 7 no intervalo.
Esse processo ocorre em um loop que roda 4 vezes e preenche o vetor que foi passado na chamada da função. Temos então a nossa senha. 

		
		
		
		
		
		
		
		
		
		
