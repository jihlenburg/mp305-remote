/* Address: CODE:10b6; name: FUN_CODE_10b6; body bytes: 1199 */

void FUN_CODE_10b6(char param_1,char param_2)

{
  char cVar1;
  char cVar2;
  undefined1 *puVar3;
  
  if (param_1 == param_2) {
    DAT_EXTMEM_04a4 = param_2;
    DAT_EXTMEM_04a5 = param_1;
    return;
  }
  DAT_EXTMEM_04a4 = param_2;
  DAT_EXTMEM_04a5 = param_1;
  FUN_CODE_8776(0,param_1,0,param_2);
  puVar3 = (undefined1 *)0x4a5;
  cVar1 = FUN_CODE_ae53(DAT_EXTMEM_04a5);
  cVar2 = '\0';
  FUN_CODE_9f19(cVar1 << 7);
  FUN_CODE_4153();
  if (cVar2 < '\0') {
    cVar2 = (DAT_INTMEM_b3 == '\0') << 7;
    if ((DAT_INTMEM_b3 == '\x01') && ((DAT_INTMEM_43 >> 2 & 1) != 0)) {
      FUN_CODE_1703(0x62);
      *puVar3 = 0x73;
      goto LAB_CODE_16e4;
    }
    FUN_CODE_8229();
  }
  else {
    FUN_CODE_8229();
    DAT_EXTMEM_04a5 = '\x04';
    FUN_CODE_8229();
  }
  FUN_CODE_a721();
  FUN_CODE_47a3();
  FUN_CODE_a763();
  FUN_CODE_a153();
  if (cVar2 < '\0') {
LAB_CODE_1416:
    FUN_CODE_47a3();
    FUN_CODE_984b();
  }
  else {
    cVar1 = 'P';
    FUN_CODE_a6a1();
    if ((cVar2 < '\0') && (FUN_CODE_9696(), cVar1 == '\x01')) goto LAB_CODE_1416;
  }
  FUN_CODE_a03c(0x2d);
LAB_CODE_16e4:
  FUN_CODE_a5c5(DAT_EXTMEM_04a5);
  return;
}

