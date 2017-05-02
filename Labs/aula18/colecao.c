#include <stdlib.h>
#include <values.h>
#include "corotinas.h"
#include "colecao.h"

struct colecao {
  int info;
  struct colecao *prox;
};

Colecao *colecaoCria(void) {
  return NULL;
}

Colecao *colecaoInsere(Colecao *ci, int v) {
  Colecao *n = (Colecao *) malloc(sizeof(Colecao));
  if (n != NULL) {
    n->info = v;
    n->prox = ci;
  }
  return n;
}

void colecaoLibera(Colecao *ci) {
  Colecao *prox, *n = ci;
  while (n != NULL) {
    prox = n->prox;
    free(n);
    n = prox;
  }
}

/*
 * Corpo da corotina que implementa o iterador 
 */
static int iteraColecao (int colecao) {

  /* Guarda a colecao que deve ser "iterada" */
  Colecao *ci = (Colecao *) colecao;

  /* Retorna o controle para quem a iniciou */
  coro_yield(NO_PARAM);

  while(1) {
    if(ci) {
	coro_yield(ci->info);
	ci = ci->prox;
    }
    else break;
  }

  return MININT;
}

/*
 * Cria uma corotina com corpo iteraColecao
 *  para percorrer a colecao
 */
void *criaIterador (Colecao *ci) {
  /* substitua o comando abaixo pela implementação da função */
  Coroutine it = coro_create("iteraColecao", (void *) &iteraColecao);
  coro_resume(it, (int) ci);

  return (void *) it; 
}

int ativaIterador (void *iterador) {
  /* substitua o comando abaixo pela implementação da função */
  return coro_resume(iterador, NO_PARAM);
}

void destroiIterador (void *iterador) {
  /* preencha o resto do código! */
  coro_free(iterador);
}
