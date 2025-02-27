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
          #pragma map call_hw VIRTEX5 0
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
