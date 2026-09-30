/* Address: CODE:42a5; name: FUN_CODE_42a5; body bytes: 296 */

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
        FUN_CODE_3555(param_1 + 0x34);
                    /* WARNING: Subroutine does not return */
        FUN_CODE_ad49();
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

