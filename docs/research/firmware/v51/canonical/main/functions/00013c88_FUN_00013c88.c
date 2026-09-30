/* Address: 00013c88; name: FUN_00013c88; body bytes: 102 */

void FUN_00013c88(int param_1,undefined4 param_2,int param_3)

{
  longlong lVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  undefined8 uVar5;
  
  if (param_3 != 3) {
    return;
  }
  uVar2 = *(uint *)(param_1 + 1);
  uVar4 = FUN_0001c358();
  uVar3 = DAT_1ffe01bc;
  uVar5 = CONCAT44(DAT_1ffe0164,DAT_1ffe0160);
  if (DAT_1ffe01bc != 0) {
    uVar5 = CONCAT44(DAT_1ffe0164,DAT_1ffe0160);
    if (((DAT_1fff9444 != 0) && (uVar5 = CONCAT44(DAT_1ffe0164,DAT_1ffe0160), DAT_1ffe01bc < uVar4))
       && (uVar5 = CONCAT44(DAT_1ffe0164,DAT_1ffe0160), DAT_1fff9444 < uVar2)) {
      lVar1 = (ulonglong)(uVar2 - DAT_1fff9444) * 100000;
      uVar5 = FUN_00010388((int)lVar1,(int)((ulonglong)lVar1 >> 0x20),uVar4 - DAT_1ffe01bc,0);
    }
    if (uVar3 < uVar4) goto LAB_00013ce0;
  }
  DAT_1ffe01bc = uVar4;
LAB_00013ce0:
  if ((DAT_1fff9444 == 0) || (uVar2 <= DAT_1fff9444)) {
    DAT_1fff9444 = uVar2;
  }
  DAT_1ffe0164 = (undefined4)((ulonglong)uVar5 >> 0x20);
  DAT_1ffe0160 = (undefined4)uVar5;
  return;
}

