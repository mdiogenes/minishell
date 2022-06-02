#include <stdio.h>
#include <stdlib.h>

typedef struct s_prueba {
	int type;
	void *content;
	struct s_prueba *next;
} t_prueba;

int main()
{
	//t_prueba hola;
	//hola.type = 2;
	int test;
	char *cadena;

	test = 0;
	cadena = "hola";
	printf("%p %x %p %s\n", (void *)NULL, test, &cadena, cadena);
	/*
	test = (int *)malloc(sizeof(int));
	test = 517;
	//hola.content = (void *)malloc(sizeof(int));
	hola.content = &test;
	printf ("%p %d\n", &hola, *((int *)hola.content));
//	printf ("%d\n", hola.next->next->type);
	*/
	return 0;
}