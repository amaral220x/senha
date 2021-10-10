# senha
Jogo Senha implementado em C para o trabalho de Comp I.

O jogo Senha consiste em uma senha de 4 digitos entre 1 e 7, não repetidos e gerados aleatoriamente.
O jogador tenta uma senha e o programa responde com pinos pretos, brancos ou espaços vazios. Pinos pretos indicam cor certa no lugar certo, brancos são cor certa em posição errada e vazio são cores erradas. Os pinos não indicam qual cor, isso faz parte do que o jogador tem que descobrir. São 10 tentativas que se esgotadas levam ao Game Over e mostram a senha.

Entrada:
	As tentativas são armazenadas no vetor de char tentativa que possui 6 caracteres disponiveis. Como os valores são char, então precisamos de 4 casas para os números, 1 casa para o caractere \0 que indica fim da string e mais uma para armazenar algo a mais que o usuario digitar, pois se ele digitar mais de 4 caracteres iremos pedir uma entrada valida. (veja função <a name="fvi">verificar_intervalo</a>)

Funções:

	O jogo conta com a função main, funções de bibliotecas externas e funções criadas para o jogo. São elas:
	
	[int verificar_intervalo(char c[6])](#fvi)
		Essa função recebe um vetor de char, que é a entrada do teclado, as tentativas. Nela testamos se a tentativa possui mais de 4 digitos ou digitos fora do intervalos correto: 1 a 7 seguindo a tabela ASCII.
		
		
		
		
		
		
		
		
		
		
