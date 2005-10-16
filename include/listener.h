/* - Internet Relay Chat, include/listener.h
 *   Copyright (C) 1999 Thomas Helvey <tomh@inxpress.net>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 1, or (at your option)
 *   any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */
/** @file
 * @brief Interface and declarations for handling listening sockets.
 * @version $Id: listener.h,v 1.6 2004/10/03 13:36:04 entrope Exp $
 */
#ifndef INCLUDED_listener_h
#define INCLUDED_listener_h
#ifndef INCLUDED_ircd_defs_h
#include "ircd_defs.h"       /* HOSTLEN */
#endif
#ifndef INCLUDED_ircd_events_h
#include "ircd_events.h"
#endif
#ifndef INCLUDED_res_h
#include "res.h"
#endif
#ifndef INCLUDED_sys_types_h
#include <sys/types.h>       /* size_t, broken BSD system headers */
#define INCLUDED_sys_types_h
#endif

struct Client;
struct StatDesc;

/** Describes a single listening port. */
struct Listener {
  struct Listener* next;               /**< list node pointer */
  int              fd;                 /**< file descriptor */
  int              ref_count;          /**< number of connection references */
  unsigned char    active;             /**< current state of listener */
  unsigned char    hidden;             /**< hidden in stats output for clients */
  unsigned char    server;             /**< 1 if port is a server listener */
  unsigned char    mask_bits;          /**< number of bits in mask address */
  int              index;              /**< index into poll array */
  time_t           last_accept;        /**< last time listener accepted */
  struct irc_sockaddr addr;            /**< virtual address and port */
  struct irc_in_addr mask;             /**< listener hostmask */
  struct Socket    socket;             /**< describe socket to event system */
};

extern void        add_listener(int port, const char* vaddr_ip, 
                                const char* mask, int is_server, 
                                int is_hidden);
extern void        close_listener(struct Listener* listener);
extern void        close_listeners(void);
extern void        count_listener_memory(int* count_out, size_t* size_out);
extern const char* get_listener_name(const struct Listener* listener);
extern void        mark_listeners_closing(void);
extern void show_ports(struct Client* client, const struct StatDesc* sd,
                       char* param);
extern void        release_listener(struct Listener* listener);

#endif /* INCLUDED_listener_h */
