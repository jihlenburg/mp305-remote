
// ==== FUN_CODE_104e @ CODE:104e size 37 callers [CODE:793a]

void FUN_CODE_104e(void)

{
  byte bVar1;
  char cVar2;
  
  bVar1 = 0xb - (((DAT_EXTMEM_05dd < 0xb9) << 7) >> 7);
  cVar2 = DAT_EXTMEM_05dc - bVar1;
  if (bVar1 <= DAT_EXTMEM_05dc) {
    DAT_EXTMEM_05dc = 0;
    DAT_EXTMEM_05dd = 0;
    FUN_CODE_9924();
    cVar2 = FUN_CODE_9e59(2,7);
  }
  FUN_CODE_a7a4(cVar2);
  FUN_CODE_8bc8(0);
  return;
}



// ==== FUN_CODE_1076 @ CODE:1076 size 5 callers [CODE:996c]

undefined1 FUN_CODE_1076(void)

{
  return DAT_INTMEM_c9;
}



// ==== FUN_CODE_107e @ CODE:107e size 5 callers [CODE:a253]

void FUN_CODE_107e(void)

{
  return;
}



// ==== FUN_CODE_1086 @ CODE:1086 size 5 callers [CODE:6f27]

void FUN_CODE_1086(void)

{
  return;
}



// ==== FUN_CODE_108e @ CODE:108e size 5 callers [CODE:6f27]

void FUN_CODE_108e(void)

{
  return;
}



// ==== FUN_CODE_1096 @ CODE:1096 size 5 callers [CODE:89b2]

undefined1 FUN_CODE_1096(void)

{
  return DAT_INTMEM_a4;
}



// ==== FUN_CODE_109e @ CODE:109e size 5 callers [CODE:8864,CODE:88c5,CODE:a5f2]

void FUN_CODE_109e(undefined1 param_1)

{
  FUN_CODE_1e8d(param_1);
  return;
}



// ==== FUN_CODE_10a6 @ CODE:10a6 size 5 callers [CODE:843b]

byte FUN_CODE_10a6(byte param_1)

{
  byte bVar1;
  
  bVar1 = SADEN;
  SADEN = bVar1 & ~param_1;
  return ~param_1;
}



// ==== FUN_CODE_10ae @ CODE:10ae size 5 callers [CODE:7a62]

void FUN_CODE_10ae(void)

{
  return;
}



// ==== FUN_CODE_1d23 @ CODE:1d23 size 7 callers [CODE:6406]

char FUN_CODE_1d23(byte *param_1)

{
  byte bVar1;
  
  bVar1 = *param_1;
  *param_1 = bVar1 + 1;
  return '\x05' - (((99 < bVar1) << 7) >> 7);
}



// ==== FUN_CODE_1d2a @ CODE:1d2a size 8 callers [CODE:6406]

char FUN_CODE_1d2a(void)

{
  char in_PSW;
  
  return '\x05' - (in_PSW >> 7);
}



// ==== FUN_CODE_1e0a @ CODE:1e0a size 17 callers [CODE:6406]

char FUN_CODE_1e0a(void)

{
  char cVar1;
  
  cVar1 = DAT_EXTMEM_04b2;
  DAT_EXTMEM_04b2 = DAT_EXTMEM_04b2 + '\x01';
  return cVar1 + -100;
}



// ==== FUN_CODE_1e41 @ CODE:1e41 size 7 callers [CODE:7a62]

void FUN_CODE_1e41(undefined1 *param_1)

{
  *param_1 = BANK0_R6;
  param_1['\x01'] = BANK0_R7;
  return;
}



// ==== FUN_CODE_1e48 @ CODE:1e48 size 7 callers [CODE:6406,CODE:9645]

char FUN_CODE_1e48(void)

{
  return DAT_INTMEM_b3 + '#';
}



// ==== FUN_CODE_1e8d @ CODE:1e8d size 11 callers [CODE:109e]

undefined1 FUN_CODE_1e8d(char param_1)

{
  return *(undefined1 *)(param_1 * '\x02' + 't');
}



// ==== FUN_CODE_1f10 @ CODE:1f10 size 8 callers [CODE:6406]

char FUN_CODE_1f10(char *param_1)

{
  char cVar1;
  
  cVar1 = *param_1;
  *param_1 = cVar1 + '\x01';
  return cVar1 + -100;
}



// ==== FUN_CODE_1f30 @ CODE:1f30 size 8 callers [CODE:6406]

void FUN_CODE_1f30(char *param_1)

{
  DAT_EXTMEM_059e = *param_1 + -2;
  return;
}



// ==== FUN_CODE_1f56 @ CODE:1f56 size 10 callers [CODE:6406]

char FUN_CODE_1f56(char *param_1)

{
  char cVar1;
  
  cVar1 = *param_1;
  *param_1 = cVar1 + '\x01';
  return cVar1 + -100;
}



// ==== thunk_FUN_CODE_996c @ CODE:1ffd size 3 callers [CODE:6aab]

void thunk_FUN_CODE_996c(char param_1)

{
  char in_PSW;
  
  FUN_CODE_1076();
  if ((param_1 != '\0') && (FUN_CODE_a7f9(), -1 < in_PSW)) {
    return;
  }
  FUN_CODE_666b(0x4a,7,1,0x4c);
  return;
}



// ==== FUN_CODE_25d4 @ CODE:25d4 size 41 callers [CODE:a069]

void FUN_CODE_25d4(char param_1,char param_2)

{
  byte bVar1;
  short sVar2;
  
  DAT_EXTMEM_04aa = param_2;
  DAT_EXTMEM_04ab = param_1;
  if (param_1 != param_2) {
    bVar1 = param_1 - 1;
    if ((bVar1 < 7) << 7 < '\0') {
      sVar2 = 0x25f4;
      if (CARRY1(bVar1,bVar1)) {
        sVar2 = 0x26f4;
      }
                    /* WARNING: Could not recover jumptable at 0x25f3. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (*(code *)(sVar2 + (ushort)(bVar1 * '\x02')))();
      return;
    }
    FUN_CODE_a6f1(param_1);
  }
  return;
}



// ==== FUN_CODE_27b2 @ CODE:27b2 size 78 callers [CODE:a069]

byte FUN_CODE_27b2(undefined1 param_1)

{
  byte bVar1;
  undefined1 uVar2;
  
  FUN_CODE_a377();
  FUN_CODE_33b9();
  FUN_CODE_a9ae(0,0x58);
  FUN_CODE_a9ae(0,0x59);
  FUN_CODE_a9ae(0,0x5a);
  FUN_CODE_a9ae(0,0x5c);
  uVar2 = 0;
  FUN_CODE_a623(0);
  FUN_CODE_33d6();
  FUN_CODE_ab68(param_1,0x50,uVar2);
  uVar2 = 0;
  FUN_CODE_a61c(0);
  FUN_CODE_33d6();
  FUN_CODE_ab68(param_1,0x52,uVar2);
  bVar1 = DAT_SFR_c2;
  DAT_SFR_c2 = bVar1 | (&DAT_CODE_b8f6)[DAT_INTMEM_b3];
  return (&DAT_CODE_b8f6)[DAT_INTMEM_b3];
}



// ==== FUN_CODE_2800 @ CODE:2800 size 603 callers [CODE:7a1a]

void FUN_CODE_2800(undefined1 param_1,undefined1 param_2,byte param_3,undefined1 param_4)

{
  byte bVar1;
  char cVar2;
  char cVar3;
  byte bVar4;
  byte bVar5;
  byte bVar6;
  char cVar7;
  char in_PSW;
  byte *pbVar8;
  undefined1 *puVar9;
  byte *pbVar10;
  undefined2 uVar11;
  
  DAT_EXTMEM_04a9 = 0;
  DAT_EXTMEM_04a5 = param_3;
  DAT_EXTMEM_04a6 = param_4;
  DAT_EXTMEM_04a7 = param_1;
  DAT_EXTMEM_04a8 = param_2;
  FUN_CODE_9d61();
  FUN_CODE_ae2a(0x4ab);
  DAT_EXTMEM_04aa = FUN_CODE_a934();
  pbVar8 = (byte *)0x4aa;
  FUN_CODE_a335();
  if (in_PSW < '\0') {
    FUN_CODE_44e9();
    bVar5 = (byte)((ushort)*pbVar8 * 4);
    bVar6 = (char)((ushort)*pbVar8 * 4 >> 8) - (((0xdb < bVar5) << 7) >> 7);
    cVar7 = (0x47 < bVar6) << 7;
    bVar4 = 4;
    FUN_CODE_448e(0xae,bVar5 + 0x24,bVar6 + 0xb8,0xff,1);
    cVar2 = DAT_EXTMEM_04ae;
    cVar3 = DAT_EXTMEM_04af;
    bVar6 = FUN_CODE_4503(0x4a5);
    bVar6 = cVar2 - (((bVar6 < (byte)(cVar3 - (cVar7 >> 7))) << 7) >> 7);
    cVar7 = (bVar4 < bVar6) << 7;
    if (bVar4 < bVar6) {
      DAT_EXTMEM_04a9 = DAT_EXTMEM_04a9 | 1;
    }
    else {
      FUN_CODE_44b1(bVar4 - bVar6);
      if (cVar7 < '\0') {
        DAT_EXTMEM_04a9 = DAT_EXTMEM_04a9 | 4;
      }
    }
    puVar9 = &DAT_EXTMEM_04a7;
    bVar6 = FUN_CODE_4503();
    bVar6 = cVar2 - (((bVar6 < (byte)(cVar3 - (cVar7 >> 7))) << 7) >> 7);
    bVar5 = (bVar4 < bVar6) << 7;
    if (bVar4 < bVar6) {
      bVar6 = puVar9[1] | 2;
      puVar9[1] = bVar6;
    }
    else {
      bVar6 = FUN_CODE_44b1(bVar4 - bVar6);
      if ((char)bVar5 < '\0') {
        bVar6 = DAT_EXTMEM_04a9 | 8;
        DAT_EXTMEM_04a9 = bVar6;
      }
    }
  }
  else {
    bVar6 = FUN_CODE_4468();
    bVar5 = 1 - (((bVar6 < 0x62) << 7) >> 7);
    cVar7 = param_3 - bVar5;
    pbVar10 = pbVar8;
    if (param_3 >= bVar5) {
      bVar4 = pbVar8[1];
      pbVar10 = pbVar8 + 2;
      bVar1 = 1 - (((*pbVar10 < 0x61U - (((param_3 < bVar5) << 7) >> 7)) << 7) >> 7);
      bVar5 = (bVar4 < bVar1) << 7;
      cVar7 = bVar4 - bVar1;
      if (bVar4 < bVar1) {
        pbVar8 = pbVar8 + 3;
        *pbVar8 = 4;
        FUN_CODE_9719();
        bVar6 = bVar6 | 4;
        *pbVar8 = bVar6;
        goto LAB_CODE_290d;
      }
    }
    bVar6 = FUN_CODE_4468(cVar7);
    bVar6 = 1 - (((bVar6 < 0x61) << 7) >> 7);
    bVar5 = (param_3 < bVar6) << 7;
    cVar7 = param_3 - bVar6;
    pbVar8 = pbVar10;
    if (param_3 < bVar6) {
      param_3 = pbVar10[1];
      pbVar8 = pbVar10 + 2;
      bVar6 = *pbVar8;
      bVar4 = 1 - (((bVar6 < 0x62) << 7) >> 7);
      bVar5 = (param_3 < bVar4) << 7;
      cVar7 = param_3 - bVar4;
      if (param_3 >= bVar4) {
        pbVar10 = pbVar10 + 3;
        *pbVar10 = 8;
        FUN_CODE_9719();
        bVar6 = bVar6 | 8;
        *pbVar10 = bVar6;
        goto LAB_CODE_290d;
      }
    }
    bVar4 = FUN_CODE_4468(cVar7);
    bVar6 = FUN_CODE_451a();
    if ((char)bVar5 < '\0') {
      bVar4 = 1 - (((bVar4 < 0x61U - ((char)bVar5 >> 7)) << 7) >> 7);
      bVar5 = (param_3 < bVar4) << 7;
      bVar6 = param_3 - bVar4;
      if (param_3 >= bVar4) {
        bVar4 = pbVar8[1];
        bVar1 = 0xf - (((pbVar8[2] < 0x2cU - ((char)bVar5 >> 7)) << 7) >> 7);
        bVar5 = (bVar4 < bVar1) << 7;
        bVar6 = bVar4 - bVar1;
        if (bVar4 < bVar1) {
          bVar1 = 1 - (((pbVar8[2] < 0x62) << 7) >> 7);
          bVar5 = (bVar4 < bVar1) << 7;
          bVar6 = bVar4 - bVar1;
          if (bVar4 >= bVar1) {
            pbVar8[3] = 0xc;
            bVar6 = FUN_CODE_4468();
            FUN_CODE_9719();
            bVar6 = bVar6 | 0xc;
            DAT_EXTMEM_04a9 = bVar6;
          }
        }
      }
    }
  }
LAB_CODE_290d:
  FUN_CODE_adf3(bVar6,0x4ab,5);
  bVar6 = FUN_CODE_a934();
  bVar5 = bVar5 & 0xdd;
  if ((bVar6 & 0xfc) != 0) {
    FUN_CODE_4468();
    FUN_CODE_451a();
    if ((char)bVar5 < '\0') {
      FUN_CODE_451a(DAT_EXTMEM_04a8,DAT_EXTMEM_04a7);
    }
  }
  bVar6 = BANK0_R4;
  FUN_CODE_7f77(BANK0_R4,DAT_EXTMEM_04a9,BANK0_R2,BANK0_R1);
  cVar7 = DAT_INTMEM_b3;
  if ((char)bVar5 < '\0') {
    DAT_EXTMEM_04b2 = 0;
    DAT_EXTMEM_04b3 = DAT_EXTMEM_04a9;
    DAT_EXTMEM_04b4 = 0;
    DAT_EXTMEM_04b5 = DAT_INTMEM_b3;
    if ((DAT_EXTMEM_04a9 == 0) ||
       (((DAT_EXTMEM_04a9 >> 2 & 1) == 0 && ((DAT_EXTMEM_04a9 >> 3 & 1) == 0)))) {
      *(undefined1 *)(DAT_INTMEM_b3 + 'k') = 0;
      *(undefined1 *)(cVar7 + -0x6d) = 0;
      *(undefined1 *)(cVar7 + '=') = 0;
      *(undefined1 *)(cVar7 * '\x02' + 'Y') = 0;
      *(undefined1 *)(cVar7 * '\x02' + 'Z') = 0;
      FUN_CODE_ad79(cVar7 * '\x04' + 'Q',0);
      nop();
      nop();
      nop();
      nop();
      cVar7 = FUN_CODE_44bf();
      FUN_CODE_ad79(cVar7 + '5');
      nop();
      nop();
      nop();
      nop();
      FUN_CODE_ad79(bVar6 * '\x04' + 'c');
      nop();
      nop();
      nop();
      nop();
      cVar7 = FUN_CODE_44bf();
      FUN_CODE_ad79(cVar7 + 'w');
      nop();
      nop();
      nop();
      nop();
      FUN_CODE_ad79(bVar6 * '\x04' + '%');
      nop();
      nop();
      nop();
      nop();
      cVar7 = FUN_CODE_44bf();
      FUN_CODE_ad79(cVar7 + 'G');
      nop();
      nop();
      nop();
      nop();
      uVar11 = 4;
      cVar7 = FUN_CODE_43fb((char)((ushort)bVar6 * 4) + '\x7f',4,(char)((ushort)bVar6 * 4 >> 8),0);
      cVar7 = FUN_CODE_43fb(cVar7 + '?');
      FUN_CODE_aefd(cVar7 + -100,0,0,(char)((ushort)uVar11 >> 8),(char)uVar11);
    }
    FUN_CODE_4495(0x4b4,0xc3,0xb7);
    FUN_CODE_4470(0x4b2);
    DAT_EXTMEM_04da = DAT_EXTMEM_04a5;
    DAT_EXTMEM_04db = DAT_EXTMEM_04a6;
    DAT_EXTMEM_04dc = DAT_EXTMEM_04a7;
    DAT_EXTMEM_04dd = DAT_EXTMEM_04a8;
    FUN_CODE_87aa();
    DAT_INTMEM_a7 = DAT_EXTMEM_04a9;
    FUN_CODE_a638(1,2);
  }
  return;
}



// ==== FUN_CODE_33b9 @ CODE:33b9 size 29 callers [CODE:27b2]

void FUN_CODE_33b9(byte param_1,char param_2)

{
  byte bVar1;
  
  FUN_CODE_adf3(0x71d);
  bVar1 = FUN_CODE_a934(param_1 + 0x5d,param_2 - (((0xa2 < param_1) << 7) >> 7));
  FUN_CODE_a99c(bVar1 | 0x11);
  bVar1 = FUN_CODE_a934();
  FUN_CODE_a99c(bVar1 & 0xfe);
  FUN_CODE_adf3(0x71d);
  return;
}



// ==== FUN_CODE_33d6 @ CODE:33d6 size 6 callers [CODE:27b2]

void FUN_CODE_33d6(void)

{
  FUN_CODE_adf3(0x71d);
  return;
}



// ==== FUN_CODE_33dc @ CODE:33dc size 3 callers [CODE:42a5]

void FUN_CODE_33dc(byte param_1,char param_2)

{
  FUN_CODE_a9ae();
  FUN_CODE_a934(param_1 + 0x58,param_2 - (((0xa7 < param_1) << 7) >> 7));
  return;
}



// ==== FUN_CODE_33df @ CODE:33df size 3 callers [CODE:803f]

void FUN_CODE_33df(byte param_1,char param_2)

{
  FUN_CODE_a934(param_1 + 0x58,param_2 - (((0xa7 < param_1) << 7) >> 7));
  return;
}



// ==== FUN_CODE_33e2 @ CODE:33e2 size 7 callers [CODE:42a5,CODE:64a1]

void FUN_CODE_33e2(undefined1 param_1,char param_2)

{
  char in_PSW;
  
  FUN_CODE_a934(param_1,param_2 - (in_PSW >> 7));
  return;
}



// ==== FUN_CODE_33e9 @ CODE:33e9 size 12 callers [CODE:42a5,CODE:5cfa,CODE:64a1,CODE:803f]

void FUN_CODE_33e9(void)

{
  FUN_CODE_adf3(0x717);
  FUN_CODE_a94d(0x58);
  return;
}



// ==== FUN_CODE_3401 @ CODE:3401 size 8 callers [CODE:84e6]

char FUN_CODE_3401(void)

{
  char in_PSW;
  
  return '\x03' - (in_PSW >> 7);
}



// ==== FUN_CODE_342b @ CODE:342b size 2 callers [CODE:803f]

char FUN_CODE_342b(byte *param_1)

{
  return '\x03' - (((0x25 < *param_1) << 7) >> 7);
}



// ==== FUN_CODE_342d @ CODE:342d size 10 callers [CODE:64a1,CODE:a1f3]

char FUN_CODE_342d(byte param_1)

{
  return '\x03' - (((0x25 < param_1) << 7) >> 7);
}



// ==== FUN_CODE_3439 @ CODE:3439 size 6 callers [CODE:64a1,CODE:803f]

void FUN_CODE_3439(void)

{
  FUN_CODE_a99c();
  FUN_CODE_a934();
  return;
}



// ==== FUN_CODE_343f @ CODE:343f size 1 callers [CODE:42a5,CODE:803f]

char FUN_CODE_343f(byte *param_1)

{
  return '\x03' - (((0xc3 < *param_1) << 7) >> 7);
}



// ==== FUN_CODE_3440 @ CODE:3440 size 2 callers [CODE:42a5]

char FUN_CODE_3440(byte param_1)

{
  return '\x03' - (((0xc3 < param_1) << 7) >> 7);
}



// ==== FUN_CODE_3442 @ CODE:3442 size 8 callers [CODE:803f]

char FUN_CODE_3442(void)

{
  char in_PSW;
  
  return '\x03' - (in_PSW >> 7);
}



// ==== FUN_CODE_344a @ CODE:344a size 2 callers [CODE:42a5,CODE:5cfa]

char FUN_CODE_344a(void)

{
  return '\x03' - (((0xc5 < DAT_INTMEM_b9) << 7) >> 7);
}



// ==== FUN_CODE_344c @ CODE:344c size 11 callers [CODE:a5bd]

char FUN_CODE_344c(byte *param_1)

{
  return '\x03' - (((0xc5 < *param_1) << 7) >> 7);
}



// ==== FUN_CODE_345c @ CODE:345c size 8 callers [CODE:42a5]

char FUN_CODE_345c(void)

{
  char in_PSW;
  
  return '\x03' - (in_PSW >> 7);
}



// ==== FUN_CODE_3471 @ CODE:3471 size 1 callers [CODE:42a5]

void FUN_CODE_3471(undefined1 param_1,undefined1 *param_2)

{
  *param_2 = param_1;
  FUN_CODE_adf3(0x717);
  return;
}



// ==== FUN_CODE_3472 @ CODE:3472 size 6 callers [CODE:42a5,CODE:5cfa,CODE:64a1,CODE:803f]

void FUN_CODE_3472(void)

{
  FUN_CODE_adf3(0x717);
  return;
}



// ==== FUN_CODE_34c6 @ CODE:34c6 size 14 callers [CODE:960e]

char FUN_CODE_34c6(void)

{
  return '\x03' - (((0x71 < DAT_INTMEM_b9) << 7) >> 7);
}



// ==== FUN_CODE_34d4 @ CODE:34d4 size 10 callers [CODE:9cdd]

undefined1 FUN_CODE_34d4(undefined1 *param_1)

{
  return *param_1;
}



// ==== FUN_CODE_34e6 @ CODE:34e6 size 11 callers [CODE:84e6]

char FUN_CODE_34e6(byte param_1)

{
  return '\x03' - (((0x73 < param_1) << 7) >> 7);
}



// ==== FUN_CODE_34f1 @ CODE:34f1 size 11 callers [CODE:960e]

char FUN_CODE_34f1(byte param_1)

{
  return '\x03' - (((0xcb < param_1) << 7) >> 7);
}



// ==== FUN_CODE_351a @ CODE:351a size 13 callers [CODE:a727,CODE:a72d]

char FUN_CODE_351a(void)

{
  return '\x03' - (((0x5b < DAT_INTMEM_b3) << 7) >> 7);
}



// ==== FUN_CODE_3555 @ CODE:3555 size 8 callers [CODE:42a5]

char FUN_CODE_3555(char param_1)

{
  char in_PSW;
  
  return param_1 - (in_PSW >> 7);
}



// ==== FUN_CODE_355d @ CODE:355d size 11 callers [CODE:47aa,CODE:75c0]

byte FUN_CODE_355d(byte *param_1)

{
  return *param_1 & ~DAT_EXTMEM_03ec;
}



// ==== FUN_CODE_3572 @ CODE:3572 size 434 callers [CODE:87aa]

undefined1 FUN_CODE_3572(byte param_1,char param_2,byte param_3,char param_4,char param_5)

{
  char cVar1;
  byte bVar2;
  undefined1 uVar3;
  undefined1 *puVar4;
  
  FUN_CODE_ae2a(0x501);
  DAT_EXTMEM_050e = 0;
  DAT_EXTMEM_050f = 0;
  while (cVar1 = FUN_CODE_53e7(), cVar1 != '\0') {
    if (cVar1 == '%') {
      FUN_CODE_53f4(0x505,0x25);
      DAT_EXTMEM_050c = 0;
      DAT_EXTMEM_050d = 0;
      DAT_EXTMEM_050a = 0;
      puVar4 = (undefined1 *)0x50b;
      DAT_EXTMEM_050b = 0;
      cVar1 = FUN_CODE_53e7();
      if (cVar1 == '\0') break;
      if (cVar1 == '%') goto LAB_CODE_36e2;
      if (cVar1 == '-') {
        FUN_CODE_53f0();
        DAT_EXTMEM_050c = 0;
        puVar4 = (undefined1 *)0x50d;
        DAT_EXTMEM_050d = 1;
      }
      while (cVar1 = FUN_CODE_53e7(), cVar1 == '0') {
        FUN_CODE_53f0();
        puVar4 = (undefined1 *)0x50d;
        DAT_EXTMEM_050d = DAT_EXTMEM_050d | 2;
      }
      while( true ) {
        bVar2 = FUN_CODE_53e7();
        cVar1 = -0x30;
        if (((bVar2 < 0x30) << 7 < '\0') || (cVar1 = -0x3a, 0x39 < bVar2)) break;
        FUN_CODE_a9d0(0,10);
        cVar1 = FUN_CODE_a934();
        param_5 = cVar1 >> 7;
        param_1 = cVar1 - 0x30;
        puVar4 = (undefined1 *)0x50a;
        FUN_CODE_aa6d();
        FUN_CODE_53f0();
      }
      cVar1 = FUN_CODE_a934(bVar2 + cVar1);
      if (cVar1 == 's') {
        param_3 = param_1;
        param_2 = FUN_CODE_548b();
        param_4 = '\0';
        FUN_CODE_ae2a(0x512);
        FUN_CODE_adf3(0x512);
        if ((param_3 == 0 && param_2 == '\0') && param_4 == '\0') {
          param_4 = -1;
          param_3 = 0xb9;
          param_2 = '|';
        }
        else {
          FUN_CODE_adf3(0x512);
        }
LAB_CODE_36b9:
        FUN_CODE_ae2a(0x53e);
        DAT_EXTMEM_0541 = DAT_EXTMEM_050a;
        DAT_EXTMEM_0542 = DAT_EXTMEM_050b;
        param_1 = DAT_EXTMEM_050b;
        FUN_CODE_5428(0x50c);
        FUN_CODE_5497();
        FUN_CODE_55c0();
        cVar1 = param_5;
        goto LAB_CODE_36f5;
      }
      cVar1 = FUN_CODE_53e7();
      if (cVar1 == 'd') {
        FUN_CODE_53fa();
        *puVar4 = 10;
        puVar4[1] = 0;
        puVar4 = puVar4 + 2;
        uVar3 = 1;
LAB_CODE_3694:
        FUN_CODE_5435(uVar3);
        uVar3 = 0x61;
LAB_CODE_3699:
        *puVar4 = uVar3;
        FUN_CODE_5497();
        FUN_CODE_4532();
        param_1 = bVar2;
        cVar1 = param_5;
        goto LAB_CODE_36f5;
      }
      cVar1 = FUN_CODE_53e7();
      if (cVar1 == 'x') {
        FUN_CODE_53fa();
        *puVar4 = 0x10;
        uVar3 = 0;
        puVar4[1] = 0;
        puVar4 = puVar4 + 2;
        goto LAB_CODE_3694;
      }
      cVar1 = FUN_CODE_53e7();
      if (cVar1 == 'X') {
        FUN_CODE_53fa();
        *puVar4 = 0x10;
        puVar4[1] = 0;
        puVar4 = puVar4 + 2;
        FUN_CODE_5435();
        uVar3 = 0x41;
        goto LAB_CODE_3699;
      }
      cVar1 = FUN_CODE_53e7();
      if (cVar1 == 'u') {
        FUN_CODE_53fa();
        *puVar4 = 10;
        uVar3 = 0;
        puVar4[1] = 0;
        puVar4 = puVar4 + 2;
        goto LAB_CODE_3694;
      }
      cVar1 = FUN_CODE_53e7();
      if (cVar1 == 'c') {
        DAT_EXTMEM_0510 = FUN_CODE_548b();
        DAT_EXTMEM_0511 = 0;
        param_4 = '\x01';
        param_3 = 5;
        param_2 = '\x10';
        goto LAB_CODE_36b9;
      }
    }
    else {
LAB_CODE_36e2:
      FUN_CODE_53e7();
      FUN_CODE_5479(0x501);
      FUN_CODE_8b47();
      param_1 = 1;
      cVar1 = '\0';
LAB_CODE_36f5:
      FUN_CODE_aa6d(cVar1,0x50e);
    }
    FUN_CODE_53f0();
  }
  FUN_CODE_5497();
  if ((param_3 != 0 || param_2 != '\0') || param_4 != '\0') {
    FUN_CODE_5497();
    FUN_CODE_ae33();
    FUN_CODE_a99c(0);
  }
  FUN_CODE_ae2a(0x507,0,0,0);
  return DAT_EXTMEM_050f;
}



// ==== FUN_CODE_3724 @ CODE:3724 size 218 callers [CODE:95f2]

undefined1 FUN_CODE_3724(char param_1,char param_2)

{
  char cVar1;
  byte bVar2;
  char cVar3;
  char cVar4;
  
  cVar1 = FUN_CODE_88fd(0x739);
  bVar2 = FUN_CODE_88f5(cVar1 + '\x11');
  DAT_EXTMEM_073a = bVar2 & 0x7f;
  bVar2 = FUN_CODE_88f5(param_1 + '\x12');
  DAT_EXTMEM_073b = bVar2 & 0x7f;
  DAT_EXTMEM_2155 = 0x10;
  DAT_EXTMEM_2154 = 4;
  cVar1 = FUN_CODE_88fd(0x73c);
  bVar2 = FUN_CODE_88f5(cVar1 + '\x14');
  DAT_EXTMEM_073d = bVar2 & 0x7f;
  bVar2 = FUN_CODE_88f5(param_1 + '\x15');
  DAT_EXTMEM_073e = bVar2 & 0x7f;
  DAT_EXTMEM_2255 = 0x10;
  cVar1 = FUN_CODE_8911(4,0x2254);
  cVar1 = FUN_CODE_8909(cVar1 + '\x16');
  DAT_EXTMEM_203c = -0x3d;
  if (cVar1 != '\0') {
    DAT_EXTMEM_203c = cVar1;
  }
  cVar3 = FUN_CODE_8909(param_2 + '\x17');
  cVar1 = -0x69;
  if (cVar3 != '\0') {
    cVar1 = cVar3;
  }
  cVar3 = FUN_CODE_8911(cVar1,0x203d);
  cVar3 = FUN_CODE_8909(cVar3 + '\x18');
  if (cVar3 == '\0') {
    cVar3 = 'C';
  }
  DAT_EXTMEM_203e = cVar3;
  cVar4 = FUN_CODE_8900();
  bVar2 = FUN_CODE_88f5(cVar4 + '\x1f');
  DAT_EXTMEM_2020 = bVar2 & 3;
  DAT_EXTMEM_2021 = FUN_CODE_88f5(cVar3 + ' ');
  cVar4 = FUN_CODE_8900();
  bVar2 = FUN_CODE_88f5(cVar4 + '\x19');
  DAT_EXTMEM_0737 = bVar2 & 0x3f;
  DAT_EXTMEM_2304 = DAT_EXTMEM_0737 + 3;
  bVar2 = FUN_CODE_88f5(cVar3 + '\x1a');
  DAT_EXTMEM_0738 = bVar2 & 0x3f;
  DAT_EXTMEM_2404 = DAT_EXTMEM_0738 + 3;
  FIE1 = 0;
  cVar1 = FUN_CODE_8909(cVar1 + '(');
  if (cVar1 != '\0') {
    FIE1 = 0x2e;
    FIE1 = 0;
    DAT_EXTMEM_1053 = cVar1;
  }
  return 0;
}



// ==== FUN_CODE_37ff @ CODE:37ff size 1 callers [CODE:8a68]

void FUN_CODE_37ff(void)

{
  return;
}



// ==== FUN_CODE_3caa @ CODE:3caa size 363 callers [CODE:73f7]

void FUN_CODE_3caa(void)

{
  byte bVar1;
  byte in_PSW;
  
  DAT_EXTMEM_04a4 = 0;
  DAT_EXTMEM_04a5 = DAT_INTMEM_b2;
  DAT_EXTMEM_04a6 = 0;
  DAT_EXTMEM_04a7 = DAT_INTMEM_b4;
  FUN_CODE_a139(DAT_INTMEM_b3);
  DAT_EXTMEM_04a9 = in_PSW >> 7;
  DAT_EXTMEM_04a8 = 0;
  FUN_CODE_a6f7();
  bVar1 = DAT_EXTMEM_04a4;
  if (DAT_EXTMEM_04a4 == 0) {
    bVar1 = DAT_EXTMEM_04a5 ^ 0x10;
  }
  if ((bVar1 != 0) ||
     ((((DAT_EXTMEM_04a7 != 0x4e || DAT_EXTMEM_04a6 != 0 &&
        (DAT_EXTMEM_04a7 != 0x11 || DAT_EXTMEM_04a6 != 0)) &&
       (DAT_EXTMEM_04a7 != 0x12 || DAT_EXTMEM_04a6 != 0)) &&
      ((DAT_EXTMEM_04a7 != 0x3f || DAT_EXTMEM_04a6 != 0 &&
       (DAT_EXTMEM_04a7 != 0x49 || DAT_EXTMEM_04a6 != 0)))))) {
    FUN_CODE_7d72(0,0xb3,0xb5,0xff);
    FUN_CODE_87aa();
    bVar1 = DAT_EXTMEM_04a4;
    if (DAT_EXTMEM_04a4 == 0) {
      bVar1 = DAT_EXTMEM_04a5 ^ 0x12;
    }
    if (bVar1 == 0) {
      FUN_CODE_7d7a();
      FUN_CODE_52ef();
      return;
    }
    bVar1 = DAT_EXTMEM_04a4;
    if (DAT_EXTMEM_04a4 == 0) {
      bVar1 = DAT_EXTMEM_04a5 ^ 0x11;
    }
    if (bVar1 == 0) {
      FUN_CODE_7d7a();
      FUN_CODE_4800();
      return;
    }
    bVar1 = DAT_EXTMEM_04a4;
    if (DAT_EXTMEM_04a4 == 0) {
      bVar1 = DAT_EXTMEM_04a5 ^ 5;
    }
    if (bVar1 == 0) {
      FUN_CODE_7d7a();
      FUN_CODE_653b();
      return;
    }
    bVar1 = DAT_EXTMEM_04a4;
    if (DAT_EXTMEM_04a4 == 0) {
      bVar1 = DAT_EXTMEM_04a5 ^ 3;
    }
    if (bVar1 == 0) {
      FUN_CODE_7d7a();
      FUN_CODE_6162();
      return;
    }
    bVar1 = DAT_EXTMEM_04a4;
    if (DAT_EXTMEM_04a4 == 0) {
      bVar1 = DAT_EXTMEM_04a5 ^ 2;
    }
    if (bVar1 == 0) {
      bVar1 = DAT_EXTMEM_04a6;
      if (DAT_EXTMEM_04a6 == 0) {
        bVar1 = DAT_EXTMEM_04a7 ^ 1;
      }
      if (bVar1 != 0) {
        FUN_CODE_7d6d(0x4a6,0xc3,0xb5,0xff);
      }
    }
    else {
      bVar1 = DAT_EXTMEM_04a4;
      if (DAT_EXTMEM_04a4 == 0) {
        bVar1 = DAT_EXTMEM_04a5 ^ 0x10;
      }
      if (bVar1 == 0) {
        FUN_CODE_7d7a();
        FUN_CODE_4e91();
        return;
      }
      bVar1 = DAT_EXTMEM_04a4;
      if (DAT_EXTMEM_04a4 == 0) {
        bVar1 = DAT_EXTMEM_04a5 ^ 1;
      }
      if (bVar1 == 0) {
        FUN_CODE_7d6d(0x4a6,0xc9,0xb5,0xff);
        FUN_CODE_7d9f(0x4a8);
      }
      else {
        bVar1 = DAT_EXTMEM_04a4;
        if (DAT_EXTMEM_04a4 == 0) {
          bVar1 = DAT_EXTMEM_04a5 ^ 4;
        }
        if (bVar1 == 0) {
          bVar1 = DAT_EXTMEM_04a6;
          if (DAT_EXTMEM_04a6 == 0) {
            bVar1 = DAT_EXTMEM_04a7 ^ 3;
          }
          if (bVar1 != 0) {
            FUN_CODE_7d6d(0x4a6,0xe5,0xb5,0xff);
          }
        }
        else {
          if (DAT_EXTMEM_04a5 == 8 && DAT_EXTMEM_04a4 == 0) {
            return;
          }
          DAT_EXTMEM_04d6 = DAT_EXTMEM_04a4;
          DAT_EXTMEM_04d7 = DAT_EXTMEM_04a5;
          FUN_CODE_7d9f(0x4a6,0xed,0xb5,0xff);
        }
      }
    }
    FUN_CODE_87aa();
  }
  return;
}



// ==== FUN_CODE_42a5 @ CODE:42a5 size 329 callers [CODE:64a1]

void FUN_CODE_42a5(byte param_1)

{
  byte bVar1;
  byte bVar2;
  short sVar3;
  byte *pbVar4;
  
  FUN_CODE_343f(0xb9);
  FUN_CODE_3471(1);
  DAT_EXTMEM_0745 = FUN_CODE_a94d(0x32);
  DAT_EXTMEM_0746 = FUN_CODE_a94d(0x33);
  DAT_EXTMEM_0740 = DAT_EXTMEM_0746 >> 6;
  DAT_EXTMEM_073f = DAT_EXTMEM_0746 & 0x1f;
  DAT_EXTMEM_0747 = (DAT_EXTMEM_0745 & 0xe) >> 1;
  if ((char)DAT_EXTMEM_0745 < '\0') {
    sVar3 = 0x73f;
    FUN_CODE_3471(DAT_EXTMEM_073f | 0x40);
    bVar1 = (0xcf < param_1) << 7;
    FUN_CODE_3555();
    DAT_INTMEM_bd = *(undefined1 *)(sVar3 + 1);
    DAT_INTMEM_bc = BANK0_R6;
  }
  else {
    bVar1 = 0;
    if ((DAT_EXTMEM_0745 & 0x70) == 0) {
      pbVar4 = &DAT_EXTMEM_073f;
      if (DAT_EXTMEM_073f == 1) {
        FUN_CODE_3440(DAT_EXTMEM_0745 & 0xe);
        *pbVar4 = 0;
        FUN_CODE_345c();
        if (DAT_EXTMEM_0747 != *pbVar4) {
          return;
        }
        bVar1 = FUN_CODE_33e9();
        if ((bVar1 >> 4 & 1) != 1) {
          bVar1 = FUN_CODE_33dc((&DAT_CODE_b902)[DAT_EXTMEM_0740],0x61);
          FUN_CODE_a99c(bVar1 | 0x10);
        }
        FUN_CODE_3472();
        bVar1 = (0xec < param_1) << 7;
        FUN_CODE_33e2();
        bVar1 = bVar1 & 0xdd;
        FUN_CODE_a99c();
      }
    }
    else {
      DAT_EXTMEM_073f = DAT_EXTMEM_073f | 0x20;
      if (DAT_EXTMEM_073f == 0x2f) {
        FUN_CODE_3472();
        bVar1 = (0xcb < param_1) << 7;
        FUN_CODE_3555();
        FUN_CODE_ad49();
        FUN_CODE_ad6d(0x741);
        if (DAT_EXTMEM_0743 < '\0') {
          bVar1 = bVar1 & 0xdd;
          DAT_EXTMEM_073f = DAT_EXTMEM_0744 & 0x1f | 0x60;
        }
      }
    }
  }
  pbVar4 = &DAT_EXTMEM_073f;
  if (DAT_EXTMEM_073f == 1) goto LAB_CODE_43d8;
  bVar2 = FUN_CODE_33e9();
  if ((bVar2 >> 4 & 1) == 0) {
LAB_CODE_43a2:
    FUN_CODE_5cfa(DAT_EXTMEM_0740,DAT_EXTMEM_0747);
  }
  else {
    FUN_CODE_344a();
    bVar1 = (*pbVar4 < 0x4c) << 7;
    if (*pbVar4 == 0x4c) goto LAB_CODE_43a2;
  }
  FUN_CODE_960e(DAT_EXTMEM_0745,DAT_EXTMEM_0746);
  if (-1 < (char)bVar1) {
    return;
  }
  if (DAT_EXTMEM_073f == 0x61) {
    *(undefined1 *)(DAT_INTMEM_b9 + -0x6d) = BANK0_R6;
  }
  FUN_CODE_84e6(DAT_INTMEM_b9,DAT_EXTMEM_073f);
LAB_CODE_43d8:
  DAT_INTMEM_ba = DAT_EXTMEM_0745;
  DAT_INTMEM_bb = DAT_EXTMEM_0746;
  FUN_CODE_957e(DAT_EXTMEM_073f,0x12);
  return;
}



// ==== FUN_CODE_43ee @ CODE:43ee size 2 callers [CODE:a335,CODE:a40d,CODE:a6fd]

char FUN_CODE_43ee(void)

{
  return '\x05' - (((0xb < DAT_INTMEM_b3) << 7) >> 7);
}



// ==== FUN_CODE_43f0 @ CODE:43f0 size 1 callers [CODE:a59d]

char FUN_CODE_43f0(byte *param_1)

{
  return '\x05' - (((0xb < *param_1) << 7) >> 7);
}



// ==== FUN_CODE_43f1 @ CODE:43f1 size 10 callers [CODE:80bc]

char FUN_CODE_43f1(byte param_1)

{
  return '\x05' - (((0xb < param_1) << 7) >> 7);
}



// ==== FUN_CODE_43fb @ CODE:43fb size 16 callers [CODE:2800]

char FUN_CODE_43fb(undefined1 param_1,undefined2 param_2)

{
  FUN_CODE_aefd(param_1,0,0,(char)((ushort)param_2 >> 8),(char)param_2);
  return DAT_INTMEM_b3 * '\x04';
}



// ==== FUN_CODE_440b @ CODE:440b size 8 callers [CODE:a077,CODE:a085,CODE:a093]

char FUN_CODE_440b(void)

{
  return DAT_INTMEM_b3 * '\x04';
}



// ==== FUN_CODE_4413 @ CODE:4413 size 11 callers [CODE:691c]

void FUN_CODE_4413(void)

{
  FUN_CODE_accc(0,0,0,0,DAT_EXTMEM_04ad,DAT_EXTMEM_04ae);
  return;
}



// ==== FUN_CODE_441e @ CODE:441e size 6 callers [CODE:691c]

void FUN_CODE_441e(undefined1 param_1)

{
  FUN_CODE_accc(param_1,param_1);
  return;
}



// ==== FUN_CODE_4434 @ CODE:4434 size 2 callers [CODE:a615]

char FUN_CODE_4434(void)

{
  return '\x06' - (((0xae < DAT_INTMEM_b3) << 7) >> 7);
}



// ==== FUN_CODE_4436 @ CODE:4436 size 11 callers [CODE:a5a5]

char FUN_CODE_4436(byte *param_1)

{
  return '\x06' - (((0xae < *param_1) << 7) >> 7);
}



// ==== FUN_CODE_4441 @ CODE:4441 size 3 callers [CODE:a6f1,CODE:a6f7]

char FUN_CODE_4441(void)

{
  return '\x06' - (((0xb1 < DAT_INTMEM_b3) << 7) >> 7);
}



// ==== FUN_CODE_4444 @ CODE:4444 size 10 callers [CODE:88c5]

char FUN_CODE_4444(byte param_1)

{
  return '\x06' - (((0xb1 < param_1) << 7) >> 7);
}



// ==== FUN_CODE_4468 @ CODE:4468 size 8 callers [CODE:2800]

undefined1 FUN_CODE_4468(void)

{
  return DAT_EXTMEM_04a6;
}



// ==== FUN_CODE_4470 @ CODE:4470 size 13 callers [CODE:2800]

void FUN_CODE_4470(undefined1 *param_1)

{
  DAT_EXTMEM_04d8 = *param_1;
  DAT_EXTMEM_04d9 = param_1[1];
  return;
}



// ==== FUN_CODE_4482 @ CODE:4482 size 8 callers [CODE:80bc]

char FUN_CODE_4482(void)

{
  char in_PSW;
  
  return '\x06' - (in_PSW >> 7);
}



// ==== FUN_CODE_448e @ CODE:448e size 7 callers [CODE:2800]

void FUN_CODE_448e(void)

{
  FUN_CODE_a90e(0,4);
  return;
}



// ==== FUN_CODE_4495 @ CODE:4495 size 15 callers [CODE:2800]

void FUN_CODE_4495(undefined1 *param_1)

{
  DAT_EXTMEM_04d6 = *param_1;
  DAT_EXTMEM_04d7 = param_1[1];
  return;
}



// ==== FUN_CODE_44b1 @ CODE:44b1 size 14 callers [CODE:2800]

char FUN_CODE_44b1(char param_1,byte param_2)

{
  return param_1 - (DAT_EXTMEM_04b0 - (((param_2 < DAT_EXTMEM_04b1) << 7) >> 7));
}



// ==== FUN_CODE_44bf @ CODE:44bf size 9 callers [CODE:2800]

char FUN_CODE_44bf(void)

{
  return DAT_INTMEM_b3 * '\x04';
}



// ==== FUN_CODE_44d1 @ CODE:44d1 size 14 callers [CODE:6d78,CODE:7f77]

undefined1 FUN_CODE_44d1(void)

{
  return *(undefined1 *)CONCAT11('\x06' - (((0x48 < DAT_INTMEM_b3) << 7) >> 7),DAT_INTMEM_b3 + 0xb7)
  ;
}



// ==== FUN_CODE_44e9 @ CODE:44e9 size 13 callers [CODE:2800]

char FUN_CODE_44e9(void)

{
  return '\x06' - (((0xe2 < DAT_INTMEM_b3) << 7) >> 7);
}



// ==== FUN_CODE_44f6 @ CODE:44f6 size 13 callers [CODE:a6eb]

char FUN_CODE_44f6(void)

{
  return '\x05' - (((1 < DAT_INTMEM_b3) << 7) >> 7);
}



// ==== FUN_CODE_4503 @ CODE:4503 size 7 callers [CODE:2800,CODE:6800]

undefined1 FUN_CODE_4503(short param_1)

{
  return *(undefined1 *)(param_1 + 1);
}



// ==== FUN_CODE_4512 @ CODE:4512 size 8 callers [CODE:a356]

char FUN_CODE_4512(void)

{
  char in_PSW;
  
  return '\x05' - (in_PSW >> 7);
}



// ==== FUN_CODE_451a @ CODE:451a size 7 callers [CODE:2800]

char FUN_CODE_451a(byte param_1,char param_2)

{
  return param_2 - ('\x0f' - (((param_1 < 0x2c) << 7) >> 7));
}



// ==== FUN_CODE_4521 @ CODE:4521 size 7 callers [CODE:7f77]

void FUN_CODE_4521(void)

{
  return;
}



// ==== FUN_CODE_4528 @ CODE:4528 size 10 callers [CODE:6d78]

void FUN_CODE_4528(void)

{
  FUN_CODE_adf3(0x4b0);
  return;
}



// ==== FUN_CODE_4532 @ CODE:4532 size 319 callers [CODE:3572]

char FUN_CODE_4532(byte param_1,byte param_2)

{
  byte bVar1;
  char cVar2;
  byte bVar3;
  
  FUN_CODE_ae2a(0x515);
  DAT_EXTMEM_0535 = 0;
  DAT_EXTMEM_0536 = '\0';
  DAT_EXTMEM_0537 = '\0';
  DAT_EXTMEM_0538 = 0;
  DAT_EXTMEM_0518 = param_1;
  DAT_EXTMEM_0519 = param_2;
  DAT_EXTMEM_0539 = param_1;
  if (param_2 == 0 && param_1 == 0) {
    DAT_EXTMEM_0524 = 0x30;
    DAT_EXTMEM_0525 = 0;
    DAT_EXTMEM_053a = param_2;
    FUN_CODE_5410(0x24,5,1);
    FUN_CODE_54d0();
    cVar2 = FUN_CODE_55c0();
    return cVar2;
  }
  cVar2 = DAT_EXTMEM_051c;
  if (DAT_EXTMEM_051c == '\0') {
    cVar2 = DAT_EXTMEM_051d;
  }
  bVar3 = 0;
  DAT_EXTMEM_053a = param_2;
  if (cVar2 != '\0') {
    bVar3 = DAT_EXTMEM_051a;
    if (DAT_EXTMEM_051a == 0) {
      bVar3 = DAT_EXTMEM_051b ^ 10;
    }
    DAT_EXTMEM_053a = param_2;
    if (bVar3 == 0) {
      bVar3 = (param_1 ^ 0x80) + 0x80;
      DAT_EXTMEM_053a = param_2;
      if ((param_1 ^ 0x80) < 0x80) {
        DAT_EXTMEM_0536 = '\x01';
        bVar3 = -param_2;
        DAT_EXTMEM_0539 = -(param_1 - (((param_2 != 0) << 7) >> 7));
        DAT_EXTMEM_053a = bVar3;
      }
    }
  }
  DAT_EXTMEM_0535 = '\0';
  FUN_CODE_ae2a(bVar3,0x530,0x2f,5,1);
  FUN_CODE_a99c(0);
  while( true ) {
    if (DAT_EXTMEM_053a == 0 && DAT_EXTMEM_0539 == 0) break;
    FUN_CODE_54aa();
    DAT_EXTMEM_0533 = param_1;
    DAT_EXTMEM_0534 = param_2;
    if (0x80U - (((param_2 < 10) << 7) >> 7) <= (param_1 ^ 0x80)) {
      FUN_CODE_aa6d(0x533,DAT_EXTMEM_0523 + -0x3a);
    }
    cVar2 = DAT_EXTMEM_0534 + 0x30;
    FUN_CODE_54b5(cVar2);
    FUN_CODE_a99c(cVar2);
    FUN_CODE_54aa();
  }
  cVar2 = DAT_EXTMEM_0535;
  if (DAT_EXTMEM_0535 == '\0') {
    cVar2 = DAT_EXTMEM_0536;
  }
  bVar3 = DAT_EXTMEM_0539;
  bVar1 = DAT_EXTMEM_053a;
  if (cVar2 != '\0') {
    cVar2 = DAT_EXTMEM_051e;
    if (DAT_EXTMEM_051e == '\0') {
      cVar2 = DAT_EXTMEM_051f;
    }
    if ((cVar2 == '\0') || ((DAT_EXTMEM_0521 >> 1 & 1) == 0)) {
      FUN_CODE_54b5(DAT_EXTMEM_053a);
      FUN_CODE_a99c(0x2d);
    }
    else {
      FUN_CODE_54d0();
      FUN_CODE_8b47(0,0x2d);
      FUN_CODE_53f3(0x537);
      FUN_CODE_5484(0x51e);
    }
  }
  FUN_CODE_adf3(0x530);
  FUN_CODE_5410();
  FUN_CODE_54d0();
  FUN_CODE_55c0();
  return DAT_EXTMEM_0537 + (bVar3 - ((CARRY1(DAT_EXTMEM_0538,bVar1) << 7) >> 7));
}



// ==== ISR_3B @ CODE:47aa size 86 callers []

undefined1 ISR_3B(undefined1 param_1)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  undefined1 uVar5;
  undefined1 uVar6;
  undefined1 uVar7;
  undefined1 uVar8;
  
  uVar8 = BANK0_R7;
  uVar7 = BANK0_R6;
  uVar6 = BANK0_R5;
  uVar5 = BANK0_R4;
  uVar4 = BANK0_R3;
  uVar3 = BANK0_R2;
  uVar2 = BANK0_R1;
  uVar1 = BANK0_R0;
  DAT_INTMEM_b9 = 0;
  DAT_EXTMEM_03ec = DAT_EXTMEM_2165;
  DAT_EXTMEM_2165 = FUN_CODE_355d();
  FUN_CODE_64a1();
  BANK0_R7 = uVar8;
  BANK0_R6 = uVar7;
  BANK0_R5 = uVar6;
  BANK0_R4 = uVar5;
  BANK0_R3 = uVar4;
  BANK0_R2 = uVar3;
  BANK0_R1 = uVar2;
  BANK0_R0 = uVar1;
  return param_1;
}



// ==== FUN_CODE_4800 @ CODE:4800 size 288 callers [CODE:3caa]

void FUN_CODE_4800(byte param_1,byte param_2)

{
  byte bVar1;
  
  DAT_EXTMEM_04aa = param_1;
  DAT_EXTMEM_04ab = param_2;
  FUN_CODE_96ff();
  FUN_CODE_7d83(0x4ac);
  FUN_CODE_87aa(0x45,0xb4);
  bVar1 = DAT_EXTMEM_04aa;
  if (DAT_EXTMEM_04aa == 0) {
    bVar1 = DAT_EXTMEM_04ab ^ 1;
  }
  if (bVar1 != 0) {
    bVar1 = DAT_EXTMEM_04aa;
    if (DAT_EXTMEM_04aa == 0) {
      bVar1 = DAT_EXTMEM_04ab ^ 2;
    }
    if (bVar1 != 0) {
      bVar1 = DAT_EXTMEM_04aa;
      if (DAT_EXTMEM_04aa == 0) {
        bVar1 = DAT_EXTMEM_04ab ^ 3;
      }
      if (bVar1 != 0) {
        bVar1 = DAT_EXTMEM_04aa;
        if (DAT_EXTMEM_04aa == 0) {
          bVar1 = DAT_EXTMEM_04ab ^ 4;
        }
        if (bVar1 != 0) {
          bVar1 = DAT_EXTMEM_04aa;
          if (DAT_EXTMEM_04aa == 0) {
            bVar1 = DAT_EXTMEM_04ab ^ 0x10;
          }
          if (bVar1 != 0) {
            bVar1 = DAT_EXTMEM_04aa;
            if (DAT_EXTMEM_04aa == 0) {
              bVar1 = DAT_EXTMEM_04ab ^ 0xd;
            }
            if (bVar1 != 0) {
              bVar1 = DAT_EXTMEM_04aa;
              if (DAT_EXTMEM_04aa == 0) {
                bVar1 = DAT_EXTMEM_04ab ^ 0xc;
              }
              if (bVar1 != 0) {
                bVar1 = DAT_EXTMEM_04aa;
                if (DAT_EXTMEM_04aa == 0) {
                  bVar1 = DAT_EXTMEM_04ab ^ 5;
                }
                if (bVar1 != 0) {
                  bVar1 = DAT_EXTMEM_04aa;
                  if (DAT_EXTMEM_04aa == 0) {
                    bVar1 = DAT_EXTMEM_04ab ^ 6;
                  }
                  if (bVar1 != 0) {
                    bVar1 = DAT_EXTMEM_04aa;
                    if (DAT_EXTMEM_04aa == 0) {
                      bVar1 = DAT_EXTMEM_04ab ^ 8;
                    }
                    if (bVar1 != 0) {
                      bVar1 = DAT_EXTMEM_04aa;
                      if (DAT_EXTMEM_04aa == 0) {
                        bVar1 = DAT_EXTMEM_04ab ^ 10;
                      }
                      if (bVar1 != 0) {
                        bVar1 = DAT_EXTMEM_04aa;
                        if (DAT_EXTMEM_04aa == 0) {
                          bVar1 = DAT_EXTMEM_04ab ^ 9;
                        }
                        if (bVar1 != 0) {
                          FUN_CODE_7d69(0x4aa,0xff);
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  FUN_CODE_87aa();
  FUN_CODE_7d6d(0x4ac,0xbe,0xb4,0xff);
  FUN_CODE_87aa();
  return;
}



// ==== FUN_CODE_4e91 @ CODE:4e91 size 267 callers [CODE:3caa]

void FUN_CODE_4e91(byte param_1,byte param_2)

{
  undefined1 uVar1;
  undefined1 uVar2;
  byte bVar3;
  undefined2 uVar4;
  
  DAT_EXTMEM_04aa = param_1;
  DAT_EXTMEM_04ab = param_2;
  FUN_CODE_a595();
  FUN_CODE_7d84(0,0x4ac);
  FUN_CODE_87aa(0x40,0xb5);
  bVar3 = DAT_EXTMEM_04aa;
  if (DAT_EXTMEM_04aa == 0) {
    bVar3 = DAT_EXTMEM_04ab ^ 0x13;
  }
  if (bVar3 == 0) {
    uVar2 = 0xb5;
    uVar1 = 0x43;
    uVar4 = 0x4ac;
  }
  else {
    bVar3 = DAT_EXTMEM_04aa;
    if (DAT_EXTMEM_04aa == 0) {
      bVar3 = DAT_EXTMEM_04ab ^ 2;
    }
    if (bVar3 == 0) goto LAB_CODE_4f93;
    bVar3 = DAT_EXTMEM_04aa;
    if (DAT_EXTMEM_04aa == 0) {
      bVar3 = DAT_EXTMEM_04ab ^ 5;
    }
    if (bVar3 == 0) goto LAB_CODE_4f93;
    bVar3 = DAT_EXTMEM_04aa;
    if (DAT_EXTMEM_04aa == 0) {
      bVar3 = DAT_EXTMEM_04ab ^ 0x2d;
    }
    if (bVar3 == 0) goto LAB_CODE_4f93;
    bVar3 = DAT_EXTMEM_04aa;
    if (DAT_EXTMEM_04aa == 0) {
      bVar3 = DAT_EXTMEM_04ab ^ 0x33;
    }
    if (bVar3 == 0) goto LAB_CODE_4f93;
    bVar3 = DAT_EXTMEM_04aa;
    if (DAT_EXTMEM_04aa == 0) {
      bVar3 = DAT_EXTMEM_04ab ^ 0xc;
    }
    if (bVar3 == 0) goto LAB_CODE_4f93;
    bVar3 = DAT_EXTMEM_04aa;
    if (DAT_EXTMEM_04aa == 0) {
      bVar3 = DAT_EXTMEM_04ab ^ 0x37;
    }
    if (bVar3 == 0) goto LAB_CODE_4f93;
    bVar3 = DAT_EXTMEM_04aa;
    if (DAT_EXTMEM_04aa == 0) {
      bVar3 = DAT_EXTMEM_04ab ^ 0x34;
    }
    if (bVar3 == 0) goto LAB_CODE_4f93;
    bVar3 = DAT_EXTMEM_04aa;
    if (DAT_EXTMEM_04aa == 0) {
      bVar3 = DAT_EXTMEM_04ab ^ 0x32;
    }
    if (bVar3 == 0) goto LAB_CODE_4f93;
    bVar3 = DAT_EXTMEM_04aa;
    if (DAT_EXTMEM_04aa == 0) {
      bVar3 = DAT_EXTMEM_04ab ^ 0x2c;
    }
    if (bVar3 == 0) goto LAB_CODE_4f93;
    bVar3 = DAT_EXTMEM_04aa;
    if (DAT_EXTMEM_04aa == 0) {
      bVar3 = DAT_EXTMEM_04ab ^ 0x30;
    }
    if (bVar3 == 0) goto LAB_CODE_4f93;
    uVar2 = 0xb4;
    uVar1 = 0x40;
    uVar4 = 0x4aa;
  }
  FUN_CODE_7d6d(uVar4,uVar1,uVar2,0xff);
LAB_CODE_4f93:
  FUN_CODE_87aa();
  FUN_CODE_7d98();
  FUN_CODE_87aa();
  return;
}



// ==== FUN_CODE_4f9c @ CODE:4f9c size 98 callers [CODE:9e99]

void FUN_CODE_4f9c(byte *param_1)

{
  byte bVar1;
  char in_PSW;
  char cVar2;
  
  FUN_CODE_9b12();
  if (in_PSW < '\0') {
    FUN_CODE_8a68();
    FUN_CODE_88c5();
  }
  bVar1 = DAT_INTMEM_b3;
  FUN_CODE_97db();
  cVar2 = (*param_1 == 0) << 7;
  if (cVar2 < '\0') {
    FUN_CODE_7a1a(*param_1 - 1);
  }
  else {
    cVar2 = (0xd4 < bVar1) << 7;
    FUN_CODE_97dd();
    *param_1 = *param_1 - 1;
  }
  if ((DAT_INTMEM_cc != '\t') && (DAT_INTMEM_cc != '\v')) {
    FUN_CODE_a139(DAT_INTMEM_b3);
    if (cVar2 < '\0') {
      FUN_CODE_97cc();
      bVar1 = 0x80 - (((param_1[1] < 0xc9) << 7) >> 7);
      if (bVar1 <= (*param_1 ^ 0x80)) {
        FUN_CODE_7712();
        return;
      }
      FUN_CODE_97cc((*param_1 ^ 0x80) - bVar1);
      FUN_CODE_aa6d(0,1);
      return;
    }
  }
  FUN_CODE_97cc();
  *param_1 = 0;
  param_1[1] = 0;
  return;
}



// ==== ISR_13 @ CODE:4fff size 1 callers []

void ISR_13(void)

{
  return;
}



// ==== FUN_CODE_5078 @ CODE:5078 size 3 callers [CODE:8864,CODE:8e81]

char FUN_CODE_5078(void)

{
  return '\a' - (((0xef < DAT_INTMEM_b3) << 7) >> 7);
}



// ==== FUN_CODE_507b @ CODE:507b size 2 callers [CODE:8864]

char FUN_CODE_507b(byte param_1)

{
  return '\a' - (((0xef < param_1) << 7) >> 7);
}



// ==== FUN_CODE_507d @ CODE:507d size 8 callers [CODE:8864]

char FUN_CODE_507d(void)

{
  char in_PSW;
  
  return '\a' - (in_PSW >> 7);
}



// ==== FUN_CODE_5085 @ CODE:5085 size 13 callers [CODE:8864,CODE:8e81]

char FUN_CODE_5085(void)

{
  return '\a' - (((0xf5 < DAT_INTMEM_b3) << 7) >> 7);
}



// ==== FUN_CODE_50a8 @ CODE:50a8 size 3 callers [CODE:8f87]

char FUN_CODE_50a8(void)

{
  return '\a' - (((0xf7 < DAT_INTMEM_b3) << 7) >> 7);
}



// ==== FUN_CODE_50ab @ CODE:50ab size 10 callers [CODE:8f87]

char FUN_CODE_50ab(byte param_1)

{
  return '\a' - (((0xf7 < param_1) << 7) >> 7);
}



// ==== FUN_CODE_50e1 @ CODE:50e1 size 13 callers [CODE:8e81,CODE:a6b5]

char FUN_CODE_50e1(void)

{
  return '\a' - (((0xf1 < DAT_INTMEM_b3) << 7) >> 7);
}



// ==== ISR_0B @ CODE:50fb size 250 callers []

undefined1 ISR_0B(undefined1 param_1)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  undefined1 uVar5;
  undefined1 uVar6;
  undefined1 uVar7;
  undefined1 uVar8;
  
  uVar8 = BANK0_R7;
  uVar7 = BANK0_R6;
  uVar6 = BANK0_R5;
  uVar5 = BANK0_R4;
  uVar4 = BANK0_R3;
  uVar3 = BANK0_R2;
  uVar2 = BANK0_R1;
  uVar1 = BANK0_R0;
  DAT_EXTMEM_0551 = DAT_EXTMEM_2038;
  DAT_EXTMEM_0552 = DAT_EXTMEM_2039;
  if (((DAT_EXTMEM_2038 & 3) != 0) || ((DAT_EXTMEM_2039 & 3) != 0)) {
    FUN_CODE_a47b(0x203a);
    DAT_EXTMEM_0763 = 2;
    DAT_INTMEM_b9 = 0;
    FUN_CODE_957e(0x2f,5);
  }
  if ((DAT_EXTMEM_0551 & 0xc) != 0) {
    DAT_EXTMEM_203a = DAT_EXTMEM_203a & 0xf3;
    DAT_INTMEM_b9 = 0;
    FUN_CODE_957e(0x31,5);
  }
  if (((DAT_EXTMEM_0551 & 0x30) != 0) || ((DAT_EXTMEM_0552 & 0xc) != 0)) {
    DAT_EXTMEM_203a = DAT_EXTMEM_203a & 0xcf;
    DAT_EXTMEM_203b = DAT_EXTMEM_203b & 0xf3;
    DAT_EXTMEM_0764 = 2;
    DAT_INTMEM_b9 = 1;
    FUN_CODE_957e(0x2f,5);
  }
  if ((DAT_EXTMEM_0551 & 0xc0) != 0) {
    DAT_EXTMEM_203a = DAT_EXTMEM_203a & 0x3f;
    DAT_INTMEM_b9 = 1;
    FUN_CODE_957e(0x31,5);
  }
  DAT_EXTMEM_2038 = DAT_EXTMEM_2038 & ~DAT_EXTMEM_0551;
  DAT_EXTMEM_2039 = DAT_EXTMEM_2039 & ~DAT_EXTMEM_0552;
  PT0 = 0;
  BANK0_R7 = uVar8;
  BANK0_R6 = uVar7;
  BANK0_R5 = uVar6;
  BANK0_R4 = uVar5;
  BANK0_R3 = uVar4;
  BANK0_R2 = uVar3;
  BANK0_R1 = uVar2;
  BANK0_R0 = uVar1;
  return param_1;
}



// ==== FUN_CODE_52ef @ CODE:52ef size 248 callers [CODE:3caa]

void FUN_CODE_52ef(void)

{
  byte bVar1;
  
  FUN_CODE_7d83(0x4aa);
  FUN_CODE_87aa(0xd1,0xb3);
  bVar1 = DAT_EXTMEM_04aa;
  if (DAT_EXTMEM_04aa == 0) {
    bVar1 = DAT_EXTMEM_04ab ^ 1;
  }
  if (bVar1 != 0) {
    bVar1 = DAT_EXTMEM_04aa;
    if (DAT_EXTMEM_04aa == 0) {
      bVar1 = DAT_EXTMEM_04ab ^ 0x21;
    }
    if (bVar1 != 0) {
      bVar1 = DAT_EXTMEM_04aa;
      if (DAT_EXTMEM_04aa == 0) {
        bVar1 = DAT_EXTMEM_04ab ^ 3;
      }
      if (bVar1 != 0) {
        bVar1 = DAT_EXTMEM_04aa;
        if (DAT_EXTMEM_04aa == 0) {
          bVar1 = DAT_EXTMEM_04ab ^ 6;
        }
        if (bVar1 != 0) {
          bVar1 = DAT_EXTMEM_04aa;
          if (DAT_EXTMEM_04aa == 0) {
            bVar1 = DAT_EXTMEM_04ab ^ 0x2a;
          }
          if (bVar1 != 0) {
            bVar1 = DAT_EXTMEM_04aa;
            if (DAT_EXTMEM_04aa == 0) {
              bVar1 = DAT_EXTMEM_04ab ^ 0x51;
            }
            if (bVar1 != 0) {
              bVar1 = DAT_EXTMEM_04aa;
              if (DAT_EXTMEM_04aa == 0) {
                bVar1 = DAT_EXTMEM_04ab ^ 0x22;
              }
              if (bVar1 != 0) {
                bVar1 = DAT_EXTMEM_04aa;
                if (DAT_EXTMEM_04aa == 0) {
                  bVar1 = DAT_EXTMEM_04ab ^ 0x61;
                }
                if (bVar1 != 0) {
                  bVar1 = DAT_EXTMEM_04aa;
                  if (DAT_EXTMEM_04aa == 0) {
                    bVar1 = DAT_EXTMEM_04ab ^ 0x29;
                  }
                  if (bVar1 != 0) {
                    bVar1 = DAT_EXTMEM_04aa;
                    if (DAT_EXTMEM_04aa == 0) {
                      bVar1 = DAT_EXTMEM_04ab ^ 0x80;
                    }
                    if (bVar1 != 0) {
                      bVar1 = DAT_EXTMEM_04aa;
                      if (DAT_EXTMEM_04aa == 0) {
                        bVar1 = DAT_EXTMEM_04ab ^ 0x50;
                      }
                      if (bVar1 != 0) {
                        FUN_CODE_7d69(0x4aa,0xff);
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  FUN_CODE_87aa();
  FUN_CODE_7d98();
  FUN_CODE_87aa();
  return;
}



// ==== FUN_CODE_53e7 @ CODE:53e7 size 3 callers [CODE:3572]

void FUN_CODE_53e7(void)

{
  FUN_CODE_adf3(0x504);
  FUN_CODE_a934();
  return;
}



// ==== FUN_CODE_53ea @ CODE:53ea size 6 callers [CODE:55c0]

void FUN_CODE_53ea(void)

{
  FUN_CODE_adf3();
  FUN_CODE_a934();
  return;
}



// ==== FUN_CODE_53f0 @ CODE:53f0 size 3 callers [CODE:3572]

void FUN_CODE_53f0(void)

{
  FUN_CODE_aa6d(0,0x505,1);
  return;
}



// ==== FUN_CODE_53f3 @ CODE:53f3 size 1 callers [CODE:4532,CODE:55c0,CODE:7207]

void FUN_CODE_53f3(void)

{
  FUN_CODE_aa6d(0,1);
  return;
}



// ==== FUN_CODE_53f4 @ CODE:53f4 size 6 callers [CODE:3572]

void FUN_CODE_53f4(void)

{
  FUN_CODE_aa6d(1);
  return;
}



// ==== FUN_CODE_53fa @ CODE:53fa size 22 callers [CODE:3572]

void FUN_CODE_53fa(void)

{
  FUN_CODE_adfc(0x507,2);
  FUN_CODE_aa99();
  DAT_EXTMEM_051a = 0;
  return;
}



// ==== FUN_CODE_5410 @ CODE:5410 size 24 callers [CODE:4532]

void FUN_CODE_5410(void)

{
  FUN_CODE_ae2a(0x53e);
  DAT_EXTMEM_0541 = DAT_EXTMEM_051e;
  DAT_EXTMEM_0542 = DAT_EXTMEM_051f;
  DAT_EXTMEM_0543 = DAT_EXTMEM_0520;
  DAT_EXTMEM_0544 = DAT_EXTMEM_0521;
  return;
}



// ==== FUN_CODE_5428 @ CODE:5428 size 13 callers [CODE:3572]

void FUN_CODE_5428(undefined1 *param_1)

{
  DAT_EXTMEM_0543 = *param_1;
  DAT_EXTMEM_0544 = param_1[1];
  return;
}



// ==== FUN_CODE_5435 @ CODE:5435 size 36 callers [CODE:3572]

void FUN_CODE_5435(undefined1 param_1,undefined1 *param_2)

{
  *param_2 = param_1;
  DAT_EXTMEM_051e = DAT_EXTMEM_050a;
  DAT_EXTMEM_051f = DAT_EXTMEM_050b;
  DAT_EXTMEM_0520 = DAT_EXTMEM_050c;
  DAT_EXTMEM_0521 = DAT_EXTMEM_050d;
  DAT_EXTMEM_0522 = 0;
  return;
}



// ==== FUN_CODE_5459 @ CODE:5459 size 16 callers [CODE:55c0]

char FUN_CODE_5459(void)

{
  return (DAT_EXTMEM_0541 ^ 0x80) - (-0x80 - (((DAT_EXTMEM_0542 == '\0') << 7) >> 7));
}



// ==== FUN_CODE_5469 @ CODE:5469 size 3 callers [CODE:81ed]

void FUN_CODE_5469(void)

{
  FUN_CODE_aa83(0,0x4c2,1);
  return;
}



// ==== FUN_CODE_546c @ CODE:546c size 13 callers [CODE:66fd]

void FUN_CODE_546c(void)

{
  FUN_CODE_aa83(0,1);
  return;
}



// ==== FUN_CODE_5479 @ CODE:5479 size 8 callers [CODE:3572,CODE:55c0]

void FUN_CODE_5479(char param_1)

{
  FUN_CODE_adf3(param_1 >> 7,param_1);
  return;
}



// ==== FUN_CODE_5481 @ CODE:5481 size 3 callers [CODE:55c0]

void FUN_CODE_5481(void)

{
  FUN_CODE_aa6d(0x541,0xff);
  return;
}



// ==== FUN_CODE_5484 @ CODE:5484 size 7 callers [CODE:4532]

void FUN_CODE_5484(void)

{
  FUN_CODE_aa6d(0xff);
  return;
}



// ==== FUN_CODE_548b @ CODE:548b size 12 callers [CODE:3572]

void FUN_CODE_548b(void)

{
  FUN_CODE_adfc(0x507,2);
  FUN_CODE_aa99();
  return;
}



// ==== FUN_CODE_5497 @ CODE:5497 size 6 callers [CODE:3572]

void FUN_CODE_5497(void)

{
  FUN_CODE_adf3(0x501);
  return;
}



// ==== FUN_CODE_549d @ CODE:549d size 13 callers [CODE:7207]

undefined1 FUN_CODE_549d(void)

{
  return *(undefined1 *)CONCAT11(DAT_EXTMEM_0559,DAT_EXTMEM_055a);
}



// ==== FUN_CODE_54aa @ CODE:54aa size 11 callers [CODE:4532]

void FUN_CODE_54aa(void)

{
  FUN_CODE_a9e2(DAT_EXTMEM_051a,DAT_EXTMEM_051b);
  return;
}



// ==== FUN_CODE_54b5 @ CODE:54b5 size 10 callers [CODE:4532]

void FUN_CODE_54b5(void)

{
  FUN_CODE_ae13(0x530,0xff);
  return;
}



// ==== FUN_CODE_54ca @ CODE:54ca size 6 callers [CODE:8b47]

void FUN_CODE_54ca(void)

{
  FUN_CODE_adf3(0x54e);
  return;
}



// ==== FUN_CODE_54d0 @ CODE:54d0 size 6 callers [CODE:4532]

void FUN_CODE_54d0(void)

{
  FUN_CODE_adf3(0x515);
  return;
}



// ==== FUN_CODE_55c0 @ CODE:55c0 size 211 callers [CODE:3572,CODE:4532]

undefined1 FUN_CODE_55c0(void)

{
  bool bVar1;
  byte bVar2;
  char cVar3;
  char in_PSW;
  
  FUN_CODE_ae2a(0x53b);
  DAT_EXTMEM_0545 = 0;
  DAT_EXTMEM_0546 = 0;
  DAT_EXTMEM_0547 = 0;
  DAT_EXTMEM_0548 = 0x20;
  FUN_CODE_5459();
  if (-1 < in_PSW) {
    DAT_EXTMEM_0549 = 0;
    DAT_EXTMEM_054a = 0;
    FUN_CODE_adf3(0x53e);
    FUN_CODE_ae2a(0x54b);
    while( true ) {
      cVar3 = FUN_CODE_53ea(0x54b);
      if (cVar3 == '\0') break;
      FUN_CODE_53f3(0x549);
      FUN_CODE_53f3(0x54c);
    }
    in_PSW = ((DAT_EXTMEM_0549 ^ 0x80) <
             (DAT_EXTMEM_0541 ^ 0x80) - (((DAT_EXTMEM_054a < DAT_EXTMEM_0542) << 7) >> 7)) << 7;
    if (in_PSW < '\0') {
      bVar1 = DAT_EXTMEM_0542 < DAT_EXTMEM_054a;
      DAT_EXTMEM_0542 = DAT_EXTMEM_0542 - DAT_EXTMEM_054a;
      bVar2 = DAT_EXTMEM_0549 - ((bVar1 << 7) >> 7);
      in_PSW = (DAT_EXTMEM_0541 < bVar2) << 7;
      DAT_EXTMEM_0541 = DAT_EXTMEM_0541 - bVar2;
    }
    else {
      DAT_EXTMEM_0541 = 0;
      DAT_EXTMEM_0542 = 0;
    }
    if ((DAT_EXTMEM_0544 >> 1 & 1) != 0) {
      DAT_EXTMEM_0547 = 0;
      DAT_EXTMEM_0548 = 0x30;
    }
  }
  if ((DAT_EXTMEM_0544 & 1) != 1) {
    while( true ) {
      FUN_CODE_5459();
      if (in_PSW < '\0') break;
      FUN_CODE_5693();
      FUN_CODE_53f3();
      FUN_CODE_5481();
    }
  }
  while( true ) {
    cVar3 = FUN_CODE_53ea(0x53e);
    if (cVar3 == '\0') break;
    FUN_CODE_5479(0x53b,cVar3);
    FUN_CODE_8b47();
    FUN_CODE_53f3(0x545);
    FUN_CODE_53f3(0x53f);
  }
  while( true ) {
    FUN_CODE_5459();
    if (in_PSW < '\0') break;
    FUN_CODE_5693();
    FUN_CODE_53f3();
    FUN_CODE_5481();
  }
  return DAT_EXTMEM_0546;
}



// ==== FUN_CODE_5693 @ CODE:5693 size 21 callers [CODE:55c0]

void FUN_CODE_5693(void)

{
  FUN_CODE_adf3(0x53b);
  FUN_CODE_8b47(DAT_EXTMEM_0547,DAT_EXTMEM_0548);
  return;
}



// ==== ISR_4B @ CODE:5c3c size 190 callers []

undefined1 ISR_4B(undefined1 param_1)

{
  byte bVar1;
  undefined1 uVar2;
  char cVar3;
  undefined1 uVar4;
  undefined1 uVar5;
  undefined1 uVar6;
  undefined1 uVar7;
  undefined1 uVar8;
  undefined1 uVar9;
  undefined1 uVar10;
  undefined1 uVar11;
  byte *pbVar12;
  
  uVar11 = BANK0_R7;
  uVar10 = BANK0_R6;
  uVar9 = BANK0_R5;
  uVar8 = BANK0_R4;
  uVar7 = BANK0_R3;
  uVar6 = BANK0_R2;
  uVar5 = BANK0_R1;
  uVar4 = BANK0_R0;
  DAT_INTMEM_b9 = DAT_EXTMEM_0721;
  cVar3 = FIFLG_7;
  if (cVar3 != '\0') {
    if (DAT_INTMEM_d0 == '\x04') {
      if (DAT_INTMEM_ce == DAT_INTMEM_d1) {
        DAT_INTMEM_d0 = '\0';
      }
      else {
        FUN_CODE_770c();
        pbVar12 = (byte *)&DAT_INTMEM_ce;
        FUN_CODE_76ec(DAT_INTMEM_ce);
        *pbVar12 = *pbVar12 + 1;
        if (0xef < *pbVar12) {
          *pbVar12 = 0;
        }
      }
    }
    FIFLG_7 = 0;
  }
  cVar3 = FIFLG_6;
  if (cVar3 != '\0') {
    FIFLG_6 = 0;
  }
  cVar3 = FIFLG_5;
  if (cVar3 != '\0') {
    if (DAT_INTMEM_cf == '\x01') {
      DAT_INTMEM_d2 = 0;
      DAT_INTMEM_cf = '\x02';
    }
    if (DAT_INTMEM_cf == '\x02') {
      bVar1 = HPSTAT;
      HPSTAT = bVar1 | 0x10;
      uVar2 = EPCONFIG;
      FUN_CODE_66fd(uVar2);
    }
    else {
      DAT_INTMEM_ba = EPCONFIG;
    }
  }
  bVar1 = HPSTAT;
  if ((bVar1 >> 3 & 1) != 0) {
    DAT_INTMEM_d2 = 0;
    DAT_INTMEM_cf = '\x01';
    bVar1 = HPSTAT;
    HPSTAT = bVar1 & 0xe7;
  }
  bVar1 = FIFLG;
  if ((bVar1 & 5) != 0) {
    FUN_CODE_9b66();
  }
  DAT_SFR_c3 = 0xfb;
  BANK0_R7 = uVar11;
  BANK0_R6 = uVar10;
  BANK0_R5 = uVar9;
  BANK0_R4 = uVar8;
  BANK0_R3 = uVar7;
  BANK0_R2 = uVar6;
  BANK0_R1 = uVar5;
  BANK0_R0 = uVar4;
  return param_1;
}



// ==== FUN_CODE_5cfa @ CODE:5cfa size 189 callers [CODE:42a5]

void FUN_CODE_5cfa(byte param_1,byte param_2)

{
  byte bVar1;
  char cVar2;
  byte bVar3;
  char *pcVar4;
  
  DAT_EXTMEM_075c = param_2 * '\x02';
  pcVar4 = &DAT_EXTMEM_075d;
  DAT_EXTMEM_075d = 1;
  DAT_EXTMEM_075b = param_1;
  FUN_CODE_344a();
  if (*pcVar4 == 'L') {
    FUN_CODE_a59d();
    param_2 = param_2 == 0;
    DAT_EXTMEM_075c = DAT_EXTMEM_075c & 0xfe | param_2;
    DAT_EXTMEM_075e = ' ';
    do {
      DAT_EXTMEM_075e = DAT_EXTMEM_075e + -1;
    } while (DAT_EXTMEM_075e != '\0');
    DAT_EXTMEM_075e = 0;
  }
  else {
    cVar2 = '\0';
    DAT_EXTMEM_075e = 0;
    while (bVar3 = FUN_CODE_33e9(cVar2), bVar1 = DAT_EXTMEM_075e, (bVar3 >> 6 & 1) != 1) {
      DAT_EXTMEM_075e = DAT_EXTMEM_075e + 1;
      cVar2 = bVar1 + 0x9c;
      if (100 < DAT_EXTMEM_075e) {
        return;
      }
    }
    FUN_CODE_a59d();
    param_2 = param_2 & 1;
    DAT_EXTMEM_075c = DAT_EXTMEM_075c & 0xfe | param_2;
  }
  FUN_CODE_a5a5();
  bVar1 = (param_2 & 1) << 5;
  DAT_EXTMEM_075d = DAT_EXTMEM_075d & 0xdf | bVar1;
  if (DAT_EXTMEM_075b != 1) {
    FUN_CODE_a7f0();
    DAT_EXTMEM_075b = bVar1;
  }
  DAT_EXTMEM_075d = DAT_EXTMEM_075d & 0x3f | DAT_EXTMEM_075b << 6;
  bVar1 = DAT_EXTMEM_075c;
  FUN_CODE_3472(DAT_EXTMEM_075c);
  FUN_CODE_a9ae(bVar1,0x12);
  FUN_CODE_a9ae(DAT_EXTMEM_075d,0x13);
  FUN_CODE_a9ae(0x11,0x58);
  return;
}



// ==== FUN_CODE_5db7 @ CODE:5db7 size 188 callers [CODE:793a]

void FUN_CODE_5db7(byte param_1,undefined1 param_2)

{
  byte bVar1;
  char cVar2;
  char cVar3;
  byte bVar4;
  undefined1 uVar5;
  char cVar6;
  short sVar7;
  byte *pbVar8;
  byte *pbVar9;
  
  bVar4 = T2MOD;
  T2MOD = bVar4 & 0xfb;
  if (BANK2_R5 == '\0') {
    bVar4 = T2MOD;
    T2MOD = bVar4 | 4;
    return;
  }
  DAT_EXTMEM_04a5 = '\0';
  DAT_EXTMEM_04a6 = BANK2_R5;
  BANK2_R5 = 0;
  bVar4 = T2MOD;
  T2MOD = bVar4 | 4;
  if (BANK1_R2 != '\0') {
    for (BANK2_R6 = 0; BANK2_R6 < 0xc; BANK2_R6 = BANK2_R6 + 1) {
      bVar4 = BANK2_R6;
      uVar5 = FUN_CODE_8b2b(BANK2_R6 - 0xc);
      DAT_EXTMEM_04a3 = uVar5;
      DAT_EXTMEM_04a4 = bVar4;
      if (*(char *)CONCAT11(param_2,bVar4) != '\0') {
        pbVar8 = (byte *)CONCAT11(4,bVar4 + 5);
        FUN_CODE_8b1b(bVar4);
        param_2 = uVar5;
        if (*pbVar8 == param_1) {
          sVar7 = 0x4a3;
          FUN_CODE_8b40();
          bVar4 = *(byte *)(sVar7 + 3);
          param_1 = *(byte *)(sVar7 + 4);
          pbVar8 = (byte *)0x4a6;
          bVar1 = DAT_EXTMEM_04a5 - (((param_1 < DAT_EXTMEM_04a6 + 1U) << 7) >> 7);
          cVar6 = (bVar4 < bVar1) << 7;
          if (bVar4 >= bVar1) {
            cVar2 = DAT_EXTMEM_04a5;
            cVar3 = DAT_EXTMEM_04a6;
            FUN_CODE_8b24();
            pbVar9 = pbVar8 + 2;
            bVar4 = cVar3 - (cVar6 >> 7);
            cVar6 = (char)((ushort)pbVar9 >> 8);
            if ((char)pbVar9 == '\0') {
              cVar6 = cVar6 + -1;
            }
            pbVar8[1] = *(char *)CONCAT11(cVar6,(char)pbVar9 + -1) -
                        (cVar2 - (((*pbVar9 < bVar4) << 7) >> 7));
            pbVar8[2] = *pbVar9 - bVar4;
            param_2 = uVar5;
            goto LAB_CODE_5e6c;
          }
          FUN_CODE_8b3b(bVar4 - bVar1);
          param_1 = *pbVar8;
          pbVar8 = pbVar8 + 1;
          FUN_CODE_8800(*pbVar8,0x10);
          param_2 = uVar5;
        }
        FUN_CODE_8b3b();
        *pbVar8 = 0;
        if (BANK1_R2 != '\0') {
          BANK1_R2 = BANK1_R2 + -1;
        }
        if (BANK1_R2 == '\0') {
          return;
        }
      }
LAB_CODE_5e6c:
    }
  }
  return;
}



// ==== FUN_CODE_5e73 @ CODE:5e73 size 48 callers [CODE:7eb6]

void FUN_CODE_5e73(char param_1)

{
  byte bVar1;
  short sVar2;
  
  _1_6 = 0;
  DAT_EXTMEM_04c5 = param_1;
  FUN_CODE_a727();
  if (DAT_EXTMEM_04c5 != param_1) {
    bVar1 = DAT_EXTMEM_04c5 - 1;
    if ((bVar1 < 9) << 7 < '\0') {
      sVar2 = 0x5e9a;
      if (CARRY1(bVar1,bVar1)) {
        sVar2 = 0x5f9a;
      }
                    /* WARNING: Could not recover jumptable at 0x5e99. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (*(code *)(sVar2 + (ushort)(bVar1 * '\x02')))();
      return;
    }
    FUN_CODE_a72d(DAT_EXTMEM_04c5);
  }
  return;
}



// ==== FUN_CODE_5fe3 @ CODE:5fe3 size 29 callers [CODE:8ff0]

void FUN_CODE_5fe3(void)

{
  DAT_INTMEM_b3 = BANK0_R7;
  FUN_CODE_a4fd();
  FUN_CODE_a76f();
  if (_0_2 != '\x01') {
    thunk_FUN_CODE_a0f5();
    FUN_CODE_a356();
    FUN_CODE_a069();
    return;
  }
  FUN_CODE_a40d();
  FUN_CODE_a615();
  return;
}



// ==== FUN_CODE_6162 @ CODE:6162 size 172 callers [CODE:3caa]

void FUN_CODE_6162(void)

{
  byte bVar1;
  
  FUN_CODE_7d83(0x4aa);
  FUN_CODE_87aa(0xff,0xb4);
  bVar1 = DAT_EXTMEM_04aa;
  if (DAT_EXTMEM_04aa == 0) {
    bVar1 = DAT_EXTMEM_04ab ^ 0xe;
  }
  if (bVar1 != 0) {
    bVar1 = DAT_EXTMEM_04aa;
    if (DAT_EXTMEM_04aa == 0) {
      bVar1 = DAT_EXTMEM_04ab ^ 2;
    }
    if (bVar1 != 0) {
      bVar1 = DAT_EXTMEM_04aa;
      if (DAT_EXTMEM_04aa == 0) {
        bVar1 = DAT_EXTMEM_04ab ^ 0xf;
      }
      if (bVar1 != 0) {
        bVar1 = DAT_EXTMEM_04aa;
        if (DAT_EXTMEM_04aa == 0) {
          bVar1 = DAT_EXTMEM_04ab ^ 0x13;
        }
        if (bVar1 != 0) {
          bVar1 = DAT_EXTMEM_04aa;
          if (DAT_EXTMEM_04aa == 0) {
            bVar1 = DAT_EXTMEM_04ab ^ 10;
          }
          if (bVar1 != 0) {
            bVar1 = DAT_EXTMEM_04aa;
            if (DAT_EXTMEM_04aa == 0) {
              bVar1 = DAT_EXTMEM_04ab ^ 0x1a;
            }
            if (bVar1 != 0) {
              bVar1 = DAT_EXTMEM_04aa;
              if (DAT_EXTMEM_04aa == 0) {
                bVar1 = DAT_EXTMEM_04ab ^ 6;
              }
              if (bVar1 != 0) {
                FUN_CODE_7d6d(0x4aa,0x40,0xb4,0xff);
              }
            }
          }
        }
      }
    }
  }
  FUN_CODE_87aa();
  FUN_CODE_7d98();
  FUN_CODE_87aa();
  return;
}



// ==== FUN_CODE_6215 @ CODE:6215 size 2 callers [CODE:8ef3]

char FUN_CODE_6215(byte param_1,char param_2)

{
  return param_2 - (((0xfa < param_1) << 7) >> 7);
}



// ==== FUN_CODE_6217 @ CODE:6217 size 7 callers [CODE:8ef3,CODE:8f19]

char FUN_CODE_6217(char param_1)

{
  char in_PSW;
  
  return param_1 - (in_PSW >> 7);
}



// ==== FUN_CODE_6283 @ CODE:6283 size 8 callers [CODE:967b]

undefined1 FUN_CODE_6283(void)

{
  return DAT_EXTMEM_0751;
}



// ==== FUN_CODE_629e @ CODE:629e size 7 callers [CODE:8ef3]

void FUN_CODE_629e(void)

{
  return;
}



// ==== FUN_CODE_6406 @ CODE:6406 size 155 callers [CODE:9645]

void FUN_CODE_6406(undefined1 param_1,undefined1 param_2)

{
  undefined1 uVar1;
  char cVar2;
  undefined1 *puVar3;
  char *pcVar4;
  
  DAT_EXTMEM_04b2 = 3;
  DAT_EXTMEM_04b3 = DAT_INTMEM_b3;
  if (*(char *)(DAT_INTMEM_b3 + '#') == '\x02') {
    uVar1 = 0x66;
  }
  else {
    uVar1 = 0x7c;
  }
  FUN_CODE_87aa(uVar1,0xb1,0xff);
  puVar3 = &DAT_EXTMEM_04b2;
  FUN_CODE_1f10();
  FUN_CODE_1d2a();
  *puVar3 = 0xb5;
  pcVar4 = &DAT_EXTMEM_04b2;
  cVar2 = DAT_EXTMEM_04b3;
  FUN_CODE_1d23();
  *pcVar4 = cVar2;
  FUN_CODE_1e48();
  puVar3 = &DAT_EXTMEM_04b2;
  FUN_CODE_1f56();
  FUN_CODE_1d2a();
  *puVar3 = param_2;
  FUN_CODE_1e0a(cVar2 * '\x02' + -0x6b);
  FUN_CODE_1d2a();
  *puVar3 = param_1;
  puVar3 = &DAT_EXTMEM_04b2;
  uVar1 = param_2;
  FUN_CODE_1d23();
  *puVar3 = uVar1;
  puVar3 = &DAT_EXTMEM_04b3;
  FUN_CODE_1e0a(DAT_EXTMEM_04b3 * '\x02' + '-');
  FUN_CODE_1d2a();
  *puVar3 = param_1;
  puVar3 = &DAT_EXTMEM_04b2;
  FUN_CODE_1d23();
  *puVar3 = param_2;
  puVar3 = &DAT_EXTMEM_04b2;
  uVar1 = DAT_INTMEM_6c;
  FUN_CODE_1d23();
  *puVar3 = uVar1;
  puVar3 = &DAT_EXTMEM_04b2;
  uVar1 = DAT_EXTMEM_0707;
  FUN_CODE_1d23();
  *puVar3 = uVar1;
  FUN_CODE_1f30(0x4b2);
  FUN_CODE_a7c3();
  return;
}



// ==== FUN_CODE_64a1 @ CODE:64a1 size 154 callers [CODE:47aa,CODE:75c0]

void FUN_CODE_64a1(void)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  char *pcVar4;
  
  FUN_CODE_9281();
  if ((DAT_EXTMEM_03ec >> 6 & 1) != 0) {
    DAT_EXTMEM_03a3 = DAT_EXTMEM_03a3 + '\x01';
    FUN_CODE_960e(0xff,0xff);
    FUN_CODE_957e(0x80,0x12);
  }
  if ((DAT_EXTMEM_03ec >> 3 & 1) != 0) {
    FUN_CODE_9d4f();
    FUN_CODE_803f();
  }
  if ((char)DAT_EXTMEM_03ec < '\0') {
    FUN_CODE_957e(3,4);
    FUN_CODE_3472();
    bVar1 = FUN_CODE_33e2();
    FUN_CODE_3439(bVar1 | 1);
    FUN_CODE_a99c();
    FUN_CODE_9cdd();
  }
  if ((DAT_EXTMEM_03ec & 3) != 0) {
    FUN_CODE_9d4f();
    FUN_CODE_3472();
    bVar2 = FUN_CODE_a94d(0x59);
    FUN_CODE_33e2();
    FUN_CODE_a99c();
    bVar1 = FUN_CODE_33e9();
    bVar1 = bVar1 >> 1 & 3;
    pcVar4 = (char *)0x5a;
    bVar3 = FUN_CODE_a94d();
    if (((bVar3 & 3) == bVar1) &&
       (((bVar2 >> 6 & 1) == 1 || (pcVar4 = &DAT_EXTMEM_03ec, (DAT_EXTMEM_03ec & 1) != 0)))) {
      FUN_CODE_342d(DAT_INTMEM_b9);
      if (*pcVar4 == '\0') {
        FUN_CODE_42a5();
      }
    }
  }
  return;
}



// ==== FUN_CODE_653b @ CODE:653b size 152 callers [CODE:3caa]

void FUN_CODE_653b(void)

{
  byte bVar1;
  
  FUN_CODE_7d83(0x4aa);
  FUN_CODE_87aa(0xc5,0xb4);
  bVar1 = DAT_EXTMEM_04aa;
  if (DAT_EXTMEM_04aa == 0) {
    bVar1 = DAT_EXTMEM_04ab ^ 0x2e;
  }
  if (bVar1 != 0) {
    bVar1 = DAT_EXTMEM_04aa;
    if (DAT_EXTMEM_04aa == 0) {
      bVar1 = DAT_EXTMEM_04ab ^ 2;
    }
    if (bVar1 != 0) {
      bVar1 = DAT_EXTMEM_04aa;
      if (DAT_EXTMEM_04aa == 0) {
        bVar1 = DAT_EXTMEM_04ab ^ 0xd;
      }
      if (bVar1 != 0) {
        bVar1 = DAT_EXTMEM_04aa;
        if (DAT_EXTMEM_04aa == 0) {
          bVar1 = DAT_EXTMEM_04ab ^ 0x13;
        }
        if (bVar1 != 0) {
          bVar1 = DAT_EXTMEM_04aa;
          if (DAT_EXTMEM_04aa == 0) {
            bVar1 = DAT_EXTMEM_04ab ^ 0xc;
          }
          if (bVar1 != 0) {
            bVar1 = DAT_EXTMEM_04aa;
            if (DAT_EXTMEM_04aa == 0) {
              bVar1 = DAT_EXTMEM_04ab ^ 0x1c;
            }
            if (bVar1 != 0) {
              FUN_CODE_7d6d(0x4aa,0x40,0xb4,0xff);
            }
          }
        }
      }
    }
  }
  FUN_CODE_87aa();
  FUN_CODE_7d98();
  FUN_CODE_87aa();
  return;
}



// ==== FUN_CODE_666b @ CODE:666b size 146 callers [CODE:843b,CODE:996c]

void FUN_CODE_666b(char param_1,char param_2,char param_3)

{
  byte bVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  char cVar6;
  char *pcVar4;
  undefined1 *puVar5;
  
  DAT_EXTMEM_04c6 = param_3;
  FUN_CODE_ae2a(0x4c7);
  FUN_CODE_a97a(1);
  DAT_EXTMEM_04ca = 0;
  while( true ) {
    cVar6 = -0x36;
    if (0xb < DAT_EXTMEM_04ca) {
      return;
    }
    bVar1 = DAT_EXTMEM_04ca;
    uVar2 = FUN_CODE_8b2b(DAT_EXTMEM_04ca - 0xc);
    if (*(char *)CONCAT11(uVar2,cVar6) == '\0') break;
    pcVar4 = (char *)CONCAT11(uVar2,cVar6 + '\x05');
    FUN_CODE_8b1b();
    if (*pcVar4 != param_1) break;
    DAT_EXTMEM_04ca = DAT_EXTMEM_04ca + 1;
  }
  cVar6 = DAT_EXTMEM_04c6;
  if (*(char *)CONCAT11(param_2,bVar1) == '\0') {
    BANK1_R2 = BANK1_R2 + '\x01';
  }
  *(char *)CONCAT11(param_2,bVar1) = DAT_EXTMEM_04c6;
  ((char *)CONCAT11(param_2,bVar1))[1] = DAT_INTMEM_b3;
  puVar5 = (undefined1 *)
           CONCAT11(-0x49 - (((0xeaU < (byte)(cVar6 * '\x02')) << 7) >> 7),cVar6 * '\x02' + 0x15);
  uVar2 = *puVar5;
  uVar3 = FUN_CODE_8b24(puVar5[1]);
  puVar5[1] = uVar2;
  puVar5[2] = uVar3;
  FUN_CODE_adf3(0x4c7);
  FUN_CODE_ae2a(CONCAT11(param_2 - (((0xfa < bVar1) << 7) >> 7),bVar1 + 5));
  puVar5 = (undefined1 *)0x4c7;
  FUN_CODE_adf3();
  FUN_CODE_a934();
  uVar2 = FUN_CODE_8b24();
  *puVar5 = uVar2;
  return;
}



// ==== FUN_CODE_66fd @ CODE:66fd size 145 callers [CODE:5c3c]

void FUN_CODE_66fd(byte param_1)

{
  byte *pbVar1;
  
  if (param_1 == 0xaa) {
    DAT_EXTMEM_0553 = DAT_EXTMEM_0553 + 1;
    if ((DAT_EXTMEM_0553 & 1) != 0) {
      return;
    }
  }
  else if ((DAT_EXTMEM_0553 & 1) != 0) {
    DAT_EXTMEM_0553 = DAT_EXTMEM_0553 + 1;
    DAT_EXTMEM_0556 = '\x01';
  }
  if (DAT_EXTMEM_0556 == '\x02') {
    if ((param_1 < 0x41) << 7 < '\0') {
      DAT_EXTMEM_0555 = param_1;
      DAT_EXTMEM_05de = param_1;
      DAT_EXTMEM_0557 = 5;
      DAT_EXTMEM_0558 = 0x5c;
      DAT_EXTMEM_0554 = DAT_EXTMEM_0554 + param_1;
      DAT_EXTMEM_0556 = 3;
      return;
    }
  }
  else {
    if (DAT_EXTMEM_0556 == '\x03') {
      pbVar1 = &DAT_EXTMEM_0557;
      FUN_CODE_546c();
      *pbVar1 = param_1;
      DAT_EXTMEM_0554 = DAT_EXTMEM_0554 + param_1;
      DAT_EXTMEM_0555 = DAT_EXTMEM_0555 + -1;
      if (DAT_EXTMEM_0555 != '\0') {
        return;
      }
      DAT_EXTMEM_0556 = 4;
      return;
    }
    if (DAT_EXTMEM_0556 != '\x04') {
      if (DAT_EXTMEM_0556 != '\x01') {
        return;
      }
      DAT_EXTMEM_0554 = param_1;
      DAT_EXTMEM_0556 = 2;
      return;
    }
    if (DAT_EXTMEM_0554 == BANK0_R7) {
      FUN_CODE_957e(7,8);
    }
  }
  DAT_EXTMEM_0556 = 0;
  return;
}



// ==== ISR_03 @ CODE:67ff size 1 callers []

void ISR_03(void)

{
  return;
}



// ==== FUN_CODE_6800 @ CODE:6800 size 145 callers [CODE:97e5]

void FUN_CODE_6800(byte param_1,byte param_2,byte param_3)

{
  byte bVar1;
  byte bVar2;
  char cVar3;
  char cVar4;
  
  FUN_CODE_ae2a(0x4af);
  DAT_EXTMEM_04b4 = 2;
  cVar4 = (param_2 < 2) << 7;
  bVar2 = param_2 - 2;
  DAT_EXTMEM_04b2 = param_2;
  DAT_EXTMEM_04b3 = param_3;
  if (param_2 >= 2) {
    bVar2 = FUN_CODE_a139(DAT_INTMEM_b3);
    if (cVar4 < '\0') {
      DAT_EXTMEM_04b4 = 1;
      FUN_CODE_9d73();
      cVar3 = FUN_CODE_aa99();
      bVar2 = 0;
      if (cVar3 != '\0' || param_1 != 0) {
        bVar2 = FUN_CODE_aac4(6);
        bVar2 = bVar2 | param_1;
        if (bVar2 == 0) {
          cVar3 = FUN_CODE_aac4(4);
          bVar2 = FUN_CODE_4503(0x4b2);
          bVar1 = param_1 - (((bVar2 < (byte)(cVar3 - (cVar4 >> 7))) << 7) >> 7);
          cVar4 = (param_2 < bVar1) << 7;
          bVar2 = param_2 - bVar1;
          if (param_2 >= bVar1) {
            cVar4 = FUN_CODE_aac4(bVar2,2);
            param_1 = param_1 - (((param_3 < cVar4 + 1U) << 7) >> 7);
            cVar4 = (param_2 < param_1) << 7;
            bVar2 = param_2 - param_1;
            if (param_2 < param_1) {
              FUN_CODE_ab68(DAT_EXTMEM_04b2,6,DAT_EXTMEM_04b3);
              bVar2 = FUN_CODE_a63f(0x13);
            }
          }
        }
      }
    }
  }
  FUN_CODE_adf3(bVar2,0x4af);
  FUN_CODE_7f77(3,DAT_EXTMEM_04b4,BANK0_R2,BANK0_R1);
  if (cVar4 < '\0') {
    FUN_CODE_a64d(DAT_EXTMEM_04b4);
  }
  return;
}



// ==== FUN_CODE_691c @ CODE:691c size 135 callers [CODE:8864]

undefined1 FUN_CODE_691c(byte param_1,undefined1 param_2,undefined1 param_3)

{
  undefined1 uVar1;
  undefined1 uVar2;
  char cVar3;
  char in_PSW;
  char cVar4;
  
  DAT_EXTMEM_04ad = param_2;
  DAT_EXTMEM_04ae = param_3;
  DAT_EXTMEM_04af = param_1;
  uVar1 = FUN_CODE_441e(3,0x20,0,0);
  if (-1 < in_PSW) {
    return uVar1;
  }
  DAT_EXTMEM_04b0 = 0;
  cVar4 = (DAT_EXTMEM_04af < 3) << 7;
  if (cVar4 < '\0') {
    cVar4 = (DAT_EXTMEM_04af < 2) << 7;
    cVar3 = DAT_EXTMEM_04af - 2;
    if (DAT_EXTMEM_04af >= 2) goto LAB_CODE_6961;
    uVar2 = 0xff;
    uVar1 = 0xec;
  }
  else {
    uVar2 = 0;
    uVar1 = 0x14;
  }
  cVar3 = FUN_CODE_aa6d(uVar2,0x4ad,uVar1);
LAB_CODE_6961:
  FUN_CODE_4413(cVar3,0x15,0x7c);
  if (cVar4 < '\0') {
    DAT_EXTMEM_04b0 = 3;
  }
  else {
    FUN_CODE_441e(0x12,0x8e,0,0,DAT_EXTMEM_04ad,DAT_EXTMEM_04ae);
    if (cVar4 < '\0') {
      DAT_EXTMEM_04b0 = 2;
    }
    else {
      FUN_CODE_4413(3,0xe8);
      if (cVar4 < '\0') {
        DAT_EXTMEM_04b0 = 1;
      }
    }
  }
  return DAT_EXTMEM_04b0;
}



// ==== FUN_CODE_6aab @ CODE:6aab size 125 callers [CODE:843b]

void FUN_CODE_6aab(void)

{
  undefined1 uVar1;
  undefined1 uVar2;
  short sVar3;
  
  FUN_CODE_95f2();
  FUN_CODE_789f();
  FUN_CODE_8fcd();
  FUN_CODE_9c07();
  FUN_CODE_8b9d();
  FUN_CODE_8ff0();
  thunk_FUN_CODE_996c();
  FUN_CODE_a569();
  FUN_CODE_a7bc();
  FUN_CODE_6ffc(2);
  DAT_INTMEM_99 = DAT_EXTMEM_0af8;
  DAT_INTMEM_9a = DAT_EXTMEM_0af9;
  FUN_CODE_a9e2(0,10,DAT_EXTMEM_0af8 - (((0xfa < DAT_EXTMEM_0af9) << 7) >> 7),DAT_EXTMEM_0af9 + 5);
  DAT_INTMEM_9b = BANK0_R7;
  FUN_CODE_9e59(2,7);
  FUN_CODE_7d8b(0x4a4);
  uVar1 = 0;
  uVar2 = DAT_EXTMEM_0af4;
  FUN_CODE_7d83(0x4a8);
  sVar3 = 0x4d6;
  FUN_CODE_7d8b(0xb9,0xb3);
  *(undefined1 *)(sVar3 + 1) = uVar1;
  *(undefined1 *)(sVar3 + 2) = uVar2;
  *(char *)(sVar3 + 3) = DAT_INTMEM_99;
  *(byte *)(sVar3 + 4) = DAT_INTMEM_9a;
  FUN_CODE_87aa();
  _2_1 = 0;
  return;
}



// ==== FUN_CODE_6c35 @ CODE:6c35 size 93 callers [CODE:9645]

void FUN_CODE_6c35(void)

{
  byte bVar1;
  byte bVar2;
  char cVar3;
  
  bVar1 = (byte)((ushort)DAT_INTMEM_b3 * 0x19);
  bVar2 = bVar1 + 0xbb;
  cVar3 = ((char)((ushort)DAT_INTMEM_b3 * 0x19 >> 8) - (((0x44 < bVar1) << 7) >> 7)) + '\x06';
  DAT_EXTMEM_04b1 = 1;
  DAT_EXTMEM_04b2 = cVar3;
  DAT_EXTMEM_04b3 = bVar2;
  if (_1_5 == '\0') {
    FUN_CODE_a9ae(0,0x14,bVar2,cVar3,1);
    bVar2 = FUN_CODE_a934(bVar2 + 0x10,cVar3 - (((0xef < bVar2) << 7) >> 7));
    bVar2 = bVar2 | 4;
  }
  else {
    FUN_CODE_a9ae(1,0x14,1);
    bVar2 = FUN_CODE_a934(bVar2 + 0x10,cVar3 - (((0xef < bVar2) << 7) >> 7));
    bVar2 = FUN_CODE_a99c(bVar2 | 2);
    bVar2 = FUN_CODE_a99c(bVar2 & 0xfb);
    bVar2 = bVar2 & 0xf7;
  }
  FUN_CODE_a99c(bVar2);
  return;
}



// ==== FUN_CODE_6d78 @ CODE:6d78 size 109 callers [CODE:97e5]

void FUN_CODE_6d78(byte param_1,byte param_2)

{
  byte bVar1;
  char cVar2;
  char cVar3;
  char cVar4;
  
  cVar2 = '\0';
  bVar1 = 2 - (((param_2 < 0xc0) << 7) >> 7);
  cVar4 = (param_1 < bVar1) << 7;
  cVar3 = param_1 - bVar1;
  if (cVar4 < '\0') {
    bVar1 = 2 - (((param_2 < 0x40) << 7) >> 7);
    cVar4 = (param_1 < bVar1) << 7;
    cVar3 = param_1 - bVar1;
    if (cVar4 < '\0') {
      bVar1 = 1 - (((param_2 < 0x53) << 7) >> 7);
      cVar4 = (param_1 < bVar1) << 7;
      cVar3 = param_1 - bVar1;
      if (param_1 >= bVar1) {
        cVar2 = '\x01';
      }
    }
    else {
      cVar2 = '\x02';
    }
  }
  else {
    cVar2 = '\x03';
  }
  FUN_CODE_a093(cVar3);
  FUN_CODE_ae2a(0x4b0);
  DAT_EXTMEM_04af = FUN_CODE_a934();
  FUN_CODE_7f77(3,BANK0_R4,BANK0_R2,BANK0_R1);
  if (-1 < cVar4) {
    return;
  }
  if (cVar2 != '\x02') {
    if (cVar2 != '\0') {
      return;
    }
    FUN_CODE_4528(0xc);
    cVar4 = FUN_CODE_a94d();
    if ((cVar4 == BANK0_R4) && (cVar4 = FUN_CODE_44d1(), cVar4 != '\x01')) {
      return;
    }
  }
  FUN_CODE_4528();
  FUN_CODE_a9ae(cVar2);
  FUN_CODE_a64d();
  return;
}



// ==== FUN_CODE_6f27 @ CODE:6f27 size 107 callers [CODE:95f2]

void FUN_CODE_6f27(undefined1 param_1,char param_2,undefined1 param_3,undefined1 param_4)

{
  char cVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  
  uVar3 = 0;
  cVar1 = '\0';
  DAT_EXTMEM_04aa = param_3;
  DAT_EXTMEM_04ab = param_4;
  DAT_EXTMEM_04ac = param_1;
  if (param_2 == '\0') {
    FUN_CODE_108e();
    uVar2 = 2;
    uVar4 = 0x80;
    DAT_EXTMEM_04ad = cVar1;
    DAT_EXTMEM_04ae = uVar3;
  }
  else {
    FUN_CODE_1086();
    uVar2 = 1;
    uVar4 = 0;
    DAT_EXTMEM_04ad = cVar1;
    DAT_EXTMEM_04ae = uVar3;
  }
  FUN_CODE_a90e(DAT_EXTMEM_04ae,DAT_EXTMEM_04ab,BANK0_R4,0xff,DAT_EXTMEM_04ad,1,uVar2,uVar4);
  FIE1 = 0x5a;
  FUN_CODE_aeaa(CONCAT11(DAT_EXTMEM_04ad + -0x10,BANK0_R7),0,DAT_EXTMEM_04ac);
  return;
}



// ==== FUN_CODE_6ffc @ CODE:6ffc size 4 callers [CODE:6aab,CODE:843b]

byte FUN_CODE_6ffc(byte param_1)

{
  byte bVar1;
  
  bVar1 = SADEN;
  SADEN = bVar1 | param_1;
  return param_1;
}



// ==== FUN_CODE_7069 @ CODE:7069 size 104 callers [CODE:8a68]

void FUN_CODE_7069(char *param_1,char param_2,byte param_3)

{
  byte bVar1;
  char cVar2;
  char cVar3;
  
  FUN_CODE_82b0();
  if (*param_1 != '\x01') {
    return;
  }
  FUN_CODE_a5f2();
  if (param_3 == 0 && param_2 == '\0') {
    DAT_EXTMEM_04a3 = param_2;
    DAT_EXTMEM_04a4 = param_3;
    return;
  }
  DAT_EXTMEM_04a3 = param_2;
  DAT_EXTMEM_04a4 = param_3;
  FUN_CODE_a12c();
  cVar3 = BANK0_R6;
  bVar1 = BANK0_R7;
  FUN_CODE_a9e2(0,10);
  DAT_EXTMEM_04a5 = param_2;
  DAT_EXTMEM_04a6 = param_3;
  if (*(char *)CONCAT11('\x04' - (((0xb8 < DAT_INTMEM_b3) << 7) >> 7),DAT_INTMEM_b3 + 0x47) == '\0')
  {
    cVar2 = '\0';
    FUN_CODE_82ca(cVar3 - (param_2 - (((bVar1 < param_3) << 7) >> 7)),bVar1 - param_3);
    if (cVar2 < '\0') {
      return;
    }
    cVar3 = -0x80;
    FUN_CODE_82ca(DAT_EXTMEM_04a6 + bVar1);
    if (-1 < cVar3) {
      return;
    }
  }
  FUN_CODE_a646(6);
  return;
}



// ==== FUN_CODE_7207 @ CODE:7207 size 102 callers [CODE:96cb]

void FUN_CODE_7207(void)

{
  char cVar1;
  undefined1 uVar2;
  
  DAT_EXTMEM_04c2 = '\0';
  DAT_EXTMEM_04c3 = '\x01';
  while (DAT_EXTMEM_05df != '\0') {
    if (DAT_EXTMEM_04c2 == '\0') {
      if (DAT_EXTMEM_05df != '\0') {
        if (DAT_EXTMEM_04c3 == '\0') {
          cVar1 = FUN_CODE_549d();
          if (cVar1 == -0x56) {
            DAT_EXTMEM_04c2 = '\x01';
            DAT_EXTMEM_05df = DAT_EXTMEM_05df + '\x01';
          }
        }
        DAT_EXTMEM_04c3 = '\0';
        uVar2 = FUN_CODE_549d();
        FUN_CODE_9137(uVar2);
        FUN_CODE_53f3(0x559);
        DAT_EXTMEM_05df = DAT_EXTMEM_05df + -1;
      }
    }
    else {
      FUN_CODE_9137(0xaa);
      DAT_EXTMEM_05df = DAT_EXTMEM_05df + -1;
      DAT_EXTMEM_04c2 = '\0';
    }
  }
  FUN_CODE_a7a4();
  FUN_CODE_8bc8(0);
  return;
}



// ==== FUN_CODE_73f7 @ CODE:73f7 size 13 callers [CODE:89b2]

void FUN_CODE_73f7(char param_1,byte param_2)

{
  byte bVar1;
  char cVar2;
  char cVar3;
  
  FUN_CODE_3caa();
  FUN_CODE_ae53(DAT_INTMEM_b2);
  if (param_2 == 0 && param_1 == '\0') {
    DAT_EXTMEM_04a3 = param_1;
    DAT_EXTMEM_04a4 = param_2;
    return;
  }
  DAT_EXTMEM_04a3 = param_1;
  DAT_EXTMEM_04a4 = param_2;
  FUN_CODE_a12c();
  cVar3 = BANK0_R6;
  bVar1 = BANK0_R7;
  FUN_CODE_a9e2(0,10);
  DAT_EXTMEM_04a5 = param_1;
  DAT_EXTMEM_04a6 = param_2;
  if (*(char *)CONCAT11('\x04' - (((0xb8 < DAT_INTMEM_b3) << 7) >> 7),DAT_INTMEM_b3 + 0x47) == '\0')
  {
    cVar2 = '\0';
    FUN_CODE_82ca(cVar3 - (param_1 - (((bVar1 < param_2) << 7) >> 7)),bVar1 - param_2);
    if (cVar2 < '\0') {
      return;
    }
    cVar3 = -0x80;
    FUN_CODE_82ca(DAT_EXTMEM_04a6 + bVar1);
    if (-1 < cVar3) {
      return;
    }
  }
  FUN_CODE_a646(6);
  return;
}



// ==== FUN_CODE_7568 @ CODE:7568 size 88 callers [CODE:9b66,CODE:9e59]

void FUN_CODE_7568(undefined1 param_1)

{
  undefined1 *puVar1;
  
  puVar1 = (undefined1 *)0xffff;
  FUN_CODE_aeac();
  *puVar1 = param_1;
  FUN_CODE_a62a();
  FUN_CODE_ae2a(0x727);
  FUN_CODE_a631();
  FUN_CODE_ae2a(0x724);
  FUN_CODE_a769(*(undefined1 *)CONCAT11(BANK1_R0,BANK1_R1));
  DAT_INTMEM_cf = 0;
  DAT_INTMEM_d0 = 0;
  DAT_SFR_c6 = 6;
  DAT_SFR_ce = 0xee;
  DAT_SFR_d6 = 3;
  RXCNTL = (&DAT_CODE_b9ce)[*(byte *)CONCAT11(BANK1_R0,BANK1_R1)];
  HPCON = (&DAT_CODE_b9d1)[*(byte *)CONCAT11(BANK1_R0,BANK1_R1)];
  FUN_CODE_a20b((&DAT_CODE_b9d1)[*(byte *)CONCAT11(BANK1_R0,BANK1_R1)]);
  HPSTAT = 4;
  FUN_CODE_a449();
  FUN_CODE_aeac(1);
  return;
}



// ==== ISR_43 @ CODE:75c0 size 86 callers []

undefined1 ISR_43(undefined1 param_1)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  undefined1 uVar5;
  undefined1 uVar6;
  undefined1 uVar7;
  undefined1 uVar8;
  
  uVar8 = BANK0_R7;
  uVar7 = BANK0_R6;
  uVar6 = BANK0_R5;
  uVar5 = BANK0_R4;
  uVar4 = BANK0_R3;
  uVar3 = BANK0_R2;
  uVar2 = BANK0_R1;
  uVar1 = BANK0_R0;
  DAT_INTMEM_b9 = 1;
  DAT_EXTMEM_03ec = DAT_EXTMEM_2265;
  DAT_EXTMEM_2265 = FUN_CODE_355d();
  FUN_CODE_64a1();
  BANK0_R7 = uVar8;
  BANK0_R6 = uVar7;
  BANK0_R5 = uVar6;
  BANK0_R4 = uVar5;
  BANK0_R3 = uVar4;
  BANK0_R2 = uVar3;
  BANK0_R1 = uVar2;
  BANK0_R0 = uVar1;
  return param_1;
}



// ==== FUN_CODE_76bf @ CODE:76bf size 23 callers [CODE:a57b]

void FUN_CODE_76bf(void)

{
  DAT_EXTMEM_1011 = DAT_EXTMEM_1011 & 0x3f | 0x40;
  DAT_EXTMEM_1010 = DAT_EXTMEM_1010 & 0xfc | 1;
  return;
}



// ==== FUN_CODE_76d6 @ CODE:76d6 size 22 callers [CODE:a20b]

undefined1 FUN_CODE_76d6(void)

{
  DAT_INTMEM_cf = 1;
  return *(undefined1 *)
          CONCAT11(-0x47 - (((0x2bU < (byte)(DAT_EXTMEM_0723 * '\x02')) << 7) >> 7),
                   DAT_EXTMEM_0723 * '\x02' - 0x2c);
}



// ==== FUN_CODE_76ec @ CODE:76ec size 13 callers [CODE:5c3c,CODE:8bc8]

void FUN_CODE_76ec(undefined1 param_1)

{
  undefined1 uVar1;
  
  uVar1 = FUN_CODE_a94d(param_1);
  EPCONFIG = uVar1;
  return;
}



// ==== FUN_CODE_770c @ CODE:770c size 6 callers [CODE:5c3c,CODE:8bc8,CODE:9137]

void FUN_CODE_770c(void)

{
  FUN_CODE_adf3(0x727);
  return;
}



// ==== FUN_CODE_7712 @ CODE:7712 size 81 callers [CODE:4f9c]

void FUN_CODE_7712(undefined1 param_1)

{
  undefined1 uVar1;
  char in_PSW;
  
  _1_4 = 0;
  uVar1 = 1;
  FUN_CODE_7763();
  DAT_EXTMEM_04a3 = param_1;
  DAT_EXTMEM_04a4 = uVar1;
  FUN_CODE_8ea7();
  DAT_EXTMEM_04a7 = uVar1;
  FUN_CODE_a584();
  if (in_PSW < '\0') {
    DAT_EXTMEM_04a5 = DAT_EXTMEM_04a3;
    DAT_EXTMEM_04a6 = DAT_EXTMEM_04a4;
    DAT_EXTMEM_04a8 = DAT_EXTMEM_04a7;
  }
  else {
    _1_4 = 0;
    uVar1 = 2;
    FUN_CODE_7763();
    DAT_EXTMEM_04a5 = param_1;
    DAT_EXTMEM_04a6 = uVar1;
    FUN_CODE_8ea7();
    DAT_EXTMEM_04a8 = uVar1;
  }
  FUN_CODE_870e(DAT_EXTMEM_04a8,DAT_EXTMEM_04a7);
  return;
}



// ==== FUN_CODE_7763 @ CODE:7763 size 81 callers [CODE:7712,CODE:7a1a,CODE:8a68]

undefined1 FUN_CODE_7763(undefined1 param_1,char param_2)

{
  undefined1 uVar1;
  
  DAT_EXTMEM_04ab = 0;
  DAT_EXTMEM_04ac = 0;
  uVar1 = (&DAT_CODE_b9c2)[(byte)((char)((ushort)DAT_INTMEM_b3 * 6) + param_2)];
  DAT_EXTMEM_04a9 = param_2;
  DAT_EXTMEM_04aa = uVar1;
  if (_1_4 == '\0') {
    _1_5 = 1;
    FUN_CODE_94ae((char)((ushort)DAT_INTMEM_b3 * 6 >> 8));
  }
  else {
    FUN_CODE_91be();
  }
  DAT_EXTMEM_04ab = param_1;
  DAT_EXTMEM_04ac = uVar1;
  FUN_CODE_9b8f(param_1,uVar1,DAT_EXTMEM_04a9);
  return DAT_EXTMEM_04ac;
}



// ==== ISR_1B @ CODE:77b4 size 76 callers []

undefined1 ISR_1B(undefined1 param_1)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  undefined1 uVar5;
  undefined1 uVar6;
  undefined1 uVar7;
  undefined1 uVar8;
  
  uVar8 = BANK0_R7;
  uVar7 = BANK0_R6;
  uVar6 = BANK0_R5;
  uVar5 = BANK0_R4;
  uVar4 = BANK0_R3;
  uVar3 = BANK0_R2;
  uVar2 = BANK0_R1;
  uVar1 = BANK0_R0;
  IP = 0xf7;
  DAT_EXTMEM_0701 = 6;
  DAT_EXTMEM_0702 = 0xf1;
  DAT_INTMEM_b9 = 0;
  thunk_FUN_CODE_9281();
  BANK0_R7 = uVar8;
  BANK0_R6 = uVar7;
  BANK0_R5 = uVar6;
  BANK0_R4 = uVar5;
  BANK0_R3 = uVar4;
  BANK0_R2 = uVar3;
  BANK0_R1 = uVar2;
  BANK0_R0 = uVar1;
  return param_1;
}



// ==== FUN_CODE_789f @ CODE:789f size 79 callers [CODE:6aab]

void FUN_CODE_789f(void)

{
  byte bVar1;
  
  DAT_INTMEM_a4 = 0;
  DAT_INTMEM_a5 = 0;
  DAT_INTMEM_a6 = 0;
  bVar1 = DAT_EXTMEM_0af0 ^ 0x66;
  if (bVar1 == 0) {
    bVar1 = DAT_EXTMEM_0af1 ^ 0x97;
  }
  if (bVar1 != 0) {
    DAT_EXTMEM_0af2 = 0;
    DAT_EXTMEM_0af4 = 0;
    DAT_EXTMEM_0af3 = 0;
    DAT_EXTMEM_0af5 = 0;
    DAT_EXTMEM_0af6 = 0;
    DAT_EXTMEM_0af7 = 0;
    DAT_EXTMEM_0afa = 0;
    DAT_EXTMEM_0af8 = 3;
    DAT_EXTMEM_0af9 = 0xf2;
    DAT_EXTMEM_0afb = 0;
    DAT_EXTMEM_0afc = 0;
    DAT_EXTMEM_0af0 = 0x66;
    DAT_EXTMEM_0af1 = 0x97;
  }
  return;
}



// ==== ISR_23 @ CODE:78ee size 76 callers []

undefined1 ISR_23(undefined1 param_1)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  undefined1 uVar5;
  undefined1 uVar6;
  undefined1 uVar7;
  undefined1 uVar8;
  
  uVar8 = BANK0_R7;
  uVar7 = BANK0_R6;
  uVar6 = BANK0_R5;
  uVar5 = BANK0_R4;
  uVar4 = BANK0_R3;
  uVar3 = BANK0_R2;
  uVar2 = BANK0_R1;
  uVar1 = BANK0_R0;
  IP = 0xef;
  DAT_EXTMEM_0701 = 6;
  DAT_EXTMEM_0702 = 0xf9;
  DAT_INTMEM_b9 = 1;
  thunk_FUN_CODE_9281();
  BANK0_R7 = uVar8;
  BANK0_R6 = uVar7;
  BANK0_R5 = uVar6;
  BANK0_R4 = uVar5;
  BANK0_R3 = uVar4;
  BANK0_R2 = uVar3;
  BANK0_R1 = uVar2;
  BANK0_R0 = uVar1;
  return param_1;
}



// ==== FUN_CODE_793a @ CODE:793a size 75 callers []

void FUN_CODE_793a(void)

{
  char in_PSW;
  
  _2_0 = 0;
  FIE1 = 0x5a;
  DAT_SFR_85 = 0x10;
  FIE1 = 0;
  do {
    DAT_EXTMEM_04a1 = DAT_EXTMEM_0760;
    if (DAT_EXTMEM_0760 == '\x01') {
      DAT_EXTMEM_04a2 = 2;
    }
    else if (DAT_EXTMEM_0760 == '\x02') {
      FUN_CODE_a7b8();
      FUN_CODE_5db7();
      if (in_PSW < '\0') {
        FUN_CODE_9e99();
      }
      FUN_CODE_89b2();
    }
    else {
      in_PSW = (0xfd < DAT_EXTMEM_0760 - 2U) << 7;
      if (DAT_EXTMEM_0760 - 2U == 0xfe) {
        DAT_EXTMEM_04a2 = 1;
      }
    }
    FUN_CODE_843b(DAT_EXTMEM_04a2,DAT_EXTMEM_04a1);
    FUN_CODE_104e();
  } while( true );
}



// ==== FUN_CODE_79d0 @ CODE:79d0 size 74 callers [CODE:959b]

void FUN_CODE_79d0(undefined1 param_1,undefined1 param_2,undefined1 param_3,undefined1 param_4)

{
  DAT_EXTMEM_04c6 = param_3;
  DAT_EXTMEM_04c7 = param_4;
  DAT_EXTMEM_04c8 = param_1;
  DAT_EXTMEM_04c9 = param_2;
  FUN_CODE_a3e8(0x4ca,0,0);
  FUN_CODE_ad55();
  FUN_CODE_aba2(0,0,DAT_EXTMEM_04c6,DAT_EXTMEM_04c7);
  FUN_CODE_a3e5();
  FUN_CODE_ad49();
  FUN_CODE_ac2d(0,0,BANK0_R6,DAT_EXTMEM_04c9,DAT_EXTMEM_04c8);
  FUN_CODE_a3e5();
  FUN_CODE_ad49();
  return;
}



// ==== FUN_CODE_7a1a @ CODE:7a1a size 72 callers [CODE:4f9c]

void FUN_CODE_7a1a(undefined1 param_1,char param_2)

{
  undefined1 uVar1;
  char in_PSW;
  
  _1_2 = 0;
  _1_3 = 0;
  FUN_CODE_a1f3();
  if (in_PSW < '\0') {
    FUN_CODE_a335();
    if (in_PSW < '\0') {
      FUN_CODE_a6eb();
      if (param_2 == '\x02') {
        _1_3 = 1;
      }
      else if (param_2 == '\x01') {
        _1_2 = 1;
      }
    }
  }
  _1_4 = _1_2 & 1;
  uVar1 = 3;
  FUN_CODE_7763();
  _1_4 = _1_3 & 1;
  DAT_EXTMEM_04a3 = param_1;
  DAT_EXTMEM_04a4 = uVar1;
  FUN_CODE_7763(4);
  FUN_CODE_2800(BANK0_R6,BANK0_R7,DAT_EXTMEM_04a3,DAT_EXTMEM_04a4);
  return;
}



// ==== FUN_CODE_7a62 @ CODE:7a62 size 72 callers [CODE:9b12]

byte FUN_CODE_7a62(undefined1 param_1)

{
  byte bVar1;
  byte bVar2;
  byte *pbVar3;
  undefined1 *puVar4;
  
  pbVar3 = (byte *)CONCAT11('\x04' - (((0x62 < DAT_INTMEM_b3) << 7) >> 7),DAT_INTMEM_b3 + 0x9d);
  bVar1 = *pbVar3;
  bVar2 = bVar1 + 1;
  *pbVar3 = bVar2;
  if (9 < bVar2) {
    *(undefined1 *)CONCAT11('\x04' - (((0x62 < DAT_INTMEM_b3) << 7) >> 7),DAT_INTMEM_b3 + 0x9d) = 0;
    bVar1 = DAT_INTMEM_b3;
    FUN_CODE_959b();
    FUN_CODE_1e41();
    FUN_CODE_10ae();
    puVar4 = (undefined1 *)
             CONCAT11('\x04' - (((0xbc < DAT_INTMEM_b3 * '\x02') << 7) >> 7),
                      DAT_INTMEM_b3 * '\x02' + 0x43);
    *puVar4 = param_1;
    puVar4[1] = bVar1;
    return bVar1;
  }
  return bVar1 - 9;
}



// ==== FUN_CODE_7aaa @ CODE:7aaa size 72 callers [CODE:8b9d]

void FUN_CODE_7aaa(void)

{
  DAT_EXTMEM_1000 = 3;
  DAT_EXTMEM_1001 = 0xf0;
  DAT_EXTMEM_1002 = 0x23;
  P0 = 0;
  DAT_EXTMEM_1003 = 0;
  DAT_EXTMEM_1008 = 0x3f;
  DAT_EXTMEM_1009 = 0xfc;
  DAT_EXTMEM_100a = 0x81;
  T2CON = 0x80;
  DAT_EXTMEM_100b = 0;
  DAT_EXTMEM_1010 = 1;
  DAT_EXTMEM_1011 = 0x40;
  DAT_EXTMEM_1012 = 8;
  DAT_SFR_f8 = 0;
  DAT_EXTMEM_1013 = 0;
  TF2 = 1;
  RCLK = 1;
  P0_5 = 0;
  CPRL2 = 0;
  DAT_EXTMEM_1016 = 0xc;
  return;
}



// ==== FUN_CODE_7d69 @ CODE:7d69 size 4 callers [CODE:4800,CODE:52ef]

void FUN_CODE_7d69(undefined1 *param_1)

{
  DAT_EXTMEM_04d6 = *param_1;
  DAT_EXTMEM_04d7 = param_1[1];
  return;
}



// ==== FUN_CODE_7d6d @ CODE:7d6d size 5 callers [CODE:3caa,CODE:4800,CODE:4e91,CODE:6162,CODE:653b]

void FUN_CODE_7d6d(undefined1 *param_1)

{
  DAT_EXTMEM_04d6 = *param_1;
  DAT_EXTMEM_04d7 = param_1[1];
  return;
}



// ==== FUN_CODE_7d72 @ CODE:7d72 size 8 callers [CODE:3caa]

void FUN_CODE_7d72(undefined1 param_1,undefined1 param_2)

{
  DAT_EXTMEM_04d6 = param_1;
  DAT_EXTMEM_04d7 = param_2;
  return;
}



// ==== FUN_CODE_7d7a @ CODE:7d7a size 9 callers [CODE:3caa]

undefined1 FUN_CODE_7d7a(void)

{
  return DAT_EXTMEM_04a7;
}



// ==== FUN_CODE_7d83 @ CODE:7d83 size 1 callers [CODE:4800,CODE:52ef,CODE:6162,CODE:653b,CODE:6aab]

void FUN_CODE_7d83(undefined1 *param_1,undefined1 param_2,undefined1 param_3)

{
  *param_1 = param_2;
  param_1[1] = param_3;
  return;
}



// ==== FUN_CODE_7d84 @ CODE:7d84 size 7 callers [CODE:4e91]

void FUN_CODE_7d84(undefined1 param_1,undefined1 *param_2,undefined1 param_3)

{
  *param_2 = param_1;
  param_2[1] = param_3;
  return;
}



// ==== FUN_CODE_7d8b @ CODE:7d8b size 13 callers [CODE:6aab]

void FUN_CODE_7d8b(undefined1 *param_1)

{
  *param_1 = 0;
  param_1[1] = 1;
  param_1[2] = 0;
  param_1[3] = 0x28;
  return;
}



// ==== FUN_CODE_7d98 @ CODE:7d98 size 7 callers [CODE:4e91,CODE:52ef,CODE:6162,CODE:653b]

void FUN_CODE_7d98(void)

{
  return;
}



// ==== FUN_CODE_7d9f @ CODE:7d9f size 13 callers [CODE:3caa]

void FUN_CODE_7d9f(undefined1 *param_1)

{
  DAT_EXTMEM_04d8 = *param_1;
  DAT_EXTMEM_04d9 = param_1[1];
  return;
}



// ==== FUN_CODE_7eb6 @ CODE:7eb6 size 65 callers [CODE:a0f5]

void FUN_CODE_7eb6(char param_1)

{
  char cVar1;
  char in_PSW;
  
  FUN_CODE_a727();
  cVar1 = '\x01';
  DAT_EXTMEM_04c4 = param_1;
  FUN_CODE_a69a();
  if (in_PSW < '\0') {
    DAT_EXTMEM_04c4 = '\x01';
  }
  else if (DAT_EXTMEM_04c4 == '\x05') {
    FUN_CODE_993c();
    DAT_EXTMEM_04c4 = cVar1;
  }
  else if (DAT_EXTMEM_04c4 == '\a') {
    FUN_CODE_a0e7();
    DAT_EXTMEM_04c4 = cVar1;
  }
  else if (DAT_EXTMEM_04c4 == '\x02') {
    FUN_CODE_967b();
    DAT_EXTMEM_04c4 = cVar1;
  }
  FUN_CODE_5e73(DAT_EXTMEM_04c4);
  return;
}



// ==== FUN_CODE_7f77 @ CODE:7f77 size 63 callers [CODE:2800,CODE:6800,CODE:6d78,CODE:870e]

void FUN_CODE_7f77(byte param_1,byte param_2,undefined1 param_3,undefined1 param_4)

{
  char cVar1;
  byte *pbVar2;
  
  pbVar2 = (byte *)(CONCAT11(param_3,param_4) + 1);
  if (*pbVar2 != param_2) {
    FUN_CODE_4521();
    *pbVar2 = 1;
  }
  pbVar2 = (byte *)(CONCAT11(param_3,param_4) + 1);
  *pbVar2 = param_2;
  FUN_CODE_4521();
  if ((*pbVar2 < param_1) << 7 < '\0') {
    FUN_CODE_4521(*pbVar2 - param_1);
    *pbVar2 = *pbVar2 + 1;
  }
  else {
    if (*(char *)CONCAT11(param_3,param_4) != BANK0_R5) {
LAB_CODE_7fa6:
      *(byte *)CONCAT11(param_3,param_4) = param_2;
      return;
    }
    if (param_2 == 0) {
      cVar1 = FUN_CODE_44d1();
      if (cVar1 == '\x01') goto LAB_CODE_7fa6;
    }
  }
  return;
}



// ==== FUN_CODE_8000 @ CODE:8000 size 26 callers [CODE:84e6]

void FUN_CODE_8000(char param_1,char param_2)

{
  DAT_EXTMEM_0390 = 0;
  FUN_CODE_ae53(param_2);
  if ((param_1 == '`') && (param_2 != 'f')) {
    DAT_EXTMEM_0390 = 1;
  }
  return;
}



// ==== FUN_CODE_803f @ CODE:803f size 63 callers [CODE:64a1]

void FUN_CODE_803f(char *param_1,char param_2)

{
  byte bVar1;
  
  FUN_CODE_342b(0xb9);
  if (*param_1 == '\0') {
    FUN_CODE_3442(param_2 + '<');
    if (*param_1 == '\x01') {
      FUN_CODE_343f();
      *param_1 = '\0';
      FUN_CODE_957e(0xe,3);
      return;
    }
    bVar1 = FUN_CODE_33e9();
    if ((bVar1 >> 3 & 1) != 0) {
      FUN_CODE_3472();
      bVar1 = FUN_CODE_33df();
      bVar1 = FUN_CODE_3439(bVar1 & 0xf7);
      FUN_CODE_a99c(bVar1 | 0x10);
      FUN_CODE_957e(0x10,3);
    }
    FUN_CODE_9cdd();
  }
  return;
}



// ==== FUN_CODE_80bc @ CODE:80bc size 61 callers [CODE:9046]

void FUN_CODE_80bc(undefined1 *param_1)

{
  FUN_CODE_9d61();
  DAT_INTMEM_cb = FUN_CODE_a934();
  FUN_CODE_43f1();
  DAT_INTMEM_ca = *param_1;
  FUN_CODE_4482();
  DAT_INTMEM_cc = *param_1;
  DAT_INTMEM_cd =
       *(undefined1 *)
        CONCAT11('\x05' - (((0x13 < DAT_INTMEM_b3 * '\x04') << 7) >> 7),
                 DAT_INTMEM_b3 * '\x04' - 0x14);
  _0_2 = (&DAT_CODE_b84d)[DAT_INTMEM_b3] != '\0';
  return;
}



// ==== FUN_CODE_81ed @ CODE:81ed size 60 callers [CODE:96cb]

void FUN_CODE_81ed(void)

{
  byte bVar1;
  byte bVar2;
  char cVar3;
  char cVar4;
  char *pcVar5;
  
  DAT_EXTMEM_04c2 = 5;
  DAT_EXTMEM_04c3 = 0x9e;
  DAT_EXTMEM_059c = 0xaa;
  DAT_EXTMEM_059d = 0x21;
  cVar3 = '!';
  bVar2 = 0;
  while( true ) {
    pcVar5 = (char *)0x59e;
    bVar1 = (0xfe < DAT_EXTMEM_059e ^ 0x80U) - (((bVar2 < DAT_EXTMEM_059e + 1) << 7) >> 7);
    cVar4 = -0x80 - bVar1;
    if (bVar1 < 0x81) break;
    FUN_CODE_5469(cVar4);
    cVar3 = *pcVar5 + cVar3;
    bVar2 = bVar2 + 1;
  }
  FUN_CODE_5469(cVar4);
  *pcVar5 = cVar3;
  return;
}



// ==== FUN_CODE_82b0 @ CODE:82b0 size 13 callers [CODE:7069]

char FUN_CODE_82b0(void)

{
  return '\a' - (((0xb1 < DAT_INTMEM_b3) << 7) >> 7);
}



// ==== FUN_CODE_82ca @ CODE:82ca size 12 callers [CODE:7069]

char FUN_CODE_82ca(char param_1,char param_2)

{
  char in_PSW;
  
  return DAT_EXTMEM_04a3 -
         (param_1 - (((DAT_EXTMEM_04a4 < (byte)(param_2 - (in_PSW >> 7))) << 7) >> 7));
}



// ==== FUN_CODE_838d @ CODE:838d size 58 callers [CODE:8ff0]

void FUN_CODE_838d(void)

{
  DAT_EXTMEM_2013 = 0xb9;
  DAT_EXTMEM_2012 = 0x11;
  DAT_EXTMEM_203a = 0;
  DAT_EXTMEM_203b = 0;
  DAT_EXTMEM_2038 = 0;
  DAT_EXTMEM_2039 = 0;
  DAT_EXTMEM_231e = 0x7a;
  DAT_EXTMEM_231f = 0x3d;
  DAT_EXTMEM_2309 = 0x10;
  DAT_EXTMEM_241e = 0x7a;
  DAT_EXTMEM_241f = 0x3d;
  DAT_EXTMEM_2409 = 0x10;
  return;
}



// ==== FUN_CODE_83dc @ CODE:83dc size 11 callers [CODE:9023,CODE:a584]

char FUN_CODE_83dc(byte *param_1)

{
  return '\x06' - (((0x10 < *param_1) << 7) >> 7);
}



// ==== FUN_CODE_83ef @ CODE:83ef size 2 callers [CODE:a0cb,CODE:a0d9]

void FUN_CODE_83ef(byte param_1,short param_2)

{
  FUN_CODE_adf3(0x714,*(undefined1 *)(param_2 + (ushort)param_1));
  return;
}



// ==== FUN_CODE_83f1 @ CODE:83f1 size 6 callers [CODE:9023]

void FUN_CODE_83f1(void)

{
  FUN_CODE_adf3(0x714);
  return;
}



// ==== FUN_CODE_843b @ CODE:843b size 57 callers [CODE:793a]

void FUN_CODE_843b(char param_1,char param_2)

{
  DAT_EXTMEM_04a3 = param_1;
  if (param_1 != param_2) {
    if (param_1 == '\x02') {
      FUN_CODE_666b(0x5f,7,1,0x4e);
    }
    else if (param_1 == '\x01') {
      FUN_CODE_10a6(0x80);
      FUN_CODE_a5eb();
      FUN_CODE_6aab();
      FUN_CODE_9544();
      FUN_CODE_6ffc(0x80);
    }
    DAT_EXTMEM_0760 = DAT_EXTMEM_04a3;
  }
  return;
}



// ==== FUN_CODE_8474 @ CODE:8474 size 26 callers [CODE:8800,CODE:957e]

void FUN_CODE_8474(undefined1 param_1,undefined1 *param_2,char param_3,undefined1 param_4,
                  undefined1 param_5)

{
  *param_2 = param_1;
  FUN_CODE_ad3d(param_3 + '\x01');
  FUN_CODE_ad6d(CONCAT11(param_4,param_5) + 3);
  DAT_INTMEM_a6 = DAT_INTMEM_a6 + 1 & 0x1f;
  DAT_INTMEM_a4 = DAT_INTMEM_a4 + '\x01';
  return;
}



// ==== FUN_CODE_848e @ CODE:848e size 19 callers [CODE:8800,CODE:957e]

void FUN_CODE_848e(undefined1 param_1)

{
  undefined1 *puVar1;
  
  puVar1 = &DAT_EXTMEM_0004;
  FUN_CODE_ade7(DAT_INTMEM_a6,7);
  *puVar1 = param_1;
  return;
}



// ==== FUN_CODE_84a1 @ CODE:84a1 size 12 callers [CODE:a61c,CODE:a623]

void FUN_CODE_84a1(undefined1 param_1)

{
  FUN_CODE_ade7(param_1,0x48);
  return;
}



// ==== FUN_CODE_84e6 @ CODE:84e6 size 57 callers [CODE:42a5]

void FUN_CODE_84e6(undefined1 *param_1,char param_2)

{
  undefined1 uVar1;
  char cVar2;
  char *pcVar3;
  undefined1 *puVar4;
  
  uVar1 = BANK0_R7;
  FUN_CODE_8000();
  FUN_CODE_3401();
  *param_1 = 0;
  pcVar3 = &DAT_EXTMEM_0390;
  if (DAT_EXTMEM_0390 != '\0') {
    FUN_CODE_34e6();
    cVar2 = *pcVar3;
    if ((cVar2 != 'c') && (cVar2 + 0x9fU < 5)) {
      FUN_CODE_3401(param_2 + 'V');
      *pcVar3 = cVar2;
    }
  }
  puVar4 = &DAT_EXTMEM_0390;
  if (DAT_EXTMEM_0390 == '\x01') {
    FUN_CODE_34e6();
    *puVar4 = uVar1;
  }
  return;
}



// ==== FUN_CODE_870e @ CODE:870e size 52 callers [CODE:7712]

void FUN_CODE_870e(char param_1)

{
  byte in_PSW;
  byte bVar1;
  undefined1 *puVar2;
  
  bVar1 = in_PSW & 0xdd;
  DAT_EXTMEM_04a9 = BANK0_R5 & 0xf | param_1 << 4;
  puVar2 = &DAT_EXTMEM_04a9;
  FUN_CODE_a085();
  FUN_CODE_7f77(3,*puVar2,BANK0_R2,BANK0_R1);
  if ((char)bVar1 < '\0') {
    DAT_INTMEM_a7 = DAT_EXTMEM_04a9;
    DAT_INTMEM_a9 = BANK0_R7;
    FUN_CODE_a638(1,1);
  }
  return;
}



// ==== FUN_CODE_8742 @ CODE:8742 size 52 callers [CODE:89b2]

byte FUN_CODE_8742(void)

{
  byte bVar1;
  
  bVar1 = DAT_INTMEM_a4;
  if ((DAT_INTMEM_a4 != 0) && (bVar1 = DAT_INTMEM_a4 - 0x21, DAT_INTMEM_a4 < 0x21)) {
    bVar1 = (byte)((ushort)DAT_INTMEM_a5 * 7);
    FUN_CODE_a90e(0xb2,bVar1 + 4,
                  (char)((ushort)DAT_INTMEM_a5 * 7 >> 8) - (((0xfb < bVar1) << 7) >> 7),1,0,0,0,7);
    DAT_INTMEM_a5 = DAT_INTMEM_a5 + 1 & 0x1f;
    DAT_INTMEM_a4 = DAT_INTMEM_a4 - 1;
    return DAT_INTMEM_a5;
  }
  return bVar1;
}



// ==== FUN_CODE_87aa @ CODE:87aa size 51 callers [CODE:2800,CODE:3caa,CODE:4800,CODE:4e91,CODE:52ef,CODE:6162,CODE:6406,CODE:653b,CODE:6aab,CODE:88c5,CODE:9645,CODE:9cca]

void FUN_CODE_87aa(void)

{
  FUN_CODE_ae2a(0x4d3);
  FUN_CODE_ae2a(0x4fe,0xd6,4,1);
  FUN_CODE_adf3(0x4d3);
  FUN_CODE_ae2a(0x504);
  FUN_CODE_adf3(0x4fe);
  FUN_CODE_ae2a(0x507);
  FUN_CODE_3572(0,0,0);
  return;
}



// ==== FUN_CODE_8800 @ CODE:8800 size 50 callers [CODE:5db7,CODE:8f87,CODE:a638]

byte FUN_CODE_8800(undefined1 param_1,undefined1 param_2,undefined1 param_3)

{
  byte bVar1;
  undefined1 uVar2;
  undefined1 *puVar3;
  
  bVar1 = SADEN;
  DAT_EXTMEM_04c8 = bVar1 & 0x80;
  puVar3 = &DAT_EXTMEM_04c8;
  bVar1 = SADEN;
  SADEN = bVar1 & 0x7f;
  DAT_EXTMEM_04c7 = param_3;
  if (DAT_INTMEM_a4 < 0x20) {
    uVar2 = BANK0_R3;
    FUN_CODE_848e(DAT_INTMEM_a4 - 0x20);
    puVar3[1] = uVar2;
    FUN_CODE_8474(DAT_EXTMEM_04c7,CONCAT11(param_1,param_2) + 2);
  }
  bVar1 = SADEN;
  SADEN = bVar1 | DAT_EXTMEM_04c8;
  return DAT_EXTMEM_04c8;
}



// ==== FUN_CODE_8864 @ CODE:8864 size 49 callers [CODE:9b12]

void FUN_CODE_8864(char *param_1)

{
  char cVar1;
  char cVar2;
  
  cVar2 = DAT_INTMEM_b3;
  FUN_CODE_109e();
  FUN_CODE_5078();
  FUN_CODE_691c(*param_1);
  cVar1 = DAT_INTMEM_b3;
  FUN_CODE_507b(DAT_INTMEM_b3);
  if (*param_1 != cVar2) {
    FUN_CODE_507d(cVar1 + '\x10');
    *param_1 = cVar2;
  }
  FUN_CODE_8e81();
  FUN_CODE_8f87();
  FUN_CODE_a595();
  FUN_CODE_5085();
  *param_1 = cVar2;
  return;
}



// ==== FUN_CODE_88c5 @ CODE:88c5 size 48 callers [CODE:4f9c]

void FUN_CODE_88c5(char *param_1,byte param_2)

{
  byte bVar1;
  
  if (_1_1 != '\0') {
    bVar1 = DAT_INTMEM_b3;
    FUN_CODE_4444();
    if (*param_1 == '\x02') {
      FUN_CODE_109e();
      bVar1 = 0xf - (((bVar1 < 0xa1) << 7) >> 7);
      if (bVar1 <= param_2) {
        _1_1 = '\0';
        FUN_CODE_a638(param_2 - bVar1,1,2);
      }
    }
    if (_1_1 != '\x01') {
      FUN_CODE_87aa(0xf7,0xb7,0xff);
    }
  }
  return;
}



// ==== FUN_CODE_88f5 @ CODE:88f5 size 8 callers [CODE:3724]

undefined1 FUN_CODE_88f5(undefined1 param_1,char param_2)

{
  char in_PSW;
  
  return *(undefined1 *)CONCAT11(param_2 - (in_PSW >> 7),param_1);
}



// ==== FUN_CODE_88fd @ CODE:88fd size 3 callers [CODE:3724]

undefined1 FUN_CODE_88fd(undefined1 *param_1)

{
  *param_1 = 7;
  return DAT_EXTMEM_0736;
}



// ==== FUN_CODE_8900 @ CODE:8900 size 9 callers [CODE:3724]

undefined1 FUN_CODE_8900(void)

{
  return DAT_EXTMEM_0736;
}



// ==== FUN_CODE_8909 @ CODE:8909 size 8 callers [CODE:3724]

undefined1 FUN_CODE_8909(undefined1 param_1,char param_2)

{
  char in_PSW;
  
  return *(undefined1 *)CONCAT11(param_2 - (in_PSW >> 7),param_1);
}



// ==== FUN_CODE_8911 @ CODE:8911 size 10 callers [CODE:3724]

undefined1 FUN_CODE_8911(undefined1 param_1,undefined1 *param_2)

{
  *param_2 = param_1;
  return DAT_EXTMEM_0736;
}



// ==== FUN_CODE_8925 @ CODE:8925 size 47 callers [CODE:9b8f]

void FUN_CODE_8925(undefined1 param_1,undefined1 param_2)

{
  undefined1 uVar1;
  undefined2 uStack_1;
  
  uStack_1 = (undefined1 *)
             CONCAT11('\x06' - (((0xfaU < (byte)(DAT_INTMEM_b3 * '\f')) << 7) >> 7),
                      DAT_INTMEM_b3 * '\f' + 5);
  uVar1 = BANK0_R5;
  DAT_EXTMEM_04ad = param_2;
  FUN_CODE_ade7(param_2,2);
  *uStack_1 = param_1;
  uStack_1[1] = uVar1;
  return;
}



// ==== FUN_CODE_89b2 @ CODE:89b2 size 46 callers [CODE:793a]

void FUN_CODE_89b2(char param_1)

{
  byte bVar1;
  byte in_PSW;
  
  FUN_CODE_1096();
  DAT_EXTMEM_04a3 = param_1;
  while( true ) {
    if (DAT_EXTMEM_04a3 == '\0') {
      return;
    }
    bVar1 = SADEN;
    SADEN = bVar1 & 0x7f;
    in_PSW = in_PSW & 0xdd;
    FUN_CODE_8742();
    _1_2 = -((char)in_PSW >> 7);
    bVar1 = SADEN;
    SADEN = bVar1 | 0x80;
    if (_1_2 == '\0') break;
    FUN_CODE_a7b8();
    FUN_CODE_a4fd();
    FUN_CODE_73f7();
    DAT_EXTMEM_04a3 = DAT_EXTMEM_04a3 + -1;
  }
  return;
}



// ==== FUN_CODE_8a68 @ CODE:8a68 size 45 callers [CODE:4f9c]

void FUN_CODE_8a68(void)

{
  char cVar1;
  char cVar2;
  char in_PSW;
  
  _1_4 = 0;
  cVar1 = '\0';
  FUN_CODE_7763();
  FUN_CODE_9983();
  FUN_CODE_a335();
  if (in_PSW < '\0') {
    FUN_CODE_a5bd();
    if (cVar1 == '\x0e') {
      FUN_CODE_37ff();
    }
    else if (cVar1 == '\n') {
      cVar2 = -0x80;
      cVar1 = '\0';
      FUN_CODE_9a0d();
      if (cVar2 == '\0' && cVar1 == '\0') {
        FUN_CODE_7069();
        return;
      }
    }
  }
  return;
}



// ==== FUN_CODE_8b1b @ CODE:8b1b size 9 callers [CODE:5db7,CODE:666b]

void FUN_CODE_8b1b(void)

{
  FUN_CODE_adf3();
  FUN_CODE_a934();
  return;
}



// ==== FUN_CODE_8b24 @ CODE:8b24 size 7 callers [CODE:5db7,CODE:666b]

void FUN_CODE_8b24(void)

{
  return;
}



// ==== FUN_CODE_8b2b @ CODE:8b2b size 16 callers [CODE:5db7,CODE:666b]

char FUN_CODE_8b2b(char param_1)

{
  return '\x06' - (((0xa8U < (byte)(param_1 * '\b')) << 7) >> 7);
}



// ==== FUN_CODE_8b3b @ CODE:8b3b size 5 callers [CODE:5db7]

undefined1 FUN_CODE_8b3b(void)

{
  return DAT_EXTMEM_04a4;
}



// ==== FUN_CODE_8b40 @ CODE:8b40 size 7 callers [CODE:5db7]

undefined1 FUN_CODE_8b40(short param_1)

{
  return *(undefined1 *)(param_1 + 1);
}



// ==== FUN_CODE_8b47 @ CODE:8b47 size 43 callers [CODE:3572,CODE:4532,CODE:55c0,CODE:5693]

void FUN_CODE_8b47(char param_1,char param_2,char param_3)

{
  undefined1 uVar1;
  
  FUN_CODE_ae2a(0x54e);
  FUN_CODE_54ca();
  if ((param_2 != '\0' || param_1 != '\0') || param_3 != '\0') {
    uVar1 = BANK0_R5;
    FUN_CODE_54ca();
    FUN_CODE_ae33();
    FUN_CODE_a99c(uVar1);
    FUN_CODE_54ca();
    FUN_CODE_aafc(0,1,1);
    return;
  }
  FUN_CODE_9137(BANK0_R5);
  return;
}



// ==== FUN_CODE_8b9d @ CODE:8b9d size 43 callers [CODE:6aab]

undefined1 FUN_CODE_8b9d(void)

{
  FIE1 = 0x5a;
  FUN_CODE_a685();
  FUN_CODE_9bdf();
  FUN_CODE_7aaa();
  FUN_CODE_a654();
  FUN_CODE_a67e();
  FIE1 = 0xce;
  FUN_CODE_a1db();
  DAT_SFR_bd = 0xff;
  SPH = 0xff;
  DAT_SFR_bf = 0xff;
  FIE1 = 0;
  IP = 0;
  DAT_SFR_c3 = 0;
  RCAP2H = 0;
  return 0;
}



// ==== FUN_CODE_8bc8 @ CODE:8bc8 size 43 callers [CODE:104e,CODE:7207]

void FUN_CODE_8bc8(void)

{
  byte *pbVar1;
  char cVar2;
  
  if ((DAT_INTMEM_d0 != '\x04') && (DAT_INTMEM_ce != DAT_INTMEM_d1)) {
    FUN_CODE_770c();
    cVar2 = DAT_INTMEM_ce;
    pbVar1 = (byte *)&DAT_INTMEM_ce;
    DAT_INTMEM_ce = DAT_INTMEM_ce + '\x01';
    FUN_CODE_76ec(cVar2);
    cVar2 = *pbVar1 + 0x10;
    if (0xef < *pbVar1) {
      cVar2 = '\0';
      *pbVar1 = 0;
    }
    DAT_INTMEM_d0 = 4;
    FUN_CODE_a449(cVar2);
    return;
  }
  return;
}



// ==== FUN_CODE_8e81 @ CODE:8e81 size 38 callers [CODE:8864]

void FUN_CODE_8e81(char *param_1,char param_2)

{
  FUN_CODE_50e1();
  if (*param_1 != '\0') {
    FUN_CODE_a6fd();
    if (param_2 == '\x01') {
      FUN_CODE_5078();
      if (*param_1 != '\x02') {
        return;
      }
    }
    else {
      FUN_CODE_5085();
      if (*param_1 != '\x02') {
        return;
      }
    }
    _1_5 = 1;
    FUN_CODE_9cca();
    FUN_CODE_a6b5();
  }
  return;
}



// ==== FUN_CODE_8ea7 @ CODE:8ea7 size 38 callers [CODE:7712]

char FUN_CODE_8ea7(byte param_1,byte param_2)

{
  byte bVar1;
  
  bVar1 = 2 - (((param_2 < 0x9e) << 7) >> 7);
  if (param_1 < bVar1) {
    return param_1 - bVar1;
  }
  bVar1 = 7 - (((param_2 < 0xba) << 7) >> 7);
  if (param_1 < bVar1) {
    return param_1 - bVar1;
  }
  return param_1 - ('\x0e' - (((param_2 < 0xe5) << 7) >> 7));
}



// ==== FUN_CODE_8ef3 @ CODE:8ef3 size 38 callers [CODE:a77b]

void FUN_CODE_8ef3(undefined1 param_1,char param_2)

{
  undefined1 uVar1;
  undefined1 *puVar2;
  
  FUN_CODE_9f29();
  puVar2 = (undefined1 *)(CONCAT11(param_1,param_2) + 1);
  *puVar2 = 0;
  FUN_CODE_6215(param_2);
  *puVar2 = 0;
  puVar2 = puVar2 + 1;
  *puVar2 = 0;
  uVar1 = FUN_CODE_629e();
  puVar2 = puVar2 + 1;
  *puVar2 = uVar1;
  FUN_CODE_6217(param_2 + '\x04');
  *puVar2 = 0;
  *(undefined1 *)CONCAT11(param_1,param_2) = 1;
  return;
}



// ==== FUN_CODE_8f19 @ CODE:8f19 size 38 callers [CODE:a77b]

void FUN_CODE_8f19(undefined1 *param_1,undefined1 param_2,char param_3)

{
  FUN_CODE_9f39();
  FUN_CODE_6217(param_3 + '\x04');
  *param_1 = 0;
  FUN_CODE_6217(param_3 + '\b');
  *param_1 = 0;
  param_1 = param_1 + 1;
  *param_1 = 0;
  FUN_CODE_6217(param_3 + '\x06');
  *param_1 = 0;
  param_1[1] = 0;
  *(undefined1 *)CONCAT11(param_2,param_3) = 1;
  return;
}



// ==== FUN_CODE_8f87 @ CODE:8f87 size 35 callers [CODE:8864]

void FUN_CODE_8f87(char *param_1,char *param_2)

{
  undefined1 uVar1;
  char cVar2;
  
  FUN_CODE_50a8();
  if (*param_1 != '\0') {
    cVar2 = *param_2;
    FUN_CODE_50ab();
    *param_1 = '\0';
    if (cVar2 == '\0') {
      uVar1 = 0;
    }
    else {
      if (DAT_INTMEM_b3 != '\x01') {
        return;
      }
      uVar1 = 1;
    }
    FUN_CODE_8800(uVar1,0x18,3);
  }
  return;
}



// ==== FUN_CODE_8fcd @ CODE:8fcd size 35 callers [CODE:6aab]

void FUN_CODE_8fcd(void)

{
  _0_4 = 0;
  _0_7 = 0;
  DAT_EXTMEM_05e8 = 2;
  DAT_EXTMEM_0603 = 0;
  _1_1 = 0;
  _0_6 = 0;
  _0_5 = 0;
  _1_0 = 0;
  DAT_EXTMEM_05e9 = 3;
  DAT_EXTMEM_0604 = 0;
  return;
}



// ==== FUN_CODE_8ff0 @ CODE:8ff0 size 16 callers [CODE:6aab]

void FUN_CODE_8ff0(void)

{
  FUN_CODE_838d();
  FUN_CODE_a5b5();
  FUN_CODE_5fe3(0);
  FUN_CODE_5fe3(1);
  return;
}



// ==== FUN_CODE_9023 @ CODE:9023 size 35 callers [CODE:a45d]

void FUN_CODE_9023(byte param_1)

{
  undefined1 uVar1;
  undefined1 *puVar2;
  
  puVar2 = &DAT_CODE_b930;
  uVar1 = (&DAT_CODE_b930)[param_1];
  if (param_1 == 1) {
    FUN_CODE_83dc(0xb3,uVar1);
    *puVar2 = 1;
  }
  else {
    FUN_CODE_83dc(0xb3,uVar1);
    *puVar2 = 0;
  }
  FUN_CODE_83f1();
  FUN_CODE_a9ae(uVar1,1);
  return;
}



// ==== FUN_CODE_9046 @ CODE:9046 size 35 callers [CODE:a4fd,CODE:a5e4,CODE:a600]

void FUN_CODE_9046(void)

{
  undefined1 uVar1;
  
  FUN_CODE_80bc();
  if (DAT_INTMEM_b3 == '\x01') {
    FUN_CODE_9c2f(0x24);
    uVar1 = 0x22;
  }
  else {
    if (DAT_INTMEM_b3 != '\0') {
      return;
    }
    FUN_CODE_9c2f(0x23);
    uVar1 = 0x21;
  }
  FUN_CODE_ae2a(0x71d,uVar1);
  return;
}



// ==== FUN_CODE_9137 @ CODE:9137 size 34 callers [CODE:7207,CODE:8b47]

char FUN_CODE_9137(undefined1 param_1)

{
  byte bVar1;
  char cVar2;
  
  cVar2 = DAT_INTMEM_d1;
  FUN_CODE_770c();
  bVar1 = cVar2 + 1;
  FUN_CODE_a9ae(param_1,BANK0_R6);
  cVar2 = bVar1 + 0x10;
  if (0xef < bVar1) {
    cVar2 = '\0';
  }
  DAT_INTMEM_d1 = BANK0_R6;
  return cVar2;
}



// ==== FUN_CODE_91be @ CODE:91be size 33 callers [CODE:7763]

void FUN_CODE_91be(void)

{
  byte bVar1;
  byte bVar2;
  char cVar3;
  char cVar4;
  byte bVar5;
  char cVar6;
  
  cVar6 = '\0';
  bVar2 = 0;
  bVar1 = 0;
  cVar4 = '\0';
  cVar3 = '\x04';
  do {
    _1_5 = 1;
    bVar5 = BANK0_R5;
    FUN_CODE_94ae(cVar6);
    bVar5 = cVar4 - (((bVar2 < bVar5) << 7) >> 7);
    cVar6 = bVar1 - bVar5;
    if (bVar1 < bVar5) {
      bVar1 = BANK0_R6;
      bVar2 = BANK0_R7;
    }
    cVar3 = cVar3 + -1;
  } while (cVar3 != '\0');
  return;
}



// ==== FUN_CODE_9281 @ CODE:9281 size 32 callers [CODE:64a1]

void FUN_CODE_9281(void)

{
  undefined1 uVar1;
  
  if (DAT_INTMEM_b9 == '\x01') {
    FUN_CODE_9c39(0x24);
    uVar1 = 0x22;
  }
  else {
    if (DAT_INTMEM_b9 != '\0') {
      return;
    }
    FUN_CODE_9c39(0x23);
    uVar1 = 0x21;
  }
  FUN_CODE_ae2a(0x717,uVar1);
  return;
}



// ==== FUN_CODE_93bc @ CODE:93bc size 31 callers [CODE:a4fd]

void FUN_CODE_93bc(void)

{
  if (DAT_INTMEM_b3 == '\x01') {
    DAT_EXTMEM_06ed = 6;
    DAT_EXTMEM_06ee = 0xf9;
  }
  else if (DAT_INTMEM_b3 == '\0') {
    DAT_EXTMEM_06ed = 6;
    DAT_EXTMEM_06ee = 0xf1;
    return;
  }
  return;
}



// ==== FUN_CODE_9436 @ CODE:9436 size 30 callers []

void FUN_CODE_9436(void)

{
  if (DAT_INTMEM_b3 == '\0') {
    P0_5 = _1_5 & 1;
    DAT_EXTMEM_06b7 = _1_5 & 1;
    return;
  }
  CPRL2 = _1_5 & 1;
  DAT_EXTMEM_06b8 = _1_5 & 1;
  return;
}



// ==== FUN_CODE_94ae @ CODE:94ae size 30 callers [CODE:7763,CODE:91be]

byte FUN_CODE_94ae(undefined1 param_1)

{
  byte bVar1;
  char cVar2;
  
  IEN1 = param_1;
  T1 = _1_5 & 1;
  WR = 1;
  do {
    cVar2 = T0;
  } while (cVar2 == '\0');
  cVar2 = IPH1;
  bVar1 = IPL1;
  WR = 0;
  return bVar1 >> 4 | cVar2 << 4;
}



// ==== FUN_CODE_9544 @ CODE:9544 size 16 callers [CODE:843b]

void FUN_CODE_9544(void)

{
  FUN_CODE_9554(0);
  FUN_CODE_a638();
  FUN_CODE_9554(1);
  FUN_CODE_a638();
  return;
}



// ==== FUN_CODE_9554 @ CODE:9554 size 13 callers [CODE:9544]

void FUN_CODE_9554(void)

{
  FUN_CODE_a5e4();
  FUN_CODE_a52a(0);
  return;
}



// ==== FUN_CODE_957e @ CODE:957e size 29 callers [CODE:42a5,CODE:50fb,CODE:64a1,CODE:66fd,CODE:803f]

void FUN_CODE_957e(short param_1,undefined1 param_2,undefined1 param_3)

{
  undefined1 uVar1;
  
  if (DAT_INTMEM_a4 < 0x20) {
    uVar1 = BANK0_R5;
    FUN_CODE_848e(DAT_INTMEM_a4 - 0x20,BANK0_R5);
    *(undefined1 *)(param_1 + 1) = DAT_INTMEM_b9;
    FUN_CODE_8474(uVar1,CONCAT11(param_2,param_3) + 2);
  }
  return;
}



// ==== FUN_CODE_959b @ CODE:959b size 29 callers [CODE:7a62]

void FUN_CODE_959b(void)

{
  undefined1 *puVar1;
  
  if (DAT_INTMEM_b3 == '\0') {
    puVar1 = &DAT_EXTMEM_072d;
  }
  else {
    puVar1 = &DAT_EXTMEM_072f;
  }
  FUN_CODE_79d0(0,100,3,7,*puVar1,puVar1[1]);
  return;
}



// ==== FUN_CODE_95f2 @ CODE:95f2 size 28 callers [CODE:6aab]

void FUN_CODE_95f2(void)

{
  P2_0 = 0;
  FIE1 = 0x5a;
  FUN_CODE_a253();
  FUN_CODE_9a4f();
  FUN_CODE_6f27(2,1,0x6b,0x28);
  FUN_CODE_9f69();
  FUN_CODE_3724();
  return;
}



// ==== FUN_CODE_960e @ CODE:960e size 28 callers [CODE:42a5,CODE:64a1]

void FUN_CODE_960e(char *param_1,char param_2,char param_3)

{
  FUN_CODE_34c6();
  if (*param_1 == BANK0_R7) {
    FUN_CODE_34f1();
    if (*param_1 == BANK0_R5) {
      return;
    }
  }
  FUN_CODE_34c6();
  *param_1 = param_3;
  FUN_CODE_34f1();
  *param_1 = param_2;
  return;
}



// ==== FUN_CODE_9645 @ CODE:9645 size 27 callers []

void FUN_CODE_9645(undefined1 *param_1)

{
  char in_PSW;
  
  FUN_CODE_1e48();
  *param_1 = 0;
  FUN_CODE_9bf3();
  if (in_PSW < '\0') {
    FUN_CODE_87aa(0xdd,0xb0,0xff);
    FUN_CODE_6406();
  }
  _1_5 = 0;
  FUN_CODE_6c35();
  return;
}



// ==== ISR_8B @ CODE:9660 size 27 callers []

undefined1 ISR_8B(undefined1 param_1)

{
  BANK1_R6 = BANK1_R6 + '\x01';
  if (BANK1_R6 == '\0') {
    BANK1_R5 = BANK1_R5 + '\x01';
  }
  BANK2_R5 = BANK2_R5 + '\x01';
  return param_1;
}



// ==== FUN_CODE_967b @ CODE:967b size 27 callers [CODE:7eb6]

void FUN_CODE_967b(void)

{
  char in_PSW;
  
  FUN_CODE_a69a(2);
  if (in_PSW < '\0') {
    FUN_CODE_6283();
    return;
  }
  return;
}



// ==== FUN_CODE_96cb @ CODE:96cb size 26 callers []

void FUN_CODE_96cb(void)

{
  FUN_CODE_81ed();
  DAT_EXTMEM_05df = DAT_EXTMEM_059e + '\x04';
  DAT_EXTMEM_0559 = 5;
  DAT_EXTMEM_055a = 0x9c;
  FUN_CODE_7207();
  return;
}



// ==== FUN_CODE_96ff @ CODE:96ff size 26 callers [CODE:4800]

char FUN_CODE_96ff(void)

{
  undefined1 *puVar1;
  
  if (DAT_INTMEM_b3 == '\x01') {
    puVar1 = &DAT_EXTMEM_072f;
  }
  else {
    if (DAT_INTMEM_b3 != '\0') {
      return DAT_INTMEM_b3;
    }
    puVar1 = &DAT_EXTMEM_072d;
  }
  return puVar1[1];
}



// ==== FUN_CODE_9719 @ CODE:9719 size 26 callers [CODE:2800]

char FUN_CODE_9719(byte param_1,byte param_2)

{
  byte bVar1;
  
  bVar1 = 8 - (((param_2 < 0xd3) << 7) >> 7);
  if (param_1 < bVar1) {
    return param_1 - bVar1;
  }
  return param_1 - ('\x0e' - (((param_2 < 0xe5) << 7) >> 7));
}



// ==== FUN_CODE_97cc @ CODE:97cc size 15 callers [CODE:4f9c]

char FUN_CODE_97cc(void)

{
  return '\a' - (((0xceU < (byte)(DAT_INTMEM_b3 * '\x02')) << 7) >> 7);
}



// ==== FUN_CODE_97db @ CODE:97db size 2 callers [CODE:4f9c]

char FUN_CODE_97db(byte param_1)

{
  return '\a' - (((0xd4 < param_1) << 7) >> 7);
}



// ==== FUN_CODE_97dd @ CODE:97dd size 8 callers [CODE:4f9c]

char FUN_CODE_97dd(void)

{
  char in_PSW;
  
  return '\a' - (in_PSW >> 7);
}



// ==== FUN_CODE_97e5 @ CODE:97e5 size 25 callers [CODE:9b8f]

void FUN_CODE_97e5(undefined1 param_1,undefined1 param_2)

{
  DAT_EXTMEM_04ad = param_1;
  DAT_EXTMEM_04ae = param_2;
  FUN_CODE_6d78();
  FUN_CODE_a077();
  FUN_CODE_6800(DAT_EXTMEM_04ad,DAT_EXTMEM_04ae);
  return;
}



// ==== ISR_83 @ CODE:97fe size 1 callers []

void ISR_83(void)

{
  return;
}



// ==== ISR_2B @ CODE:97ff size 1 callers []

void ISR_2B(void)

{
  return;
}



// ==== ISR_73 @ CODE:98ac size 24 callers []

undefined1 ISR_73(undefined1 param_1)

{
  DAT_INTMEM_b9 = 0;
  return param_1;
}



// ==== ISR_7B @ CODE:98c4 size 24 callers []

undefined1 ISR_7B(undefined1 param_1)

{
  DAT_INTMEM_b9 = 1;
  return param_1;
}



// ==== FUN_CODE_9924 @ CODE:9924 size 24 callers [CODE:104e]

void FUN_CODE_9924(void)

{
  byte bVar1;
  
  bVar1 = FIFLG1;
  FIFLG1 = bVar1 & 0xfb;
  DAT_INTMEM_cf = 0;
  DAT_INTMEM_d0 = 0;
  DAT_INTMEM_ce = 0;
  DAT_INTMEM_d1 = 0;
  DAT_SFR_c6 = 0;
  DAT_SFR_ce = 0;
  DAT_SFR_d6 = 0;
  HPSTAT = 0;
  return;
}



// ==== FUN_CODE_993c @ CODE:993c size 24 callers [CODE:7eb6]

void FUN_CODE_993c(void)

{
  char in_PSW;
  
  FUN_CODE_9eb9(1,0x12);
  if (in_PSW < '\0') {
    return;
  }
  FUN_CODE_a69a(3);
  return;
}



// ==== FUN_CODE_996c @ CODE:996c size 23 callers []

void FUN_CODE_996c(char param_1)

{
  char in_PSW;
  
  FUN_CODE_1076();
  if ((param_1 != '\0') && (FUN_CODE_a7f9(), -1 < in_PSW)) {
    return;
  }
  FUN_CODE_666b(0x4a,7,1,0x4c);
  return;
}



// ==== FUN_CODE_9983 @ CODE:9983 size 23 callers [CODE:8a68]

void FUN_CODE_9983(undefined1 param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  if (DAT_INTMEM_b3 == '\x01') {
    puVar1 = &DAT_EXTMEM_072f;
  }
  else {
    if (DAT_INTMEM_b3 != '\0') {
      return;
    }
    puVar1 = &DAT_EXTMEM_072d;
  }
  *puVar1 = param_1;
  puVar1[1] = param_2;
  return;
}



// ==== FUN_CODE_9a0d @ CODE:9a0d size 22 callers [CODE:8a68]

byte FUN_CODE_9a0d(byte param_1)

{
  undefined1 *puVar1;
  
  if (DAT_INTMEM_b3 == '\x01') {
    puVar1 = &DAT_EXTMEM_0633;
  }
  else {
    puVar1 = &DAT_EXTMEM_0631;
  }
  return puVar1[1] & param_1;
}



// ==== FUN_CODE_9a4f @ CODE:9a4f size 22 callers [CODE:95f2]

void FUN_CODE_9a4f(void)

{
  DAT_EXTMEM_10b8 = 0xaa;
  DAT_EXTMEM_10ba = 0x55;
  DAT_EXTMEM_10bd = 0xa5;
  TXCON = 0xff;
  return;
}



// ==== FUN_CODE_9b12 @ CODE:9b12 size 21 callers [CODE:4f9c]

void FUN_CODE_9b12(byte param_1)

{
  char cVar1;
  
  FUN_CODE_a521();
  cVar1 = (param_1 < 2) << 7;
  if (param_1 >= 2) {
    FUN_CODE_7a62(param_1 - 2);
    if (cVar1 < '\0') {
      FUN_CODE_8864();
      return;
    }
  }
  return;
}



// ==== FUN_CODE_9b66 @ CODE:9b66 size 21 callers [CODE:5c3c]

void FUN_CODE_9b66(void)

{
  DAT_INTMEM_cf = 5;
  DAT_SFR_ce = 0;
  FIFLG_3 = 1;
  DAT_EXTMEM_0722 = EPCONFIG;
  FUN_CODE_7568(DAT_EXTMEM_0723);
  return;
}



// ==== FUN_CODE_9b8f @ CODE:9b8f size 20 callers [CODE:7763]

void FUN_CODE_9b8f(void)

{
  char cVar1;
  
  cVar1 = BANK0_R7;
  FUN_CODE_8925(BANK0_R4,BANK0_R5);
  if (cVar1 == '\0') {
    FUN_CODE_97e5(BANK0_R2,BANK0_R3);
  }
  return;
}



// ==== FUN_CODE_9bdf @ CODE:9bdf size 20 callers [CODE:8b9d]

undefined1 FUN_CODE_9bdf(void)

{
  DAT_SFR_86 = 0;
  DAT_EXTMEM_2039 = 0;
  DAT_SFR_a4 = 1;
  DAT_EXTMEM_04aa = DAT_SFR_bc;
  DAT_SFR_bc = 0;
  return 0;
}



// ==== FUN_CODE_9bf3 @ CODE:9bf3 size 20 callers [CODE:9645]

char FUN_CODE_9bf3(void)

{
  return *(char *)CONCAT11('\x06' - (((0x30U < (byte)(DAT_INTMEM_b3 * '\x19')) << 7) >> 7),
                           DAT_INTMEM_b3 * '\x19' - 0x31) + -1;
}



// ==== FUN_CODE_9c07 @ CODE:9c07 size 20 callers [CODE:6aab]

void FUN_CODE_9c07(void)

{
  FUN_CODE_aefd(0x57,6,1,0,0,0x60);
  BANK1_R2 = 0;
  return;
}



// ==== FUN_CODE_9c2f @ CODE:9c2f size 10 callers [CODE:9046]

void FUN_CODE_9c2f(void)

{
  FUN_CODE_ae2a(0x714,0,1);
  return;
}



// ==== FUN_CODE_9c39 @ CODE:9c39 size 10 callers [CODE:9281]

void FUN_CODE_9c39(void)

{
  FUN_CODE_ae2a(0x71a,0,1);
  return;
}



// ==== FUN_CODE_9cca @ CODE:9cca size 19 callers [CODE:8e81]

void FUN_CODE_9cca(void)

{
  undefined1 uVar1;
  
  if (_1_5 == '\0') {
    uVar1 = 0xaa;
  }
  else {
    uVar1 = 0xa1;
  }
  FUN_CODE_87aa(uVar1,0xb0,0xff);
  return;
}



// ==== FUN_CODE_9cdd @ CODE:9cdd size 19 callers [CODE:64a1,CODE:803f]

void FUN_CODE_9cdd(byte param_1)

{
  byte bVar1;
  
  bVar1 = FUN_CODE_34d4(0xb9);
  DAT_EXTMEM_2013 = bVar1 | param_1;
  return;
}



// ==== ISR_93 @ CODE:9d29 size 19 callers []

undefined1 ISR_93(undefined1 param_1)

{
  DAT_EXTMEM_0767 = DAT_EXTMEM_0767 + '\x01';
  return param_1;
}



// ==== FUN_CODE_9d4f @ CODE:9d4f size 18 callers [CODE:64a1]

void FUN_CODE_9d4f(void)

{
  undefined1 *puVar1;
  
  if (DAT_INTMEM_b9 == '\x01') {
    puVar1 = &DAT_EXTMEM_05e6;
  }
  else {
    puVar1 = &DAT_EXTMEM_05e2;
  }
  *puVar1 = 1;
  return;
}



// ==== FUN_CODE_9d61 @ CODE:9d61 size 18 callers [CODE:2800,CODE:80bc]

void FUN_CODE_9d61(void)

{
  if (DAT_INTMEM_b3 == '\x01') {
    return;
  }
  return;
}



// ==== FUN_CODE_9d73 @ CODE:9d73 size 18 callers [CODE:6800,CODE:a12c]

char FUN_CODE_9d73(void)

{
  return ((char)((ushort)DAT_INTMEM_b3 * 10 >> 8) -
         (((0xc6 < (byte)((ushort)DAT_INTMEM_b3 * 10)) << 7) >> 7)) + '\x06';
}



// ==== FUN_CODE_9dcd @ CODE:9dcd size 18 callers [CODE:a453]

void FUN_CODE_9dcd(undefined1 param_1)

{
  *(undefined1 *)
   CONCAT11(DAT_EXTMEM_06ed - (((0xf9 < DAT_EXTMEM_06ee) << 7) >> 7),DAT_EXTMEM_06ee + 6) = param_1;
  return;
}



// ==== FUN_CODE_9e59 @ CODE:9e59 size 16 callers [CODE:104e,CODE:6aab]

void FUN_CODE_9e59(undefined1 param_1)

{
  DAT_EXTMEM_04aa = param_1;
  FUN_CODE_a57b();
  FUN_CODE_7568(DAT_EXTMEM_04aa);
  return;
}



// ==== FUN_CODE_9e99 @ CODE:9e99 size 16 callers [CODE:793a]

void FUN_CODE_9e99(void)

{
  FUN_CODE_a600(0);
  FUN_CODE_4f9c();
  FUN_CODE_a600(1);
  FUN_CODE_4f9c();
  return;
}



// ==== FUN_CODE_9eb9 @ CODE:9eb9 size 16 callers [CODE:993c,CODE:a0e7,CODE:a69a]

void FUN_CODE_9eb9(void)

{
  if ((DAT_INTMEM_ab == BANK0_R7) && (DAT_INTMEM_ad == BANK0_R5)) {
    return;
  }
  return;
}



// ==== FUN_CODE_9ef9 @ CODE:9ef9 size 16 callers [CODE:a26b]

void FUN_CODE_9ef9(void)

{
  if (DAT_INTMEM_b3 == '\x01') {
    return;
  }
  return;
}



// ==== FUN_CODE_9f29 @ CODE:9f29 size 16 callers [CODE:8ef3]

void FUN_CODE_9f29(void)

{
  if (DAT_INTMEM_b3 == '\x01') {
    return;
  }
  return;
}



// ==== FUN_CODE_9f39 @ CODE:9f39 size 16 callers [CODE:8f19]

void FUN_CODE_9f39(void)

{
  if (DAT_INTMEM_b3 == '\x01') {
    return;
  }
  return;
}



// ==== FUN_CODE_9f69 @ CODE:9f69 size 16 callers [CODE:95f2]

void FUN_CODE_9f69(void)

{
  DAT_EXTMEM_10b8 = 0;
  DAT_EXTMEM_10ba = 0;
  DAT_EXTMEM_10bd = 0;
  TXCON = 0;
  return;
}



// ==== FUN_CODE_a069 @ CODE:a069 size 14 callers [CODE:5fe3]

void FUN_CODE_a069(byte param_1)

{
  FUN_CODE_25d4((&DAT_CODE_b9ad)[param_1],0);
  FUN_CODE_27b2();
  return;
}



// ==== FUN_CODE_a077 @ CODE:a077 size 14 callers [CODE:97e5]

char FUN_CODE_a077(char param_1)

{
  byte bVar1;
  
  bVar1 = FUN_CODE_440b();
  return (param_1 - (((0xd8 < bVar1) << 7) >> 7)) + '\x06';
}



// ==== FUN_CODE_a085 @ CODE:a085 size 14 callers [CODE:870e]

char FUN_CODE_a085(char param_1)

{
  byte bVar1;
  
  bVar1 = FUN_CODE_440b();
  return (param_1 - (((0x13 < bVar1) << 7) >> 7)) + '\x05';
}



// ==== FUN_CODE_a093 @ CODE:a093 size 14 callers [CODE:6d78,CODE:a595]

char FUN_CODE_a093(char param_1)

{
  byte bVar1;
  
  bVar1 = FUN_CODE_440b();
  return (param_1 - (((0xe0 < bVar1) << 7) >> 7)) + '\x06';
}



// ==== FUN_CODE_a0bd @ CODE:a0bd size 14 callers [CODE:a453]

void FUN_CODE_a0bd(undefined1 param_1)

{
  *(undefined1 *)CONCAT11(DAT_EXTMEM_06ed,DAT_EXTMEM_06ee) = param_1;
  return;
}



// ==== FUN_CODE_a0cb @ CODE:a0cb size 14 callers [CODE:a45d]

void FUN_CODE_a0cb(undefined1 param_1)

{
  FUN_CODE_83ef(param_1,0xb936);
  FUN_CODE_a9ae(param_1,0x1d);
  return;
}



// ==== FUN_CODE_a0d9 @ CODE:a0d9 size 14 callers [CODE:a5cd]

void FUN_CODE_a0d9(undefined1 param_1)

{
  FUN_CODE_83ef(_1_2 & 1,0xb945);
  FUN_CODE_a99c(param_1);
  return;
}



// ==== FUN_CODE_a0e7 @ CODE:a0e7 size 14 callers [CODE:7eb6]

void FUN_CODE_a0e7(void)

{
  FUN_CODE_9eb9(0x3f,0x10);
  return;
}



// ==== FUN_CODE_a0f5 @ CODE:a0f5 size 14 callers []

void FUN_CODE_a0f5(void)

{
  DAT_INTMEM_ab = 4;
  DAT_INTMEM_ad = 1;
  FUN_CODE_7eb6();
  FUN_CODE_a77b();
  return;
}



// ==== FUN_CODE_a12c @ CODE:a12c size 13 callers [CODE:7069]

void FUN_CODE_a12c(void)

{
  FUN_CODE_9d73();
  FUN_CODE_aac4(8);
  return;
}



// ==== FUN_CODE_a139 @ CODE:a139 size 13 callers [CODE:3caa,CODE:4f9c,CODE:6800]

void FUN_CODE_a139(void)

{
  return;
}



// ==== FUN_CODE_a1db @ CODE:a1db size 12 callers [CODE:8b9d]

undefined1 FUN_CODE_a1db(void)

{
  IE = 0;
  DAT_SFR_aa = 0x3e;
  SADDR = 0x80;
  EX0 = 1;
  return 0;
}



// ==== FUN_CODE_a1f3 @ CODE:a1f3 size 12 callers [CODE:7a1a]

void FUN_CODE_a1f3(void)

{
  FUN_CODE_342d(DAT_INTMEM_b3);
  return;
}



// ==== FUN_CODE_a20b @ CODE:a20b size 12 callers [CODE:7568]

undefined1 FUN_CODE_a20b(short param_1)

{
  undefined1 uVar1;
  
  uVar1 = FUN_CODE_76d6();
  PCON1 = uVar1;
  CCAPM4 = *(undefined1 *)(param_1 + 1);
  return *(undefined1 *)(param_1 + 1);
}



// ==== FUN_CODE_a253 @ CODE:a253 size 12 callers [CODE:95f2]

void FUN_CODE_a253(undefined1 param_1,undefined1 param_2)

{
  FUN_CODE_107e();
  DAT_EXTMEM_0735 = param_1;
  DAT_EXTMEM_0736 = param_2;
  return;
}



// ==== FUN_CODE_a26b @ CODE:a26b size 12 callers [CODE:a4fd]

void FUN_CODE_a26b(undefined1 param_1,undefined1 param_2)

{
  FUN_CODE_9ef9();
  DAT_EXTMEM_0750 = param_1;
  DAT_EXTMEM_0751 = param_2;
  return;
}



// ==== FUN_CODE_a335 @ CODE:a335 size 11 callers [CODE:2800,CODE:7a1a,CODE:8a68]

void FUN_CODE_a335(char *param_1)

{
  FUN_CODE_43ee();
  if (*param_1 == '\x01') {
    return;
  }
  return;
}



// ==== FUN_CODE_a356 @ CODE:a356 size 11 callers [CODE:5fe3]

undefined1 FUN_CODE_a356(undefined1 *param_1)

{
  FUN_CODE_4512(DAT_INTMEM_b3 + -0x18);
  return *param_1;
}



// ==== FUN_CODE_a377 @ CODE:a377 size 11 callers [CODE:27b2]

byte FUN_CODE_a377(void)

{
  byte bVar1;
  
  bVar1 = FIFLG1;
  FIFLG1 = bVar1 & ~(&DAT_CODE_b8f0)[DAT_INTMEM_b3];
  return ~(&DAT_CODE_b8f0)[DAT_INTMEM_b3];
}



// ==== FUN_CODE_a3e5 @ CODE:a3e5 size 3 callers [CODE:79d0]

void FUN_CODE_a3e5(void)

{
  FUN_CODE_ad6d(0x4ca);
  return;
}



// ==== FUN_CODE_a3e8 @ CODE:a3e8 size 7 callers [CODE:79d0]

void FUN_CODE_a3e8(void)

{
  FUN_CODE_ad6d();
  return;
}



// ==== FUN_CODE_a40d @ CODE:a40d size 10 callers [CODE:5fe3]

void FUN_CODE_a40d(undefined1 *param_1)

{
  FUN_CODE_43ee();
  *param_1 = 1;
  DAT_INTMEM_ca = 1;
  return;
}



// ==== FUN_CODE_a449 @ CODE:a449 size 10 callers [CODE:7568,CODE:8bc8]

void FUN_CODE_a449(void)

{
  byte bVar1;
  
  DAT_SFR_ce = 0xee;
  bVar1 = DAT_SFR_c2;
  DAT_SFR_c2 = bVar1 | 4;
  bVar1 = FIFLG1;
  FIFLG1 = bVar1 | 4;
  return;
}



// ==== FUN_CODE_a453 @ CODE:a453 size 10 callers [CODE:a76f]

void FUN_CODE_a453(void)

{
  FUN_CODE_a0bd(0);
  FUN_CODE_9dcd(0);
  return;
}



// ==== FUN_CODE_a45d @ CODE:a45d size 10 callers [CODE:a5cd]

void FUN_CODE_a45d(void)

{
  FUN_CODE_9023(0);
  FUN_CODE_a0cb(0);
  return;
}



// ==== FUN_CODE_a47b @ CODE:a47b size 10 callers [CODE:50fb]

void FUN_CODE_a47b(byte *param_1)

{
  *param_1 = *param_1 & 0xfc;
  param_1[1] = param_1[1] & 0xfc;
  return;
}



// ==== FUN_CODE_a4fd @ CODE:a4fd size 9 callers [CODE:5fe3,CODE:89b2]

void FUN_CODE_a4fd(void)

{
  FUN_CODE_9046();
  FUN_CODE_a26b();
  FUN_CODE_93bc();
  return;
}



// ==== FUN_CODE_a521 @ CODE:a521 size 9 callers [CODE:9b12]

undefined1 FUN_CODE_a521(void)

{
  return *(undefined1 *)(DAT_INTMEM_b3 + -0x39);
}



// ==== FUN_CODE_a52a @ CODE:a52a size 9 callers [CODE:9554]

void FUN_CODE_a52a(void)

{
  *(undefined1 *)(DAT_INTMEM_b3 + -0x39) = BANK0_R7;
  return;
}



// ==== FUN_CODE_a569 @ CODE:a569 size 9 callers [CODE:6aab]

undefined1 FUN_CODE_a569(void)

{
  byte bVar1;
  
  IE = 0;
  EX0 = 1;
  bVar1 = T2MOD;
  T2MOD = bVar1 | 4;
  return 0;
}



// ==== FUN_CODE_a57b @ CODE:a57b size 9 callers [CODE:9e59]

void FUN_CODE_a57b(undefined1 param_1)

{
  DAT_EXTMEM_072a = param_1;
  FUN_CODE_76bf();
  return;
}



// ==== FUN_CODE_a584 @ CODE:a584 size 9 callers [CODE:7712]

char FUN_CODE_a584(char *param_1)

{
  FUN_CODE_83dc(0xb3);
  return *param_1 + -1;
}



// ==== FUN_CODE_a595 @ CODE:a595 size 8 callers [CODE:4e91,CODE:8864]

void FUN_CODE_a595(void)

{
  FUN_CODE_a093();
  FUN_CODE_a934();
  return;
}



// ==== FUN_CODE_a59d @ CODE:a59d size 8 callers [CODE:5cfa]

undefined1 FUN_CODE_a59d(undefined1 *param_1)

{
  FUN_CODE_43f0(0xb9);
  return *param_1;
}



// ==== FUN_CODE_a5a5 @ CODE:a5a5 size 8 callers [CODE:5cfa]

undefined1 FUN_CODE_a5a5(undefined1 *param_1)

{
  FUN_CODE_4436(0xb9);
  return *param_1;
}



// ==== FUN_CODE_a5b5 @ CODE:a5b5 size 8 callers [CODE:8ff0]

void FUN_CODE_a5b5(void)

{
  DAT_EXTMEM_2013 = DAT_EXTMEM_2013 | 0x76;
  return;
}



// ==== FUN_CODE_a5bd @ CODE:a5bd size 8 callers [CODE:8a68]

undefined1 FUN_CODE_a5bd(undefined1 *param_1)

{
  FUN_CODE_344c(0xb3);
  return *param_1;
}



// ==== FUN_CODE_a5cd @ CODE:a5cd size 8 callers [CODE:a76f]

void FUN_CODE_a5cd(void)

{
  FUN_CODE_a45d();
  _1_2 = 1;
  FUN_CODE_a0d9();
  return;
}



// ==== FUN_CODE_a5e4 @ CODE:a5e4 size 7 callers [CODE:9554]

void FUN_CODE_a5e4(void)

{
  DAT_INTMEM_b3 = BANK0_R7;
  FUN_CODE_9046();
  return;
}



// ==== FUN_CODE_a5eb @ CODE:a5eb size 7 callers [CODE:843b]

void FUN_CODE_a5eb(void)

{
  DAT_INTMEM_c7 = 0;
  DAT_INTMEM_c8 = 0;
  return;
}



// ==== FUN_CODE_a5f2 @ CODE:a5f2 size 7 callers [CODE:7069]

void FUN_CODE_a5f2(void)

{
  FUN_CODE_109e(DAT_INTMEM_b3);
  return;
}



// ==== FUN_CODE_a600 @ CODE:a600 size 7 callers [CODE:9e99]

void FUN_CODE_a600(void)

{
  DAT_INTMEM_b3 = BANK0_R7;
  FUN_CODE_9046();
  return;
}



// ==== FUN_CODE_a615 @ CODE:a615 size 7 callers [CODE:5fe3]

void FUN_CODE_a615(undefined1 *param_1)

{
  FUN_CODE_4434();
  *param_1 = 1;
  return;
}



// ==== FUN_CODE_a61c @ CODE:a61c size 7 callers [CODE:27b2]

void FUN_CODE_a61c(void)

{
  FUN_CODE_84a1(0x134);
  return;
}



// ==== FUN_CODE_a623 @ CODE:a623 size 7 callers [CODE:27b2]

void FUN_CODE_a623(void)

{
  FUN_CODE_84a1(0x11c);
  return;
}



// ==== FUN_CODE_a62a @ CODE:a62a size 7 callers [CODE:7568]

void FUN_CODE_a62a(void)

{
  return;
}



// ==== FUN_CODE_a631 @ CODE:a631 size 7 callers [CODE:7568]

void FUN_CODE_a631(void)

{
  return;
}



// ==== FUN_CODE_a638 @ CODE:a638 size 7 callers [CODE:2800,CODE:870e,CODE:88c5,CODE:9544,CODE:a63f,CODE:a646,CODE:a64d]

void FUN_CODE_a638(void)

{
  FUN_CODE_8800(DAT_INTMEM_b3);
  return;
}



// ==== FUN_CODE_a63f @ CODE:a63f size 7 callers [CODE:6800]

void FUN_CODE_a63f(void)

{
  FUN_CODE_a638(BANK0_R7,5);
  return;
}



// ==== FUN_CODE_a646 @ CODE:a646 size 7 callers [CODE:7069]

void FUN_CODE_a646(void)

{
  FUN_CODE_a638(BANK0_R7,3);
  return;
}



// ==== FUN_CODE_a64d @ CODE:a64d size 7 callers [CODE:6800,CODE:6d78]

void FUN_CODE_a64d(void)

{
  FUN_CODE_a638(BANK0_R7,0x11);
  return;
}



// ==== FUN_CODE_a654 @ CODE:a654 size 7 callers [CODE:8b9d]

void FUN_CODE_a654(void)

{
  DAT_EXTMEM_2011 = 0x12;
  return;
}



// ==== FUN_CODE_a67e @ CODE:a67e size 7 callers [CODE:8b9d]

void FUN_CODE_a67e(void)

{
  RD = 0;
  INT0 = 1;
  T1 = 0;
  return;
}



// ==== FUN_CODE_a685 @ CODE:a685 size 7 callers [CODE:8b9d]

void FUN_CODE_a685(void)

{
  HIE = 0xff;
  P2 = 0xf2;
  return;
}



// ==== FUN_CODE_a69a @ CODE:a69a size 7 callers [CODE:7eb6,CODE:967b,CODE:993c]

void FUN_CODE_a69a(void)

{
  FUN_CODE_9eb9(BANK0_R7,4);
  return;
}



// ==== FUN_CODE_a6b5 @ CODE:a6b5 size 6 callers [CODE:8e81]

void FUN_CODE_a6b5(undefined1 *param_1)

{
  FUN_CODE_50e1();
  *param_1 = 0;
  return;
}



// ==== FUN_CODE_a6eb @ CODE:a6eb size 6 callers [CODE:7a1a]

undefined1 FUN_CODE_a6eb(undefined1 *param_1)

{
  FUN_CODE_44f6();
  return *param_1;
}



// ==== FUN_CODE_a6f1 @ CODE:a6f1 size 6 callers [CODE:25d4]

void FUN_CODE_a6f1(undefined1 *param_1,undefined1 param_2)

{
  FUN_CODE_4441();
  *param_1 = param_2;
  return;
}



// ==== FUN_CODE_a6f7 @ CODE:a6f7 size 6 callers [CODE:3caa]

undefined1 FUN_CODE_a6f7(undefined1 *param_1)

{
  FUN_CODE_4441();
  return *param_1;
}



// ==== FUN_CODE_a6fd @ CODE:a6fd size 6 callers [CODE:8e81]

undefined1 FUN_CODE_a6fd(undefined1 *param_1)

{
  FUN_CODE_43ee();
  return *param_1;
}



// ==== FUN_CODE_a727 @ CODE:a727 size 6 callers [CODE:5e73,CODE:7eb6]

undefined1 FUN_CODE_a727(undefined1 *param_1)

{
  FUN_CODE_351a();
  return *param_1;
}



// ==== FUN_CODE_a72d @ CODE:a72d size 6 callers [CODE:5e73]

void FUN_CODE_a72d(undefined1 *param_1,undefined1 param_2)

{
  FUN_CODE_351a();
  *param_1 = param_2;
  return;
}



// ==== FUN_CODE_a769 @ CODE:a769 size 6 callers [CODE:7568]

void FUN_CODE_a769(undefined1 param_1)

{
  DAT_EXTMEM_0723 = param_1;
  return;
}



// ==== FUN_CODE_a76f @ CODE:a76f size 6 callers [CODE:5fe3]

void FUN_CODE_a76f(void)

{
  FUN_CODE_a453();
  FUN_CODE_a5cd();
  return;
}



// ==== FUN_CODE_a77b @ CODE:a77b size 6 callers [CODE:a0f5]

void FUN_CODE_a77b(void)

{
  FUN_CODE_8ef3();
  FUN_CODE_8f19();
  return;
}



// ==== FUN_CODE_a7a4 @ CODE:a7a4 size 5 callers [CODE:104e,CODE:7207]

undefined1 FUN_CODE_a7a4(void)

{
  return DAT_INTMEM_d1;
}



// ==== FUN_CODE_a7b8 @ CODE:a7b8 size 4 callers [CODE:793a,CODE:89b2]

void FUN_CODE_a7b8(void)

{
  byte bVar1;
  
  bVar1 = P2;
  P2 = bVar1 | 4;
  return;
}



// ==== FUN_CODE_a7bc @ CODE:a7bc size 4 callers [CODE:6aab]

void FUN_CODE_a7bc(void)

{
  byte bVar1;
  
  bVar1 = P2;
  P2 = bVar1 | 1;
  return;
}



// ==== thunk_FUN_CODE_793a @ CODE:a7c0 size 3 callers [CODE:af88]

void thunk_FUN_CODE_793a(void)

{
  char in_PSW;
  
  _2_0 = 0;
  FIE1 = 0x5a;
  DAT_SFR_85 = 0x10;
  FIE1 = 0;
  do {
    DAT_EXTMEM_04a1 = DAT_EXTMEM_0760;
    if (DAT_EXTMEM_0760 == '\x01') {
      DAT_EXTMEM_04a2 = 2;
    }
    else if (DAT_EXTMEM_0760 == '\x02') {
      FUN_CODE_a7b8();
      FUN_CODE_5db7();
      if (in_PSW < '\0') {
        FUN_CODE_9e99();
      }
      FUN_CODE_89b2();
    }
    else {
      in_PSW = (0xfd < DAT_EXTMEM_0760 - 2U) << 7;
      if (DAT_EXTMEM_0760 - 2U == 0xfe) {
        DAT_EXTMEM_04a2 = 1;
      }
    }
    FUN_CODE_843b(DAT_EXTMEM_04a2,DAT_EXTMEM_04a1);
    FUN_CODE_104e();
  } while( true );
}



// ==== FUN_CODE_a7c3 @ CODE:a7c3 size 3 callers [CODE:6406]

void FUN_CODE_a7c3(void)

{
  FUN_CODE_81ed();
  DAT_EXTMEM_05df = DAT_EXTMEM_059e + '\x04';
  DAT_EXTMEM_0559 = 5;
  DAT_EXTMEM_055a = 0x9c;
  FUN_CODE_7207();
  return;
}



// ==== FUN_CODE_a7f0 @ CODE:a7f0 size 3 callers [CODE:5cfa]

void FUN_CODE_a7f0(void)

{
  return;
}



// ==== FUN_CODE_a7f9 @ CODE:a7f9 size 3 callers [CODE:996c]

void FUN_CODE_a7f9(void)

{
  return;
}



// ==== thunk_FUN_CODE_9281 @ CODE:a833 size 3 callers [CODE:77b4,CODE:78ee]

void thunk_FUN_CODE_9281(void)

{
  undefined1 uVar1;
  
  if (DAT_INTMEM_b9 == '\x01') {
    FUN_CODE_9c39(0x24);
    uVar1 = 0x22;
  }
  else {
    if (DAT_INTMEM_b9 != '\0') {
      return;
    }
    FUN_CODE_9c39(0x23);
    uVar1 = 0x21;
  }
  FUN_CODE_ae2a(0x717,uVar1);
  return;
}



// ==== thunk_FUN_CODE_a0f5 @ CODE:a839 size 3 callers [CODE:5fe3]

void thunk_FUN_CODE_a0f5(void)

{
  DAT_INTMEM_ab = 4;
  DAT_INTMEM_ad = 1;
  FUN_CODE_7eb6();
  FUN_CODE_a77b();
  return;
}



// ==== FUN_CODE_a90e @ CODE:a90e size 45 callers [CODE:448e,CODE:6f27,CODE:8742]

char FUN_CODE_a90e(undefined1 param_1,char param_2,char param_3,char param_4,char param_5)

{
  byte bVar1;
  char cVar2;
  
  if (param_5 != '\0') {
    param_4 = param_4 + '\x01';
  }
  if (((param_5 != '\0' || param_4 != '\0') && (param_3 + 2U < 4)) &&
     (bVar1 = param_2 + 2, bVar1 < 4)) {
    bVar1 = (bVar1 * '\x02' | bVar1 >> 7) << 1 | (bVar1 & 0x7f) >> 6 | param_3 + 2U;
                    /* WARNING: Could not recover jumptable at 0xa933. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    cVar2 = (*(code *)((ushort)(bVar1 << 1 | bVar1 >> 7) + 0xa88e))(param_1);
    return cVar2;
  }
  return param_3;
}



// ==== FUN_CODE_a934 @ CODE:a934 size 25 callers [CODE:2800,CODE:33b9,CODE:33e2,CODE:3439,CODE:3572,CODE:53ea,CODE:666b,CODE:6c35,CODE:6d78,CODE:80bc,CODE:8b1b,CODE:a595]

undefined1 FUN_CODE_a934(undefined1 *param_1,undefined1 param_2,char param_3)

{
  if (param_3 == '\x01') {
    return *(undefined1 *)CONCAT11(param_2,param_1);
  }
  if (param_3 == '\0') {
    return *param_1;
  }
  if (param_3 == -2) {
    return *(undefined1 *)ZEXT12(param_1);
  }
  return *(undefined1 *)CONCAT11(param_2,param_1);
}



// ==== FUN_CODE_a94d @ CODE:a94d size 45 callers [CODE:33e9,CODE:42a5,CODE:64a1,CODE:6d78,CODE:76ec]

undefined1 FUN_CODE_a94d(undefined2 param_1,byte param_2,char param_3,char param_4)

{
  char cVar1;
  byte bVar2;
  
  bVar2 = (byte)param_1;
  cVar1 = (char)((ushort)param_1 >> 8);
  if (param_4 == '\x01') {
    return *(undefined1 *)
            CONCAT11(cVar1 + (param_3 - ((CARRY1(bVar2,param_2) << 7) >> 7)),bVar2 + param_2);
  }
  if (param_4 == '\0') {
    return *(undefined1 *)(param_2 + bVar2);
  }
  if (param_4 == -2) {
    return *(undefined1 *)(ushort)(param_2 + bVar2);
  }
  return *(undefined1 *)
          CONCAT11(cVar1 + (param_3 - ((CARRY1(bVar2,param_2) << 7) >> 7)),bVar2 + param_2);
}



// ==== FUN_CODE_a97a @ CODE:a97a size 34 callers [CODE:666b]

char FUN_CODE_a97a(char param_1,char *param_2,undefined1 param_3,char param_4)

{
  char cVar1;
  
  if (param_4 == '\x01') {
    param_1 = *(char *)CONCAT11(param_3,param_2) + param_1;
    *(char *)CONCAT11(param_3,param_2) = param_1;
    return param_1;
  }
  if (param_4 == '\0') {
    cVar1 = *param_2;
    *param_2 = param_1 + cVar1;
    return param_1 + cVar1;
  }
  if (param_4 == -2) {
    cVar1 = *(char *)ZEXT12(param_2);
    *(char *)ZEXT12(param_2) = cVar1 + param_1;
    return cVar1 + param_1;
  }
  return *(char *)CONCAT11(param_3,param_2) + param_1;
}



// ==== FUN_CODE_a99c @ CODE:a99c size 18 callers [CODE:33b9,CODE:3439,CODE:3572,CODE:42a5,CODE:4532,CODE:64a1,CODE:6c35,CODE:803f,CODE:8b47,CODE:a0d9]

void FUN_CODE_a99c(undefined1 param_1,undefined1 *param_2,undefined1 param_3,char param_4)

{
  if (param_4 == '\x01') {
    *(undefined1 *)CONCAT11(param_3,param_2) = param_1;
    return;
  }
  if (param_4 == '\0') {
    *param_2 = param_1;
    return;
  }
  if (param_4 == -2) {
    *(undefined1 *)ZEXT12(param_2) = param_1;
  }
  return;
}



// ==== FUN_CODE_a9ae @ CODE:a9ae size 34 callers [CODE:27b2,CODE:33dc,CODE:5cfa,CODE:6c35,CODE:6d78,CODE:9023,CODE:9137,CODE:a0cb]

void FUN_CODE_a9ae(undefined1 param_1,undefined2 param_2,byte param_3,char param_4,char param_5)

{
  byte bVar1;
  
  bVar1 = (byte)param_2;
  if (param_5 == '\x01') {
    *(undefined1 *)
     CONCAT11((char)((ushort)param_2 >> 8) + (param_4 - ((CARRY1(bVar1,param_3) << 7) >> 7)),
              bVar1 + param_3) = param_1;
    return;
  }
  if (param_5 == '\0') {
    *(undefined1 *)(param_3 + bVar1) = param_1;
    return;
  }
  if (param_5 == -2) {
    *(undefined1 *)(ushort)(param_3 + bVar1) = param_1;
  }
  return;
}



// ==== FUN_CODE_a9d0 @ CODE:a9d0 size 18 callers [CODE:3572]

char FUN_CODE_a9d0(char param_1,byte param_2,char param_3,byte param_4)

{
  return param_3 * param_2 + param_4 * param_1 + (char)((ushort)param_4 * (ushort)param_2 >> 8);
}



// ==== FUN_CODE_a9e2 @ CODE:a9e2 size 85 callers [CODE:54aa,CODE:6aab,CODE:7069]

byte FUN_CODE_a9e2(char param_1,byte param_2,byte param_3,byte param_4)

{
  bool bVar1;
  byte bVar2;
  char cVar3;
  byte bVar4;
  byte bVar5;
  byte bVar6;
  
  if (param_1 != '\0') {
    bVar2 = 0;
    cVar3 = '\b';
    do {
      bVar1 = CARRY1(param_4,param_4);
      param_4 = param_4 * '\x02';
      bVar4 = param_3 << 1 | bVar1;
      bVar6 = bVar2 << 1 | param_3 >> 7;
      bVar5 = param_1 - (((bVar4 < param_2 - ((char)bVar2 >> 7)) << 7) >> 7);
      bVar2 = bVar6;
      if (bVar6 >= bVar5) {
        bVar4 = bVar4 - (param_2 - (((bVar6 < bVar5) << 7) >> 7));
        param_4 = param_4 + 1;
        bVar2 = bVar6 - bVar5;
      }
      cVar3 = cVar3 + -1;
      param_3 = bVar4;
    } while (cVar3 != '\0');
    return bVar4;
  }
  if (param_3 == 0) {
    if (param_2 != 0) {
      param_4 = param_4 / param_2;
    }
    return param_4;
  }
  bVar2 = 0;
  bVar5 = param_3;
  if (param_2 != 0) {
    bVar5 = param_3 / param_2;
    bVar2 = param_3 % param_2;
  }
  cVar3 = OV;
  if (cVar3 != '\x01') {
    cVar3 = '\b';
    bVar5 = bVar2;
LAB_CODE_aa20:
    do {
      bVar1 = CARRY1(param_4,param_4);
      param_4 = param_4 * '\x02';
      bVar2 = bVar5 << 1 | bVar1;
      if ((char)bVar5 < '\0') {
        bVar5 = bVar2 - param_2;
      }
      else {
        bVar4 = param_2 - ((char)bVar5 >> 7);
        bVar6 = bVar2 - bVar4;
        bVar5 = bVar6;
        if (bVar2 < bVar4) {
          cVar3 = cVar3 + -1;
          bVar5 = bVar2;
          if (cVar3 == '\0') {
            return bVar6;
          }
          goto LAB_CODE_aa20;
        }
      }
      param_4 = param_4 + 1;
      cVar3 = cVar3 + -1;
    } while (cVar3 != '\0');
  }
  return bVar5;
}



// ==== FUN_CODE_aa6d @ CODE:aa6d size 22 callers [CODE:3572,CODE:4532,CODE:4f9c,CODE:53f4,CODE:5484,CODE:691c,CODE:aafc]

void FUN_CODE_aa6d(char param_1,short param_2,byte param_3)

{
  byte bVar1;
  char cVar2;
  byte *pbVar3;
  char *pcVar4;
  
  pbVar3 = (byte *)(param_2 + 1);
  bVar1 = *pbVar3;
  *pbVar3 = bVar1 + param_3;
  cVar2 = (char)((ushort)pbVar3 >> 8);
  if ((char)pbVar3 == '\0') {
    cVar2 = cVar2 + -1;
  }
  pcVar4 = (char *)CONCAT11(cVar2,(char)pbVar3 + -1);
  *pcVar4 = *pcVar4 + (param_1 - ((CARRY1(bVar1,param_3) << 7) >> 7));
  return;
}



// ==== FUN_CODE_aa83 @ CODE:aa83 size 22 callers [CODE:546c]

char FUN_CODE_aa83(char param_1,short param_2,byte param_3)

{
  byte bVar1;
  char cVar2;
  byte *pbVar3;
  char *pcVar4;
  
  pbVar3 = (byte *)(param_2 + 1);
  bVar1 = *pbVar3;
  *pbVar3 = param_3 + bVar1;
  cVar2 = (char)((ushort)pbVar3 >> 8);
  if ((char)pbVar3 == '\0') {
    cVar2 = cVar2 + -1;
  }
  pcVar4 = (char *)CONCAT11(cVar2,(char)pbVar3 + -1);
  cVar2 = *pcVar4;
  *pcVar4 = param_1 + (cVar2 - ((CARRY1(param_3,bVar1) << 7) >> 7));
  return cVar2;
}



// ==== FUN_CODE_aa99 @ CODE:aa99 size 43 callers [CODE:53fa,CODE:548b,CODE:6800]

undefined1 FUN_CODE_aa99(char param_1,undefined1 param_2,char param_3)

{
  if (param_3 == '\x01') {
    return *(undefined1 *)(CONCAT11(param_2,param_1) + 1);
  }
  if (param_3 == '\0') {
    return *(undefined1 *)(param_1 + '\x01');
  }
  if (param_3 == -2) {
    return *(undefined1 *)(ushort)(param_1 + 1);
  }
  return *(undefined1 *)(CONCAT11(param_2,param_1) + 1);
}



// ==== FUN_CODE_aac4 @ CODE:aac4 size 56 callers [CODE:6800,CODE:a12c]

undefined1 FUN_CODE_aac4(undefined2 param_1,byte param_2,char param_3,char param_4)

{
  char cVar1;
  byte bVar2;
  
  bVar2 = (byte)param_1;
  cVar1 = (char)((ushort)param_1 >> 8);
  if (param_4 == '\x01') {
    return *(undefined1 *)
            (CONCAT11(cVar1 + (param_3 - ((CARRY1(bVar2,param_2) << 7) >> 7)),bVar2 + param_2) + 1);
  }
  if (param_4 == '\0') {
    return *(undefined1 *)(param_2 + bVar2 + '\x01');
  }
  if (param_4 == -2) {
    return *(undefined1 *)(ushort)(param_2 + bVar2 + 1);
  }
  return *(undefined1 *)(CONCAT11(cVar1 + param_3,bVar2) + 1 + (ushort)param_2);
}



// ==== FUN_CODE_aafc @ CODE:aafc size 77 callers [CODE:8b47]

char FUN_CODE_aafc(char param_1,undefined2 param_2,byte param_3,char param_4,char param_5,
                  char param_6)

{
  byte bVar1;
  byte *pbVar2;
  char cVar3;
  char *pcVar4;
  byte bVar5;
  char *pcVar6;
  
  if (param_6 == '\x01') {
    cVar3 = FUN_CODE_aa6d(param_1);
    return cVar3;
  }
  cVar3 = (char)param_2;
  if (param_6 == '\0') {
    pcVar4 = (char *)(cVar3 + param_4);
    pbVar2 = (byte *)(pcVar4 + '\x01');
    bVar1 = *pbVar2;
    *pbVar2 = param_3 + *pbVar2;
    param_1 = param_1 + (*pcVar4 - ((CARRY1(param_3,bVar1) << 7) >> 7));
    *pcVar4 = param_1;
    return param_1;
  }
  if (param_6 == -2) {
    bVar5 = cVar3 + param_4;
    bVar1 = *(byte *)(ushort)(bVar5 + 1);
    *(byte *)(ushort)(bVar5 + 1) = bVar1 + param_3;
    cVar3 = *(char *)(ushort)bVar5 + (param_1 - ((CARRY1(bVar1,param_3) << 7) >> 7));
    *(char *)(ushort)bVar5 = cVar3;
    return cVar3;
  }
  pcVar6 = (char *)CONCAT11((char)((ushort)param_2 >> 8) + param_5,cVar3 + param_4);
  return *pcVar6 + (param_1 - ((CARRY1(pcVar6[1],param_3) << 7) >> 7));
}



// ==== FUN_CODE_ab68 @ CODE:ab68 size 45 callers [CODE:27b2,CODE:6800]

void FUN_CODE_ab68(undefined1 param_1,undefined2 param_2,undefined1 param_3,byte param_4,
                  char param_5,char param_6)

{
  byte bVar2;
  undefined1 *puVar1;
  
  bVar2 = (byte)param_2;
  if (param_6 == '\x01') {
    puVar1 = (undefined1 *)
             CONCAT11((char)((ushort)param_2 >> 8) + (param_5 - ((CARRY1(bVar2,param_4) << 7) >> 7))
                      ,bVar2 + param_4);
    *puVar1 = param_1;
    puVar1[1] = param_3;
    return;
  }
  if (param_6 == '\0') {
    *(undefined1 *)(param_4 + bVar2) = param_1;
    ((undefined1 *)(param_4 + bVar2))['\x01'] = param_3;
    return;
  }
  if (param_6 == -2) {
    *(undefined1 *)(ushort)(param_4 + bVar2) = param_1;
    *(undefined1 *)(ushort)(param_4 + bVar2 + 1) = param_3;
  }
  return;
}



// ==== FUN_CODE_aba2 @ CODE:aba2 size 79 callers [CODE:79d0]

char FUN_CODE_aba2(char param_1,byte param_2,byte param_3,byte param_4,char param_5,byte param_6,
                  byte param_7,byte param_8)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  byte bVar6;
  byte bVar7;
  byte bVar8;
  
  bVar3 = (byte)((ushort)param_3 * (ushort)param_7);
  bVar4 = (byte)((ushort)param_6 * (ushort)param_4);
  bVar5 = bVar4 + bVar3;
  bVar6 = (byte)((ushort)param_2 * (ushort)param_8);
  bVar7 = bVar6 + bVar5;
  bVar8 = (byte)((ushort)param_4 * (ushort)param_7);
  bVar2 = (byte)((ushort)param_4 * (ushort)param_8 >> 8);
  bVar1 = (char)((ushort)param_4 * (ushort)param_7 >> 8) - ((CARRY1(bVar2,bVar8) << 7) >> 7);
  return ((param_6 * param_3 + param_2 * param_7 + param_5 * param_4 + param_1 * param_8 +
           ((char)((ushort)param_3 * (ushort)param_7 >> 8) - ((CARRY1(bVar4,bVar3) << 7) >> 7)) +
           (char)((ushort)param_6 * (ushort)param_4 >> 8) +
          ((char)((ushort)param_2 * (ushort)param_8 >> 8) - ((CARRY1(bVar6,bVar5) << 7) >> 7))) -
         ((CARRY1(bVar7,bVar1) << 7) >> 7)) -
         ((CARRY1(bVar7 + bVar1,
                  (char)((ushort)param_3 * (ushort)param_8 >> 8) -
                  ((CARRY1((byte)((ushort)param_3 * (ushort)param_8),bVar2 + bVar8) << 7) >> 7)) <<
          7) >> 7);
}



// ==== FUN_CODE_ac2d @ CODE:ac2d size 206 callers [CODE:79d0]

byte FUN_CODE_ac2d(char param_1,char param_2,char param_3,byte param_4,byte param_5,byte param_6,
                  byte param_7,byte param_8)

{
  bool bVar1;
  bool bVar2;
  char cVar3;
  char cVar4;
  byte bVar5;
  byte bVar6;
  byte bVar7;
  byte bVar8;
  byte bVar9;
  byte bVar10;
  
  if (param_1 != '\0') {
    cVar4 = '\b';
    bVar7 = 0;
    do {
      bVar1 = CARRY1(param_8,param_8);
      param_8 = param_8 * '\x02';
      bVar10 = param_7 << 1 | bVar1;
      bVar8 = param_6 << 1 | param_7 >> 7;
      bVar9 = param_5 << 1 | param_6 >> 7;
      bVar6 = bVar7 << 1 | param_5 >> 7;
      bVar5 = param_1 - (((bVar9 < (byte)(param_2 -
                                         (((bVar8 < (byte)(param_3 -
                                                          (((bVar10 < param_4 - ((char)bVar7 >> 7))
                                                           << 7) >> 7))) << 7) >> 7))) << 7) >> 7);
      bVar7 = bVar6;
      if (bVar6 >= bVar5) {
        bVar7 = param_4 - (((bVar6 < bVar5) << 7) >> 7);
        bVar1 = bVar10 < bVar7;
        bVar10 = bVar10 - bVar7;
        bVar7 = param_3 - ((bVar1 << 7) >> 7);
        bVar1 = bVar8 < bVar7;
        bVar8 = bVar8 - bVar7;
        bVar9 = bVar9 - (param_2 - ((bVar1 << 7) >> 7));
        param_8 = param_8 + 1;
        bVar7 = bVar6 - bVar5;
      }
      cVar4 = cVar4 + -1;
      param_5 = bVar9;
      param_6 = bVar8;
      param_7 = bVar10;
    } while (cVar4 != '\0');
    return bVar9;
  }
  if (param_2 != '\0') {
    cVar4 = '\x10';
    bVar7 = 0;
    do {
      bVar1 = CARRY1(param_8,param_8);
      param_8 = param_8 * '\x02';
      bVar10 = param_6 << 1 | param_7 >> 7;
      bVar8 = param_5 << 1 | param_6 >> 7;
      bVar9 = bVar7 << 1 | param_5 >> 7;
      bVar5 = bVar7 & 0x80;
      cVar3 = C;
      if (cVar3 == '\0') {
        bVar2 = bVar9 < (byte)(param_2 -
                              (((bVar8 < (byte)(param_3 -
                                               (((bVar10 < param_4 - ((char)bVar7 >> 7)) << 7) >> 7)
                                               )) << 7) >> 7));
        bVar5 = bVar2 << 7;
        if (!bVar2) goto LAB_CODE_aca8;
      }
      else {
        C = 0;
LAB_CODE_aca8:
        bVar7 = param_4 - ((char)bVar5 >> 7);
        bVar2 = bVar10 < bVar7;
        bVar10 = bVar10 - bVar7;
        bVar7 = param_3 - ((bVar2 << 7) >> 7);
        bVar2 = bVar8 < bVar7;
        bVar8 = bVar8 - bVar7;
        bVar9 = bVar9 - (param_2 - ((bVar2 << 7) >> 7));
        param_8 = param_8 + 1;
      }
      cVar4 = cVar4 + -1;
      bVar7 = bVar9;
      param_5 = bVar8;
      param_6 = bVar10;
      param_7 = param_7 << 1 | bVar1;
      if (cVar4 == '\0') {
        return bVar9;
      }
    } while( true );
  }
  if (param_3 != '\0') {
    cVar4 = '\x18';
    bVar7 = 0;
    do {
      bVar1 = CARRY1(param_8,param_8);
      param_8 = param_8 * '\x02';
      bVar8 = param_5 << 1 | param_6 >> 7;
      bVar9 = bVar7 << 1 | param_5 >> 7;
      bVar5 = bVar7 & 0x80;
      cVar3 = C;
      if (cVar3 == '\0') {
        bVar2 = bVar9 < (byte)(param_3 - (((bVar8 < param_4 - ((char)bVar7 >> 7)) << 7) >> 7));
        bVar5 = bVar2 << 7;
        if (!bVar2) goto LAB_CODE_ac7c;
      }
      else {
        C = 0;
LAB_CODE_ac7c:
        bVar7 = param_4 - ((char)bVar5 >> 7);
        bVar2 = bVar8 < bVar7;
        bVar8 = bVar8 - bVar7;
        bVar9 = bVar9 - (param_3 - ((bVar2 << 7) >> 7));
        param_8 = param_8 + 1;
      }
      cVar4 = cVar4 + -1;
      bVar7 = bVar9;
      param_5 = bVar8;
      param_6 = param_6 << 1 | param_7 >> 7;
      param_7 = param_7 << 1 | bVar1;
      if (cVar4 == '\0') {
        return bVar8;
      }
    } while( true );
  }
  bVar5 = 0;
  bVar7 = param_5;
  if (param_4 != 0) {
    bVar7 = param_5 / param_4;
    bVar5 = param_5 % param_4;
  }
  cVar4 = '\x18';
  do {
    bVar1 = CARRY1(bVar7,bVar7);
    bVar7 = bVar7 * '\x02';
    bVar8 = bVar5 << 1 | param_6 >> 7;
    bVar9 = bVar5 & 0x80;
    cVar3 = C;
    if (cVar3 == '\0') {
      bVar2 = bVar8 < param_4 - ((char)bVar5 >> 7);
      bVar9 = bVar2 << 7;
      if (!bVar2) goto LAB_CODE_ac59;
    }
    else {
      C = 0;
LAB_CODE_ac59:
      bVar8 = bVar8 - (param_4 - ((char)bVar9 >> 7));
      bVar7 = bVar7 + 1;
    }
    cVar4 = cVar4 + -1;
    bVar5 = bVar8;
    param_6 = param_6 << 1 | param_7 >> 7;
    param_7 = param_7 << 1 | param_8 >> 7;
    param_8 = param_8 << 1 | bVar1;
    if (cVar4 == '\0') {
      return 0;
    }
  } while( true );
}



// ==== FUN_CODE_accc @ CODE:accc size 17 callers [CODE:441e]

byte FUN_CODE_accc(char param_1,byte param_2,byte param_3,byte param_4,char param_5,char param_6,
                  char param_7,char param_8)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  char in_PSW;
  
  bVar1 = param_8 - (in_PSW >> 7);
  bVar2 = param_7 - (((param_4 < bVar1) << 7) >> 7);
  bVar3 = param_6 - (((param_3 < bVar2) << 7) >> 7);
  return param_1 - (param_5 - (((param_2 < bVar3) << 7) >> 7)) |
         param_4 - bVar1 | param_3 - bVar2 | param_2 - bVar3;
}



// ==== FUN_CODE_ad3d @ CODE:ad3d size 12 callers [CODE:8474]

undefined1 FUN_CODE_ad3d(char param_1)

{
  return *(undefined1 *)(param_1 + '\x03');
}



// ==== FUN_CODE_ad49 @ CODE:ad49 size 12 callers [CODE:42a5,CODE:79d0]

undefined1 FUN_CODE_ad49(short param_1)

{
  return *(undefined1 *)(param_1 + 3);
}



// ==== FUN_CODE_ad55 @ CODE:ad55 size 12 callers [CODE:79d0]

undefined1 FUN_CODE_ad55(short param_1)

{
  return *(undefined1 *)(param_1 + 3);
}



// ==== FUN_CODE_ad6d @ CODE:ad6d size 12 callers [CODE:42a5,CODE:8474,CODE:a3e8]

void FUN_CODE_ad6d(undefined1 *param_1,undefined1 param_2,undefined1 param_3,undefined1 param_4,
                  undefined1 param_5)

{
  *param_1 = param_2;
  param_1[1] = param_3;
  param_1[2] = param_4;
  param_1[3] = param_5;
  return;
}



// ==== FUN_CODE_ad79 @ CODE:ad79 size 25 callers [CODE:2800]

void FUN_CODE_ad79(undefined1 *param_1)

{
  undefined1 *puVar1;
  undefined1 uStackX_0;
  undefined1 in_stack_000000ff;
  
  puVar1 = (undefined1 *)CONCAT11(uStackX_0,in_stack_000000ff);
  *param_1 = *puVar1;
  param_1['\x01'] = puVar1[1];
  param_1['\x02'] = puVar1[2];
  param_1['\x03'] = puVar1[3];
                    /* WARNING: Could not recover jumptable at 0xad91. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)(puVar1 + 4))();
  return;
}



// ==== FUN_CODE_ade7 @ CODE:ade7 size 12 callers [CODE:848e,CODE:84a1,CODE:8925]

char FUN_CODE_ade7(byte param_1,undefined2 param_2,byte param_3)

{
  return (char)((ushort)param_1 * (ushort)param_3 >> 8) +
         ((char)((ushort)param_2 >> 8) -
         ((CARRY1((byte)((ushort)param_1 * (ushort)param_3),(byte)param_2) << 7) >> 7));
}



// ==== FUN_CODE_adf3 @ CODE:adf3 size 9 callers [CODE:2800,CODE:33b9,CODE:33d6,CODE:33e9,CODE:3472,CODE:3572,CODE:4528,CODE:4532,CODE:53ea,CODE:5479,CODE:5497,CODE:54ca,CODE:54d0,CODE:55c0,CODE:5693,CODE:666b,CODE:6800,CODE:770c,CODE:83f1,CODE:87aa,CODE:8b1b,CODE:ae33]

undefined1 FUN_CODE_adf3(short param_1)

{
  return *(undefined1 *)(param_1 + 2);
}



// ==== FUN_CODE_adfc @ CODE:adfc size 23 callers [CODE:53fa,CODE:548b]

void FUN_CODE_adfc(char param_1,short param_2,byte param_3)

{
  byte bVar1;
  char cVar2;
  byte *pbVar3;
  char *pcVar4;
  
  pbVar3 = (byte *)(param_2 + 2);
  bVar1 = *pbVar3;
  *pbVar3 = bVar1 + param_3;
  cVar2 = (char)((ushort)pbVar3 >> 8);
  if ((char)pbVar3 == '\0') {
    cVar2 = cVar2 + -1;
  }
  pcVar4 = (char *)CONCAT11(cVar2,(char)pbVar3 + -1);
  *pcVar4 = *pcVar4 + (param_1 - ((CARRY1(bVar1,param_3) << 7) >> 7));
  return;
}



// ==== FUN_CODE_ae13 @ CODE:ae13 size 23 callers [CODE:54b5]

void FUN_CODE_ae13(char param_1,short param_2,byte param_3)

{
  byte bVar1;
  char cVar2;
  byte *pbVar3;
  char *pcVar4;
  
  pbVar3 = (byte *)(param_2 + 2);
  bVar1 = *pbVar3;
  *pbVar3 = bVar1 + param_3;
  cVar2 = (char)((ushort)pbVar3 >> 8);
  if ((char)pbVar3 == '\0') {
    cVar2 = cVar2 + -1;
  }
  pcVar4 = (char *)CONCAT11(cVar2,(char)pbVar3 + -1);
  *pcVar4 = *pcVar4 + (param_1 - ((CARRY1(bVar1,param_3) << 7) >> 7));
  return;
}



// ==== FUN_CODE_ae2a @ CODE:ae2a size 9 callers [CODE:2800,CODE:3572,CODE:4532,CODE:5410,CODE:55c0,CODE:666b,CODE:6800,CODE:6d78,CODE:7568,CODE:87aa,CODE:8b47,CODE:9046,CODE:9281,CODE:9c2f,CODE:9c39]

void FUN_CODE_ae2a(undefined1 *param_1,undefined1 param_2,undefined1 param_3,undefined1 param_4)

{
  *param_1 = param_4;
  param_1[1] = param_3;
  param_1[2] = param_2;
  return;
}



// ==== FUN_CODE_ae33 @ CODE:ae33 size 32 callers [CODE:3572,CODE:8b47]

void FUN_CODE_ae33(undefined1 param_1,char param_2)

{
  if (param_2 == '\x01') {
    FUN_CODE_adf3(param_1);
    return;
  }
  if (param_2 == '\0') {
    FUN_CODE_af6a(param_1);
    return;
  }
  if (param_2 == -2) {
    FUN_CODE_af73(param_1);
    return;
  }
  FUN_CODE_af7c(param_1);
  return;
}



// ==== FUN_CODE_ae53 @ CODE:ae53 size 38 callers [CODE:73f7,CODE:8000]

void FUN_CODE_ae53(char param_1)

{
  char *pcVar1;
  undefined1 uStackX_0;
  undefined1 in_stack_000000ff;
  
  for (pcVar1 = (char *)CONCAT11(uStackX_0,in_stack_000000ff);
      (*pcVar1 != '\0' || (pcVar1[1] != '\0')); pcVar1 = pcVar1 + 3) {
    if (pcVar1[2] == param_1) goto LAB_CODE_ae63;
  }
  pcVar1 = pcVar1 + 2;
LAB_CODE_ae63:
                    /* WARNING: Could not recover jumptable at 0xae6d. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)pcVar1)();
  return;
}



// ==== FUN_CODE_aeaa @ CODE:aeaa size 2 callers [CODE:6f27]

void FUN_CODE_aeaa(code *UNRECOVERED_JUMPTABLE)

{
                    /* WARNING: Could not recover jumptable at 0xaeab. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)();
  return;
}



// ==== FUN_CODE_aeac @ CODE:aeac size 36 callers [CODE:7568]

void FUN_CODE_aeac(undefined2 param_1)

{
  char cVar1;
  char cVar2;
  char cVar3;
  
  cVar2 = BANK1_R1 + (byte)param_1;
  cVar3 = BANK1_R0 + ((char)((ushort)param_1 >> 8) - ((CARRY1(BANK1_R1,(byte)param_1) << 7) >> 7));
  if (cVar3 == BANK1_R0) {
    BANK1_R1 = cVar2;
    return;
  }
  cVar1 = EA;
  if (cVar1 != '\0') {
    EA = 0;
    BANK1_R1 = cVar2;
    BANK1_R0 = cVar3;
    EA = 1;
    return;
  }
  BANK1_R1 = cVar2;
  BANK1_R0 = cVar3;
  return;
}



// ==== FUN_CODE_aefd @ CODE:aefd size 44 callers [CODE:2800,CODE:43fb,CODE:9c07]

void FUN_CODE_aefd(undefined1 *param_1,undefined1 param_2,char param_3,undefined1 param_4,
                  char param_5,char param_6)

{
  undefined1 *puVar1;
  
  if (param_6 != '\0' || param_5 != '\0') {
    if (param_6 != '\0') {
      param_5 = param_5 + '\x01';
    }
    if (param_3 != '\x01') {
      if (param_3 == '\0') {
        do {
          *param_1 = param_4;
          param_1 = param_1 + '\x01';
          param_6 = param_6 + -1;
        } while (param_6 != '\0');
      }
      else if (param_3 == -2) {
        do {
          *(undefined1 *)ZEXT12(param_1) = param_4;
          param_1 = param_1 + '\x01';
          param_6 = param_6 + -1;
        } while (param_6 != '\0');
        return;
      }
      return;
    }
    puVar1 = (undefined1 *)CONCAT11(param_2,param_1);
    do {
      do {
        *puVar1 = param_4;
        puVar1 = puVar1 + 1;
        param_6 = param_6 + -1;
      } while (param_6 != '\0');
      param_5 = param_5 + -1;
    } while (param_5 != '\0');
  }
  return;
}



// ==== FUN_CODE_af6a @ CODE:af6a size 9 callers [CODE:ae33]

undefined1 FUN_CODE_af6a(char param_1)

{
  return *(undefined1 *)(param_1 + '\x02');
}



// ==== FUN_CODE_af73 @ CODE:af73 size 9 callers [CODE:ae33]

undefined1 FUN_CODE_af73(char param_1)

{
  return *(undefined1 *)(ushort)(param_1 + 2);
}



// ==== FUN_CODE_af7c @ CODE:af7c size 12 callers [CODE:ae33]

undefined1 FUN_CODE_af7c(short param_1)

{
  return *(undefined1 *)(param_1 + 2);
}



// ==== ISR_00 @ CODE:af88 size 146 callers []

void ISR_00(void)

{
  undefined1 *puVar1;
  char cVar2;
  byte bVar3;
  char cVar4;
  byte *pbVar5;
  byte bVar6;
  byte bVar7;
  undefined1 *puVar8;
  byte *pbVar9;
  byte *pbVar10;
  
  puVar1 = (undefined1 *)0xff;
  do {
    *puVar1 = 0;
    puVar1 = puVar1 + -1;
  } while (puVar1 != (undefined1 *)0x0);
  puVar8 = (undefined1 *)0x0;
  cVar4 = -0x10;
  cVar2 = '\v';
  do {
    do {
      *puVar8 = 0;
      puVar8 = puVar8 + 1;
      cVar4 = cVar4 + -1;
    } while (cVar4 != '\0');
    cVar2 = cVar2 + -1;
  } while (cVar2 != '\0');
  SP = 0xd2;
  pbVar9 = &DAT_CODE_b022;
  while( true ) {
    bVar3 = 1;
    bVar6 = *pbVar9;
    if (bVar6 == 0) break;
    bVar7 = bVar6 & 0x3f;
    pbVar10 = pbVar9 + 1;
    if (bVar7 >> 5 != 0) {
      bVar3 = bVar6 & 0x1f;
      bVar7 = pbVar9[1];
      pbVar10 = pbVar9 + 2;
      if (bVar7 != 0) {
        bVar3 = bVar3 + 1;
      }
    }
    pbVar9 = pbVar10;
    cVar2 = CARRY1(bVar6 & 0xc0,bVar6 & 0xc0) << 7;
    if ((bVar6 & 0x40) == 0) {
      pbVar5 = (byte *)*pbVar9;
      pbVar9 = pbVar9 + 1;
      do {
        bVar3 = *pbVar9;
        pbVar9 = pbVar9 + 1;
        if (cVar2 < '\0') {
          *(byte *)ZEXT12(pbVar5) = bVar3;
        }
        else {
          *pbVar5 = bVar3;
        }
        pbVar5 = pbVar5 + '\x01';
        bVar7 = bVar7 - 1;
      } while (bVar7 != 0);
    }
    else if (cVar2 < '\0') {
      do {
        bVar3 = *pbVar9;
        pbVar9 = pbVar9 + 1;
        pbVar5 = (byte *)((bVar3 & 0x7f) >> 3 | 0x20);
        bVar6 = *(byte *)((ushort)((bVar3 & 7) + 0xc) + 0xafc9);
        if ((char)bVar3 < '\0') {
          bVar6 = bVar6 | *pbVar5;
        }
        else {
          bVar6 = ~bVar6 & *pbVar5;
        }
        *pbVar5 = bVar6;
        bVar7 = bVar7 - 1;
      } while (bVar7 != 0);
    }
    else {
      pbVar10 = *(byte **)pbVar9;
      pbVar9 = pbVar9 + 2;
      do {
        do {
          bVar6 = *pbVar9;
          pbVar9 = pbVar9 + 1;
          *pbVar10 = bVar6;
          pbVar10 = pbVar10 + 1;
          bVar7 = bVar7 - 1;
        } while (bVar7 != 0);
        bVar3 = bVar3 - 1;
      } while (bVar3 != 0);
    }
  }
  thunk_FUN_CODE_793a();
  return;
}


