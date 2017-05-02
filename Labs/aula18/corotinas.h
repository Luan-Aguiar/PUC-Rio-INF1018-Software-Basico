#define NO_PARAM 0

/* corpo de uma corotina */
typedef int (*FuncP)(int param);

/* referencia para uma corotina */
typedef struct coroutine *Coroutine; 

/* 
 * coro_create: cria uma nova corotina
 *
 * Parâmetro: função que implementa o "corpo" da corotina
 * Retorna: referencia para a corotina criada
 */
Coroutine coro_create(char *name, FuncP func);

/*
 * coro_resume: (re)ativa a execução de uma corotina
 *
 * Parâmetros:
 *   - referencia para a corotina a (re)ativar
 *   - parametro para a corotina (parametro inicial ou retorno do yield)
 *
 * Retorna:
 *   o parâmetro passado a coro_yield quando a corotina suspender,
 *   ou o retorno do "corpo" da corotina, quando ela terminar
 */
int coro_resume(Coroutine coro, int param);

/*
 * coro_yield: suspende a execução de uma corotina, retomando a execução 
 *             do chamador 
 * Parâmetros:
 *   - valor de retorno para o chamador (retorno do resume)
 *
 * Retorna:
 *   o parâmetro passado a coro_resume quando a corotina for reativada
 */
int coro_yield(int param);

/*
 * coro_free: libera área usada por corotina
 *
 * Parâmetro: referencia para a corotina
 */
void coro_free(Coroutine coro);
