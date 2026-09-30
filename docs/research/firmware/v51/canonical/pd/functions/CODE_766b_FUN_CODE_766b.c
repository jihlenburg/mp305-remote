/* Address: CODE:766b; name: FUN_CODE_766b; body bytes: 84 */

void FUN_CODE_766b(byte param_1,byte param_2)

{
  char cVar1;
  byte bVar2;
  
  DAT_EXTMEM_04b2 = param_1;
  DAT_EXTMEM_04b3 = param_2;
  FUN_CODE_a521();
  if (param_2 == 4) {
    FUN_CODE_1ec0();
    cVar1 = '\v';
    FUN_CODE_a9d0(0,0xb);
    FUN_CODE_a9e2(cVar1 + -1);
    DAT_EXTMEM_04b2 = param_1;
    DAT_EXTMEM_04b3 = param_2;
  }
  bVar2 = FUN_CODE_1ec0();
  if ((param_1 < 0xeU - (((bVar2 < 0x11) << 7) >> 7)) << 7 < '\0') {
    bVar2 = 1 - (((param_2 < 0x2c) << 7) >> 7);
    cVar1 = param_1 - bVar2;
    if (param_1 < bVar2) {
      DAT_EXTMEM_04b2 = 1;
      cVar1 = ',';
      DAT_EXTMEM_04b3 = 0x2c;
    }
  }
  else {
    DAT_EXTMEM_04b2 = 0xe;
    cVar1 = '\x10';
    DAT_EXTMEM_04b3 = 0x10;
  }
  FUN_CODE_1ec0(cVar1);
  FUN_CODE_9261();
  return;
}

