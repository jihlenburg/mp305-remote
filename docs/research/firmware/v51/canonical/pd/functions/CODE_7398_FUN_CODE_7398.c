/* Address: CODE:7398; name: FUN_CODE_7398; body bytes: 95 */

void FUN_CODE_7398(char param_1,char param_2)

{
  byte bVar1;
  
  DAT_EXTMEM_04a4 = param_2;
  FUN_CODE_a34b();
  if (DAT_EXTMEM_04a4 == '\x02') {
    FUN_CODE_33d6();
    FUN_CODE_33e2(param_1 + ']');
    bVar1 = FUN_CODE_3437();
    FUN_CODE_a99c(bVar1 | 0x80);
    if (DAT_INTMEM_b3 == '\x01') {
      DAT_EXTMEM_205a = 0;
      return;
    }
  }
  else {
    if (DAT_EXTMEM_04a4 == '\x03') {
      if (DAT_INTMEM_b3 != '\x01') {
        return;
      }
      DAT_EXTMEM_205a = 1;
      FUN_CODE_33d6();
      bVar1 = FUN_CODE_33e2(param_1 + ']');
      bVar1 = bVar1 | 0x80;
    }
    else {
      if (DAT_EXTMEM_04a4 != '\x01') {
        return;
      }
      FUN_CODE_33d6();
      FUN_CODE_33e2(param_1 + ']');
      bVar1 = FUN_CODE_3437();
      bVar1 = bVar1 | 0x40;
    }
    FUN_CODE_a99c(bVar1);
  }
  return;
}

