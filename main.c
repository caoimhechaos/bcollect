#include <bcollect.h>

char *file = DEFAULT_PATH;

static void usage(void)
{
	fprintf(stderr, "Usage: bcollect [-c configfile] [-p] <interval> "
		"<backup>|-a\n");
	exit(EXIT_FAILURE);
}

int main(int argc, char **argv)
{
	struct backup *cur = NULL;
	struct interval *interval = NULL;
	unsigned long all_backups = 0, leftover_args;
	char *intervalname;
	char *backupname;
	FILE *fp;
	int i;

	init_interval();

	for (;;)
	{
		int c = getopt(argc, argv, "ac:pv");
		if (c == -1)
			break;

		switch (c)
		{
		case 'a':
			all_backups = 1;
			break;
		case 'c':
			file = optarg;
			break;
		case 'p':
			fprintf(stderr, "WARNING! Parallel mode is not yet implemented.\n");
			break;
		case 'v':
			fprintf(stderr, "bcollect version %s\n"
				"Compiled for %s\n", PACKAGE_STRING,
				PACKAGE_OSNAME);
			exit(EXIT_SUCCESS);
		default:
			usage;
		}
	}

	leftover_args = argc - optind;
	if (leftover_args + all_backups != 2)
		usage();

	intervalname = argv[optind];
	if (!all_backups)
	{
		if (strcmp(argv[optind + 1], "-a") == 0)
			all_backups = 1;
		else
			backupname = argv[optind + 1];
	}

	if (!file)
		file = DEFAULT_PATH;

	fp = fopen(file, "r");
	if (!fp)
	{
		perror(file);
		exit(EXIT_FAILURE);
	}

	yyin = fp;

	yyparse();

	fclose(fp);

	interval = c_hashtable_lookup(intervals, intervalname);
	if (!interval)
	{
		fprintf(stderr, "No such interval: %s\n", intervalname);
		exit(EXIT_FAILURE);
	}

	for (cur = backups.next; cur && cur != &backups; cur = cur->next)
		if (all_backups || strcmp(backupname, cur->name) == 0)
			do_backup(interval, cur);

	exit(EXIT_SUCCESS);
}
