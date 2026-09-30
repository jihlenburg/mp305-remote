/* Address: 00014080; name: FUN_00014080; body bytes: 92 */

void FUN_00014080(void)

{
  longlong lVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  short sVar8;
  undefined8 uVar9;
  
  iVar5 = DAT_1fffa954 * 100;
  if (iVar5 < 0x1e) {
    iVar5 = 0x1e;
  }
  iVar7 = (DAT_1fffa968 + 5) / 10;
  iVar2 = iVar5 - iVar7;
  iVar3 = iVar2;
  if (iVar2 < 1) {
    iVar3 = -iVar2;
  }
  if (iVar3 < 0x2e) {
    return;
  }
  iVar3 = DAT_1fffa95c + ((int)(iVar2 + ((uint)(iVar2 >> 0x1f) >> 0x1d)) >> 3);
  if (iVar7 < iVar5) {
    iVar2 = iVar5 + 20000;
    if (iVar5 + 20000 < iVar3) {
LAB_000140d0:
      iVar3 = iVar2;
    }
  }
  else {
    iVar2 = iVar5 + -20000;
    if (iVar3 < iVar5 + -20000) goto LAB_000140d0;
  }
  if (iVar3 < 0) {
    iVar3 = 0;
  }
  else if (550000 < iVar3) {
    iVar3 = 550000;
  }
  uVar4 = iVar3 * -6 + 3300000;
  lVar1 = (ulonglong)uVar4 * 0xfffff;
  uVar9 = FUN_000103ea((int)lVar1,((int)uVar4 >> 0x1f) * 0xfffff + (int)((ulonglong)lVar1 >> 0x20),
                       0xce4,0);
  uVar4 = FUN_000103ea((int)uVar9,(int)((ulonglong)uVar9 >> 0x20),1000,0);
  if (iVar3 < 0x1f41) {
    if (iVar3 < 5000) {
      DAT_1ffe01dc = '\0';
    }
    else if (DAT_1ffe01dc != '\0') goto LAB_0001f4b6;
    sVar8 = (short)(uVar4 >> 8);
    uVar4 = 0x3ff;
    uVar6 = 0;
  }
  else {
    DAT_1ffe01dc = '\x01';
LAB_0001f4b6:
    sVar8 = (short)(uVar4 >> 9) * 2;
    uVar4 = uVar4 & 0x1ff;
    uVar6 = 1;
  }
  FUN_0001416c(&DAT_40041000,1,uVar6);
  FUN_0001ce68(sVar8);
  FUN_0001ce98(uVar4);
  DAT_1fffa95c = iVar3;
  return;
}

