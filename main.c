#include <bcollect.h>

char *file;

void
yyerror(char *str)
{
	fprintf(stderr, "Parse error at %s: %s\n", file, str);
	exit(EXIT_FAILURE);
}

static void usage(void)
{
	fprintf(stderr, "Usage: bcollect configfile\n");
	exit(EXIT_FAILURE);
}

int main(int argc, char **argv)
{
	struct backup *cur;
	FILE *fp;
	int i;

	init_interval();

	if (argc < 2)
		usage();

	file = *(argv + 1);

	fp = fopen(file, "r");
	if (!fp)
	{
		perror(file);
		exit(EXIT_FAILURE);
	}

	yyin = fp;

	yyparse();

	fclose(fp);

	/* TODO: Work with the backups here... */

	exit(EXIT_SUCCESS);
}
