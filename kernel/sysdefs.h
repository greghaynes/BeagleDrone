#include <stdint.h>

typedef volatile uint32_t REG32;

#define pREG32 (REG32 *)

#define HWREG(x) (*(pREG32 (x)))
