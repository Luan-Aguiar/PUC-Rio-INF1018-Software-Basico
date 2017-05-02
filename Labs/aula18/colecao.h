typedef struct colecao Colecao;

Colecao *colecaoCria(void);
Colecao *colecaoInsere(Colecao *ci, int v);
void colecaoLibera(Colecao *ci);

void *criaIterador (Colecao *ci);
int ativaIterador (void *iterador);
void destroiIterador (void *iterador);

