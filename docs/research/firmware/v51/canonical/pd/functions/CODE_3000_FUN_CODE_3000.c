/* Address: CODE:3000; name: FUN_CODE_3000; body bytes: 477 */

char FUN_CODE_3000(char *param_1,byte *param_2,byte param_3)

{
  char cVar1;
  undefined1 uVar2;
  char cVar3;
  byte bVar4;
  char cVar5;
  undefined1 *puVar6;
  
  DAT_EXTMEM_04a8 = '\x03';
  FUN_CODE_1ef6(DAT_EXTMEM_055d,0x4a9);
  FUN_CODE_1ef6(DAT_EXTMEM_055e,0x4ab);
  DAT_EXTMEM_04ad = 0;
  DAT_EXTMEM_04ae = DAT_EXTMEM_055f;
  DAT_EXTMEM_04af = DAT_EXTMEM_0560;
  cVar3 = '\0';
  FUN_CODE_9000();
  FUN_CODE_1e48();
  if (*param_1 == '\x01') {
    FUN_CODE_a6cd();
    cVar1 = ((DAT_EXTMEM_04ac < cVar3 + 1U) << 7) >> 7;
    cVar5 = (DAT_EXTMEM_04ab < (byte)-cVar1) << 7;
    DAT_EXTMEM_04b0 = cVar3;
    if (cVar5 < '\0') {
      cVar3 = '\b';
      param_3 = 0x80;
      FUN_CODE_9a0d(DAT_EXTMEM_04ab + cVar1);
      if (cVar3 == '\b' && param_3 == 0) {
        FUN_CODE_a153();
        if (-1 < cVar5) {
          param_2 = &BANK2_R7;
          FUN_CODE_87aa(0xb1,0xff);
          FUN_CODE_a646(0x13);
        }
      }
    }
    else {
      FUN_CODE_a6d3(cVar3 + '\x01');
      FUN_CODE_a63f(0x36);
      param_2 = &DAT_INTMEM_c9;
      FUN_CODE_87aa(0xb0,0xff);
    }
  }
  else {
    cVar3 = FUN_CODE_1ec9();
    if (cVar3 == '\x02') {
      bVar4 = FUN_CODE_1e98(0x4a9);
      bVar4 = bVar4 ^ *param_2;
      if (bVar4 == 0) {
        param_2 = param_2 + -1;
        bVar4 = param_3 ^ *param_2;
      }
      if (bVar4 != 0) {
        FUN_CODE_1e39();
        FUN_CODE_8800(0x1a,3);
      }
    }
  }
  cVar3 = '\x01';
  FUN_CODE_9000();
  FUN_CODE_a356();
  if (cVar3 != '\x01') {
    FUN_CODE_9e27(1);
    FUN_CODE_a638(3,2);
    param_2 = (byte *)0x25;
    FUN_CODE_87aa(0xb1,0xff);
  }
  cVar3 = FUN_CODE_1ec9();
  if (cVar3 == '\x02') {
    bVar4 = FUN_CODE_1e98(0x4ad);
    bVar4 = bVar4 ^ *param_2;
    if (bVar4 == 0) {
      bVar4 = param_3 ^ param_2[-1];
    }
    if (bVar4 != 0) {
      FUN_CODE_1e39();
      FUN_CODE_8800(0x1a,3);
    }
  }
  if ((DAT_EXTMEM_04af == '\0') && (DAT_EXTMEM_0af4 == '\0')) {
    DAT_EXTMEM_0af4 = '\x01';
    uVar2 = 0xf;
  }
  else {
    if (((DAT_EXTMEM_04af == '\0') << 7 < '\0') || (DAT_EXTMEM_0af4 == '\0')) goto LAB_CODE_3117;
    DAT_EXTMEM_0af4 = '\0';
    uVar2 = 0x15;
  }
  FUN_CODE_9733(uVar2,0x11);
LAB_CODE_3117:
  DAT_INTMEM_99 = 0;
  DAT_INTMEM_9a = BANK0_R7;
  DAT_INTMEM_5d = BANK0_R6;
  DAT_INTMEM_5e = BANK0_R7;
  DAT_INTMEM_5f = BANK0_R6;
  DAT_INTMEM_60 = BANK0_R7;
  puVar6 = &DAT_EXTMEM_04a8;
  uVar2 = DAT_EXTMEM_04ae;
  FUN_CODE_1f10(DAT_EXTMEM_04ad);
  FUN_CODE_1d2a();
  *puVar6 = 0xb1;
  FUN_CODE_1d1f(DAT_INTMEM_6e);
  *puVar6 = uVar2;
  FUN_CODE_1d1f(DAT_INTMEM_92);
  *puVar6 = uVar2;
  FUN_CODE_1d1f(DAT_INTMEM_8c);
  *puVar6 = uVar2;
  cVar3 = '#';
  FUN_CODE_1d1f(DAT_INTMEM_23);
  *puVar6 = uVar2;
  FUN_CODE_1d1f(*(undefined1 *)(cVar3 + '\x01'));
  *puVar6 = uVar2;
  FUN_CODE_1d1f(DAT_INTMEM_89);
  *puVar6 = uVar2;
  puVar6 = &DAT_EXTMEM_070c;
  FUN_CODE_1d1f(DAT_EXTMEM_070c);
  *puVar6 = uVar2;
  cVar3 = 's';
  FUN_CODE_1d06(0x73);
  *puVar6 = uVar2;
  FUN_CODE_1d06(cVar3 + '\x01');
  *puVar6 = uVar2;
  FUN_CODE_1d06(0x95);
  *puVar6 = uVar2;
  FUN_CODE_1d06(0x2d);
  *puVar6 = uVar2;
  FUN_CODE_1d06(0x97);
  *puVar6 = uVar2;
  FUN_CODE_1d06(0x2f);
  *puVar6 = uVar2;
  FUN_CODE_1d1f(DAT_INTMEM_6c);
  *puVar6 = uVar2;
  puVar6 = &DAT_EXTMEM_0707;
  FUN_CODE_1d1f(DAT_EXTMEM_0707);
  *puVar6 = uVar2;
  puVar6 = &DAT_EXTMEM_03f0;
  FUN_CODE_1d1f(DAT_EXTMEM_03f0);
  *puVar6 = uVar2;
  puVar6 = &DAT_EXTMEM_0442;
  FUN_CODE_1d0a(DAT_EXTMEM_0442,DAT_EXTMEM_0441);
  *puVar6 = uVar2;
  return DAT_EXTMEM_04a8 + -2;
}

