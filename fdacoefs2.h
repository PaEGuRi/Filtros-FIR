/*
 * Filter Coefficients (C Source) generated by the Filter Design and Analysis Tool
 * Generated by MATLAB(R) 9.13 and DSP System Toolbox 9.15.
 * Generated on: 12-Apr-2023 19:06:51
 */

/*
 * Discrete-Time FIR Filter (real)
 * -------------------------------
 * Filter Structure  : Direct-Form FIR
 * Filter Length     : 8
 * Stable            : Yes
 * Linear Phase      : Yes (Type 2)
 * Arithmetic        : fixed
 * Numerator         : s12,12 -> [-5.000000e-01 5.000000e-01)
 * Input             : s12,12 -> [-5.000000e-01 5.000000e-01)
 * Filter Internals  : Full Precision
 *   Output          : s25,24 -> [-1 1)  (auto determined)
 *   Product         : s23,24 -> [-2.500000e-01 2.500000e-01)  (auto determined)
 *   Accumulator     : s25,24 -> [-1 1)  (auto determined)
 *   Round Mode      : No rounding
 *   Overflow Mode   : No overflow
 */

/* General type conversion for MATLAB generated C-code  */
//#include "tmwtypes.h"
/* 
 * Expected path to tmwtypes.h 
 * C:\Program Files\MATLAB\R2022b\extern\include\tmwtypes.h 
 */
//const int BL = 8;
//const int B[8] = {
//      928,   3712,  10864,  17264,  17264,  10864,   3712,    928
//};

//FILTRO PASABAJOS 10Hz 7 ORDEN 
#define BL 8
const int32_t B[8] = {
        6214,   7837,   9039,   9678,   9678,   9039,   7837,   6214
};