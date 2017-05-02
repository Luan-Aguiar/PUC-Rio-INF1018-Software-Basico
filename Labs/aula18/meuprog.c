#include <stdio.h>
#include "corotinas.h"

int pingpong(int val) {
	int ativacao = 1;
	
	while(1) {
		printf("ativacao: %d\n", ativacao);

		ativacao++;
		val++;
	
		coro_yield(val);
	}

	return ativacao;
}

int main(void) {
	int numPing = 0, numPong = 100, i;
	
	Coroutine ping = coro_create("ping", (void *) &pingpong);
	Coroutine pong = coro_create("pong", (void *) &pingpong);

	for(i = 0; i < 5; i++) {
		printf("ativando ping!\n");
		numPing = coro_resume(ping, numPing);
		printf("main recebeu: %d\n", numPing);

		printf("ativando pong!\n");
		numPong = coro_resume(pong, numPong);
		printf("main recebeu: %d\n", numPong);
	}
	
	coro_free(ping);
	coro_free(pong);

	return 0;
}
