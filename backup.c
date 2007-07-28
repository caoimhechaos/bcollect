#include <bcollect.h>

#define MIN(a,b)	((a) < (b) ? (a) : (b))

void
do_backup(struct interval *interval, struct backup *backup)
{
	time_t now_tt = time(NULL);
	struct tm *now = localtime(&now_tt);

	size_t proglen = strlen(backup->dest) + 21;
	size_t locklen = strlen(backup->dest) + 7;
	size_t len = strlen(backup->dest) + strlen(interval->name) +
		strlen(backup->name) + 20;
	char *lockpath = malloc(locklen);
	char *progpath = malloc(proglen);
	char *path = malloc(len + 1);

	int lockfd, progfd;


	if (!path || !lockpath)
	{
		perror("malloc");
		goto out_free;
	}

	memset(lockpath, 0, locklen);
	memset(path, 0, len);

	snprintf(lockpath, locklen, "%s/.lock", backup->dest);
	snprintf(progpath, proglen, "%s/.backup_in_progress", backup->dest);
	snprintf(path, len - 16, "%s/%s-%s-", backup->dest, backup->name,
		interval->name);
	strftime(path + len - 17, 16, "%Y-%m-%d_%Hh%M", now);

	printf("Executing backup %s with interval %s, lock %s, progress lock %s to %s\n",
		backup->name, interval->name, lockpath, progpath, path);

	lockfd = open(lockpath, O_RDONLY | O_CREAT);
	if (lockfd == -1)
	{
		fprintf(stderr, "Locking backup directory for %s: %s\n",
			backup->name, strerror(errno));
		goto out_free;
	}
	if (flock(lockfd, LOCK_EX | LOCK_NB))
	{
		if (errno == EAGAIN)
			fprintf(stderr, "%s: Backup already in progress\n",
				backup->name);
		else
			fprintf(stderr, "Locking backup directory for %s: %s\n",
				backup->name, strerror(errno));

		goto out_close_lock;
	}

	progfd = open(progpath, O_RDONLY | O_CREAT | O_EXCL);
	if (progfd == -1)
	{
		struct dirent *de;
		struct stat sb;
		char *latest;
		time_t latestmtime = 0;
		DIR *d;

		if (errno != EEXIST)
		{
			fprintf(stderr, "Locking backup directory for %s: %s\n",
				backup->name, strerror(errno));
			goto out_unlock;
		}
		if (!(d = opendir(backup->dest)))
		{
			perror("opendir");
			close(progfd);
			goto out_unlock;
		}
		while (de = readdir(d))
		{
			size_t entry_len = strlen(backup->dest) +
				strlen(de->d_name) + 3;
			size_t minlen = MIN(strlen(de->d_name),
				strlen(backup->name));
			char *entry = NULL;

			/* Check if the directory entry is a backup */
			if (minlen < strlen(backup->name) ||
				strncmp(de->d_name, backup->name, minlen))
				continue;

			entry = malloc(entry_len);

			if (!entry)
			{
				perror("malloc");
				continue;
			}

			memset(entry, 0, entry_len);
			snprintf(entry, entry_len - 1, "%s/%s", backup->dest,
				de->d_name);
			printf("Looking at %s\n", entry);

			if (stat(entry, &sb)) perror(entry);
			else if (sb.st_mtime > latestmtime)
			{
				latest = entry;
				latestmtime = sb.st_mtime;
			}
			else
				free(entry);
		}
		closedir(d);

		if (latest)
		{
			fprintf(stderr, "Removing stale backup directory %s\n",
				latest);
			rmdir_recursive(latest);
			free(latest);
		}
	}
	close(progfd);

	/*
	 * We can mkdir only now because we weren't protected by the lock
	 * before.
	 */
	if (mkdir(path, 0755))
	{
		perror(path);
		goto out_unlock;
	}

	sleep(10);

out_unlock:
	flock(lockfd, LOCK_UN);

out_close_lock:
	close(lockfd);
	unlink(progpath);
	unlink(lockpath);

out_free:
	if (progpath) free(progpath);
	if (lockpath) free(lockpath);
	if (path) free(path);
}
