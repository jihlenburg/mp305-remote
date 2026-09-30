/* Address: 00065e34; name: FUN_00065e34; body bytes: 746 */

void FUN_00065e34(void)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined *puVar5;
  char *pcVar6;
  uint uVar7;
  uint uVar8;
  undefined1 auStack_88 [72];
  undefined4 local_40;
  undefined4 uStack_3c;
  undefined4 local_38;
  undefined4 uStack_34;
  undefined4 local_30;
  undefined4 uStack_2c;
  
  iVar1 = FUN_0004675a();
  DAT_1fffaad6 = iVar1 != DAT_1ffe0364;
  DAT_1fffaad7 = !(bool)DAT_1fffaad6;
  DAT_1ffe023c = !(bool)DAT_1fffaad6;
  FUN_0001814c();
  FUN_00055f1c();
  if (DAT_1fffaad7 == '\0') {
    FUN_000499de(DAT_1ffe0428,&DAT_00066144,0,0x402e8000);
    FUN_000499de(DAT_1ffe042c,&DAT_00066144,0,0x403e8000);
    FUN_0004e00e(DAT_1ffe0410,1);
    if ((DAT_1fffaae4 & 1) != 0) goto LAB_00065ed6;
    FUN_0004e00e(DAT_1ffe0444,1);
  }
  else {
    FUN_000499de(DAT_1ffe0428,&DAT_00066144,0x66666666,&DAT_40046666);
    FUN_000499de(DAT_1ffe042c,&DAT_00066144,0x66666666,&DAT_40146666);
    FUN_0004aa6e(DAT_1ffe0410,1);
LAB_00065ed6:
    FUN_0004aa6e(DAT_1ffe0444,1);
  }
  if (DAT_1fffaafb != '\x01') {
    uVar2 = FUN_0004037c(0xffffff);
    FUN_0004e8b2(iVar1,uVar2,0);
    uVar2 = FUN_0004037c(0x333333);
    iVar3 = DAT_1ffe0354;
    if (DAT_1fffaad6 != '\0') {
      iVar3 = DAT_1ffe0364;
    }
    FUN_0004e8b2(iVar3,uVar2,0);
    iVar3 = DAT_1ffe0354;
    if (DAT_1fffaad6 != '\0') {
      iVar3 = DAT_1ffe0364;
    }
    uVar2 = FUN_0004b9de(iVar3,0);
    FUN_0004e00e(uVar2,1);
    iVar3 = DAT_1ffe0354;
    if (DAT_1fffaad6 != '\0') {
      iVar3 = DAT_1ffe0364;
    }
    uVar2 = FUN_0004b9de(iVar3,1);
    FUN_0004e00e(uVar2,1);
    iVar3 = DAT_1ffe0354;
    if (DAT_1fffaad6 != '\0') {
      iVar3 = DAT_1ffe0364;
    }
    uVar2 = FUN_0004b9de(iVar3,2);
    FUN_0004aa6e(uVar2,1);
    uVar2 = FUN_0004b9de(iVar1,0);
    FUN_0004aa6e(uVar2,1);
    uVar2 = FUN_0004b9de(iVar1,1);
    FUN_0004aa6e(uVar2,1);
    uVar2 = FUN_0004b9de(iVar1,2);
    FUN_0004e00e(uVar2,1);
    if (DAT_1fffaad7 == '\0') {
      pcVar6 = "V-SET";
    }
    else {
      pcVar6 = "I-SET";
    }
    FUN_00049974(DAT_1ffe03dc,pcVar6);
    if (DAT_1fffaad7 == '\0') {
      uVar2 = 0x21;
    }
    else {
      uVar2 = 0x45;
    }
    FUN_0004e654(DAT_1ffe040c,uVar2);
    if (DAT_1fffaad7 == '\0') {
      uVar2 = 100;
    }
    else {
      uVar2 = 0xa8;
    }
    FUN_0004eae2(DAT_1ffe0440,uVar2);
    uStack_3c = FUN_000375f8();
    local_30 = 0x53ed9;
    uStack_2c = 0x53cf5;
    local_38 = 0;
    uStack_34 = 0x2396d;
    local_40 = DAT_1ffe03c8;
    FUN_0001046a(auStack_88,&DAT_1fffbb28,0x48);
    puVar4 = &DAT_1fffbb18;
    goto LAB_00066112;
  }
  if (DAT_1fffaad7 == '\0') {
    puVar5 = &DAT_00066178;
  }
  else {
    puVar5 = &DAT_00066174;
  }
  FUN_00049974(DAT_1ffe03dc,puVar5);
  FUN_0004aa6e(iVar1,1);
  uVar2 = DAT_1ffe0358;
  if (DAT_1fffaad7 != '\0') {
    uVar2 = DAT_1ffe0368;
  }
  FUN_0004e00e(uVar2,1);
  FUN_0004e00e(DAT_1ffe03c0,1);
  iVar1 = DAT_1ffe0354;
  if (DAT_1fffaad6 != '\0') {
    iVar1 = DAT_1ffe0364;
  }
  FUN_0004e00e(iVar1,1);
  uVar2 = DAT_1ffe0358;
  if (DAT_1fffaad6 != '\0') {
    uVar2 = DAT_1ffe0368;
  }
  FUN_0004aa6e(uVar2,1);
  if (DAT_1fffaad7 == '\0') {
    uVar2 = 0x3e;
  }
  else {
    uVar2 = 0xa5;
  }
  FUN_0004e7c2(DAT_1ffe03c0,0x7e,uVar2);
  if (DAT_1fffaad7 == '\0') {
    uVar2 = 0x29;
  }
  else {
    uVar2 = 0x56;
  }
  FUN_0004e654(DAT_1ffe040c,uVar2);
  if (DAT_1fffaad7 == '\0') {
    uVar2 = 0x54;
  }
  else {
    uVar2 = 0x81;
  }
  FUN_0004eae2(DAT_1ffe0440,uVar2);
  if (DAT_1fffaad6 == '\0') {
    if (DAT_1fffaad7 != '\0') {
      uVar7 = DAT_1fffab76 / 1000;
      uVar8 = (uint)DAT_1fffab76 % 1000;
      uVar2 = FUN_0004b9de(DAT_1ffe0368,0);
      pcVar6 = "SET : %01d.%03d A";
      goto LAB_00066012;
    }
  }
  else {
    uVar7 = DAT_1fffab74 / 100;
    uVar8 = (uint)DAT_1fffab74 % 100;
    uVar2 = FUN_0004b9de(DAT_1ffe0358,0);
    pcVar6 = "SET : %02d.%02d V";
LAB_00066012:
    FUN_000499de(uVar2,pcVar6,uVar7,uVar8);
  }
  uStack_3c = FUN_00037604();
  local_30 = 0x53ed9;
  uStack_2c = 0x53cf5;
  local_38 = 0;
  uStack_34 = 0x23969;
  local_40 = DAT_1ffe03c8;
  FUN_0001046a(auStack_88,&DAT_1fffbad0,0x48);
  puVar4 = &DAT_1fffbac0;
LAB_00066112:
  FUN_00058430(*puVar4,puVar4[1],puVar4[2],puVar4[3]);
  return;
}

