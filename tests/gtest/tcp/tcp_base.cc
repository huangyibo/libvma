/*
 * Copyright (c) 2016 Mellanox Technologies, Ltd. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the main directory of this source tree, or the
 * BSD license below:
 *
 *     Redistribution and use in source and binary forms, with or
 *     without modification, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary form must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the documentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "common/def.h"
#include "common/log.h"
#include "common/sys.h"
#include "common/base.h"

#include "tcp_base.h"

void tcp_base::SetUp()
{
	errno = EOK;
}

void tcp_base::TearDown()
{
}

int tcp_base::sock_create(void)
{
	int fd;

	fd = socket(PF_INET, SOCK_STREAM, IPPROTO_IP);
	if (fd < 0) {
		log_error("failed socket() %s\n", strerror(errno));
	}

	return fd;
}

int tcp_base::sock_create_nb(void)
{
	int rc;
	int fd;

	fd = socket(PF_INET, SOCK_STREAM, IPPROTO_IP);
	if (fd < 0) {
		log_error("failed socket() %s\n", strerror(errno));
	}

	rc = test_base::sock_noblock(fd);
	if (rc < 0) {
		log_error("failed sock_noblock() %s\n", strerror(errno));
		close(fd);
		fd = -1;
	}

	return fd;
}