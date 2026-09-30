/* Address: CODE:6406; name: FUN_CODE_6406; body bytes: 155 */

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

