/* Address: 00019dd4; name: FUN_00019dd4; body bytes: 52 */

void FUN_00019dd4(int param_1,int param_2)

{
  longlong lVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 unaff_r4;
  short sVar4;
  undefined4 unaff_r5;
  undefined4 unaff_r6;
  undefined4 unaff_lr;
  undefined8 uVar5;
  
  if (DAT_1fffaa2f == '\0') {
    DAT_1fffaa2f = '\x01';
    FUN_00018c74(1);
    FUN_00019e44();
  }
  FUN_0001f548(param_1 * 10);
  param_2 = param_2 * 100;
  if (param_2 < 0) {
    param_2 = 0;
  }
  else if (550000 < param_2) {
    param_2 = 550000;
  }
  uVar2 = param_2 * -6 + 3300000;
  lVar1 = (ulonglong)uVar2 * 0xfffff;
  uVar5 = FUN_000103ea((int)lVar1,((int)uVar2 >> 0x1f) * 0xfffff + (int)((ulonglong)lVar1 >> 0x20),
                       0xce4,0,unaff_r4,unaff_r5,unaff_r6,unaff_lr);
  uVar2 = FUN_000103ea((int)uVar5,(int)((ulonglong)uVar5 >> 0x20),1000,0);
  if (param_2 < 0x1f41) {
    if (param_2 < 5000) {
      DAT_1ffe01dc = '\0';
    }
    else if (DAT_1ffe01dc != '\0') goto LAB_0001f4b6;
    sVar4 = (short)(uVar2 >> 8);
    uVar2 = 0x3ff;
    uVar3 = 0;
  }
  else {
    DAT_1ffe01dc = '\x01';
LAB_0001f4b6:
    sVar4 = (short)(uVar2 >> 9) * 2;
    uVar2 = uVar2 & 0x1ff;
    uVar3 = 1;
  }
  FUN_0001416c(&DAT_40041000,1,uVar3);
  FUN_0001ce68(sVar4);
  FUN_0001ce98(uVar2);
  DAT_1fffa95c = param_2;
  return;
}

