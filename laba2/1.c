#include <stdlib.h>
#include <stdio.h>

#define env_variable "TEST_VAR"
int main(int argc, char *argv[])
{
	extern char **environ;
	if (getenv(env_variable) == NULL)
		printf("No match with \e[33m%s\e[0m enviromental variable\n", env_variable);
	else 
		printf("Created enviromental variable: %s\n", getenv(env_variable));
	putenv("TEST_VAR=New enviromental variable");
	if ( (getenv(env_variable) == NULL) && (setenv("TEST_VAR", "New enviromental variable2", 0)) == 0 )
		printf("Enviromental variable wasn't created yet\n");
	else 
		printf("Ovewritten value of setenv() assigned to 0\n");
	printf("Created enviromental variable: \e[4m%s\e[0m\n", getenv(env_variable));

	int i = 1;
  char *s = *environ;

  for (; s; i++) {
    printf("%s\n", s);
    s = *(environ+i);
  }

	return 0;
}