/*
 * RSACRTTimingDiffImplementationProgram.c
 *
 *  Created on: 4-Nov-2021
 *  Author: Ayub Shaikh
 */

#include <stdio.h>

#include <stdlib.h>

#include <math.h>

#include<time.h>

#define MAXDIGITS 90000

#define PLUS 1
#define MINUS - 1



clock_t START_TIME, END_TIME;
double processing_Comp_time_used;

void preChineseReminderTheoremProcessing();

void RSAEncryption();
void decryptionByRSABasicMethod();
void decryptionByChineseReminderTheorem();

void subtractBignum();
void zeroToJustify();
/*Defined the customized data type */
typedef struct {
  char digits[MAXDIGITS];
  int signbit;
  int bigIntLastdigit;
}bignum;
bignum  dec1 , dec2, one, zero, mp, mq;

bignum d, m ,  c, e;
int compareBignum();
void addBignum();
void divideBigNumber();
void multiplyBigNumber();
void IntToBignumConvertion();
void powerOf();
void moduloMethod();
void printBignum();
bignum moduloInverse();
void convertion();


bignum p, q, n;
int numberTwo;
int number;

 int main() {

	 printf("--------------------------------------------------------------------\n");
	 printf("--------------------------------------------------------------------\n");

  printf("---*** C language Program To compare the timing difference between RSA Encryption and Decryption with and without Chinese Remainder Theorem.  ***---\n");

  printf("--------------------------------------------------------------------\n");
  printf("-------Assignment-3 Submitted by Roll number: CS21M515 -------------\n");
  printf("--------------------------------------------------------------------\n");
  printf("Please Enter the number:\n");
  scanf("%d", & number);
  convertion();

  // Encryption of the numbers BY RSA in belwo method
  RSAEncryption(e, m);

  START_TIME = clock();
  // Decryption by RSA basic method without chinese reminder theorem
  decryptionByRSABasicMethod();
  END_TIME = clock();
  processing_Comp_time_used = ((double)(END_TIME - START_TIME)) / CLOCKS_PER_SEC;
  printf("The Time taken by RSA Basic method without Chinese Reminder:= %lf s", processing_Comp_time_used);

  preChineseReminderTheoremProcessing();
  START_TIME = clock();

  // Decryption by  chinese reminder theorem
  decryptionByChineseReminderTheorem(dec1, dec2, mp, mq);
  END_TIME = clock();
  processing_Comp_time_used = ((double)(END_TIME - START_TIME)) / CLOCKS_PER_SEC;
  printf("The Time taken by CHINESE REMINDER THEOREM  = %lf s\n", processing_Comp_time_used);

  printf("Enter any number to exit:\n");
    scanf("%d", & numberTwo);


    if(numberTwo > 0){
       return 0;
    }

  //return 0;
}


void preChineseReminderTheoremProcessing() {
  bignum ptemp, qtemp;
  subtractBignum( & p, & one, & ptemp);
  subtractBignum( & q, & one, & qtemp);
  moduloMethod( & d, & ptemp, & dec1);
  moduloMethod( & d, & qtemp, & dec2);
  bignum modInverseNumOne = moduloInverse(q, p);
  bignum modInverseNumTwo = moduloInverse(p, q);
  multiplyBigNumber( & q, & modInverseNumOne, & mp);
  multiplyBigNumber( & p, & modInverseNumTwo, & mq);
}


 /*The encrypt function encrypts block if edflag is 0, otherwise it decrypts block, using a key previously set by setkey. The
 result is placed in block.Like setkey, block is specified as an array of 64 bits each stored in a char, but there are no parity bits in block.  */

void RSAEncryption(bignum e, bignum m) {
  bignum cx;
  powerOf( & m, & e, & cx);
  moduloMethod( & cx, & n, & c);
  printf("BY Using RSA THE ENCRYPTED NUMBER IS\n");
  printBignum( & c);
}

void convertion() {
	IntToBignumConvertion(number, & m);
	IntToBignumConvertion(173, & p);
	IntToBignumConvertion(149, & q);
	IntToBignumConvertion(3, & e);
	IntToBignumConvertion(16971, & d);
	IntToBignumConvertion(1, & one);
    multiplyBigNumber( & p, & q, & n);
}


// Description by using RSA basic method without Chinese Remainder Theorem
void decryptionByRSABasicMethod() {
  bignum cNum, DecKey, tempNum;
  cNum = one;
  DecKey = d;
  IntToBignumConvertion(0, & zero);
  bignum keytemp = DecKey;
  while (compareBignum( & DecKey, & zero) != 0) {
    subtractBignum( & keytemp, & one, & DecKey);
    multiplyBigNumber( & cNum, & c, & tempNum);
    moduloMethod( & tempNum, & n, & cNum);
    keytemp = DecKey;
  }
  printf("BY RSA THE DECRYPTED NUMBER BY RSA (without CRT)\n");
  printBignum( & cNum);
}
void decryptionByChineseReminderTheorem(bignum d1, bignum d2, bignum xp, bignum xq) {
  bignum c1, c2, keytemp, vp, vptemp, vq, vqtemp, op;
  vp = one;
  vq = one;
  moduloMethod( & c, & p, & c1);
  moduloMethod( & c, & q, & c2);
  IntToBignumConvertion(0, & zero);
  while (compareBignum( & d1, & zero) != 0) {
    keytemp = d1;
    subtractBignum( & keytemp, & one, & d1);
    multiplyBigNumber( & vp, & c1, & vptemp);
    moduloMethod( & vptemp, & p, & vp);
  }
  while (compareBignum( & d2, & zero) != 0) {
    keytemp = d2;
    subtractBignum( & keytemp, & one, & d2);
    multiplyBigNumber( & vq, & c2, & vqtemp);
    moduloMethod( & vqtemp, & q, & vq);
  }
  bignum result1, result2, result3;
  multiplyBigNumber( & xp, & vp, & result2);
  multiplyBigNumber( & xq, & vq, & result3);
  addBignum( & result2, & result3, & result1);
  moduloMethod( & result1, & n, & op);
  printf("\nThe DECRYPTED NUMBER by using CHINESE REMINDER THEOREM is :- \n");
  printBignum( & op);
}

void gcdExtended(bignum a, bignum b, bignum * s, bignum * t) {
  IntToBignumConvertion(0, & zero);
  if (compareBignum( & zero, & a) == 0) {
    IntToBignumConvertion(1, & one);
    * s = zero;
    * t = one;
    return;
  }
  bignum x1, y1, c, var1, var2;
  moduloMethod( & b, & a, & c);
  gcdExtended(c, a, & x1, & y1);
  divideBigNumber( & b, & a, & var2);
  multiplyBigNumber( & var2, & x1, & var1);
  subtractBignum( & y1, & var1, s);
  * t = x1;

}

bignum moduloInverse(bignum a, bignum m) {
  bignum s, t, res, temp1, temp2;
  gcdExtended(a, m, & s, & t);
  moduloMethod( & s, & m, & temp2);
  addBignum( & temp2, & m, & temp1);
  moduloMethod( & temp1, & m, & res);
  return res;
}

void printBignum(bignum * num) {
  int i;

  for (i = num -> bigIntLastdigit; i >= 0; i--)
    printf("%c", '0' + num -> digits[i]);

  printf("\n");
}

void IntToBignumConvertion(int s, bignum * number) {
  int count;
  int absoluteValueOfNumber;

  number -> signbit = PLUS;

  for (count = 0; count < MAXDIGITS; count++) number -> digits[count] = (char) 0;

  number -> bigIntLastdigit = -1;

/* These abs(s) functions return the absolute value of number. Most computers use a two's complement integer representation, in which the absolute value of INT_MIN (the smallest
 possible int) cannot be represented; thus, abs (INT_MIN) is not defined.
 * */
  absoluteValueOfNumber = abs(s);

  while (absoluteValueOfNumber > 0) {
	  number -> bigIntLastdigit++;
	  number -> digits[number -> bigIntLastdigit] = (absoluteValueOfNumber % 10);
	  absoluteValueOfNumber = absoluteValueOfNumber / 10;
  }

  if (s == 0) number -> bigIntLastdigit = 0;
}

void initializeBignum(bignum * n) {
  IntToBignumConvertion(0, n);
}

int max(int a, int b) {
  if (a > b) return (a);
  else return (b);
}

void addBignum(bignum * a, bignum * b, bignum * c) {
  int carry;
  int i;

  initializeBignum(c);

  if (a -> signbit == b -> signbit) c -> signbit = a -> signbit;
  else {
    if (a -> signbit == MINUS) {
      a -> signbit = PLUS;
      subtractBignum(b, a, c);
      a -> signbit = MINUS;
    } else {
      b -> signbit = PLUS;
      subtractBignum(a, b, c);
      b -> signbit = MINUS;
    }
    return;
  }

  c -> bigIntLastdigit = max(a -> bigIntLastdigit, b -> bigIntLastdigit) + 1;
  carry = 0;

  for (i = 0; i <= (c -> bigIntLastdigit); i++) {
    c -> digits[i] = (char)(carry + a -> digits[i] + b -> digits[i]) % 10;
    carry = (carry + a -> digits[i] + b -> digits[i]) / 10;
  }

  zeroToJustify(c);
}

void subtractBignum(bignum * a, bignum * b, bignum * c) {
  int borrow;
  int v;
  int i;

  initializeBignum(c);

  if ((a -> signbit == MINUS) || (b -> signbit == MINUS)) {
    b -> signbit = -1 * b -> signbit;
    addBignum(a, b, c);
    b -> signbit = -1 * b -> signbit;
    return;
  }

  if (compareBignum(a, b) == PLUS) {
    subtractBignum(b, a, c);
    c -> signbit = MINUS;
    return;
  }

  c -> bigIntLastdigit = max(a -> bigIntLastdigit, b -> bigIntLastdigit);
  borrow = 0;

  for (i = 0; i <= (c -> bigIntLastdigit); i++) {
    v = (a -> digits[i] - borrow - b -> digits[i]);
    if (a -> digits[i] > 0)
      borrow = 0;
    if (v < 0) {
      v = v + 10;
      borrow = 1;
    }

    c -> digits[i] = (char) v % 10;
  }

  zeroToJustify(c);
}

int compareBignum(bignum * a, bignum * b) {
  int i;

  if ((a -> signbit == MINUS) && (b -> signbit == PLUS)) return (PLUS);
  if ((a -> signbit == PLUS) && (b -> signbit == MINUS)) return (MINUS);

  if (b -> bigIntLastdigit > a -> bigIntLastdigit) return (PLUS * a -> signbit);
  if (a -> bigIntLastdigit > b -> bigIntLastdigit) return (MINUS * a -> signbit);

  for (i = a -> bigIntLastdigit; i >= 0; i--) {
    if (a -> digits[i] > b -> digits[i]) return (MINUS * a -> signbit);
    if (b -> digits[i] > a -> digits[i]) return (PLUS * a -> signbit);
  }

  return (0);
}

void zeroToJustify(bignum * n) {
  while ((n -> bigIntLastdigit > 0) && (n -> digits[n -> bigIntLastdigit] == 0))
    n -> bigIntLastdigit--;

  if ((n -> bigIntLastdigit == 0) && (n -> digits[0] == 0))
    n -> signbit = PLUS;
}

void digit_shift(bignum * n, int d) {
  int i;

  if ((n -> bigIntLastdigit == 0) && (n -> digits[0] == 0)) return;

  for (i = n -> bigIntLastdigit; i >= 0; i--)
    n -> digits[i + d] = n -> digits[i];

  for (i = 0; i < d; i++) n -> digits[i] = 0;

  n -> bigIntLastdigit = n -> bigIntLastdigit + d;
}

void multiplyBigNumber(bignum * a, bignum * b, bignum * c) {
  bignum row;
  bignum tmp;
  int i, j;

  initializeBignum(c);

  row = * a;

  for (i = 0; i <= b -> bigIntLastdigit; i++) {
    for (j = 1; j <= b -> digits[i]; j++) {
      addBignum(c, & row, & tmp);
      * c = tmp;
    }
    digit_shift( & row, 1);
  }

  c -> signbit = a -> signbit * b -> signbit;

  zeroToJustify(c);
}

void powerOf(bignum * base, bignum * exponent, bignum * result) {
  bignum zero, one, nx1, nx2;
  IntToBignumConvertion(0, & zero);
  IntToBignumConvertion(1, & one);
  IntToBignumConvertion(1, & nx2);
  nx1 = * exponent;
  while (compareBignum( & zero, exponent) != 0) {
    multiplyBigNumber( & nx2, base, result);
    subtractBignum( & nx1, & one, exponent);
    nx1 = * exponent;
    nx2 = * result;
  }
}


void divideBigNumber(bignum * a, bignum * b, bignum * c) {
  bignum row;
  bignum tmp;
  int asign, bsign;
  int index;

  initializeBignum(c);

  c -> signbit = a -> signbit * b -> signbit;

  asign = a -> signbit;
  bsign = b -> signbit;

  a -> signbit = PLUS;
  b -> signbit = PLUS;

  initializeBignum( & row);
  initializeBignum( & tmp);

  c -> bigIntLastdigit = a -> bigIntLastdigit;

  for (index = a -> bigIntLastdigit; index >= 0; index--) {
    digit_shift( & row, 1);
    row.digits[0] = a -> digits[index];
    c -> digits[index] = 0;
    while (compareBignum( & row, b) != PLUS) {
      c -> digits[index]++;
      subtractBignum( & row, b, & tmp);
      row = tmp;
    }
  }

  zeroToJustify(c);

  a -> signbit = asign;
  b -> signbit = bsign;
}
void moduloMethod(bignum * num, bignum * divisor, bignum * remainder) {
  bignum nx1, nx2;
  initializeBignum( & nx1);
  initializeBignum( & nx2);
  divideBigNumber(num, divisor, & nx1);
  multiplyBigNumber(divisor, & nx1, & nx2);
  subtractBignum(num, & nx2, remainder);

}


