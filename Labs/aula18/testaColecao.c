#include <stdio.h>
#include <values.h>
#include "colecao.h"

int main(void) {

  int sum = 0, mult = 1, temp;

  Colecao *ci1 = colecaoCria();
  Colecao *ci2 = colecaoCria();
  
  void *it1, *it2;

  ci1 = colecaoInsere(ci1, 1);
  ci1 = colecaoInsere(ci1, 2);
  ci1 = colecaoInsere(ci1, 3);
  ci1 = colecaoInsere(ci1, 4);
  ci1 = colecaoInsere(ci1, 5);

  ci2 = colecaoInsere(ci2, 2);
  ci2 = colecaoInsere(ci2, 5);
  ci2 = colecaoInsere(ci2, 1);

  it1 = (void *) criaIterador(ci1);
  it2 = (void *) criaIterador(ci2);

  while(1) {
	temp = ativaIterador(it1);
	if(temp == MININT) break;
	sum += temp;
  }

  while(1) {
	temp = ativaIterador(it2);
	if(temp == MININT) break;
	mult *= temp;
  }

  /* Obtenha a soma dos elementos armazenados na coleção ci1 */
  printf("soma da colecao 1 = %d\n", sum);

  /* Obtenha o produto dos elementos armazenados na coleção ci2 */
  printf("produto da colecao 2 = %d\n", mult);
  
  destroiIterador(it1);
  destroiIterador(it2);

  colecaoLibera(ci1);
  colecaoLibera(ci2);

  return 0;
}

