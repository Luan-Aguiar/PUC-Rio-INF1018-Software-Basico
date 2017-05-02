#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

#include "corotinas.h"

#define STACK_SIZE 4096

typedef unsigned int *Stack;      /* pilha */
typedef unsigned int Register;    /* registrador */


typedef enum {ALIVE, DEAD} Status;

/* Descritor de uma corotina */
struct coroutine {

  /* área para a pilha da corotina */
  Register  esp;
  Stack stack;

  /* descritor da corotina "chamadora" */
  struct coroutine *caller;

  /* status e nome da corotina */
  int	status;
  char  *name;
};

/* descritor dummy para programa principal */
static struct coroutine mainCoroutine = {0,NULL,NULL,ALIVE,"main"};

static Coroutine mainCoro = &mainCoroutine;

/* guarda o descritor da corotina corrente */
static Coroutine currentCoro = &mainCoroutine;

/* Funções em assembly */
void icoro_begin();
int icoro_transfer(Coroutine from, Coroutine to, int param);

/*
 * Termina o programa com erro
 */
static void error(const char* msg, const char *name) {
  fprintf(stderr, "\nERRO: %s (%s)\n",msg, name);
  exit(EXIT_FAILURE);
}

/* 
 * coro_create: cria uma nova corotina
 *
 * Parâmetro: função que implementa o "corpo" da corotina
 * Retorna: ponteiro para o descritor da corotina criada
 */

Coroutine coro_create(char *name, FuncP func) {

   /* aloca o descritor da corotina */
   Coroutine coro = (Coroutine) malloc(sizeof(struct coroutine));

   /* aloca a pilha */
   coro->stack = (Stack) malloc(STACK_SIZE*4);

   /* coloca no fundo da pilha o endereço do corpo da corotina 
        e o endereço da função de inicialização da corotina */
   coro->stack[STACK_SIZE-1] = (unsigned int)func;
   coro->stack[STACK_SIZE-2] = (unsigned int)icoro_begin;
   coro->esp = (Register) &(coro->stack[STACK_SIZE-2]);

   coro->name = name;
   coro->status = ALIVE;
   return coro;
}

/*
 * coro_resume: (re)ativa a execução de uma corotina
 *
 * Parâmetros:
 *   - ponteiro para o descritor da corotina a (re)ativar
 *   - parametro para a corotina (parametro inicial ou retorno de coro_yield)
 *
 * Retorna:
 *   o parâmetro passado a coro_yield quando a corotina suspender,
 *   ou o retorno do "corpo" da corotina, quando ela terminar
 */
int coro_resume(Coroutine coro, int param) {

  /* somente pode reativar corotina que não terminou */
  if (coro->status == DEAD)
    error("Tentativa de reativar corotina terminada", coro->name);

  /* guarda o chamador e transfere controle */
  coro->caller = currentCoro;
  currentCoro = coro;

  return icoro_transfer(coro->caller, coro, param);
}

/*
 * coro_yield: suspende a execução de uma corotina, retomando a execução 
 *             do chamador 
 * Parâmetros:
 *   - valor de retorno para o chamador (retorno de coro_resume)
 *
 * Retorna:
 *   o parâmetro passado a coro_resume quando a corotina for reativada
 */
int coro_yield(int param){

  Coroutine curr;

  /* programa principal (main) não pode chamar yield */
  if (currentCoro == mainCoro)
    error("Programa principal não pode suspender", NULL);

  /* transfere o controle para o chamador */
  curr = currentCoro;
  currentCoro = curr->caller;

  return icoro_transfer(curr, currentCoro, param);
}

/*
 * coro_end: termina uma corotina, colocando-a no estado "morto" e devolvendo
 *           controle a seu chamador
 *
 * Parâmetros:
 *   - valor de retorno para o chamador
 */
void coro_end(int param) {
  Coroutine curr;
  curr = currentCoro;
  currentCoro = curr->caller;
  curr->status = DEAD;

  icoro_transfer(curr, currentCoro, param);
  
  error("Corotina terminada não pode retomar controle!", curr->name);
}

/*
 * coro_free: libera área usada por corotina
 *
 * Parâmetro: ponteiro para o descritor da corotina
 */
void coro_free(Coroutine coro) {

  /* libera a área de pilha */
  free(coro->stack);

  /* libera o descritor */
  free(coro);
}
