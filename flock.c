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

#ifndef HAVE_FLOCK

/*
 * Replacement for flock for systems that have flock64_t
 */
int
flock(int fd, int operation)
{
	flock64_t lock;

	memset(&lock, 0, sizeof(flock_t));
	lock.l_whence = SEEK_SET;

	if (operation & LOCK_SH)
	{
		lock.l_type = F_RDLCK;
		return fcntl(fd, (operation & LOCK_NB ? F_SETLK64 : F_SETLKW64),
			&lock);
	}
	else if (operation & LOCK_EX)
	{
		lock.l_type = F_WRLCK;
		return fcntl(fd, (operation & LOCK_NB ? F_SETLK64 : F_SETLKW64),
			&lock);
	}
	else if (operation & LOCK_UN)
	{
		lock.l_type = F_UNLCK;
		return fcntl(fd, F_SETLK64, &lock);
	}
	else
		return -1;
}

#endif
