/*
+--------------------------------------------------------------------------+
| CHStone : a suite of benchmark programs for C-based High-Level Synthesis |
| ======================================================================== |
|                                                                          |
| * Collected and Modified : Y. Hara, H. Tomiyama, S. Honda,               |
|                            H. Takada and K. Ishii                        |
|                            Nagoya University, Japan                      |
|                                                                          |
| * Remark :                                                               |
|    1. This source code is modified to unify the formats of the benchmark |
|       programs in CHStone.                                               |
|    2. Test vectors are added for CHStone.                                |
|    3. If "main_result" is 0 at the end of the program, the program is    |
|       correctly executed.                                                |
|    4. Please follow the copyright of each benchmark program.             |
+--------------------------------------------------------------------------+
*/
/* aes.c */
/*
 * Copyright (C) 2005
 * Akira Iwata & Masayuki Sato
 * Akira Iwata Laboratory,
 * Nagoya Institute of Technology in Japan.
 *
 * All rights reserved.
 *
 * This software is written by Masayuki Sato.
 * And if you want to contact us, send an email to Kimitake Wakayama
 * (wakayama@elcom.nitech.ac.jp)
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. All advertising materials mentioning features or use of this software must
 *    display the following acknowledgment:
 *    "This product includes software developed by Akira Iwata Laboratory,
 *    Nagoya Institute of Technology in Japan (http://mars.elcom.nitech.ac.jp/)."
 *
 * 4. Redistributions of any form whatsoever must retain the following
 *    acknowledgment:
 *    "This product includes software developed by Akira Iwata Laboratory,
 *     Nagoya Institute of Technology in Japan (http://mars.elcom.nitech.ac.jp/)."
 *
 *   THIS SOFTWARE IS PROVIDED "AS IS" WITHOUT EXPRESS OR IMPLIED WARRANTY.
 *   AKIRA IWATA LABORATORY DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS
 *   SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS,
 *   IN NO EVENT SHALL AKIRA IWATA LABORATORY BE LIABLE FOR ANY SPECIAL,
 *   INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING
 *   FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
 *   NEGLIGENCE OR OTHER TORTUOUS ACTION, ARISING OUT OF OR IN CONNECTION
 *   WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */
#define TESTMODE
//#define DWARV

/* DWARV cannot handle system-wide includes */
#ifdef TESTMODE
#include <stdio.h>
#ifdef DWARV
  #include <stdlib.h> /* The Bluebee toolchain requires `malloc', so we need to include this header */
#endif /* DWARV */
#endif /* TESTMODE */


int main_result;

#include "aes.h"
//#include "aes_enc.c"


//#include "aes_dec.c"
//#include "aes_key.c"
//#include "aes_func.c"

/*
+--------------------------------------------------------------------------+
| CHStone : a suite of benchmark programs for C-based High-Level Synthesis |
| ======================================================================== |
|                                                                          |
| * Collected and Modified : Y. Hara, H. Tomiyama, S. Honda,               |
|                            H. Takada and K. Ishii                        |
|                            Nagoya University, Japan                      |
|                                                                          |
| * Remark :                                                               |
|    1. This source code is modified to unify the formats of the benchmark |
|       programs in CHStone.                                               |
|    2. Test vectors are added for CHStone.                                |
|    3. If "main_result" is 0 at the end of the program, the program is    |
|       correctly executed.                                                |
|    4. Please follow the copyright of each benchmark program.             |
+--------------------------------------------------------------------------+
*/
/* aes_enc.c */
/*
 * Copyright (C) 2005
 * Akira Iwata & Masayuki Sato
 * Akira Iwata Laboratory,
 * Nagoya Institute of Technology in Japan.
 *
 * All rights reserved.
 *
 * This software is written by Masayuki Sato.
 * And if you want to contact us, send an email to Kimitake Wakayama
 * (wakayama@elcom.nitech.ac.jp)
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. All advertising materials mentioning features or use of this software must
 *    display the following acknowledgment:
 *    "This product includes software developed by Akira Iwata Laboratory,
 *    Nagoya Institute of Technology in Japan (http://mars.elcom.nitech.ac.jp/)."
 *
 * 4. Redistributions of any form whatsoever must retain the following
 *    acknowledgment:
 *    "This product includes software developed by Akira Iwata Laboratory,
 *     Nagoya Institute of Technology in Japan (http://mars.elcom.nitech.ac.jp/)."
 *
 *   THIS SOFTWARE IS PROVIDED "AS IS" WITHOUT EXPRESS OR IMPLIED WARRANTY.
 *   AKIRA IWATA LABORATORY DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS
 *   SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS,
 *   IN NO EVENT SHALL AKIRA IWATA LABORATORY BE LIABLE FOR ANY SPECIAL,
 *   INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING
 *   FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
 *   NEGLIGENCE OR OTHER TORTUOUS ACTION, ARISING OUT OF OR IN CONNECTION
 *   WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */
/*  ******* encrypto ************ */
#ifdef DWARV
#ifndef TESTMODE /* The Bluebee toolchain (except for DWARV) should not have the pragma here */
//  #pragma map generate_hw 0 /* Not tested by LegUp */
  /* DWARV: Compiles */
#endif /* TESTMODE */
#endif /* DWARV */
int
#ifdef DWARV
encrypt (int statemt[32], int key[32], int type, int round, int nb, int *word, int *Sbox, int *Rcon0, int *main_result)
#else
encrypt (int statemt[32], int key[32], int type)
#endif /* DWARV */
{
  int i;
/*
+--------------------------------------------------------------------------+
| * Test Vector (added for CHStone)                                        |
|     out_enc_statemt : expected output data for "encrypt"                 |
+--------------------------------------------------------------------------+
*/
/*  const int out_enc_statemt[16] =
    { 0x39, 0x25, 0x84, 0x1d, 0x2, 0xdc, 0x9, 0xfb, 0xdc, 0x11, 0x85, 0x97,
    0x19, 0x6a, 0xb, 0x32
  }; */
    int out_enc_statemt[16];
    out_enc_statemt[0] = 0x39;
    out_enc_statemt[1] = 0x25;
    out_enc_statemt[2] = 0x84;
    out_enc_statemt[3] = 0x1d;
    out_enc_statemt[4] = 0x2;
    out_enc_statemt[5] = 0xdc;
    out_enc_statemt[6] = 0x9;
    out_enc_statemt[7] = 0xfb;
    out_enc_statemt[8] = 0xdc;
    out_enc_statemt[9] = 0x11;
    out_enc_statemt[10] = 0x85;
    out_enc_statemt[11] = 0x97;
    out_enc_statemt[12] = 0x19;
    out_enc_statemt[13] = 0x6a;
    out_enc_statemt[14] = 0xb;
    out_enc_statemt[15] = 0x32;

#ifdef DWARV
  //#pragma map call_hw VIRTEX5 0
  KeySchedule (type, key, word, Sbox, Rcon0);
#else
  KeySchedule (type, key);
#endif
  switch (type)
    {
    case 128128:
      round = 0;
      nb = 4;
      break;
    case 192128:
      round = 2;
      nb = 4;
      break;
    case 256128:
      round = 4;
      nb = 4;
      break;
    case 128192:
    case 192192:
      round = 2;
      nb = 6;
      break;
    case 256192:
      round = 4;
      nb = 6;
      break;
    case 128256:
    case 192256:
    case 256256:
      round = 4;
      nb = 8;
      break;
    }
#ifdef DWARV
  //#pragma map call_hw VIRTEX5 0
  AddRoundKey (statemt, type, 0, word);
#else
  AddRoundKey (statemt, type, 0);
#endif /* DWARV */
  for (i = 1; i <= round + 9; ++i)
    {
#ifdef DWARV
       //#pragma map call_hw VIRTEX5 0
      ByteSub_ShiftRow (statemt, nb, Sbox);
      //#pragma map call_hw VIRTEX5 0
      MixColumn_AddRoundKey (statemt, nb, i, word);
#else
      ByteSub_ShiftRow (statemt, nb);
      MixColumn_AddRoundKey (statemt, nb, i);
#endif /* DWARV */
    }
#ifdef DWARV
  //#pragma map call_hw VIRTEX5 0
  ByteSub_ShiftRow (statemt, nb, Sbox);
  //#pragma map call_hw VIRTEX5 0
  AddRoundKey (statemt, type, i, word);
#else
  ByteSub_ShiftRow (statemt, nb);
  AddRoundKey (statemt, type, i);
#endif /* DWARV */

#ifndef DWARV
  printf ("encrypted message \t");
  for (i = 0; i < nb * 4; ++i)
    {
      if (statemt[i] < 16)
	printf ("0");
      printf ("%x", statemt[i]);
    }
#endif /* DWARV */

  for (i = 0; i < 16; i++)
#ifdef DWARV
    *main_result += (statemt[i] != out_enc_statemt[i]);
#else
    main_result += (statemt[i] != out_enc_statemt[i]);
#endif /* DWARV */

  return 0;
}

/*
+--------------------------------------------------------------------------+
| CHStone : a suite of benchmark programs for C-based High-Level Synthesis |
| ======================================================================== |
|                                                                          |
| * Collected and Modified : Y. Hara, H. Tomiyama, S. Honda,               |
|                            H. Takada and K. Ishii                        |
|                            Nagoya University, Japan                      |
|                                                                          |
| * Remark :                                                               |
|    1. This source code is modified to unify the formats of the benchmark |
|       programs in CHStone.                                               |
|    2. Test vectors are added for CHStone.                                |
|    3. If "main_result" is 0 at the end of the program, the program is    |
|       correctly executed.                                                |
|    4. Please follow the copyright of each benchmark program.             |
+--------------------------------------------------------------------------+
*/
/* aes_dec.c */
/*
 * Copyright (C) 2005
 * Akira Iwata & Masayuki Sato
 * Akira Iwata Laboratory,
 * Nagoya Institute of Technology in Japan.
 *
 * All rights reserved.
 *
 * This software is written by Masayuki Sato.
 * And if you want to contact us, send an email to Kimitake Wakayama
 * (wakayama@elcom.nitech.ac.jp)
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. All advertising materials mentioning features or use of this software must
 *    display the following acknowledgment:
 *    "This product includes software developed by Akira Iwata Laboratory,
 *    Nagoya Institute of Technology in Japan (http://mars.elcom.nitech.ac.jp/)."
 *
 * 4. Redistributions of any form whatsoever must retain the following
 *    acknowledgment:
 *    "This product includes software developed by Akira Iwata Laboratory,
 *     Nagoya Institute of Technology in Japan (http://mars.elcom.nitech.ac.jp/)."
 *
 *   THIS SOFTWARE IS PROVIDED "AS IS" WITHOUT EXPRESS OR IMPLIED WARRANTY.
 *   AKIRA IWATA LABORATORY DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS
 *   SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS,
 *   IN NO EVENT SHALL AKIRA IWATA LABORATORY BE LIABLE FOR ANY SPECIAL,
 *   INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING
 *   FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
 *   NEGLIGENCE OR OTHER TORTUOUS ACTION, ARISING OUT OF OR IN CONNECTION
 *   WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */
#ifdef DWARV
#ifndef TESTMODE /* The Bluebee toolchain (except for DWARV) should not have the pragma here */
  #pragma map generate_hw 1
  /* DWARV: Compiles */
#endif /* TESTMODE */
#endif /* DWARV */
int
#ifdef DWARV
decrypt(int statemt[32], int key[32], int type, int round, int nb, int *word,
        int *Sbox, int *invSbox, int *Rcon0, int *main_result)
#else
    __attribute__((noinline)) decrypt(int statemt[32], int key[32], int type)
#endif /* DWARV */
{
  int i;
/*
+--------------------------------------------------------------------------+
| * Test Vector (added for CHStone)                                        |
|     out_enc_statemt : expected output data for "decrypt"                 |
+--------------------------------------------------------------------------+
*/
/*const int out_dec_statemt[16] =
    { 0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30, 0x8d, 0x31, 0x31, 0x98, 0xa2,
    0xe0, 0x37, 0x7, 0x34
  };*/
 int out_dec_statemt[16];
 out_dec_statemt[0] = 0x32;
 out_dec_statemt[1] = 0x43;
 out_dec_statemt[2] = 0xf6;
 out_dec_statemt[3] = 0xa8;
 out_dec_statemt[4] = 0x88;
 out_dec_statemt[5] = 0x5a;
 out_dec_statemt[6] = 0x30;
 out_dec_statemt[7] = 0x8d;
 out_dec_statemt[8] = 0x31;
 out_dec_statemt[9] = 0x31;
 out_dec_statemt[10] = 0x98;
 out_dec_statemt[11] = 0xa2;
 out_dec_statemt[12] = 0xe0;
 out_dec_statemt[13] = 0x37;
 out_dec_statemt[14] = 0x7;
 out_dec_statemt[15] = 0x34;

#ifdef DWARV
 KeySchedule (type, key, word, Sbox, Rcon0);
#else
 KeySchedule (type, key);
#endif /* DWARV */

  switch (type)
    {
    case 128128:
      round = 10;
      nb = 4;
      break;
    case 128192:
    case 192192:
      round = 12;
      nb = 6;
      break;
    case 192128:
      round = 12;
      nb = 4;
      break;
    case 128256:
    case 192256:
      round = 14;
      nb = 8;
      break;
    case 256128:
      round = 14;
      nb = 4;
      break;
    case 256192:
      round = 14;
      nb = 6;
      break;
    case 256256:
      round = 14;
      nb = 8;
      break;
    }

#ifdef DWARV
  AddRoundKey (statemt, type, round, word);
  InversShiftRow_ByteSub (statemt, nb, invSbox);
#else
  AddRoundKey (statemt, type, round);
  InversShiftRow_ByteSub (statemt, nb);
#endif /* DWARV */

  for (i = round - 1; i >= 1; --i)
    {
#ifdef DWARV
      AddRoundKey_InversMixColumn (statemt, nb, i, word);
      InversShiftRow_ByteSub (statemt, nb, invSbox);
#else
      AddRoundKey_InversMixColumn (statemt, nb, i);
      InversShiftRow_ByteSub (statemt, nb);
#endif /* DWARV */
    }

#ifdef DWARV
  AddRoundKey (statemt, type, 0, word);
#else
  AddRoundKey (statemt, type, 0);
#endif /* DWARV */

#ifndef DWARV
  printf ("\ndecrypto message\t");
  for (i = 0; i < ((type % 1000) / 8); ++i)
    {
      if (statemt[i] < 16)
	printf ("0");
      printf ("%x", statemt[i]);
    }
#endif /* DWARV */

  for (i = 0; i < 16; i++)
#ifdef DWARV
    *main_result += (statemt[i] != out_dec_statemt[i]);
#else
    main_result += (statemt[i] != out_dec_statemt[i]);
#endif /* DWARV */

  return 0;
}

/*
+--------------------------------------------------------------------------+
| CHStone : a suite of benchmark programs for C-based High-Level Synthesis |
| ======================================================================== |
|                                                                          |
| * Collected and Modified : Y. Hara, H. Tomiyama, S. Honda,               |
|                            H. Takada and K. Ishii                        |
|                            Nagoya University, Japan                      |
|                                                                          |
| * Remark :                                                               |
|    1. This source code is modified to unify the formats of the benchmark |
|       programs in CHStone.                                               |
|    2. Test vectors are added for CHStone.                                |
|    3. If "main_result" is 0 at the end of the program, the program is    |
|       correctly executed.                                                |
|    4. Please follow the copyright of each benchmark program.             |
+--------------------------------------------------------------------------+
*/
/* aes_key.c */
/*
 * Copyright (C) 2005
 * Akira Iwata & Masayuki Sato
 * Akira Iwata Laboratory,
 * Nagoya Institute of Technology in Japan.
 *
 * All rights reserved.
 *
 * This software is written by Masayuki Sato.
 * And if you want to contact us, send an email to Kimitake Wakayama
 * (wakayama@elcom.nitech.ac.jp)
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. All advertising materials mentioning features or use of this software must
 *    display the following acknowledgment:
 *    "This product includes software developed by Akira Iwata Laboratory,
 *    Nagoya Institute of Technology in Japan (http://mars.elcom.nitech.ac.jp/)."
 *
 * 4. Redistributions of any form whatsoever must retain the following
 *    acknowledgment:
 *    "This product includes software developed by Akira Iwata Laboratory,
 *     Nagoya Institute of Technology in Japan (http://mars.elcom.nitech.ac.jp/)."
 *
 *   THIS SOFTWARE IS PROVIDED "AS IS" WITHOUT EXPRESS OR IMPLIED WARRANTY.
 *   AKIRA IWATA LABORATORY DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS
 *   SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS,
 *   IN NO EVENT SHALL AKIRA IWATA LABORATORY BE LIABLE FOR ANY SPECIAL,
 *   INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING
 *   FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
 *   NEGLIGENCE OR OTHER TORTUOUS ACTION, ARISING OUT OF OR IN CONNECTION
 *   WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */

/* **************key generate & key display *******************/
const int Rcon0[30] = {
  0x01, 0x02, 0x04, 0x08,
  0x10, 0x20, 0x40, 0x80,
  0x1b, 0x36, 0x6c, 0xd8,
  0xab, 0x4d, 0x9a, 0x2f,
  0x5e, 0xbc, 0x63, 0xc6,
  0x97, 0x35, 0x6a, 0xd4,
  0xb3, 0x7d, 0xfa, 0xef,
  0xc5, 0x91,
};

/*  **************** key expand ************************ */
int
#ifdef DWARV
KeySchedule(int type, int key[32], int *word, int *Sbox, int *Rcon0)
#else
KeySchedule(int type, int key[32])
#endif /* DWARV */
{
  int nk, nb, round;
  int i, j, temp[4];

  switch (type)
    {
    case 128128:
      nk = 4;
      nb = 4;
      round = 10;
      break;
    case 128192:
      nk = 4;
      nb = 6;
      round = 12;
      break;
    case 128256:
      nk = 4;
      nb = 8;
      round = 14;
      break;
    case 192128:
      nk = 6;
      nb = 4;
      round = 12;
      break;
    case 192192:
      nk = 6;
      nb = 6;
      round = 12;
      break;
    case 192256:
      nk = 6;
      nb = 8;
      round = 14;
      break;
    case 256128:
      nk = 8;
      nb = 4;
      round = 14;
      break;
    case 256192:
      nk = 8;
      nb = 6;
      round = 14;
      break;
    case 256256:
      nk = 8;
      nb = 8;
      round = 14;
      break;
    default:
      return -1;
    }

  for (j = 0; j < nk; ++j)
    for (i = 0; i < 4; ++i)
/* 0 word */
{
#ifdef DWARV
      word[j + 120 * (i)] = key[i + j * 4];
#else
      word[i][j] = key[i + j * 4];
#endif /* DWARV */
}

/* expanded key is generated */
  for (j = nk; j < nb * (round + 1); ++j)
    {

/* RotByte */
      if ((j % nk) == 0)
	{
#ifdef DWARV
//          #pragma map call_hw VIRTEX5 0
          temp[0] = SubByte (word[j - 1 + 120 * (1)], Sbox) ^ Rcon0[(j / nk) - 1];
          temp[1] = SubByte (word[j - 1 + 120 * (2)], Sbox);
          temp[2] = SubByte (word[j - 1 + 120 * (3)], Sbox);
          temp[3] = SubByte (word[j - 1 + 120 * (0)], Sbox);
#else
	  temp[0] = SubByte (word[1][j - 1]) ^ Rcon0[(j / nk) - 1];
	  temp[1] = SubByte (word[2][j - 1]);
	  temp[2] = SubByte (word[3][j - 1]);
	  temp[3] = SubByte (word[0][j - 1]);
#endif /* DWARV */
	}
      if ((j % nk) != 0)
	{
#ifdef DWARV
	  temp[0] = word[j - 1 + 120 * (0)];
	  temp[1] = word[j - 1 + 120 * (1)];
	  temp[2] = word[j - 1 + 120 * (2)];
	  temp[3] = word[j - 1 + 120 * (3)];
#else
	  temp[0] = word[0][j - 1];
	  temp[1] = word[1][j - 1];
	  temp[2] = word[2][j - 1];
	  temp[3] = word[3][j - 1];
#endif /* DWARV */
	}
      if (nk > 6 && j % nk == 4)
	for (i = 0; i < 4; ++i)
#ifdef DWARV
          //#pragma map call_hw VIRTEX5 0
          temp[i] = SubByte (temp[i], Sbox);
#else
	  temp[i] = SubByte (temp[i]);
#endif /* DWARV */
      for (i = 0; i < 4; ++i)
#ifdef DWARV
	word[j + 120 * (i)] = word[j - nk + 120 * (i)] ^ temp[i];
#else
	word[i][j] = word[i][j - nk] ^ temp[i];
#endif /* DWARV */
    }
  return 0;
}

/*
+--------------------------------------------------------------------------+
| CHStone : a suite of benchmark programs for C-based High-Level Synthesis |
| ======================================================================== |
|                                                                          |
| * Collected and Modified : Y. Hara, H. Tomiyama, S. Honda,               |
|                            H. Takada and K. Ishii                        |
|                            Nagoya University, Japan                      |
|                                                                          |
| * Remark :                                                               |
|    1. This source code is modified to unify the formats of the benchmark |
|       programs in CHStone.                                               |
|    2. Test vectors are added for CHStone.                                |
|    3. If "main_result" is 0 at the end of the program, the program is    |
|       correctly executed.                                                |
|    4. Please follow the copyright of each benchmark program.             |
+--------------------------------------------------------------------------+
*/
/* aes_function.c */
/*
 * Copyright (C) 2005
 * Akira Iwata & Masayuki Sato
 * Akira Iwata Laboratory,
 * Nagoya Institute of Technology in Japan.
 *
 * All rights reserved.
 *
 * This software is written by Masayuki Sato.
 * And if you want to contact us, send an email to Kimitake Wakayama
 * (wakayama@elcom.nitech.ac.jp)
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. All advertising materials mentioning features or use of this software must
 *    display the following acknowledgment:
 *    "This product includes software developed by Akira Iwata Laboratory,
 *    Nagoya Institute of Technology in Japan (http://mars.elcom.nitech.ac.jp/)."
 *
 * 4. Redistributions of any form whatsoever must retain the following
 *    acknowledgment:
 *    "This product includes software developed by Akira Iwata Laboratory,
 *     Nagoya Institute of Technology in Japan (http://mars.elcom.nitech.ac.jp/)."
 *
 *   THIS SOFTWARE IS PROVIDED "AS IS" WITHOUT EXPRESS OR IMPLIED WARRANTY.
 *   AKIRA IWATA LABORATORY DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS
 *   SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS,
 *   IN NO EVENT SHALL AKIRA IWATA LABORATORY BE LIABLE FOR ANY SPECIAL,
 *   INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING
 *   FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
 *   NEGLIGENCE OR OTHER TORTUOUS ACTION, ARISING OUT OF OR IN CONNECTION
 *   WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */
const int Sbox[16][16] = {
  {0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b,
   0xfe, 0xd7, 0xab, 0x76},
  {0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf,
   0x9c, 0xa4, 0x72, 0xc0},
  {0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1,
   0x71, 0xd8, 0x31, 0x15},
  {0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2,
   0xeb, 0x27, 0xb2, 0x75},
  {0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3,
   0x29, 0xe3, 0x2f, 0x84},
  {0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39,
   0x4a, 0x4c, 0x58, 0xcf},
  {0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f,
   0x50, 0x3c, 0x9f, 0xa8},
  {0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21,
   0x10, 0xff, 0xf3, 0xd2},
  {0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d,
   0x64, 0x5d, 0x19, 0x73},
  {0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14,
   0xde, 0x5e, 0x0b, 0xdb},
  {0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62,
   0x91, 0x95, 0xe4, 0x79},
  {0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea,
   0x65, 0x7a, 0xae, 0x08},
  {0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f,
   0x4b, 0xbd, 0x8b, 0x8a},
  {0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9,
   0x86, 0xc1, 0x1d, 0x9e},
  {0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9,
   0xce, 0x55, 0x28, 0xdf},
  {0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f,
   0xb0, 0x54, 0xbb, 0x16}
};
const int invSbox[16][16] = {
  {0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e,
   0x81, 0xf3, 0xd7, 0xfb},
  {0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44,
   0xc4, 0xde, 0xe9, 0xcb},
  {0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b,
   0x42, 0xfa, 0xc3, 0x4e},
  {0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49,
   0x6d, 0x8b, 0xd1, 0x25},
  {0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc,
   0x5d, 0x65, 0xb6, 0x92},
  {0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57,
   0xa7, 0x8d, 0x9d, 0x84},
  {0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05,
   0xb8, 0xb3, 0x45, 0x06},
  {0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03,
   0x01, 0x13, 0x8a, 0x6b},
  {0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce,
   0xf0, 0xb4, 0xe6, 0x73},
  {0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8,
   0x1c, 0x75, 0xdf, 0x6e},
  {0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e,
   0xaa, 0x18, 0xbe, 0x1b},
  {0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe,
   0x78, 0xcd, 0x5a, 0xf4},
  {0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59,
   0x27, 0x80, 0xec, 0x5f},
  {0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f,
   0x93, 0xc9, 0x9c, 0xef},
  {0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c,
   0x83, 0x53, 0x99, 0x61},
  {0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63,
   0x55, 0x21, 0x0c, 0x7d}
};

/* ********* ByteSub & ShiftRow ********* */
void
#ifdef DWARV
ByteSub_ShiftRow (int statemt[32], int nb, int *Sbox)
#else
ByteSub_ShiftRow (int statemt[32], int nb)
#endif /* DWARV */
{
  int temp;

  switch (nb)
    {
    case 4:
#ifdef DWARV
      temp = Sbox[(statemt[1] & 0xf) + 16 * (statemt[1] >> 4)];
      statemt[1] = Sbox[(statemt[5] & 0xf) + 16 * (statemt[5] >> 4)];
      statemt[5] = Sbox[(statemt[9] & 0xf) + 16 * (statemt[9] >> 4)];
      statemt[9] = Sbox[(statemt[13] & 0xf) + 16 * (statemt[13] >> 4)];
      statemt[13] = temp;

      temp = Sbox[(statemt[2] & 0xf) + 16 * (statemt[2] >> 4)];
      statemt[2] = Sbox[(statemt[10] & 0xf) + 16 * (statemt[10] >> 4)];
      statemt[10] = temp;
      temp = Sbox[(statemt[6] & 0xf) + 16 * (statemt[6] >> 4)];
      statemt[6] = Sbox[(statemt[14] & 0xf) + 16 * (statemt[14] >> 4)];
      statemt[14] = temp;

      temp = Sbox[(statemt[3] & 0xf) + 16 * (statemt[3] >> 4)];
      statemt[3] = Sbox[(statemt[15] & 0xf) + 16 * (statemt[15] >> 4)];
      statemt[15] = Sbox[(statemt[11] & 0xf) + 16 * (statemt[11] >> 4)];
      statemt[11] = Sbox[(statemt[7] & 0xf) + 16 * (statemt[7] >> 4)];
      statemt[7] = temp;

      statemt[0] = Sbox[(statemt[0] & 0xf) + 16 * (statemt[0] >> 4)];
      statemt[4] = Sbox[(statemt[4] & 0xf) + 16 * (statemt[4] >> 4)];
      statemt[8] = Sbox[(statemt[8] & 0xf) + 16 * (statemt[8] >> 4)];
      statemt[12] = Sbox[(statemt[12] & 0xf) + 16 * (statemt[12] >> 4)];
#else
      temp = Sbox[statemt[1] >> 4][statemt[1] & 0xf];
      statemt[1] = Sbox[statemt[5] >> 4][statemt[5] & 0xf];
      statemt[5] = Sbox[statemt[9] >> 4][statemt[9] & 0xf];
      statemt[9] = Sbox[statemt[13] >> 4][statemt[13] & 0xf];
      statemt[13] = temp;

      temp = Sbox[statemt[2] >> 4][statemt[2] & 0xf];
      statemt[2] = Sbox[statemt[10] >> 4][statemt[10] & 0xf];
      statemt[10] = temp;
      temp = Sbox[statemt[6] >> 4][statemt[6] & 0xf];
      statemt[6] = Sbox[statemt[14] >> 4][statemt[14] & 0xf];
      statemt[14] = temp;

      temp = Sbox[statemt[3] >> 4][statemt[3] & 0xf];
      statemt[3] = Sbox[statemt[15] >> 4][statemt[15] & 0xf];
      statemt[15] = Sbox[statemt[11] >> 4][statemt[11] & 0xf];
      statemt[11] = Sbox[statemt[7] >> 4][statemt[7] & 0xf];
      statemt[7] = temp;

      statemt[0] = Sbox[statemt[0] >> 4][statemt[0] & 0xf];
      statemt[4] = Sbox[statemt[4] >> 4][statemt[4] & 0xf];
      statemt[8] = Sbox[statemt[8] >> 4][statemt[8] & 0xf];
      statemt[12] = Sbox[statemt[12] >> 4][statemt[12] & 0xf];
#endif /* DWARV */
      break;
    case 6:
#ifdef DWARV
      temp = Sbox[(statemt[1] & 0xf) + 16 * (statemt[1] >> 4)];
      statemt[1] = Sbox[(statemt[5] & 0xf) + 16 * (statemt[5] >> 4)];
      statemt[5] = Sbox[(statemt[9] & 0xf) + 16 * (statemt[9] >> 4)];
      statemt[9] = Sbox[(statemt[13] & 0xf) + 16 * (statemt[13] >> 4)];
      statemt[13] = Sbox[(statemt[17] & 0xf) + 16 * (statemt[17] >> 4)];
      statemt[17] = Sbox[(statemt[21] & 0xf) + 16 * (statemt[21] >> 4)];
      statemt[21] = temp;

      temp = Sbox[(statemt[2] & 0xf) + 16 * (statemt[2] >> 4)];
      statemt[2] = Sbox[(statemt[10] & 0xf) + 16 * (statemt[10] >> 4)];
      statemt[10] = Sbox[(statemt[18] & 0xf) + 16 * (statemt[18] >> 4)];
      statemt[18] = temp;
      temp = Sbox[(statemt[6] & 0xf) + 16 * (statemt[6] >> 4)];
      statemt[6] = Sbox[(statemt[14] & 0xf) + 16 * (statemt[14] >> 4)];
      statemt[14] = Sbox[(statemt[22] & 0xf) + 16 * (statemt[22] >> 4)];
      statemt[22] = temp;

      temp = Sbox[(statemt[3] & 0xf) + 16 * (statemt[3] >> 4)];
      statemt[3] = Sbox[(statemt[15] & 0xf) + 16 * (statemt[15] >> 4)];
      statemt[15] = temp;
      temp = Sbox[(statemt[7] & 0xf) + 16 * (statemt[7] >> 4)];
      statemt[7] = Sbox[(statemt[19] & 0xf) + 16 * (statemt[19] >> 4)];
      statemt[19] = temp;
      temp = Sbox[(statemt[11] & 0xf) + 16 * (statemt[11] >> 4)];
      statemt[11] = Sbox[(statemt[23] & 0xf) + 16 * (statemt[23] >> 4)];
      statemt[23] = temp;

      statemt[0] = Sbox[(statemt[0] & 0xf) + 16 * (statemt[0] >> 4)];
      statemt[4] = Sbox[(statemt[4] & 0xf) + 16 * (statemt[4] >> 4)];
      statemt[8] = Sbox[(statemt[8] & 0xf) + 16 * (statemt[8] >> 4)];
      statemt[12] = Sbox[(statemt[12] & 0xf) + 16 * (statemt[12] >> 4)];
      statemt[16] = Sbox[(statemt[16] & 0xf) + 16 * (statemt[16] >> 4)];
      statemt[20] = Sbox[(statemt[20] & 0xf) + 16 * (statemt[20] >> 4)];
#else
      temp = Sbox[statemt[1] >> 4][statemt[1] & 0xf];
      statemt[1] = Sbox[statemt[5] >> 4][statemt[5] & 0xf];
      statemt[5] = Sbox[statemt[9] >> 4][statemt[9] & 0xf];
      statemt[9] = Sbox[statemt[13] >> 4][statemt[13] & 0xf];
      statemt[13] = Sbox[statemt[17] >> 4][statemt[17] & 0xf];
      statemt[17] = Sbox[statemt[21] >> 4][statemt[21] & 0xf];
      statemt[21] = temp;

      temp = Sbox[statemt[2] >> 4][statemt[2] & 0xf];
      statemt[2] = Sbox[statemt[10] >> 4][statemt[10] & 0xf];
      statemt[10] = Sbox[statemt[18] >> 4][statemt[18] & 0xf];
      statemt[18] = temp;
      temp = Sbox[statemt[6] >> 4][statemt[6] & 0xf];
      statemt[6] = Sbox[statemt[14] >> 4][statemt[14] & 0xf];
      statemt[14] = Sbox[statemt[22] >> 4][statemt[22] & 0xf];
      statemt[22] = temp;

      temp = Sbox[statemt[3] >> 4][statemt[3] & 0xf];
      statemt[3] = Sbox[statemt[15] >> 4][statemt[15] & 0xf];
      statemt[15] = temp;
      temp = Sbox[statemt[7] >> 4][statemt[7] & 0xf];
      statemt[7] = Sbox[statemt[19] >> 4][statemt[19] & 0xf];
      statemt[19] = temp;
      temp = Sbox[statemt[11] >> 4][statemt[11] & 0xf];
      statemt[11] = Sbox[statemt[23] >> 4][statemt[23] & 0xf];
      statemt[23] = temp;

      statemt[0] = Sbox[statemt[0] >> 4][statemt[0] & 0xf];
      statemt[4] = Sbox[statemt[4] >> 4][statemt[4] & 0xf];
      statemt[8] = Sbox[statemt[8] >> 4][statemt[8] & 0xf];
      statemt[12] = Sbox[statemt[12] >> 4][statemt[12] & 0xf];
      statemt[16] = Sbox[statemt[16] >> 4][statemt[16] & 0xf];
      statemt[20] = Sbox[statemt[20] >> 4][statemt[20] & 0xf];
#endif /* DWARV */
      break;
    case 8:
#ifdef DWARV
      temp = Sbox[(statemt[1] & 0xf) + 16 * (statemt[1] >> 4)];
      statemt[1] = Sbox[(statemt[5] & 0xf) + 16 * (statemt[5] >> 4)];
      statemt[5] = Sbox[(statemt[9] & 0xf) + 16 * (statemt[9] >> 4)];
      statemt[9] = Sbox[(statemt[13] & 0xf) + 16 * (statemt[13] >> 4)];
      statemt[13] = Sbox[(statemt[17] & 0xf) + 16 * (statemt[17] >> 4)];
      statemt[17] = Sbox[(statemt[21] & 0xf) + 16 * (statemt[21] >> 4)];
      statemt[21] = Sbox[(statemt[25] & 0xf) + 16 * (statemt[25] >> 4)];
      statemt[25] = Sbox[(statemt[29] & 0xf) + 16 * (statemt[29] >> 4)];
      statemt[29] = temp;

      temp = Sbox[(statemt[2] & 0xf) + 16 * (statemt[2] >> 4)];
      statemt[2] = Sbox[(statemt[14] & 0xf) + 16 * (statemt[14] >> 4)];
      statemt[14] = Sbox[(statemt[26] & 0xf) + 16 * (statemt[26] >> 4)];
      statemt[26] = Sbox[(statemt[6] & 0xf) + 16 * (statemt[6] >> 4)];
      statemt[6] = Sbox[(statemt[18] & 0xf) + 16 * (statemt[18] >> 4)];
      statemt[18] = Sbox[(statemt[30] & 0xf) + 16 * (statemt[30] >> 4)];
      statemt[30] = Sbox[(statemt[10] & 0xf) + 16 * (statemt[10] >> 4)];
      statemt[10] = Sbox[(statemt[22] & 0xf) + 16 * (statemt[22] >> 4)];
      statemt[22] = temp;

      temp = Sbox[(statemt[3] & 0xf) + 16 * (statemt[3] >> 4)];
      statemt[3] = Sbox[(statemt[19] & 0xf) + 16 * (statemt[19] >> 4)];
      statemt[19] = temp;
      temp = Sbox[(statemt[7] & 0xf) + 16 * (statemt[7] >> 4)];
      statemt[7] = Sbox[(statemt[23] & 0xf) + 16 * (statemt[23] >> 4)];
      statemt[23] = temp;
      temp = Sbox[(statemt[11] & 0xf) + 16 * (statemt[11] >> 4)];
      statemt[11] = Sbox[(statemt[27] & 0xf) + 16 * (statemt[27] >> 4)];
      statemt[27] = temp;
      temp = Sbox[(statemt[15] & 0xf) + 16 * (statemt[15] >> 4)];
      statemt[15] = Sbox[(statemt[31] & 0xf) + 16 * (statemt[31] >> 4)];
      statemt[31] = temp;

      statemt[0] = Sbox[(statemt[0] & 0xf) + 16 * (statemt[0] >> 4)];
      statemt[4] = Sbox[(statemt[4] & 0xf) + 16 * (statemt[4] >> 4)];
      statemt[8] = Sbox[(statemt[8] & 0xf) + 16 * (statemt[8] >> 4)];
      statemt[12] = Sbox[(statemt[12] & 0xf) + 16 * (statemt[12] >> 4)];
      statemt[16] = Sbox[(statemt[16] & 0xf) + 16 * (statemt[16] >> 4)];
      statemt[20] = Sbox[(statemt[20] & 0xf) + 16 * (statemt[20] >> 4)];
      statemt[24] = Sbox[(statemt[24] & 0xf) + 16 * (statemt[24] >> 4)];
      statemt[28] = Sbox[(statemt[28] & 0xf) + 16 * (statemt[28] >> 4)];
#else
      temp = Sbox[statemt[1] >> 4][statemt[1] & 0xf];
      statemt[1] = Sbox[statemt[5] >> 4][statemt[5] & 0xf];
      statemt[5] = Sbox[statemt[9] >> 4][statemt[9] & 0xf];
      statemt[9] = Sbox[statemt[13] >> 4][statemt[13] & 0xf];
      statemt[13] = Sbox[statemt[17] >> 4][statemt[17] & 0xf];
      statemt[17] = Sbox[statemt[21] >> 4][statemt[21] & 0xf];
      statemt[21] = Sbox[statemt[25] >> 4][statemt[25] & 0xf];
      statemt[25] = Sbox[statemt[29] >> 4][statemt[29] & 0xf];
      statemt[29] = temp;

      temp = Sbox[statemt[2] >> 4][statemt[2] & 0xf];
      statemt[2] = Sbox[statemt[14] >> 4][statemt[14] & 0xf];
      statemt[14] = Sbox[statemt[26] >> 4][statemt[26] & 0xf];
      statemt[26] = Sbox[statemt[6] >> 4][statemt[6] & 0xf];
      statemt[6] = Sbox[statemt[18] >> 4][statemt[18] & 0xf];
      statemt[18] = Sbox[statemt[30] >> 4][statemt[30] & 0xf];
      statemt[30] = Sbox[statemt[10] >> 4][statemt[10] & 0xf];
      statemt[10] = Sbox[statemt[22] >> 4][statemt[22] & 0xf];
      statemt[22] = temp;

      temp = Sbox[statemt[3] >> 4][statemt[3] & 0xf];
      statemt[3] = Sbox[statemt[19] >> 4][statemt[19] & 0xf];
      statemt[19] = temp;
      temp = Sbox[statemt[7] >> 4][statemt[7] & 0xf];
      statemt[7] = Sbox[statemt[23] >> 4][statemt[23] & 0xf];
      statemt[23] = temp;
      temp = Sbox[statemt[11] >> 4][statemt[11] & 0xf];
      statemt[11] = Sbox[statemt[27] >> 4][statemt[27] & 0xf];
      statemt[27] = temp;
      temp = Sbox[statemt[15] >> 4][statemt[15] & 0xf];
      statemt[15] = Sbox[statemt[31] >> 4][statemt[31] & 0xf];
      statemt[31] = temp;

      statemt[0] = Sbox[statemt[0] >> 4][statemt[0] & 0xf];
      statemt[4] = Sbox[statemt[4] >> 4][statemt[4] & 0xf];
      statemt[8] = Sbox[statemt[8] >> 4][statemt[8] & 0xf];
      statemt[12] = Sbox[statemt[12] >> 4][statemt[12] & 0xf];
      statemt[16] = Sbox[statemt[16] >> 4][statemt[16] & 0xf];
      statemt[20] = Sbox[statemt[20] >> 4][statemt[20] & 0xf];
      statemt[24] = Sbox[statemt[24] >> 4][statemt[24] & 0xf];
      statemt[28] = Sbox[statemt[28] >> 4][statemt[28] & 0xf];
#endif /* DWARV */
      break;
    }
}

int
#ifdef DWARV
SubByte (int in, int *Sbox)
{
  return 0;//Sbox[((in % 16)) + 16 * ((in / 16))];
}
#else
SubByte (int in)
{
  return Sbox[(in / 16)][(in % 16)];
}
#endif /* DWARV */

/* ********* InversShiftRow & ByteSub ********* */
void
#ifdef DWARV
InversShiftRow_ByteSub (int statemt[32], int nb, int *invSbox)
#else
InversShiftRow_ByteSub (int statemt[32], int nb)
#endif /* DWARV */
{
  int temp;

  switch (nb)
    {
    case 4:
#ifdef DWARV
      temp = invSbox[(statemt[13] & 0xf) + 16 * (statemt[13] >> 4)];
      statemt[13] = invSbox[(statemt[9] & 0xf) + 16 * (statemt[9] >> 4)];
      statemt[9] = invSbox[(statemt[5] & 0xf) + 16 * (statemt[5] >> 4)];
      statemt[5] = invSbox[(statemt[1] & 0xf) + 16 * (statemt[1] >> 4)];
      statemt[1] = temp;

      temp = invSbox[(statemt[14] & 0xf) + 16 * (statemt[14] >> 4)];
      statemt[14] = invSbox[(statemt[6] & 0xf) + 16 * (statemt[6] >> 4)];
      statemt[6] = temp;
      temp = invSbox[(statemt[2] & 0xf) + 16 * (statemt[2] >> 4)];
      statemt[2] = invSbox[(statemt[10] & 0xf) + 16 * (statemt[10] >> 4)];
      statemt[10] = temp;

      temp = invSbox[(statemt[15] & 0xf) + 16 * (statemt[15] >> 4)];
      statemt[15] = invSbox[(statemt[3] & 0xf) + 16 * (statemt[3] >> 4)];
      statemt[3] = invSbox[(statemt[7] & 0xf) + 16 * (statemt[7] >> 4)];
      statemt[7] = invSbox[(statemt[11] & 0xf) + 16 * (statemt[11] >> 4)];
      statemt[11] = temp;

      statemt[0] = invSbox[(statemt[0] & 0xf) + 16 * (statemt[0] >> 4)];
      statemt[4] = invSbox[(statemt[4] & 0xf) + 16 * (statemt[4] >> 4)];
      statemt[8] = invSbox[(statemt[8] & 0xf) + 16 * (statemt[8] >> 4)];
      statemt[12] = invSbox[(statemt[12] & 0xf) + 16 * (statemt[12] >> 4)];
#else
      temp = invSbox[statemt[13] >> 4][statemt[13] & 0xf];
      statemt[13] = invSbox[statemt[9] >> 4][statemt[9] & 0xf];
      statemt[9] = invSbox[statemt[5] >> 4][statemt[5] & 0xf];
      statemt[5] = invSbox[statemt[1] >> 4][statemt[1] & 0xf];
      statemt[1] = temp;

      temp = invSbox[statemt[14] >> 4][statemt[14] & 0xf];
      statemt[14] = invSbox[statemt[6] >> 4][statemt[6] & 0xf];
      statemt[6] = temp;
      temp = invSbox[statemt[2] >> 4][statemt[2] & 0xf];
      statemt[2] = invSbox[statemt[10] >> 4][statemt[10] & 0xf];
      statemt[10] = temp;

      temp = invSbox[statemt[15] >> 4][statemt[15] & 0xf];
      statemt[15] = invSbox[statemt[3] >> 4][statemt[3] & 0xf];
      statemt[3] = invSbox[statemt[7] >> 4][statemt[7] & 0xf];
      statemt[7] = invSbox[statemt[11] >> 4][statemt[11] & 0xf];
      statemt[11] = temp;

      statemt[0] = invSbox[statemt[0] >> 4][statemt[0] & 0xf];
      statemt[4] = invSbox[statemt[4] >> 4][statemt[4] & 0xf];
      statemt[8] = invSbox[statemt[8] >> 4][statemt[8] & 0xf];
      statemt[12] = invSbox[statemt[12] >> 4][statemt[12] & 0xf];
#endif /* DWARV */
      break;
    case 6:
#ifdef DWARV
      temp = invSbox[(statemt[21] & 0xf) + 16 * (statemt[21] >> 4)];
      statemt[21] = invSbox[(statemt[17] & 0xf) + 16 * (statemt[17] >> 4)];
      statemt[17] = invSbox[(statemt[13] & 0xf) + 16 * (statemt[13] >> 4)];
      statemt[13] = invSbox[(statemt[9] & 0xf) + 16 * (statemt[9] >> 4)];
      statemt[9] = invSbox[(statemt[5] & 0xf) + 16 * (statemt[5] >> 4)];
      statemt[5] = invSbox[(statemt[1] & 0xf) + 16 * (statemt[1] >> 4)];
      statemt[1] = temp;

      temp = invSbox[(statemt[22] & 0xf) + 16 * (statemt[22] >> 4)];
      statemt[22] = invSbox[(statemt[14] & 0xf) + 16 * (statemt[14] >> 4)];
      statemt[14] = invSbox[(statemt[6] & 0xf) + 16 * (statemt[6] >> 4)];
      statemt[6] = temp;
      temp = invSbox[(statemt[18] & 0xf) + 16 * (statemt[18] >> 4)];
      statemt[18] = invSbox[(statemt[10] & 0xf) + 16 * (statemt[10] >> 4)];
      statemt[10] = invSbox[(statemt[2] & 0xf) + 16 * (statemt[2] >> 4)];
      statemt[2] = temp;

      temp = invSbox[(statemt[15] & 0xf) + 16 * (statemt[15] >> 4)];
      statemt[15] = invSbox[(statemt[3] & 0xf) + 16 * (statemt[3] >> 4)];
      statemt[3] = temp;
      temp = invSbox[(statemt[19] & 0xf) + 16 * (statemt[19] >> 4)];
      statemt[19] = invSbox[(statemt[7] & 0xf) + 16 * (statemt[7] >> 4)];
      statemt[7] = temp;
      temp = invSbox[(statemt[23] & 0xf) + 16 * (statemt[23] >> 4)];
      statemt[23] = invSbox[(statemt[11] & 0xf) + 16 * (statemt[11] >> 4)];
      statemt[11] = temp;

      statemt[0] = invSbox[(statemt[0] & 0xf) + 16 * (statemt[0] >> 4)];
      statemt[4] = invSbox[(statemt[4] & 0xf) + 16 * (statemt[4] >> 4)];
      statemt[8] = invSbox[(statemt[8] & 0xf) + 16 * (statemt[8] >> 4)];
      statemt[12] = invSbox[(statemt[12] & 0xf) + 16 * (statemt[12] >> 4)];
      statemt[16] = invSbox[(statemt[16] & 0xf) + 16 * (statemt[16] >> 4)];
      statemt[20] = invSbox[(statemt[20] & 0xf) + 16 * (statemt[20] >> 4)];
#else
      temp = invSbox[statemt[21] >> 4][statemt[21] & 0xf];
      statemt[21] = invSbox[statemt[17] >> 4][statemt[17] & 0xf];
      statemt[17] = invSbox[statemt[13] >> 4][statemt[13] & 0xf];
      statemt[13] = invSbox[statemt[9] >> 4][statemt[9] & 0xf];
      statemt[9] = invSbox[statemt[5] >> 4][statemt[5] & 0xf];
      statemt[5] = invSbox[statemt[1] >> 4][statemt[1] & 0xf];
      statemt[1] = temp;

      temp = invSbox[statemt[22] >> 4][statemt[22] & 0xf];
      statemt[22] = invSbox[statemt[14] >> 4][statemt[14] & 0xf];
      statemt[14] = invSbox[statemt[6] >> 4][statemt[6] & 0xf];
      statemt[6] = temp;
      temp = invSbox[statemt[18] >> 4][statemt[18] & 0xf];
      statemt[18] = invSbox[statemt[10] >> 4][statemt[10] & 0xf];
      statemt[10] = invSbox[statemt[2] >> 4][statemt[2] & 0xf];
      statemt[2] = temp;

      temp = invSbox[statemt[15] >> 4][statemt[15] & 0xf];
      statemt[15] = invSbox[statemt[3] >> 4][statemt[3] & 0xf];
      statemt[3] = temp;
      temp = invSbox[statemt[19] >> 4][statemt[19] & 0xf];
      statemt[19] = invSbox[statemt[7] >> 4][statemt[7] & 0xf];
      statemt[7] = temp;
      temp = invSbox[statemt[23] >> 4][statemt[23] & 0xf];
      statemt[23] = invSbox[statemt[11] >> 4][statemt[11] & 0xf];
      statemt[11] = temp;

      statemt[0] = invSbox[statemt[0] >> 4][statemt[0] & 0xf];
      statemt[4] = invSbox[statemt[4] >> 4][statemt[4] & 0xf];
      statemt[8] = invSbox[statemt[8] >> 4][statemt[8] & 0xf];
      statemt[12] = invSbox[statemt[12] >> 4][statemt[12] & 0xf];
      statemt[16] = invSbox[statemt[16] >> 4][statemt[16] & 0xf];
      statemt[20] = invSbox[statemt[20] >> 4][statemt[20] & 0xf];
#endif /* DWARV */
      break;
    case 8:
#ifdef DWARV
      temp = invSbox[(statemt[29] & 0xf) + 16 * (statemt[29] >> 4)];
      statemt[29] = invSbox[(statemt[25] & 0xf) + 16 * (statemt[25] >> 4)];
      statemt[25] = invSbox[(statemt[21] & 0xf) + 16 * (statemt[21] >> 4)];
      statemt[21] = invSbox[(statemt[17] & 0xf) + 16 * (statemt[17] >> 4)];
      statemt[17] = invSbox[(statemt[13] & 0xf) + 16 * (statemt[13] >> 4)];
      statemt[13] = invSbox[(statemt[9] & 0xf) + 16 * (statemt[9] >> 4)];
      statemt[9] = invSbox[(statemt[5] & 0xf) + 16 * (statemt[5] >> 4)];
      statemt[5] = invSbox[(statemt[1] & 0xf) + 16 * (statemt[1] >> 4)];
      statemt[1] = temp;

      temp = invSbox[(statemt[30] & 0xf) + 16 * (statemt[30] >> 4)];
      statemt[30] = invSbox[(statemt[18] & 0xf) + 16 * (statemt[18] >> 4)];
      statemt[18] = invSbox[(statemt[6] & 0xf) + 16 * (statemt[6] >> 4)];
      statemt[6] = invSbox[(statemt[26] & 0xf) + 16 * (statemt[26] >> 4)];
      statemt[26] = invSbox[(statemt[14] & 0xf) + 16 * (statemt[14] >> 4)];
      statemt[14] = invSbox[(statemt[2] & 0xf) + 16 * (statemt[2] >> 4)];
      statemt[2] = invSbox[(statemt[22] & 0xf) + 16 * (statemt[22] >> 4)];
      statemt[22] = invSbox[(statemt[10] & 0xf) + 16 * (statemt[10] >> 4)];
      statemt[10] = temp;

      temp = invSbox[(statemt[31] & 0xf) + 16 * (statemt[31] >> 4)];
      statemt[31] = invSbox[(statemt[15] & 0xf) + 16 * (statemt[15] >> 4)];
      statemt[15] = temp;
      temp = invSbox[(statemt[27] & 0xf) + 16 * (statemt[27] >> 4)];
      statemt[27] = invSbox[(statemt[11] & 0xf) + 16 * (statemt[11] >> 4)];
      statemt[11] = temp;
      temp = invSbox[(statemt[23] & 0xf) + 16 * (statemt[23] >> 4)];
      statemt[23] = invSbox[(statemt[7] & 0xf) + 16 * (statemt[7] >> 4)];
      statemt[7] = temp;
      temp = invSbox[(statemt[19] & 0xf) + 16 * (statemt[19] >> 4)];
      statemt[19] = invSbox[(statemt[3] & 0xf) + 16 * (statemt[3] >> 4)];
      statemt[3] = temp;

      statemt[0] = invSbox[(statemt[0] & 0xf) + 16 * (statemt[0] >> 4)];
      statemt[4] = invSbox[(statemt[4] & 0xf) + 16 * (statemt[4] >> 4)];
      statemt[8] = invSbox[(statemt[8] & 0xf) + 16 * (statemt[8] >> 4)];
      statemt[12] = invSbox[(statemt[12] & 0xf) + 16 * (statemt[12] >> 4)];
      statemt[16] = invSbox[(statemt[16] & 0xf) + 16 * (statemt[16] >> 4)];
      statemt[20] = invSbox[(statemt[20] & 0xf) + 16 * (statemt[20] >> 4)];
      statemt[24] = invSbox[(statemt[24] & 0xf) + 16 * (statemt[24] >> 4)];
      statemt[28] = invSbox[(statemt[28] & 0xf) + 16 * (statemt[28] >> 4)];
#else
      temp = invSbox[statemt[29] >> 4][statemt[29] & 0xf];
      statemt[29] = invSbox[statemt[25] >> 4][statemt[25] & 0xf];
      statemt[25] = invSbox[statemt[21] >> 4][statemt[21] & 0xf];
      statemt[21] = invSbox[statemt[17] >> 4][statemt[17] & 0xf];
      statemt[17] = invSbox[statemt[13] >> 4][statemt[13] & 0xf];
      statemt[13] = invSbox[statemt[9] >> 4][statemt[9] & 0xf];
      statemt[9] = invSbox[statemt[5] >> 4][statemt[5] & 0xf];
      statemt[5] = invSbox[statemt[1] >> 4][statemt[1] & 0xf];
      statemt[1] = temp;

      temp = invSbox[statemt[30] >> 4][statemt[30] & 0xf];
      statemt[30] = invSbox[statemt[18] >> 4][statemt[18] & 0xf];
      statemt[18] = invSbox[statemt[6] >> 4][statemt[6] & 0xf];
      statemt[6] = invSbox[statemt[26] >> 4][statemt[26] & 0xf];
      statemt[26] = invSbox[statemt[14] >> 4][statemt[14] & 0xf];
      statemt[14] = invSbox[statemt[2] >> 4][statemt[2] & 0xf];
      statemt[2] = invSbox[statemt[22] >> 4][statemt[22] & 0xf];
      statemt[22] = invSbox[statemt[10] >> 4][statemt[10] & 0xf];
      statemt[10] = temp;

      temp = invSbox[statemt[31] >> 4][statemt[31] & 0xf];
      statemt[31] = invSbox[statemt[15] >> 4][statemt[15] & 0xf];
      statemt[15] = temp;
      temp = invSbox[statemt[27] >> 4][statemt[27] & 0xf];
      statemt[27] = invSbox[statemt[11] >> 4][statemt[11] & 0xf];
      statemt[11] = temp;
      temp = invSbox[statemt[23] >> 4][statemt[23] & 0xf];
      statemt[23] = invSbox[statemt[7] >> 4][statemt[7] & 0xf];
      statemt[7] = temp;
      temp = invSbox[statemt[19] >> 4][statemt[19] & 0xf];
      statemt[19] = invSbox[statemt[3] >> 4][statemt[3] & 0xf];
      statemt[3] = temp;

      statemt[0] = invSbox[statemt[0] >> 4][statemt[0] & 0xf];
      statemt[4] = invSbox[statemt[4] >> 4][statemt[4] & 0xf];
      statemt[8] = invSbox[statemt[8] >> 4][statemt[8] & 0xf];
      statemt[12] = invSbox[statemt[12] >> 4][statemt[12] & 0xf];
      statemt[16] = invSbox[statemt[16] >> 4][statemt[16] & 0xf];
      statemt[20] = invSbox[statemt[20] >> 4][statemt[20] & 0xf];
      statemt[24] = invSbox[statemt[24] >> 4][statemt[24] & 0xf];
      statemt[28] = invSbox[statemt[28] >> 4][statemt[28] & 0xf];
#endif /* DWARV */
      break;
    }
}

/* ******** MixColumn ********** */
int
#ifdef DWARV
MixColumn_AddRoundKey (int statemt[32], int nb, int n, int *word)
#else
MixColumn_AddRoundKey (int statemt[32], int nb, int n)
#endif /* DWARV */
{
  int ret[8 * 4], j;
  register int x;

  for (j = 0; j < nb; ++j)
    {
      ret[j * 4] = (statemt[j * 4] << 1);
      if ((ret[j * 4] >> 8) == 1)
	ret[j * 4] ^= 283;
      x = statemt[1 + j * 4];
      x ^= (x << 1);
      if ((x >> 8) == 1)
	ret[j * 4] ^= (x ^ 283);
      else
	ret[j * 4] ^= x;
      ret[j * 4] ^=
#ifdef DWARV
	statemt[2 + j * 4] ^ statemt[3 + j * 4] ^ word[j + nb * n + 120 * (0)];
#else
	statemt[2 + j * 4] ^ statemt[3 + j * 4] ^ word[0][j + nb * n];
#endif /* DWARV */

      ret[1 + j * 4] = (statemt[1 + j * 4] << 1);
      if ((ret[1 + j * 4] >> 8) == 1)
	ret[1 + j * 4] ^= 283;
      x = statemt[2 + j * 4];
      x ^= (x << 1);
      if ((x >> 8) == 1)
	ret[1 + j * 4] ^= (x ^ 283);
      else
	ret[1 + j * 4] ^= x;
      ret[1 + j * 4] ^=
#ifdef DWARV
	statemt[3 + j * 4] ^ statemt[j * 4] ^ word[j + nb * n + 120 * (1)];
#else
	statemt[3 + j * 4] ^ statemt[j * 4] ^ word[1][j + nb * n];
#endif /* DWARV */

      ret[2 + j * 4] = (statemt[2 + j * 4] << 1);
      if ((ret[2 + j * 4] >> 8) == 1)
	ret[2 + j * 4] ^= 283;
      x = statemt[3 + j * 4];
      x ^= (x << 1);
      if ((x >> 8) == 1)
	ret[2 + j * 4] ^= (x ^ 283);
      else
	ret[2 + j * 4] ^= x;
      ret[2 + j * 4] ^=
#ifdef DWARV
	statemt[j * 4] ^ statemt[1 + j * 4] ^ word[j + nb * n + 120 * (2)];
#else
	statemt[j * 4] ^ statemt[1 + j * 4] ^ word[2][j + nb * n];
#endif /* DWARV */

      ret[3 + j * 4] = (statemt[3 + j * 4] << 1);
      if ((ret[3 + j * 4] >> 8) == 1)
	ret[3 + j * 4] ^= 283;
      x = statemt[j * 4];
      x ^= (x << 1);
      if ((x >> 8) == 1)
	ret[3 + j * 4] ^= (x ^ 283);
      else
	ret[3 + j * 4] ^= x;
      ret[3 + j * 4] ^=
#ifdef DWARV
	statemt[1 + j * 4] ^ statemt[2 + j * 4] ^ word[j + nb * n + 120 * (3)];
#else
	statemt[1 + j * 4] ^ statemt[2 + j * 4] ^ word[3][j + nb * n];
#endif /* DWARV */
    }
  for (j = 0; j < nb; ++j)
    {
      statemt[j * 4] = ret[j * 4];
      statemt[1 + j * 4] = ret[1 + j * 4];
      statemt[2 + j * 4] = ret[2 + j * 4];
      statemt[3 + j * 4] = ret[3 + j * 4];
    }
  return 0;
}

/* ******** InversMixColumn ********** */
int
#ifdef DWARV
AddRoundKey_InversMixColumn (int statemt[32], int nb, int n, int *word)
#else
AddRoundKey_InversMixColumn (int statemt[32], int nb, int n)
#endif /* DWARV */
{
  int ret[8 * 4], i, j;
  register int x;

  for (j = 0; j < nb; ++j)
    {
#ifdef DWARV
      statemt[j * 4] ^= word[j + nb * n + 120 * (0)];
      statemt[1 + j * 4] ^= word[j + nb * n + 120 * (1)];
      statemt[2 + j * 4] ^= word[j + nb * n + 120 * (2)];
      statemt[3 + j * 4] ^= word[j + nb * n + 120 * (3)];
#else
      statemt[j * 4] ^= word[0][j + nb * n];
      statemt[1 + j * 4] ^= word[1][j + nb * n];
      statemt[2 + j * 4] ^= word[2][j + nb * n];
      statemt[3 + j * 4] ^= word[3][j + nb * n];
#endif /* DWARV */
    }
  for (j = 0; j < nb; ++j)
    for (i = 0; i < 4; ++i)
      {
	x = (statemt[i + j * 4] << 1);
	if ((x >> 8) == 1)
	  x ^= 283;
	x ^= statemt[i + j * 4];
	x = (x << 1);
	if ((x >> 8) == 1)
	  x ^= 283;
	x ^= statemt[i + j * 4];
	x = (x << 1);
	if ((x >> 8) == 1)
	  x ^= 283;
	ret[i + j * 4] = x;

	x = (statemt[(i + 1) % 4 + j * 4] << 1);
	if ((x >> 8) == 1)
	  x ^= 283;
	x = (x << 1);
	if ((x >> 8) == 1)
	  x ^= 283;
	x ^= statemt[(i + 1) % 4 + j * 4];
	x = (x << 1);
	if ((x >> 8) == 1)
	  x ^= 283;
	x ^= statemt[(i + 1) % 4 + j * 4];
	ret[i + j * 4] ^= x;

	x = (statemt[(i + 2) % 4 + j * 4] << 1);
	if ((x >> 8) == 1)
	  x ^= 283;
	x ^= statemt[(i + 2) % 4 + j * 4];
	x = (x << 1);
	if ((x >> 8) == 1)
	  x ^= 283;
	x = (x << 1);
	if ((x >> 8) == 1)
	  x ^= 283;
	x ^= statemt[(i + 2) % 4 + j * 4];
	ret[i + j * 4] ^= x;

	x = (statemt[(i + 3) % 4 + j * 4] << 1);
	if ((x >> 8) == 1)
	  x ^= 283;
	x = (x << 1);
	if ((x >> 8) == 1)
	  x ^= 283;
	x = (x << 1);
	if ((x >> 8) == 1)
	  x ^= 283;
	x ^= statemt[(i + 3) % 4 + j * 4];
	ret[i + j * 4] ^= x;
      }
  for (i = 0; i < nb; ++i)
    {
      statemt[i * 4] = ret[i * 4];
      statemt[1 + i * 4] = ret[1 + i * 4];
      statemt[2 + i * 4] = ret[2 + i * 4];
      statemt[3 + i * 4] = ret[3 + i * 4];
    }
  return 0;
}

/* ******** AddRoundKey ********** */
int
#ifdef DWARV
AddRoundKey (int statemt[32], int type, int n, int *word)
#else
AddRoundKey (int statemt[32], int type, int n)
#endif /* DWARV */
{
  int j, nb;

  switch (type)
    {
    case 128128:
    case 192128:
    case 256128:
      nb = 4;
      break;
    case 128192:
    case 192192:
    case 256192:
      nb = 6;
      break;
    case 128256:
    case 192256:
    case 256256:
      nb = 8;
      break;
    }
  for (j = 0; j < nb; ++j)
    {
#ifdef DWARV
      statemt[j * 4] ^= word[j + nb * n + 120 * (0)];
      statemt[1 + j * 4] ^= word[j + nb * n + 120 * (1)];
      statemt[2 + j * 4] ^= word[j + nb * n + 120 * (2)];
      statemt[3 + j * 4] ^= word[j + nb * n + 120 * (3)];
#else
      statemt[j * 4] ^= word[0][j + nb * n];
      statemt[1 + j * 4] ^= word[1][j + nb * n];
      statemt[2 + j * 4] ^= word[2][j + nb * n];
      statemt[3 + j * 4] ^= word[3][j + nb * n];
#endif /* DWARV */
    }
  return 0;
}

#ifdef TESTMODE
/* ***************** main **************************** */
int
aes_main (void)
{
/*
+--------------------------------------------------------------------------+
| * Test Vectors (added for CHStone)                                       |
|     statemt, key : input data                                            |
+--------------------------------------------------------------------------+
*/
#ifdef DWARV
  int i;

  int *statemt = (int *) malloc( 32 * sizeof( int ) );
  int *key = (int *) malloc( 32 * sizeof( int ) );
  int *word = (int *) malloc( 4 * 120 * sizeof( int ) );

  int *m_Sbox = (int *) malloc( 16 * 16 * sizeof( int ) );
  int *m_invSbox = (int *) malloc( 16 * 16 * sizeof( int ) );

  int *m_Rcon0 = (int *) malloc( 30 * sizeof( int ) );
  int *main_result = (int *) malloc( sizeof( int ) );
#endif /* DWARV */

  statemt[0] = 50;
  statemt[1] = 67;
  statemt[2] = 246;
  statemt[3] = 168;
  statemt[4] = 136;
  statemt[5] = 90;
  statemt[6] = 48;
  statemt[7] = 141;
  statemt[8] = 49;
  statemt[9] = 49;
  statemt[10] = 152;
  statemt[11] = 162;
  statemt[12] = 224;
  statemt[13] = 55;
  statemt[14] = 7;
  statemt[15] = 52;

  key[0] = 43;
  key[1] = 126;
  key[2] = 21;
  key[3] = 22;
  key[4] = 40;
  key[5] = 174;
  key[6] = 210;
  key[7] = 166;
  key[8] = 171;
  key[9] = 247;
  key[10] = 21;
  key[11] = 136;
  key[12] = 9;
  key[13] = 207;
  key[14] = 79;
  key[15] = 60;

#ifdef DWARV
  int j;

  for( i = 0; i < 16; i++ ) {
    for( j = 0; j < 16; j++ ) {
      m_Sbox[j + 16 * i] = Sbox[i][j];
      m_invSbox[j + 16 * i] = invSbox[i][j];
    }
  }

  for( i = 0; i < 30; i++ ) {
    m_Rcon0[i] = Rcon0[i];
  }
 
  *main_result = 0;
//  #pragma map call_hw VIRTEX5 0
  encrypt (statemt, key, 128128, round, nb, word, m_Sbox, m_Rcon0, main_result);

  #pragma map call_hw VIRTEX5 0
  decrypt (statemt, key, 128128, round, nb, word, m_Sbox, m_invSbox, m_Rcon0, main_result);
#else
  encrypt (statemt, key, 128128);
  printf("\n--------------------------------------------\n");
  printf("\nDecrypt start\n");
  printf("\n--------------------------------------------\n");
  int ret = decrypt (statemt, key, 128128);
  printf("\n--------------------------------------------\n");
  printf("\nDecrypt end %d\n", ret+5);
  printf("\n--------------------------------------------\n");
#endif /* DWARV */
  return 0;
}

int
main ()
{
      main_result = 0;
      aes_main ();
      printf("\naes_main end:\n");
      printf ("\nmain_result: %d\n", main_result);
      return main_result;
    }
#endif /* TESTMODE */
