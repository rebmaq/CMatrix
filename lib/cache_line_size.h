#ifndef CACHE_LINE_SIZE_H_INCLUDED
#define CACHE_LINE_SIZE_H_INCLUDED

// Author: Nick Strupat, modified by Qamber Jafri
// Date: October 29, 2010, modified on January 9, 2023
// Returns the cache line size (in bytes) of the processor, or 0 on failure

#include <stddef.h>
size_t cache_line_size();

#endif