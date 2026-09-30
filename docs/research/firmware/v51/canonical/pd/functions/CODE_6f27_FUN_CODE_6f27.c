/* Address: CODE:6f27; name: FUN_CODE_6f27; body bytes: 107 */

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

