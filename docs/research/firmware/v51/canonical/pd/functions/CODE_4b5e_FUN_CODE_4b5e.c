/* Address: CODE:4b5e; name: FUN_CODE_4b5e; body bytes: 178 */

void FUN_CODE_4b5e(byte param_1,byte param_2)

{
  byte bVar1;
  char cVar2;
  
  if (DAT_INTMEM_b2 == '\x05') {
    bVar1 = FUN_CODE_ae53(DAT_INTMEM_b4);
    cVar2 = (bVar1 | param_2) + param_1;
  }
  else {
    cVar2 = (10 < DAT_INTMEM_b2 - 5U) << 7;
    if (DAT_INTMEM_b2 == '\x10') {
      if (DAT_INTMEM_b4 == 'C') {
        _1_3 = 0;
LAB_CODE_4c6e:
        FUN_CODE_86da();
        return;
      }
      if (DAT_INTMEM_b4 == 'D') {
        if (DAT_INTMEM_cc == '\x04') {
          _1_3 = 1;
          goto LAB_CODE_4c6e;
        }
      }
      else if (DAT_INTMEM_b4 == 'G') {
        FUN_CODE_a32a(0xc);
      }
      else if (DAT_INTMEM_b4 == 'F') {
        FUN_CODE_a64d(10);
        return;
      }
      return;
    }
    if (DAT_INTMEM_b2 != '\x11') {
      return;
    }
    bVar1 = FUN_CODE_ae53(DAT_INTMEM_b4);
    cVar2 = (bVar1 | param_1) - (param_1 - (cVar2 >> 7));
  }
  FUN_CODE_87aa(cVar2,0x5f,0xb4,0xff);
  FUN_CODE_7d6d(0x4ac,0xbe,0xb4,0xff);
  FUN_CODE_87aa();
  return;
}

