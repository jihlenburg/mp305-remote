/* Address: 0002075c; name: FUN_0002075c; body bytes: 366 */

void FUN_0002075c(int *param_1,int param_2,int param_3,uint param_4,uint param_5,int param_6)

{
  uint uVar1;
  char extraout_r2;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  bool bVar9;
  undefined1 uVar10;
  undefined8 uVar11;
  undefined8 uVar12;
  longlong lVar13;
  
  uVar1 = 0;
  if (param_3 == 0 && param_4 == 0) {
    if (param_6 == 1) {
      uVar1 = ~param_5;
    }
    *param_1 = (int)&DAT_000208d4;
    param_1[1] = uVar1;
    param_1[2] = 1;
    param_1[3] = param_6;
  }
  else {
    iVar5 = (int)(((param_4 >> 0x14) - 0x3ff) * 0x4d10) >> 0x10;
    do {
      while( true ) {
        if (param_6 == 1) {
          uVar1 = -param_5;
        }
        else {
          uVar1 = (iVar5 - param_5) + 1;
        }
        uVar11 = 0x4014000000000000;
        uVar12 = 0x3ff0000000000000;
        uVar3 = uVar1;
        if ((int)uVar1 < 0) {
          uVar3 = -uVar1;
        }
        iVar4 = uVar3 * 0x100000;
        while( true ) {
          uVar6 = (undefined4)((ulonglong)uVar11 >> 0x20);
          uVar8 = (undefined4)((ulonglong)uVar12 >> 0x20);
          uVar7 = (undefined4)uVar12;
          if (uVar3 == 0) break;
          if ((uVar3 & 1) != 0) {
            uVar12 = FUN_0001083c(uVar7,uVar8,(int)uVar11,uVar6);
          }
          uVar11 = FUN_0001083c((int)uVar11,uVar6);
          uVar3 = (int)uVar3 >> 1;
        }
        uVar10 = 1;
        if ((int)uVar1 < 0) {
          uVar12 = FUN_0001083c();
          uVar12 = FUN_0001083c((int)uVar12,(int)((ulonglong)uVar12 >> 0x20),uVar7,uVar8);
        }
        else {
          uVar12 = FUN_00010920(param_3,param_4,0,iVar4 + 0x3ff00000);
          uVar12 = FUN_00010920((int)uVar12,(int)((ulonglong)uVar12 >> 0x20),uVar7,uVar8);
        }
        bVar9 = true;
        FUN_00010b18();
        if ((bool)uVar10 && !bVar9) {
          FUN_000106ee((int)uVar12,(int)((ulonglong)uVar12 >> 0x20),0,0x3fe00000);
          lVar13 = FUN_00010eb4();
        }
        else {
          lVar13 = -1;
        }
        iVar4 = 0x10;
        while( true ) {
          if ((lVar13 == 0) || (iVar4 < 0)) break;
          lVar13 = FUN_00010388((int)lVar13,(int)((ulonglong)lVar13 >> 0x20),10,0);
          *(char *)(param_2 + iVar4) = extraout_r2 + '0';
          iVar4 = iVar4 + -1;
        }
        iVar2 = 0x11 - (iVar4 + 1);
        if (param_6 != 1) break;
        if (lVar13 == 0) {
          iVar5 = (iVar2 - param_5) + -1;
          goto LAB_000208bc;
        }
        param_5 = 0x11;
        param_6 = 0;
      }
      bVar9 = true;
      if ((lVar13 == 0) && (iVar2 <= (int)param_5)) {
        if (iVar2 < (int)param_5) {
          bVar9 = false;
          iVar5 = iVar5 + -1;
        }
      }
      else {
        bVar9 = false;
        iVar5 = iVar5 + 1;
      }
    } while (!bVar9);
LAB_000208bc:
    param_1[2] = iVar2;
    param_1[3] = param_6;
    *param_1 = iVar4 + 1 + param_2;
    param_1[1] = iVar5;
  }
  return;
}

