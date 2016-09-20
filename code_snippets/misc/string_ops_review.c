
int main(void)
{
	char *p = malloc(25);
	char *q = malloc(25);

	strcpy(p, "pune       ");
	strcpy(q, "hello      ");
	strcat(p, q);

	printf("%s\n", p);
	//free(p);
	//free(q);
}
