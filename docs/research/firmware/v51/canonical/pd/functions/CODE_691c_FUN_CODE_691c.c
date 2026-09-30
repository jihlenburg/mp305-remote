/* Address: CODE:691c; name: FUN_CODE_691c; body bytes: 135 */

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

