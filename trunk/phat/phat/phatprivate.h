#ifndef __PHAT_PRIVATE_H__
#define __PHAT_PRIVATE_H__

#include <stdio.h>
#include "config.h"

#define debug(...) if (DEBUG) fprintf (stderr, __VA_ARGS__)

void phat_warp_pointer (int xsrc, int ysrc,
			int xdest, int ydest);

#endif /* __PHAT_PRIVATE_H__ */
