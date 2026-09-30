/* Address: CODE:66fd; name: FUN_CODE_66fd; body bytes: 145 */

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

