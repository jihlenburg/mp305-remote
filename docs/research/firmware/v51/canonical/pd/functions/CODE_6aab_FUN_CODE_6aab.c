/* Address: CODE:6aab; name: FUN_CODE_6aab; body bytes: 125 */

void FUN_CODE_6aab(void)

{
  undefined1 uVar1;
  undefined1 uVar2;
  short sVar3;
  
  FUN_CODE_95f2();
  FUN_CODE_789f();
  FUN_CODE_8fcd();
  FUN_CODE_9c07();
  FUN_CODE_8b9d();
  FUN_CODE_8ff0();
  thunk_FUN_CODE_996c();
  FUN_CODE_a569();
  FUN_CODE_a7bc();
  FUN_CODE_6ffc(2);
  DAT_INTMEM_99 = DAT_EXTMEM_0af8;
  DAT_INTMEM_9a = DAT_EXTMEM_0af9;
  FUN_CODE_a9e2(0,10,DAT_EXTMEM_0af8 - (((0xfa < DAT_EXTMEM_0af9) << 7) >> 7),DAT_EXTMEM_0af9 + 5);
  DAT_INTMEM_9b = BANK0_R7;
  FUN_CODE_9e59(2,7);
  FUN_CODE_7d8b(0x4a4);
  uVar1 = 0;
  uVar2 = DAT_EXTMEM_0af4;
  FUN_CODE_7d83(0x4a8);
  sVar3 = 0x4d6;
  FUN_CODE_7d8b(0xb9,0xb3);
  *(undefined1 *)(sVar3 + 1) = uVar1;
  *(undefined1 *)(sVar3 + 2) = uVar2;
  *(char *)(sVar3 + 3) = DAT_INTMEM_99;
  *(byte *)(sVar3 + 4) = DAT_INTMEM_9a;
  FUN_CODE_87aa();
  _2_1 = 0;
  return;
}

