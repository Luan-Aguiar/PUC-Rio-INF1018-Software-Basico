/* Renan da Fonte Simas dos Santos 1412122 3WB */
/* Marcelo Paulon Jucá Vasconcelos 1411029 3WB */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "geracod.h"

typedef int (*funcp) ();

typedef union intChar {
	int i;
	unsigned char c[4];
	} intchar;

typedef struct retStruct {
	int size;
	unsigned char *ret;
	intchar endereco; 
	} retstruct;

int linhas;  // Variável para indicar a linha atual, para que sejam mostradas informações que auxiliem no debug em caso de erro

void testaVar(char type, int var) { //Testa se o tipo da variável é inválido ou se ela está acima do número máximo permitido para seu tipo (ex: p5 ou v10)
	if(type == 'p') {
		if(var > 4) {
			printf("Erro (linha %d): so sao permitidos 5 parametros em SB (p0~p4)\n", linhas);
			exit(-1);
		}
	}
	else if(type == 'v') {
		if(var > 9) {
			printf("Erro (linha %d): so sao permitidos 10 variaveis locais em SB (v0~v9)\n", linhas);
			exit(-1);
		}
	}
	else if(type != '$') {
		printf("Erro (linha %d): tipo de variavel invalido\n", linhas);
		exit(-1);
	}
}

//movlMemToReg: escreve o código do movl de uma das partes do assign para um registrador
retstruct movlMemToReg (char type, int var, char reg){ //reg é c se %ecx e d se %edx
	unsigned char *execstack;
	int bytesEscritos=0;
	intchar temp;
	retstruct retorno;
	if(type=='p'||type=='v'){ //Casos em que o primeiro byte é 0x8b
		execstack=(unsigned char*)malloc(3); //o código de mov da pilha para um registrador possui 3 bytes
		execstack[0] = 0x8b; 
		if(reg=='c')execstack[1] = 0x4d; //valor de %ecx como destino
		else execstack[1]=0x55; //valor de %edx como destino
		//Dois casos possíveis para execstack[2]: parâmetro ou variável local
		if(type=='p') execstack[2]=(unsigned char)8+4*var; //se for parâmetro
		else execstack[2]=(unsigned char)-4*var-4; //se for variável local
		bytesEscritos+=3;
	}

	else if(type=='$'){ //caso de constante
		execstack=(unsigned char*)malloc(5); //o código de mov de constante possui 5 bytes
		if(reg=='c')execstack[0] = 0xb9; //movl para %ecx
		else execstack[0] = 0xba; //movl para %edx
		temp.i = var; //passa constante para a union
		memcpy(&execstack[1],temp.c,sizeof(int)); //passa constante para o vetor
		bytesEscritos+=5;
	}

	else{
		printf("Erro (linha %d): tipo de variavel nao reconhecido\n", linhas);
		exit(-1);
	}

	retorno.ret = execstack;
	retorno.size = bytesEscritos;
	return retorno;
}


//movlFromReg: escreve o código do movl do %edx para a memória (ou para o %eax)
retstruct movlFromReg (char type, int var){
	unsigned char *execstack;
	retstruct retorno;
	int bytesEscritos=0;

	//mov para a memória
	execstack=(unsigned char *)malloc(3);
	execstack[0]=0x89;
	execstack[1]=0x55;
	if(type=='p') execstack[2]=(unsigned char)8+4*var; //se for parâmetro
	else execstack[2]=(unsigned char)-4*var-4; //se for variável local
	bytesEscritos+=3;

	retorno.ret = execstack;
	retorno.size = bytesEscritos;
	return retorno;
}


//assign: escreve o codigo das atribuições
// varc0type, varc1type e varc2type indicam se a variável é uma constante, uma variável local ou um parâmetro
// formato: varc0 = varc1 op varc2
retstruct assign(char varc0Type, int varc0, char varc1Type, int varc1,char varc2Type, int varc2, char op) {
	/*Type -> $, v ou p
	$ -> constante
	v -> variável local [(-4*x-4)(%ebp)]
	p -> parâmetro [(8+4*x)(%ebp)]

	Formato do assembly:
	movl varc1 %ecx
	movl varc2 %edx
	op   %ecx %edx
	movl %edx arg0*/ 
	int maxSizeMovToReg=5,maxSizeOp=3,maxSizeMovFromReg=3,bytesEscritos=0; //Respectivamente, número de posições do vetor ocupadas em caso de: mover para registrador, operação, mover o resultado da operação e bytes já escritos no execstack
	unsigned char *execstack=(unsigned char *)malloc(2*maxSizeMovToReg+maxSizeOp+maxSizeMovFromReg); //espaço alocado considerando o caso com maior tamanho necessário
	retstruct func;
	
	testaVar(varc0Type, varc0);
	testaVar(varc1Type, varc1);
	testaVar(varc2Type, varc2);

	if(varc0Type=='$'){
		printf("Erro (linha %d): nao e possivel atribuir valor a uma constante\n", linhas);
		exit(-1);
	}

	if(op=='-')func=movlMemToReg(varc1Type,varc1,'d'); //se for subtração, move para o %edx
	else func=movlMemToReg(varc1Type,varc1,'c'); //se não, move para o %ecx
	memcpy(execstack,func.ret,func.size);
	bytesEscritos+=func.size;

	if(op=='-')func=movlMemToReg(varc2Type,varc2,'c'); //se for subtração, move para o %ecx
	else func=movlMemToReg(varc2Type,varc2,'d'); //se não, move para o %edx
	memcpy(&execstack[bytesEscritos],func.ret,func.size);
	bytesEscritos+=func.size;

	//op %ecx %edx
	switch(op){
	
		case '+': //add %ecx %edx
			func.ret=(unsigned char *)malloc(2);
			func.ret[0]=0x01;
			func.ret[1]=0xca;
			func.size=2;
			break;

		case '-': //sub %ecx %edx
			func.ret=(unsigned char *)malloc(2);
			func.ret[0]=0x29;
			func.ret[1]=0xca;
			func.size=2;
			break;

		case '*': //imul %ecx %edx
			func.ret=(unsigned char *)malloc(3);
			func.ret[0]=0x0f;
			func.ret[1]=0xaf;
			func.ret[2]=0xd1;
			func.size=3;
			break;

		default:
			printf("Erro (linha %d): operacao invalida\n", linhas);
			exit(-1);
			break;
	}
	memcpy(&execstack[bytesEscritos],func.ret,func.size);
	bytesEscritos+=func.size;

	func=movlFromReg(varc0Type,varc0); //move do %edx para a memória
	memcpy(&execstack[bytesEscritos],func.ret,func.size);
	bytesEscritos+=func.size;

	func.ret=execstack;
	func.size=bytesEscritos;
	return func;
}


//while: escreve o código dos while's
retstruct whileFunc(char type, int var) {
	//cmpl $0, var
	//je end
	unsigned char *execstack;
	retstruct retorno;
	int i;
	testaVar(type, var);
	execstack = (unsigned char *) malloc(10);

	execstack[0]=0x83; //cmp opcodes
	execstack[1]=0x7d;

	if(type=='p') execstack[2]=8+4*var; //se for parametro
	else if(type=='v') execstack[2]=-4*var-4; //se for variavel local
	else {
		printf("Erro (linha %d): constantes nao sao permitidas em um while\n", linhas);
		exit(-1);
	}
	
	execstack[3]=0x00;
	execstack[4]=0x0f; //je opcodes
	execstack[5]=0x84;
	for(i=6;i<=9;i++) execstack[i]=0xff; //placeholder para o deslocamento que sera colocado durante a funcao _end
	retorno.ret = execstack;
	retorno.size=10;

	return retorno;
}

int endFunc(unsigned char *execstack,int enderecoEnd,intchar *enderecoCmplWhile) { //retorna o numero de bytes escritos no execstack
	//jmp while
	intchar temp;
	temp.i = (enderecoEnd + 4) - (enderecoCmplWhile->i+9); //deslocamento do je (do final do je até após o jmp do end) 
	memcpy(&execstack[(enderecoCmplWhile->i)+6],temp.c,4); //coloca o deslocamento do je 
	execstack[enderecoEnd] = 0xe9; //opcode de jmp
	temp.i = enderecoCmplWhile->i-(enderecoEnd+5);//deslocamento do jmp (do final do jmp até o cmpl do while)
	memcpy(&execstack[enderecoEnd+1],temp.c,4); //coloca o deslocamento do jmp
	return 5;
}


funcp geracod (FILE *f) {
	unsigned char *mcodes = (unsigned char *)malloc(50*16); // mcodes - execstack, onde serao armazenados os codigos das instrucoes; alocação de memória supondo gasto máximo (todas as linhas como atribuições)
	unsigned char prologo[] = {0x55,0x89,0xe5,0x83,0xec,0x28}; //salva o valor de %ebp e aloca a memória para as variáveis locais
	unsigned char finalizacao[] = {0x8b,0x45,0xfc,0x89,0xec,0x5d,0xc3}; //coloca o v0 em %eax, restaura o valor de %ebp e retorna
	unsigned char temp=' ',vartype[3],op;
	retstruct func;
	intchar temp2;
	int bytes=0,var[3], nwhiles=0; //nwhiles guarda o numero de whiles "ativos" em um dado momento da execucao do programa (para que o end saiba a qual while se refere)
	int enderecoCmplWhiles[25]; //enderecoCmplWhiles guarda os endereços dos whiles ativos e possui 25 de tamanho pois o máximo possível de whiles ativos é 25, considerando que o máximo de linhas que um programa em sb pode ter é 50 e cada while precisa de um end.
	
	linhas = 1;

	memcpy(mcodes,prologo,sizeof(prologo)); // copia prologo para mcodes
	bytes+=sizeof(prologo);
	while((fread(&vartype[0],1,1,f)>0)&&(vartype[0]!='r')&&(linhas<=50)){ // le o início de cada linha, armazenando o tipo de instrução em vartype[0]
		if(bytes>=50*16){
			printf("Erro: Numero maximo de instrucoes excedido.\n");
			exit(-1);
		}

		switch(vartype[0]){
			case 'v':
			case 'p': //assign
				fscanf(f,"%d = %c%d %c %c%d",&var[0],&vartype[1],&var[1],&op,&vartype[2],&var[2]); //lê o resto da linha da atribuição, salvando cada valor em uma variável separada
				func=assign(vartype[0],var[0],vartype[1],var[1],vartype[2],var[2],op);
				memcpy(&mcodes[bytes],func.ret,func.size);
				bytes+=func.size;
				break;

			case 'w': //while
				fscanf(f,"hile %c%d",&vartype[0],&var[0]); //lê o resto da linha do while, salvando cada valor em uma variável separada
				
				enderecoCmplWhiles[nwhiles]=bytes; // Armazena o endereço do cmpl do while atual

				func = whileFunc(vartype[0],var[0]);

				memcpy(&mcodes[bytes],func.ret,func.size);
				bytes+=func.size;
				nwhiles++; // faz com que, caso haja um while dentro do atual, o endereço de seu cmpl seja armazenado em outra posição do vetor
				break;
			case 'e': //end
				if(nwhiles==0){
					printf("Erro (linha %d): nao ha um while aberto para o end declarado.\n", linhas);
					exit(-1);
				}

				nwhiles--; // decremento necessário para que seja buscada a posição do vetor em que está armazenado o último while chamado
				temp2.i=enderecoCmplWhiles[nwhiles];
				bytes+=endFunc(mcodes,bytes,&temp2);
				fseek(f,2,SEEK_CUR);

			case 'r': //ret
				break;	
			case '/': //comentario
				fscanf(f,"%c",&temp);
				if(temp!='/'){
					printf("Erro de leitura (linha %d): caractere invalido encontrado ('%c')\nDica: comentarios se iniciam com // e nao com /\n", linhas, temp);
					exit(-1);
				}
				else while(temp!='\n') fscanf(f,"%c",&temp);
				linhas++;
				break;
			case '\n': //newline
				linhas++;
				break;
			case '\t': //tabulação
				break;

			case ' ': //tabulação
				break;
	
			default: 
				printf("Erro de leitura (linha %d): caractere invalido encontrado ('%c')\n", linhas, vartype[0]);
				exit(-1);
				break;
		}
	}

	if(nwhiles>0){
		printf("Erro: nem todos os whiles foram fechados.\n");
		exit(-1);
	}

	if(vartype[0]!='r') printf("Aviso: final do codigo alcancado sem ret chamado.\n");

	if(linhas>50){
		printf("Erro: maximo de linhas atingido.\n");
		exit(-1);
	}

	memcpy(&mcodes[bytes],finalizacao,sizeof(finalizacao));
	funcp p = (funcp)mcodes;
	rewind(f);
	return p;
}


void liberacod (void *p){
	free(p);
}
