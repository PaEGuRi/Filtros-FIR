/*
 * Filter Coefficients (C Source) generated by the Filter Design and Analysis Tool
 * Generated by MATLAB(R) 9.13 and DSP System Toolbox 9.15.
 * Generated on: 13-Apr-2023 16:38:39
 */

/*
 * Discrete-Time FIR Filter (real)
 * -------------------------------
 * Filter Structure  : Direct-Form FIR
 * Filter Length     : 31
 * Stable            : Yes
 * Linear Phase      : Yes (Type 1)
 * Arithmetic        : fixed
 * Numerator         : s16,16 -> [-5.000000e-01 5.000000e-01)
 * Input             : s12,12 -> [-5.000000e-01 5.000000e-01)
 * Filter Internals  : Full Precision
 *   Output          : s29,28 -> [-1 1)  (auto determined)
 *   Product         : s27,28 -> [-2.500000e-01 2.500000e-01)  (auto determined)
 *   Accumulator     : s29,28 -> [-1 1)  (auto determined)
 *   Round Mode      : No rounding
 *   Overflow Mode   : No overflow
 */

/* General type conversion for MATLAB generated C-code  */
//#include "tmwtypes.h"
#include <stdint.h>

/*
 * Expected path to tmwtypes.h
 * D:\Program Files\extern\include\tmwtypes.h
 */

 //FILTRO PASABAJOS 25Hz 30 ORDEN 
#define BL = 31;
const int32_t B[31] = {
       -1256,      0,   1449,   1362,   -423,  -2039,  -1449,   1134,   2987,
     1512,  -2607,  -5096,  -1551,   8174,  18839,  23461,  18839,   8174,
    -1551,  -5096,  -2607,   1512,   2987,   1134,  -1449,  -2039,   -423,
     1362,   1449,      0,  -1256
};