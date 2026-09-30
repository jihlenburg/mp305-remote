/* Address: CODE:4a3f; name: FUN_CODE_4a3f; body bytes: 251 */

void FUN_CODE_4a3f(char param_1)

{
  byte bVar1;
  undefined1 uVar2;
  char cVar3;
  char *pcVar4;
  
  _1_5 = 1;
  FUN_CODE_4b3a(3);
  FUN_CODE_1dd3(0x6d);
  FUN_CODE_1f28(0x6d);
  FUN_CODE_4b3a(4);
  FUN_CODE_1dd3(0x91);
  FUN_CODE_1f28(0x91);
  FUN_CODE_4b4c(5);
  FUN_CODE_1dd3(0x8b);
  FUN_CODE_1f28(0x8b);
  bVar1 = 6;
  FUN_CODE_4b4c();
  cVar3 = DAT_EXTMEM_03f0 + bVar1;
  pcVar4 = &DAT_EXTMEM_03ef;
  FUN_CODE_1ddb(DAT_EXTMEM_03ef + (param_1 - ((CARRY1(DAT_EXTMEM_03f0,bVar1) << 7) >> 7)));
  *pcVar4 = param_1;
  pcVar4[1] = cVar3;
  _1_5 = 1;
  uVar2 = 7;
  FUN_CODE_94ae();
  FUN_CODE_79d0(3,0x33,0x1f,0xea);
  DAT_EXTMEM_0af8 = DAT_INTMEM_99;
  DAT_EXTMEM_0af9 = DAT_INTMEM_9a;
  DAT_EXTMEM_0441 = param_1;
  DAT_EXTMEM_0442 = uVar2;
  FUN_CODE_a9e2(0,10,DAT_INTMEM_99 - (((0xfa < DAT_INTMEM_9a) << 7) >> 7),DAT_INTMEM_9a + 5);
  DAT_INTMEM_9b = BANK0_R7;
  DAT_EXTMEM_04a4 = 0;
  DAT_EXTMEM_04a5 = DAT_INTMEM_23;
  uVar2 = 0;
  FUN_CODE_9afd();
  DAT_EXTMEM_04a6 = 0;
  DAT_EXTMEM_04d6 = DAT_EXTMEM_04a4;
  DAT_EXTMEM_04d7 = DAT_EXTMEM_04a5;
  DAT_EXTMEM_04d8 = 0;
  DAT_EXTMEM_04a7 = uVar2;
  DAT_EXTMEM_04d9 = uVar2;
  FUN_CODE_1d8d(0x73,0xc4,0xb1,0xff);
  DAT_EXTMEM_04dc = DAT_EXTMEM_0443;
  DAT_EXTMEM_04dd = DAT_EXTMEM_0444;
  FUN_CODE_1d8d(0x95);
  FUN_CODE_1d8d(0x2d);
  FUN_CODE_1d8d(0x5d);
  FUN_CODE_1d8d(0x75);
  FUN_CODE_1d8d(0x5f);
  FUN_CODE_1d8d(0x99);
  FUN_CODE_1d8d(0x8b);
  FUN_CODE_1d8d(0x6d);
  FUN_CODE_1d8d(0x91);
  FUN_CODE_87aa();
  return;
}

