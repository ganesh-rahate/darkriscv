/*
 * Copyright (c) 2018, Marcelo Samsoniuk
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 * 
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 * 
 * * Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
 */

#include "io.h"
#include "stdio.h"

extern int main(void);
struct DARKIO *io;

void _start(void)
{
  
  /* 
   * put the data and bss initialization here:
   * 
   * memcpy(&data_rom, &data_ram,data_len);
   * memset(&bss_ram,0,bss_len);
   *
   * you need ensure the boot.o(.text) is the first block in the rom!
   *
   */

   io = (struct DARKIO *) 0x80000000; // io start here!


  // https://github.com/riscv/riscv-pk/blob/master/bbl/riscv_logo.txt
  // https://github.com/riscv/riscv-pk/blob/master/LICENSE.riscv_logo.txt
  // Copyright (C) 2015 Andrew Waterman

  char *logo =
    "              vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv\n"
    "                  vvvvvvvvvvvvvvvvvvvvvvvvvvvv\n"
    "rrrrrrrrrrrrr       vvvvvvvvvvvvvvvvvvvvvvvvvv\n"
    "rrrrrrrrrrrrrrrr      vvvvvvvvvvvvvvvvvvvvvvvv\n"
    "rrrrrrrrrrrrrrrrrr    vvvvvvvvvvvvvvvvvvvvvvvv\n"
    "rrrrrrrrrrrrrrrrrr    vvvvvvvvvvvvvvvvvvvvvvvv\n"
    "rrrrrrrrrrrrrrrrrr    vvvvvvvvvvvvvvvvvvvvvvvv\n"
    "rrrrrrrrrrrrrrrr      vvvvvvvvvvvvvvvvvvvvvv  \n"
    "rrrrrrrrrrrrr       vvvvvvvvvvvvvvvvvvvvvv    \n"
    "rr                vvvvvvvvvvvvvvvvvvvvvv      \n"
    "rr            vvvvvvvvvvvvvvvvvvvvvvvv      rr\n"
    "rrrr      vvvvvvvvvvvvvvvvvvvvvvvvvv      rrrr\n"
    "rrrrrr      vvvvvvvvvvvvvvvvvvvvvv      rrrrrr\n"
    "rrrrrrrr      vvvvvvvvvvvvvvvvvv      rrrrrrrr\n"
    "rrrrrrrrrr      vvvvvvvvvvvvvv      rrrrrrrrrr\n"
    "rrrrrrrrrrrr      vvvvvvvvvv      rrrrrrrrrrrr\n"
    "rrrrrrrrrrrrrr      vvvvvv      rrrrrrrrrrrrrr\n"
    "rrrrrrrrrrrrrrrr      vv      rrrrrrrrrrrrrrrr\n"
    "rrrrrrrrrrrrrrrrrr          rrrrrrrrrrrrrrrrrr\n"
    "rrrrrrrrrrrrrrrrrrrr      rrrrrrrrrrrrrrrrrrrr\n"
    "rrrrrrrrrrrrrrrrrrrrrr  rrrrrrrrrrrrrrrrrrrrrr\n"
    "\n"
    "       INSTRUCTION SETS WANT TO BE FREE\n\n";

  // rle compressor: 1030 to 269 bytes! +_+

  register int xc=0,xs=0;
  register char *xp;

  for(xp=logo;;xp++)
  {
      if(xc!=*xp)
      {
          if(xc)
          {
              printf("0x");
              putx(xc);
              printf(", 0x");
              putx(xs);
              printf(" ");
          }
          xs=1;
          if(!(xc=*xp)) break;
      }
      else xs++;
  }

  printf("press any key to continue...");
  getchar();
  
  char rle_logo[] = { 
      0x20, 0x0e, 0x76, 0x20, 0x0a, 0x01, 0x20, 0x12, 0x76, 0x1c, 0x0a,
      0x01, 0x72, 0x0d, 0x20, 0x07, 0x76, 0x1a, 0x0a, 0x01, 0x72, 0x10,
      0x20, 0x06, 0x76, 0x18, 0x0a, 0x01, 0x72, 0x12, 0x20, 0x04, 0x76,
      0x18, 0x0a, 0x01, 0x72, 0x12, 0x20, 0x04, 0x76, 0x18, 0x0a, 0x01,
      0x72, 0x12, 0x20, 0x04, 0x76, 0x18, 0x0a, 0x01, 0x72, 0x10, 0x20,
      0x06, 0x76, 0x16, 0x20, 0x02, 0x0a, 0x01, 0x72, 0x0d, 0x20, 0x07,
      0x76, 0x16, 0x20, 0x04, 0x0a, 0x01, 0x72, 0x02, 0x20, 0x10, 0x76,
      0x16, 0x20, 0x06, 0x0a, 0x01, 0x72, 0x02, 0x20, 0x0c, 0x76, 0x18,
      0x20, 0x06, 0x72, 0x02, 0x0a, 0x01, 0x72, 0x04, 0x20, 0x06, 0x76,
      0x1a, 0x20, 0x06, 0x72, 0x04, 0x0a, 0x01, 0x72, 0x06, 0x20, 0x06,
      0x76, 0x16, 0x20, 0x06, 0x72, 0x06, 0x0a, 0x01, 0x72, 0x08, 0x20,
      0x06, 0x76, 0x12, 0x20, 0x06, 0x72, 0x08, 0x0a, 0x01, 0x72, 0x0a,
      0x20, 0x06, 0x76, 0x0e, 0x20, 0x06, 0x72, 0x0a, 0x0a, 0x01, 0x72,
      0x0c, 0x20, 0x06, 0x76, 0x0a, 0x20, 0x06, 0x72, 0x0c, 0x0a, 0x01,
      0x72, 0x0e, 0x20, 0x06, 0x76, 0x06, 0x20, 0x06, 0x72, 0x0e, 0x0a,
      0x01, 0x72, 0x10, 0x20, 0x06, 0x76, 0x02, 0x20, 0x06, 0x72, 0x10,
      0x0a, 0x01, 0x72, 0x12, 0x20, 0x0a, 0x72, 0x12, 0x0a, 0x01, 0x72,
      0x14, 0x20, 0x06, 0x72, 0x14, 0x0a, 0x01, 0x72, 0x16, 0x20, 0x02,
      0x72, 0x16, 0x0a, 0x02, 0x20, 0x07, 0x49, 0x01, 0x4e, 0x01, 0x53,
      0x01, 0x54, 0x01, 0x52, 0x01, 0x55, 0x01, 0x43, 0x01, 0x54, 0x01,
      0x49, 0x01, 0x4f, 0x01, 0x4e, 0x01, 0x20, 0x01, 0x53, 0x01, 0x45,
      0x01, 0x54, 0x01, 0x53, 0x01, 0x20, 0x01, 0x57, 0x01, 0x41, 0x01,
      0x4e, 0x01, 0x54, 0x01, 0x20, 0x01, 0x54, 0x01, 0x4f, 0x01, 0x20,
      0x01, 0x42, 0x01, 0x45, 0x01, 0x20, 0x01, 0x46, 0x01, 0x52, 0x01,
      0x45, 0x02, 0x0a, 0x02, 0x00 };

  printf("\33[H\33[2J");
  
  register int c,s;
  register char *p = rle_logo;
  
  while(*p)
  {
      c = *p++;
      s = *p++;
      
      while(s--) putchar(c);
  }

   main();
   
   while(1);
}
