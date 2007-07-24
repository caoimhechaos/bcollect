#include <bcollect.h>

char *file;

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

	for (i = 0; i < nintervals; i++)
		printf("Interval \"%s\" count %d\n", intervals[i].name,
			intervals[i].count);

	/* for (cur = backups.next; cur != &backups; cur = cur->next)
		printf("Backup %s\n", cur->name); */

	exit(EXIT_SUCCESS);
}
