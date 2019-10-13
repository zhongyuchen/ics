/* 
 * CS:APP Data Lab 
 * 
 *16307130194 Chen Zhongyu <Please put your name and userid here>
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
editing the collection of function in this source file.

INTEGER CODING RULES
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
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

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

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

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
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
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

/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) 
{
  return ~((~x)|(~y));//De Morgan's Laws
}

/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) 
{
  //main idea: cancel all the bits on either side of the wanted Byte
  n=n<<3;//n=n*8
         //n: how many bits are on the right
  x=x>>n;//right shift: cancel all the bits on the right
  x=x&255;//x=x&(00...00 1111 1111)
          //turn all the bits on the left into 0

  return x;//the wanted Byte
}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n)
{
  int cancel;
  x=x>>n;//shift x to the right by n
  cancel=1<<31>>n<<1;
  //using arithmetic shift
  //1-> 1000 .... 0000-> 1...1 0000 .... 0000-> 1..10 0000 .... 0000
  //now there are n "1"s on the left & the rest are "0"s
  cancel=~cancel;
  //1..10 0000 .... 0000-> 0..01 1111 .... 1111
  //now there are n "0"s on the left & the rest are "1"s
  x=x&cancel;//turn n sign bits generated by arithmetic shift into 0
  return x;//logical shift
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x)
{
  int count=0;
  int getbit=1+(1<<8);
  getbit=(getbit<<16)+getbit;//getbit:0000 0001 0000 0001 0000 0001 0000 0001
  //dichotomy method:
  //divide int x into 4B
  //each time get the "1"(4 at a time) on LSb of every Byte and store the count of "1" at LSb of each B
  //right shift x for 1 bit every time, and get the "1" on higher bit(4 at a time)
  //and then accumulates at the 4 LSb chosen
  count=count+(x&getbit);
  count=count+((x>>1)&getbit);//priority:"+" > ">>" > "&"
  count=count+((x>>2)&getbit);
  count=count+((x>>3)&getbit);
  count=count+((x>>4)&getbit); 
  count=count+((x>>5)&getbit); 
  count=count+((x>>6)&getbit); 
  count=count+((x>>7)&getbit);
  //count: each Byte(4B), equals to the number of "1"s of that Byte
  count=count+(count>>16);
  count=count+(count>>8);
  //now LSB equals to the number of "1"s of all 4 Byte
  count=count&((1<<8)-1);//count=count&1111 1111
  //extract LSB as it equals to the number of "1"s of x
  return count;
}
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) 
{
  //dichotomy method:
  //every time equally divide x into 2 parts, then MSB part shifts right, and "|" LSB part
  //OR operation makes sure "1" will not disappear during dichotomy method
  x=(x>>16)|x;
  x=(x>>8)|x;
  x=(x>>4)|x;
  x=(x>>2)|x;
  x=(x>>1)|x;
  //if there is at least one "1", then LSb of x must be "1"
  //if there is no "1" at all, then x is still 0 now
  x=(~x)&1;
  //NOT operation flips x and then extract LSb
  //if there is at least one "1", then LSb is 0
  //else LSb is 1
  return x;
}
/* 
 * tmin - return minimum two's complement integer(二进制补码的整数） 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) 
{
  //the smallest integer(4B) is -2^31
  //using two's completement integer, it should be 1000 0000 0000 0000 0000 0000 0000 0000
  return 1<<31;
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) 
{
  //n-bit two's completement integer: -2^(n-1) ~ 2^(n-1)-1
  int y=x;
  int result;
  int shift=32+((~n)+1);//shift=32-n;
  y=x<<shift;
  y=y>>shift;
  //if x is between -2^(n-1) ~ 2^(n-1)-1
  //then after shift x left (n-1) and shift back, x does not change
  //else x changes
  result=!(x^y);
  //if x does not change, then x^y=0, !(x^y)=1
  //if x changes, then x^y!=0, !(x^y)=0
  return result;
}
/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) 
{
	int negative=(x>>31)&1;
	//if negative=1, then x<0, else negative=0, means x>=0
	int divisibility=!(x&((1<<n)+((~1)+1)));
	//if divisibility=1, then x%(2^n)=0, else =0, means x%(2^n)!=0
	int result=(x>>n)+(negative&(!divisibility));
	//x>>n, means x/(2^n)
	//if x>=0 || x%(2^n)==0, result = x>>n
	//if x<0 && x%(2^n)!=0, result = (x>>n)+1
	//at this time, "round down" is the opposite of "round towards 0", so it needs to +1 then round down
	return result;
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) 
{
  return (~x)+1;//using two's completement integer to get its opposite number
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) 
{
  int sign=!(x>>31);//after x>>31, x is either 0000 .... 0000 or 1111 .... 1111
  //if sign=1, x>=0; if sign=0, x<0
  int zero=!x;//if zero=1, x=0; if zero=0, x!=0
  int positive=sign&(!zero);
  //if sign=1 && zero==0, then x>0, positive=1
  return positive;
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) 
{
  //normal situation:
  int difference=y+((~x)+1);//difference=y-x;
  int positive=!(difference>>31);
  //dif>>31 is either 00 .... 00 or 11 .... 11 (32 sign bits of dif) 
  //!(dif>>31) is either 1 or 0(accordingly)
  //positive=1, means sign bit of dif is 0, then dif>=0, then x<=y
  
  int sign_x=(x>>31)&1;//store sign of x(1 means x<0, 0 means x>=0)
  int sign_y=(y>>31)&1;//store sign of y(1 means y<0, 0 means y>=0) 
  //overflow situation 1:
  int sign=sign_x&(!sign_y);//if=1, means x<0,y>=0, then it must be x<=y
  //overflow situation 2:
  int notsign=(!sign_x)&sign_y;//if=1, means x>=0,y<0, then it must be x>y

  return (sign|positive)&(!notsign);
  //if sign=1, then it must be result=1(to avoid overflow situation 1)
  //if positive=1, then it may be result=1
  //if notsign=1, then it must be result=0(to avoid overflow situation 2)
}
/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x) 
{
  //dichotomy method
  int allone;
  int position=0;
  int leftpart;

  //x: 32 bit
  allone=1<<31>>15;//allone=1111 1111 1111 1111 0000 0000 0000 0000
  leftpart=!(!(x&allone));//if leftpart=0, then there is no "1" on left part
  position=position+(leftpart<<4);//if leftpart=1, then p+=16, if leftpart=0, then p+=0
  x=x>>(leftpart<<4);//if left=1, then shift right 16 bit, else do not shift
  allone=(1<<16)+((~1)+1);//allone=1111 1111 1111 1111
  x=x&allone;//extract 16 bit on the right
  
  //x: 16 bit
  allone=allone>>8<<8;//1111 1111 0000 0000
  leftpart=!(!(x&allone));//if leftpart=0, then there is no "1" on left part
  position=position+(leftpart<<3);//if leftpart=1, then position+=8, if=0, then position+=0
  x=x>>(leftpart<<3);//if left=1, shift right 8 bit, else do not shift
  allone=allone>>8;//1111 1111
  x=x&allone;//extract 8 bit on the right

  //x: 8 bit
  allone=240;//1111 0000
  leftpart=!(!(x&allone));//if leftpart=0, then there is no "1" on left part
  position=position+(leftpart<<2);//if left=1, then p+=4, if left=0, then p+=0;
  x=x>>(leftpart<<2);//if left=1, shift right 4 bit, else do not shift
  allone=allone>>4;//1111
  x=x&allone;//extract 4 bit on the right

  //x: 4 bit
  allone=12;//1100
  leftpart=!(!(x&allone));//if left=1, then there is "1" in the left part
  position=position+(leftpart<<1);//if left=1, then p+=2, if left=0, then p+=0
  x=x>>(leftpart<<1);//if left=1, shift right 2 bit, else do not shift
  allone=allone>>2;//11
  x=x&allone;//extract 2 bit on the right

  //x: 2 bit
  allone=2;//10
  leftpart=!(!(x&allone));//if left=1, then leftbit is 1, else leftbit is 0 & right bit is 1
  position=position+leftpart;//if left=1, then p+=1, if left=0, p+=0
  
  //position=position+1;
  //exp=position-1;
  //then it means exp==position

  return position;
}
/* 
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) 
{
  int exp=uf&0x7f800000;//extract exp part of uf
  int frac=uf&0x007fffff;//extract frac part of uf
  if(exp==0x7f800000 && frac)//if exp==0111 1111 1000 .... 0000 && frac!=0, then uf is NaN
    return uf;
  
  //uf is not NaN: flip sign
  if(uf>=0)//0->1
    uf=uf+0x80000000;//uf=uf+1000 .... 0000
  else//1->0
    uf=uf&0x7fffffff;//uf=uf&0111 .... 1111

  return uf;
}
/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x)
{
  unsigned exp=-1;
  unsigned frac,fullfrac,midfrac,LSbfrac;
  unsigned result=0;
  int extractfrac;
  int y;//as an alternative of x
    
  //exception:
  //x=0
  if(x==0)
    return 0;
  //x=-2^31
  if(x==0x80000000)
    return 0xcf000000;

  //sign:
  if(x<0)
  {
    result+=0x80000000;//if x<0, sign is 1, put sign part into result
	x=~(x-1);//turn negative x into positive
  }
  
  //get exp:
  y=x&0x7fffffff;//extract 31 bit(except sign bit) of x
  while(y)
  {
    y=y>>1;
	exp++;
  }            
  //exp equals to the number of frac bits
  
  //frac:
  extractfrac=(1<<exp)-1;//11 .... 11, there is exp(this many) "1"s
  frac=x&extractfrac;//extract frac part of x
  if(exp<=23)//if frac bits<=23
    frac=frac<<(23-exp);//shift left, then it's done(no rounding is needed)
  else//if frac bits>23, rounding is needed
  {
    fullfrac=frac;//store full prac
	frac=fullfrac&(1<<31>>(31-(exp-23)));//set all the redundant bits "0"
	//at this time, frac is rounded toward 0
	LSbfrac=1<<(exp-23);//set only the LSb "1", other bits are "0"
	midfrac=frac|(1<<(exp-24));
	//turn frac's first bit behind the dicimal point "1", then this is midfrac
	if(fullfrac>midfrac || (fullfrac==midfrac && frac&LSbfrac))
	  frac+=LSbfrac;//round up
	frac=frac>>(exp-23);//get rid of the redundant bits more than 23 bits
  }
  result+=frac;//put frac part into result

  //exp:
  exp+=127;//bias: exp=n+127;
  exp=exp<<23;//shift to the right part
  result+=exp;//push exp part into result
  
  return result;
}
/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) 
{
  unsigned exp;
  unsigned frac;
  unsigned twice;
  
  exp=uf&0x7f800000;//extract exp part of uf
  frac=uf&0x007fffff;//extract frac part of uf
  
  //uf: 0 or -0
  if((!exp)&&(!frac))//exp==0 && frac==0
    return uf;

  //uf: infinite or NaN
  if(exp==0x7f800000)//exp==0111 1111 1000 .... 0000
    return uf;
  
  //uf: denormalized
  if((!exp)&&frac)//exp==0 && frac!=0
  {
    uf+=frac;//only frac part * 2
	return uf;
  }

  //uf: normalized
  twice=1<<23;//twice==0 0000 0001 000 0000 0000 0000 0000 0000
  uf+=twice;//equivalent to exp++(interprete as uf*2)
  return uf; 
}
