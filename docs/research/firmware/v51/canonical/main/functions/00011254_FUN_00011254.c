/* Address: 00011254; name: FUN_00011254; body bytes: 296 */

void FUN_00011254(undefined4 *param_1,byte *param_2,byte *param_3,int param_4)

{
  byte bVar1;
  ulonglong uVar2;
  int iVar3;
  uint uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  uint uVar8;
  bool bVar9;
  undefined8 uVar10;
  undefined8 uVar11;
  undefined8 uVar12;
  
  bVar1 = *param_2;
  if (bVar1 == 0xff) {
    iVar3 = 0;
  }
  else {
    iVar3 = 0;
    while( true ) {
      param_2 = param_2 + 1;
      if (*param_2 == 0xff) break;
      iVar3 = (uint)*param_2 + iVar3 * 10;
    }
    if (bVar1 == 0x2d) {
      iVar3 = -iVar3;
    }
  }
  bVar9 = false;
  bVar1 = *param_3;
  uVar2 = 0;
  if ((bVar1 == 0x2d) || (bVar1 == 0x2b)) {
    param_3 = param_3 + 1;
    bVar9 = bVar1 == 0x2d;
  }
  while( true ) {
    bVar1 = *param_3;
    if (bVar1 == 0xff) break;
    param_3 = param_3 + 1;
    uVar2 = (uVar2 & 0xffffffff) * 10 + CONCAT44((int)(uVar2 >> 0x20) * 10,(uint)bVar1);
  }
  uVar8 = param_4 + iVar3;
  if ((uVar2 == 0) || ((int)uVar8 < -400)) {
    *param_1 = 0;
    param_1[1] = 0;
  }
  else {
    uVar11 = 0x4014000000000000;
    uVar12 = 0x3ff0000000000000;
    uVar10 = FUN_00010a3a((int)uVar2);
    uVar4 = uVar8;
    if ((int)uVar8 < 0) {
      uVar4 = -uVar8;
    }
    iVar3 = uVar4 * 0x100000;
    while( true ) {
      uVar5 = (undefined4)((ulonglong)uVar11 >> 0x20);
      uVar7 = (undefined4)((ulonglong)uVar12 >> 0x20);
      uVar6 = (undefined4)uVar12;
      if (uVar4 == 0) break;
      if ((uVar4 & 1) != 0) {
        uVar12 = FUN_0001083c(uVar6,uVar7,(int)uVar11,uVar5);
      }
      uVar11 = FUN_0001083c((int)uVar11,uVar5);
      uVar4 = (int)uVar4 >> 1;
    }
    if ((int)uVar8 < 0) {
      uVar12 = FUN_00010920();
      uVar12 = FUN_00010920((int)uVar12,(int)((ulonglong)uVar12 >> 0x20),uVar6,uVar7);
    }
    else {
      uVar12 = FUN_0001083c((int)uVar10,(int)((ulonglong)uVar10 >> 0x20),0,iVar3 + 0x3ff00000);
      uVar12 = FUN_0001083c((int)uVar12,(int)((ulonglong)uVar12 >> 0x20),uVar6,uVar7);
    }
    uVar8 = (uint)((ulonglong)uVar12 >> 0x20);
    if (bVar9) {
      uVar8 = uVar8 ^ 0x80000000;
    }
    *param_1 = (int)uVar12;
    param_1[1] = uVar8;
  }
  return;
}

