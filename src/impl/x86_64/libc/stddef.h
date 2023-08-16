#ifndef STDDEF
#define STDDEF

typedef unsigned int size_t;

# ifndef NULL
#  if defined(__cplusplus)
#   define NULL 0L
#  else
#   define NULL 0
#  endif
# endif

#endif
