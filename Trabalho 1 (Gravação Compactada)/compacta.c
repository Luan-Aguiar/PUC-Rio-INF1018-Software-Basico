/* Marcelo Paulon 1411029 (3WB - Ana) */
/* Renan da Fonte 1412122 (3WB - Ana) */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "compacta.h"


void compacta_processaStruct(unsigned char *valor, char *campos, char ord, FILE* arquivo) {
  int i,j,qtdCampos=strlen(campos), memcounter=0; 
  // memcounter é usado para percorrer a memória, para o programa escrever no arquivo os valores das variáveis no struct

  char *temp;

  for(i=0;i<qtdCampos;i++) {  // percorre o vetor campos
    switch(campos[i]) {
      case 'c':
        temp = (char*)(&valor[memcounter]);
        fwrite(temp,1,1,arquivo);   // campo é um char, basta escrever o seu valor no arquivo

        memcounter += 1;  // adiciona o tamanho do char ao memcounter

        break;
      case 's':
        while(memcounter % 2 != 0) memcounter++;  // caso a última posição não seja múltipla de 2 (short), pular o padding

        if(ord == 'L')  { // little endian 
          temp = (char*)(&valor[memcounter]);
          fwrite(temp,2,1,arquivo);               // como a arquitetura é IA-32 (little endian), basta escrever o valor do short no arquivo
        }
        else { // big endian 
          for(j = 1; j >= 0; j--) {               // como a arquitetura é IA-32 (little endian), o valor do short deve ser obtido com seus bytes em ordem inversa para serem escritos no arquivo
            temp = (char*)(&valor[memcounter+j]);
            fwrite(temp,1,1,arquivo);
          }
        }

        memcounter += 2;  // adiciona o tamanho do short ao memcounter

        break;
      case 'i':
        while(memcounter % 4 != 0) memcounter++;  // caso a última posição não seja múltipla de 4 (int), pular o padding
        
        if(ord == 'L')  { // little endian 
          temp = (char*)(&valor[memcounter]);
          fwrite(temp,4,1,arquivo);               // como a arquitetura é IA-32 (little endian), basta escrever o valor do int no arquivo
        }
        else {
          for(j = 3; j >= 0; j--) {               // como a arquitetura é IA-32 (little endian), o valor do int deve ser obtido com seus bytes em ordem inversa para serem escritos no arquivo
            temp = (char*)(&valor[memcounter+j]);
            fwrite(temp,1,1,arquivo);
          }
        }

        memcounter += 4;  // adiciona o tamanho do int ao memcounter

        break;
    }
  }
}

int compacta (int nstructs, void* valores, char* campos, char ord, FILE* arquivo) {
  int i, j, tamstruct=0, hasS=0, hasI=0;    // hasS => Há um short int no vetor campos ; hasI => Há um int no vetor campos
  
  unsigned char *structPtr = (unsigned char *)valores;

  unsigned char numMaxStructs = (unsigned char) nstructs; // Número máximo de structs, limitado até 255
  fwrite(&numMaxStructs,1,1,arquivo); // Escreve no arquivo o número máximo de structs (primeiro byte)

  // Próximo byte do cabeçalho: bit indicando se é little endian ou big endian + 7 bits indicando o número de campos dos structs
  char numMaxCampos = (char) strlen(campos);
  if(ord == 'L') numMaxCampos |= 0x80;  // Seta o primeiro bit como 1, se little endian

  fwrite(&numMaxCampos,1,1,arquivo);

  for(i = 0; i < strlen(campos); i += 4) {  // Percorre o vetor campos, e escreve os próximos bytes do cabeçalho (os tipos de campos) de acordo com ele
    char byteatual=0;             // Como cada byte conterá informações sobre 4 posições do vetor, é necessário uma variável para formar o byte antes de escrevê-lo no arquivo
    for(j = 3; j >= 0; j--) {
      switch(campos[i+(3-j)]) {   // Como o byte é preenchido em ordem inversa para facilitar o shift, é necessário um ajuste para o programa ler a posição correta do vetor
        case 'c':
          byteatual |= (0x01 << (2*j));   // char: 01
          tamstruct+=1;
          break;
        case 's':
          while(tamstruct % 2 != 0) tamstruct++;  // Se a última posição não for um múltiplo de 2 (short), pular o padding (avançar até que seja múltiplo)

          hasS = 1;
          byteatual |= (0x02 << (2*j));   // short: 10
          tamstruct+=2;
          break;
        case 'i':
          while(tamstruct % 4 != 0) tamstruct++;  // Se a última posição não for um múltiplo de 4 (int), pular o padding (avançar até que seja múltiplo)

          hasI = 1;
          byteatual |= (0x03 << (2*j));   // int: 11
          tamstruct+=4;
          break;
      }
    }

    fwrite(&byteatual,1,1,arquivo);
  }

  if(hasI && tamstruct % 4 != 0) {  // Se há um inteiro e a última posição não for múltipla de 4,
    while(tamstruct % 4 != 0) tamstruct++;  // .. pular padding
  }
  else if(hasS && tamstruct % 2 != 0) { // Se há um short e a última posição não for múltipla de 2,
    while(tamstruct % 2 != 0) tamstruct++;  // .. pular padding
  }

  for(i = 0; i < nstructs; i++) { // Para cada struct no vetor, escrever seus campos no arquivo
    compacta_processaStruct(&structPtr[i*tamstruct], campos, ord, arquivo);
  };

  return 0;
}

void mostra (FILE *arquivo){
  /*Leitura do cabeçalho - 1° byte -> número de structs*/
  int nstructs,nvar,i,j,k; /*nstructs recebe o número de structs; nvar armazena o numero de variáveis de cada struct; tam recebe o numero de bytes que a variavel ocupa*/
  char leitor, *tipovar; /*leitor le o arquivo pelo fscanf antes de repassar para outras variáveis e tipovar é um vetor que recebe os tipos de variáveis da struct*/
	
  fscanf(arquivo,"%c",&leitor);
  nstructs=(int)leitor;

  /*2º byte -> ord e numero de campos de cada struct armazenada*/
  fscanf(arquivo,"%c",&leitor);

  if(leitor>>7) printf("little\n"); //Testa o 1° bit, que representa a ord
  else printf("big\n");
  printf("%d\n",nstructs);

  nvar=leitor & 0x7f; //shifts para descartar o bit que representa ord
  
  tipovar = (char *)malloc(nvar*sizeof(char));
  if(tipovar==NULL){
    printf("Erro durante alocacao de memoria.\n");
    exit(-1);
  }

  /*3º byte em diante -> campos da struct*/
  for(i=0;i<nvar;i+=4){
    fscanf(arquivo,"%c",&leitor);
    for(j=0;j<4;j++){ //4 pares de bits em 1 byte
      if(leitor==0) break;
      tipovar[i+j]=leitor>>6;  //separa os bits 2 a 2 e coloca-os no vetor
      tipovar[i+j]&=0x03; //máscara para remover os 1's que aparecem com o shift
      leitor=leitor<<2;
    }
  }

  /*próxima etapa: ler as structs e imprimir na tela*/
  for(j=0;j<nstructs;j++){
      printf("------------\n");
      for(i=0;i<nvar;i++){
        int nbytes=pow(2,tipovar[i]-1); /*a codificacao dos bits dos descritores de campo torna esse método possível: 1 -> char (2⁰ bytes), 2 -> short (2¹ bytes), 3 -> int (2² bytes)*/
        for(k=0;k<nbytes;k++){
          fscanf(arquivo,"%c",&leitor);
          if(leitor >> 4 == 0) {        // verifica se é necessário colocar um zero à frente do número
            printf("0%x ", (leitor&0x000000ff));  // imprime o valor do byte (com o zero na frente).
          }                                       // & 0x000000ff é usado para exibir apenas um byte
          else {
            printf("%x ", (leitor&0x000000ff));   // imprime o valor do byte.
          }
        }
        printf("\n");
      }
        
  }

  /*finalização*/
  printf("------------\n");
}




