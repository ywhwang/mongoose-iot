/*
 * Copyright (c) 2014-2016 Cesanta Software Limited
 * All rights reserved
 */

#ifndef MG_LOCALS_INCLUDED
#define MG_LOCALS_INCLUDED

/*
 * This file is included by mongoose.h and provides the definitions
 * necessary for Mongoose core to work w/o BSD socket headers.
 */

#ifndef RTOS_SDK

/*
 * ESP LWIP is compiled w/o socket support but we need a few declarations
 * for Mongoose core (sockaddr_in and such).
 */
#if LWIP_SOCKET
#error "Did not expect LWIP_SOCKET to be enabled."
#endif

/*
 * We really want the definitions from sockets.h for Mongoose,
 * so we include them even if LWIP_SOCKET is disabled.
 */
#ifdef __LWIP_SOCKETS_H__
#undef __LWIP_SOCKETS_H__
#endif

/* Implemented in libc_replacements */
long int random(void);

#endif

#endif /* MG_LOCALS_INCLUDED */