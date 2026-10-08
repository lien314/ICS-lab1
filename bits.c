/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.
  4. Interprets integer expressions using the Data Lab 32-bit bit-vector
     model: results outside the signed range retain their low 32 bits.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
#include "bits.h"

// P1
/* 
 * signMask - return a mask with only the most significant bit set (0x80000000)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int signMask(void) {
  return 1 << 31;
}

// P2
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1, bitXor(7, 7) = 0
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 2
 */
int bitXor(int x, int y) {
	return ~(~x & ~y) & ~(x & y);
}

// P3
/*
 * negativePart - return -x if x < 0, otherwise return 0
 *   Examples: negativePart(-10) = 10, negativePart(5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int negativePart(int x){
  return (x >> 31) & (~x + 1);
}


// P4
/*
 * copyByteWithin - copy byte src of x to byte dst, leaving all other bytes unchanged
 *   Bytes are numbered from 0 (least significant) to 3 (most significant).
 *   You can assume 0 <= src <= 3 and 0 <= dst <= 3.
 *   Example: copyByteWithin(0x11223344, 0, 2) = 0x11443344
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int copyByteWithin(int x, int src, int dst) {
  int srcShift = src << 3;
  int dstShift = dst << 3;
  int srcByte = (x >> srcShift) & 0xFF;
  int mask = ~(0xFF << dstShift);
  return (x & mask) | (srcByte << dstShift);
}

// P5
/* 
 * logicalShift - shift x to the right by n bits, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int logicalShift(int x, int n) {
  return (x >> n) & ~(((1 << 31) >> n) << 1);
}

// P6
/*
 * swapNibblePairs - swap the low and high 4 bits within each byte of x
 *   Examples: swapNibblePairs(0xAB) = 0xBA
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 18
 *   Rating: 4
 */
int swapNibblePairs(int x) {
  int mask = 0x0F | (0x0F << 8) | (0x0F << 16) | (0x0F << 24);
  return ((x & mask) << 4) | ((x >> 4) & mask);
}

// P7
/*
 * secondLowestZeroBit - return a mask that marks the position of the second least significant 0 bit
 *   Examples: secondLowestZeroBit(0xFFFFFFFA) = 0x4, secondLowestZeroBit(0x7FFFFFFF) = 0
 *             secondLowestZeroBit(-1) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 4
 */
int secondLowestZeroBit(int x) {
  int y = ~x;
  int t = y & (y + ~0);
  return t & (~t + 1);
}

// P8
/*
 * oddParity - return the odd parity bit of x, that is,
 *      when the number of 1s in the binary representation of x is even, then the return 1, otherwise return 0.
 *   Examples: oddParity(5) = 1, oddParity(7) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 56
 *   Rating: 5
 */
int oddParity(int x) {
  x ^= x >> 16;
  x ^= x >> 8;
  x ^= x >> 4;
  x ^= x >> 2;
  x ^= x >> 1;
  return !(x & 1);
}

// P9
/* 
 * rotateRightBits - rotate x to right by n bits
 *   you can assume n >= 0
 *   Examples: rotateRightBits(0x12345678, 8) = 0x78123456
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 5
 */
// P9
int rotateRightBits(int x, int n) {
  int n_mod = n & 31;
  int left_shift = (33 + ~n_mod) & 31;
  int mask = ~((~0) << left_shift) | ~((!n_mod) + ~0);
  return ((x >> n_mod) & mask) | (x << left_shift);
}

// P10
/*
 * roundEvenPow2 - round nonnegative x to the nearest multiple of 2^n.
 *   If x is exactly halfway between two multiples, choose the multiple whose
 *   quotient by 2^n is even.
 *   You can assume 0 <= x <= 0x3fffffff and 1 <= n <= 16.
 *   Examples: roundEvenPow2(10, 2) = 8, roundEvenPow2(14, 2) = 16
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 5
 */
int roundEvenPow2(int x, int n) {
  int d = 1 << n;
  int half_d = d >> 1;
  int q = x >> n;
  int r = x & (d + ~0);
  int is_half = !(r ^ half_d);
  int is_even = !(q & 1);
  int add = half_d + (((is_half & is_even) << 31) >> 31);
  return ((x + add) >> n) << n;
}

// P11
/* 
 * midpointTowardFirst - return the exact mathematical midpoint (x+y)/2
 *   without overflow. If the exact midpoint lies halfway between two
 *   integers, choose the adjacent integer that is closer to the first
 *   argument x.
 *   Examples: midpointTowardFirst(4, 7) = 5,
 *             midpointTowardFirst(7, 4) = 6
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 32
 *   Rating: 5
 */
int midpointTowardFirst(int x, int y) {
  int sign_x = x >> 31;
  int sign_y = y >> 31;
  int diff = x + (~y + 1);
  int same = ~(sign_x ^ sign_y);
  int diff_pos = ~(diff >> 31);
  int x_gt_y = (same & diff_pos) | (~same & ~sign_x);
  int odd = (x ^ y) & 1;
  int add = (odd & x_gt_y);
  return (x & y) + ((x ^ y) >> 1) + add;
}


// P12
/* 
 * isBetweenEitherOrder - return 1 when x lies in the inclusive interval whose
 *   endpoints are a and b. The endpoints may be given in either order.
 *   Example: isBetweenEitherOrder(5, 8, 3) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 48
 *   Rating: 7
 */
int isBetweenEitherOrder(int x, int a, int b) {
  int diff_ab = (a ^ b) >> 31;
  int sa = a >> 31;
  int diff_part_ab = sa & diff_ab;
  int v_minus_u_ab = b + (~a + 1);
  int same_part_ab = ~diff_ab & !(v_minus_u_ab >> 31);
  int leq_ab = (diff_part_ab | same_part_ab) & 1;

  int mask = ~leq_ab + 1;
  int ab_xor = a ^ b;
  int t = ab_xor & mask;
  int min = b ^ t;

  int diff_min_x = (min ^ x) >> 31;
  int smin = min >> 31;
  int diff_part_min = smin & diff_min_x;
  int v_minus_u_min = x + (~min + 1);
  int same_part_min = ~diff_min_x & !(v_minus_u_min >> 31);
  int leq_min_x = (diff_part_min | same_part_min) & 1;

  int max = a ^ t;

  int diff_x_max = (x ^ max) >> 31;
  int sx = x >> 31;
  int diff_part_x = sx & diff_x_max;
  int v_minus_u_x = max + (~x + 1);
  int same_part_x = ~diff_x_max & !(v_minus_u_x >> 31);
  int leq_x_max = (diff_part_x | same_part_x) & 1;

  return leq_min_x & leq_x_max;
}

// P13
/* 
 * mul5Sat - return x*5, and if x*5 overflow, change the result to 
 * INT_MAX(0x7fffffff) or INT_MIN(0x80000000) correspondingly
 *   Examples: mul5Sat(1) = 0x5, mul5Sat(0x40000000) = 0x7fffffff
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 7
 */
int mul5Sat(int x) {
  int mask = x >> 31;
  int abs_x = (x + mask) ^ mask;
  int t = (0x19 << 24) | (0x99 << 16) | (0x99 << 8) | 0x9A;
  int diff = abs_x + (~t + 1);
  int overflow = ~(diff >> 31);
  int r = (x << 2) + x;
  int max_val = ~(1 << 31);
  int min_val = 1 << 31;
  int sat_val = (mask & min_val) | (~mask & max_val);
  return (r & ~overflow) | (sat_val & overflow);
}

// P14
/* 
 * classifyAdd3 - classify the exact mathematical sum x+y+z.
 *   Return 1 if the sum is greater than INT_MAX, -1 if it is less than
 *   INT_MIN, and 0 otherwise. You may not use a wider integer type.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 52
 *   Rating: 7
 */
int classifyAdd3(int x, int y, int z) {
  int s1 = x + y;
  int c1 = (((x & y) | ((x | y) & ~s1)) >> 31) & 1;

  int s = s1 + z;
  int c2 = (((s1 & z) | ((s1 | z) & ~s)) >> 31) & 1;
  int carry = c1 + c2;

  int nx = x >> 31;
  int ny = y >> 31;
  int nz = z >> 31;
  int nsum = nx + ny + nz;
  int Nneg = ~nsum + 1;

  int sign_s = (s >> 31) & 1;
  int t = carry + sign_s;
  int K = t + ~Nneg + 1;

  int isneg = K >> 31;
  int notzero = !!K;
  int ispos = notzero & ~isneg;

  return ispos | isneg;
}

// P15
/*
 * floatScaleThreeHalves - Return bit-level equivalent of expression f*3/2 for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   Use round-to-nearest-even. Preserve the sign of both +0 and -0.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 60
 *   Rating: 7
 */
// P15
// P15
unsigned floatScaleThreeHalves(unsigned uf) {
    unsigned s = uf >> 31;
    unsigned exp = (uf >> 23) & 0xFF;
    unsigned frac = uf & 0x7FFFFF;

    if (exp == 0xFF) return uf;
    if (exp == 0 && frac == 0) return uf;

    unsigned M = exp ? ((1 << 23) | frac) : frac;
    unsigned N = M + (M << 1);   // 3 * M

    if (exp == 0 && N < (1 << 24)) {
        unsigned q = N >> 1;
        if ((N & 1) && (q & 1)) q++;
        if (q >= (1 << 23)) return (s << 31) | (1 << 23);
        return (s << 31) | q;
    }

    int k = 31;
    while (!((N >> k) & 1)) k--;
    int shift = k - 23;
    unsigned M_new = N >> shift;
    unsigned rem = N & ((1 << shift) - 1);
    unsigned half = 1 << (shift - 1);
    if (rem > half || (rem == half && (M_new & 1))) M_new++;
    int E_new = exp ? (exp + k - 24) : (k - 23);
    if (M_new == (1 << 24)) { M_new = 1 << 23; E_new++; }
    if (E_new >= 255) return (s << 31) | 0x7F800000;
    return (s << 31) | (E_new << 23) | (M_new & 0x7FFFFF);
}

// P16
/* 
 * floatRoundEven - round the floating-point value represented by uf to the
 *   nearest integer, with halfway cases rounded to the even integer. Return
 *   the bit-level representation of that integer as a single-precision float.
 *   If rounding produces zero, preserve the input sign; thus a negative
 *   value that rounds to zero returns -0. When uf is NaN or infinity,
 *   return uf unchanged.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 65
 *   Rating: 10
 */
unsigned floatRoundEven(unsigned uf) {
    unsigned s = uf >> 31;
    unsigned exp = (uf >> 23) & 0xFF;
    unsigned frac = uf & 0x7FFFFF;

    if (exp == 0xFF) {
        return uf;
    }

    if (exp == 0) {
        return s << 31;
    }

    int E = exp - 127;

    if (E >= 23) {
        return uf;
    }

    if (E < 0) {
        if (E <= -2) {
            return s << 31;
        }
        /* E == -1 */
        if (frac == 0) {
            return s << 31;
        } else {
            return (s << 31) | 0x3F800000;
        }
    }

    /* 0 <= E < 23: value has fractional part */
    unsigned M = (1 << 23) | frac;
    int shift = 23 - E;
    unsigned q = M >> shift;
    unsigned r = M & ((1 << shift) - 1);
    unsigned half = 1 << (shift - 1);

    if (r > half || (r == half && (q & 1))) {
        q = q + 1;
    }

    if (q == 0) {
        return s << 31;
    }

    int E_new = E;
    if (q >> (E + 1)) {
        E_new = E + 1;
    }

    unsigned M_new = q << (23 - E_new);
    unsigned frac_new = M_new & 0x7FFFFF;
    unsigned exp_new = E_new + 127;

    return (s << 31) | (exp_new << 23) | frac_new;
}

// P17
/*
 * float_i2f - Return bit-level equivalent of expression (float) x.
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 40
 *   Rating: 10
 */
unsigned float_i2f(int x) {
    unsigned sign = x & 0x80000000;
    unsigned absx = x;
    if (x < 0) absx = -x;
    if (absx == 0) return 0;
    int e = 31;
    while (!(absx >> e)) e--;
    int shift = e - 23;
    unsigned frac;
    if (shift > 0) {
        unsigned q = absx >> shift;
        unsigned r = absx & ((1 << shift) - 1);
        unsigned half = 1 << (shift - 1);
        if (r > half || (r == half && (q & 1))) {
            q++;
            if (q == (1 << 24)) {
                q >>= 1;
                e++;
            }
        }
        frac = q & 0x7FFFFF;
    } else {
        frac = (absx << (-shift)) & 0x7FFFFF;
    }
    return sign | ((e + 127) << 23) | frac;
}



// P18
/*
 * bitCount - return count of number of 1's in the binary representation of x
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 10
 */
int bitCount(int x) {
  int m1 = 0x55;
  m1 = m1 | (m1 << 8);
  m1 = m1 | (m1 << 16);
  int m2 = 0x33;
  m2 = m2 | (m2 << 8);
  m2 = m2 | (m2 << 16);
  int m4 = 0x0F;
  m4 = m4 | (m4 << 8);
  m4 = m4 | (m4 << 16);
  int m8 = 0xFF;
  m8 = m8 | (m8 << 16);
  int m16 = 0xFF;
  m16 = m16 | (m16 << 8);

  x = (x & m1) + ((x >> 1) & m1);
  x = (x & m2) + ((x >> 2) & m2);
  x = (x & m4) + ((x >> 4) & m4);
  x = (x & m8) + ((x >> 8) & m8);
  x = (x & m16) + ((x >> 16) & m16);
  return x;
}

// P19
/*
 * bitReverse - Reverse bits in an 32-bit integer
 *   Examples: bitReverse(0x80000004) = 0x20000001
 *             bitReverse(0x7FFFFFFF) = 0xFFFFFFFE
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 34
 *   Rating: 10
 */
// P19
int bitReverse(int x)
{
    int m1, m2, m3, m4;

    m4 = 0xFF + (0xFF << 16);
    m3 = m4 ^ (m4 << 4);
    m2 = m3 ^ (m3 << 2);
    m1 = m2 ^ (m2 << 1);

    x = ((x & m1) << 1) | ((x >> 1) & m1);
    x = ((x & m2) << 2) | ((x >> 2) & m2);
    x = ((x & m3) << 4) | ((x >> 4) & m3);
    x = ((x & m4) << 8) | ((x >> 8) & m4);
    x = (x << 16) | ((x >> 16) & ((0xFF << 8) + 0xFF));

    return x;
}