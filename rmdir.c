/*
 * (c) 2007, Tonnerre Lombard <tonnerre@bsdprojects.net>,
 *	     BSD projects network. All rights reserved.
 *
 * Redistribution and use in source  and binary forms, with or without
 * modification, are permitted  provided that the following conditions
 * are met:
 *
 * * Redistributions of  source code  must retain the  above copyright
 *   notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright
 *   notice, this  list of conditions and the  following disclaimer in
 *   the  documentation  and/or  other  materials  provided  with  the
 *   distribution.
 * * Neither the name of the BSD projects  network nor the name of its
 *   contributors may  be used to endorse or  promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS"  AND ANY EXPRESS  OR IMPLIED WARRANTIES  OF MERCHANTABILITY
 * AND FITNESS  FOR A PARTICULAR  PURPOSE ARE DISCLAIMED. IN  NO EVENT
 * SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL,  EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED  TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE,  DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT  LIABILITY,  OR  TORT  (INCLUDING NEGLIGENCE  OR  OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include <bcollect.h>

/* FIXME: This function ought to be iterative! */
int
rmdir_recursive(const char *basedir)
{
	DIR *d = opendir(basedir);
	struct dirent *dp;

	printf("Called on %s\n", basedir);
	sleep(1);

	if (!d)
	{
		perror(basedir);
		return -1;
	}
	while (dp = readdir(d))
	{
		size_t len = strlen(basedir) + strlen(dp->d_name) + 3;
		struct stat sb;
		char *path;

		if (!strcmp(dp->d_name, ".") || !strcmp(dp->d_name, ".."))
			continue;

		printf("Dir part: %s\n", dp->d_name);

		path = malloc(len);

		if (!path)
		{
			perror("malloc");
			free(path);
			continue;
		}

		memset(path, 0, len);
		snprintf(path, len - 1, "%s/%s", basedir, dp->d_name);

		if (stat(path, &sb))
		{
			perror(path);
			free(path);
			continue;
		}

		if (sb.st_mode & S_IFDIR)
			rmdir_recursive(path);
		else
			unlink(path);

		free(path);
	}

	closedir(d);

	return rmdir(basedir);
}
