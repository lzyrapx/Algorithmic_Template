#define setbit(x, p) ((x)[(p) >> 5] |= 1u << ((p) & 31))
#define getbit(x, p) ((x)[(p) >> 5] >> ((p) & 31) & 1)