/** @file random.h
 * @brief 32-bit pseudo-random number generator interface.
 * @version $Id: random.h,v 1.4 2004/10/03 17:53:13 entrope Exp $
 */
#ifndef INCLUDED_random_h
#define INCLUDED_random_h

struct Client;

/*
 * Proto types
 */

extern int random_seed_set(struct Client* from, const char* const* fields,
			   int count);

extern unsigned int ircrandom(void);

#endif /* INCLUDED_random_h */