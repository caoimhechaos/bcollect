/*
 * (c) 2005, Caoimhe Chaos <caoimhechaos@protonmail.com>,
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
 * * Neither the name of the BSD  projects network nor the name of its
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
 *
 * bcollect main header file.
 */

/*
 * Definitions
 */
#ifndef LOCK_SH
#define LOCK_SH	0x01	/* shared file lock */
#endif /* LOCK_SH */
#ifndef LOCK_EX
#define	LOCK_EX	0x02	/* exclusive file lock */
#endif /* LOCK_EX */
#ifndef LOCK_NB
#define LOCK_NB	0x04	/* don't block when locking */
#endif /* LOCK_NB */
#ifndef LOCK_UN
#define LOCK_UN	0x08	/* unlock file */
#endif /* LOCK_UN */

/*
 * flock function
 */
#ifndef HAVE_FLOCK
extern int flock(int fd, int operation);
#endif
