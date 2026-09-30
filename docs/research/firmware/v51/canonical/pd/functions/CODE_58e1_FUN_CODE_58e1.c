/* Address: CODE:58e1; name: FUN_CODE_58e1; body bytes: 223 */

void FUN_CODE_58e1(undefined1 param_1)

{
  char cVar1;
  char cVar2;
  undefined1 *puVar3;
  
  FUN_CODE_a467();
  DAT_EXTMEM_04a8 = param_1;
  DAT_EXTMEM_04a9 = param_1;
  if (4 < DAT_INTMEM_cc) {
    FUN_CODE_a3c4(DAT_INTMEM_cc - 5);
    cVar2 = '\0';
    goto LAB_CODE_59bc;
  }
  if (DAT_INTMEM_b2 == '\x01') {
    if ((DAT_INTMEM_b4 == '\x01') &&
       ((((DAT_INTMEM_b5 == '3' || (DAT_INTMEM_b5 == 'C')) || (DAT_INTMEM_b5 == 'D')) ||
        (DAT_INTMEM_b5 == '2')))) {
      FUN_CODE_a217(0x41);
    }
  }
  else {
    cVar2 = (0xf < DAT_INTMEM_b2 - 1U) << 7;
    if (DAT_INTMEM_b2 - 1U == 0x10) {
      if (DAT_INTMEM_b4 != '\t') {
        if (DAT_INTMEM_b4 != '\n') goto LAB_CODE_59b7;
        FUN_CODE_a3c4();
      }
      DAT_EXTMEM_04a9 = 8;
    }
    else {
      cVar1 = 'A';
      FUN_CODE_a607();
      if (cVar2 < '\0') {
        DAT_EXTMEM_04aa = 0xb;
        DAT_EXTMEM_04ab = 0xb8;
        if (DAT_INTMEM_cd == '3') {
          DAT_EXTMEM_04a9 = 0xb;
          DAT_EXTMEM_04aa = 7;
          DAT_EXTMEM_04ab = 0xd0;
        }
        else if (DAT_INTMEM_cd == 'C') {
          DAT_EXTMEM_04a9 = 10;
        }
        else if (DAT_INTMEM_cd == 'D') {
          DAT_EXTMEM_04a9 = 0xc;
          DAT_EXTMEM_04aa = 3;
          DAT_EXTMEM_04ab = 0xe8;
        }
        else {
          if (DAT_INTMEM_cd != '2') goto LAB_CODE_59b7;
          DAT_EXTMEM_04a9 = 9;
        }
        cVar2 = FUN_CODE_a3da();
        if (cVar2 != '\0') {
          puVar3 = (undefined1 *)
                   CONCAT11(-0x47 - (((0x59U < (byte)(cVar1 * '\x02')) << 7) >> 7),
                            cVar1 * '\x02' + 0xa6);
          FUN_CODE_9d97(DAT_EXTMEM_04aa,DAT_EXTMEM_04ab,*puVar3,puVar3[1]);
          FUN_CODE_a63f(0x14);
        }
      }
    }
  }
LAB_CODE_59b7:
  cVar2 = FUN_CODE_a3da();
  if (cVar2 == '\0') {
    return;
  }
LAB_CODE_59bc:
  FUN_CODE_9dcd(cVar2);
  return;
}

