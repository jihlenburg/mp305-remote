/* Address: 0004f7c4; name: FUN_0004f7c4; body bytes: 452 */

/* Recovered from stored Thumb pointer at 0007ae00; callback identification is inferred until
   reviewed. */

void FUN_0004f7c4(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined4 uVar8;
  int iVar9;
  undefined8 uVar10;
  undefined1 auStack_78 [96];
  undefined4 uStack_18;
  
  uStack_18 = param_3;
  iVar1 = FUN_0004b9b2(&DAT_0007adf4);
  if (iVar1 != 1) {
    return;
  }
  iVar1 = FUN_00046688(param_2);
  uVar10 = FUN_00046698(param_2);
  uVar8 = (undefined4)((ulonglong)uVar10 >> 0x20);
  iVar9 = (int)uVar10;
  if (iVar1 == 0x31) {
    puVar2 = (undefined4 *)FUN_0004673a(param_2);
    uVar8 = FUN_00037b88(iVar9);
    *puVar2 = uVar8;
    return;
  }
  if (iVar1 == 0x2f) {
    iVar1 = FUN_0003759c();
    if (iVar1 != 0) {
      FUN_0004e5a6(iVar1,0x2f,0);
    }
    FUN_0004deac(iVar9);
    iVar1 = 0;
  }
  else if (iVar1 == 0x2e) {
    iVar1 = 0;
  }
  else {
    if (iVar1 == 1) {
      if (*(uint *)(iVar9 + 0x2c) < 2) {
        return;
      }
      *(uint *)(iVar9 + 0x3c) = *(uint *)(iVar9 + 0x3c) & 0xfffffffb;
      uVar8 = FUN_0003759c(iVar9);
      FUN_0003c97c(uVar8,0x5e7b9,uStack_18,param_4);
      return;
    }
    if (iVar1 == 2) {
      if (*(uint *)(iVar9 + 0x2c) < 2) {
        return;
      }
      uVar8 = FUN_00047eec();
      FUN_000482e8(uVar8,&uStack_18);
      FUN_000643e4(iVar9,&uStack_18);
      if (param_4 == 0) {
        return;
      }
      uVar8 = FUN_0003759c(iVar9);
      iVar1 = FUN_0004cd7e();
      FUN_0004eb3a(uVar8,param_4 + iVar1);
      *(uint *)(iVar9 + 0x3c) = *(uint *)(iVar9 + 0x3c) | 4;
      return;
    }
    if ((iVar1 == 8) || (iVar1 == 3)) {
      if (*(uint *)(iVar9 + 0x2c) < 2) {
        return;
      }
      FUN_0005ae30(iVar9,uVar8,uStack_18,param_4);
      return;
    }
    if (iVar1 == 0x10) {
      uVar8 = FUN_0004bbe2();
      FUN_00047eec();
      iVar1 = FUN_000482e0();
      if ((iVar1 != 4) || (iVar1 = FUN_000472d4(uVar8), iVar1 != 0)) {
        *(undefined4 *)(iVar9 + 0x34) = *(undefined4 *)(iVar9 + 0x30);
        return;
      }
    }
    else if (iVar1 != 0x11) {
      if (iVar1 == 0xe) {
        if (*(uint *)(iVar9 + 0x2c) < 2) {
          return;
        }
        iVar1 = FUN_00046700(param_2);
        if ((iVar1 == 0x13) || (iVar1 == 0x12)) {
          if (*(uint *)(iVar9 + 0x2c) <= *(int *)(iVar9 + 0x30) + 1U) {
            return;
          }
          iVar1 = *(int *)(iVar9 + 0x30) + 1;
          uVar8 = *(undefined4 *)(iVar9 + 0x34);
        }
        else {
          if ((iVar1 != 0x14) && (iVar1 != 0x11)) {
            return;
          }
          if (*(int *)(iVar9 + 0x30) == 0) {
            return;
          }
          iVar1 = *(int *)(iVar9 + 0x30) + -1;
          uVar8 = *(undefined4 *)(iVar9 + 0x34);
        }
      }
      else {
        if (iVar1 != 0xf) {
          if (iVar1 == 0x18) {
            uVar10 = FUN_0003759c();
            FUN_0004de6c((int)uVar10,(int)((ulonglong)uVar10 >> 0x20),uStack_18,param_4);
            return;
          }
          if ((iVar1 != 0x1a) && (iVar1 != 0x1d)) {
            return;
          }
          FUN_0002da78(param_2,uVar8,uStack_18,param_4);
          return;
        }
        if (*(uint *)(iVar9 + 0x2c) < 2) {
          return;
        }
        iVar1 = FUN_0004673e(param_2);
        iVar1 = iVar1 + *(int *)(iVar9 + 0x30);
        iVar7 = *(int *)(iVar9 + 0x2c) + -1;
        iVar3 = iVar7;
        if (iVar1 < iVar7) {
          iVar3 = iVar1;
        }
        if (iVar3 < 0) {
          iVar1 = 0;
        }
        else if (iVar7 <= iVar1) {
          iVar1 = *(int *)(iVar9 + 0x2c) + -1;
        }
        if (*(int *)(iVar9 + 0x30) == iVar1) {
          return;
        }
        uVar8 = *(undefined4 *)(iVar9 + 0x34);
      }
      FUN_0004fb30(iVar9,iVar1,1);
      *(undefined4 *)(iVar9 + 0x34) = uVar8;
      return;
    }
    if (*(int *)(iVar9 + 0x30) == *(int *)(iVar9 + 0x34)) {
      return;
    }
    iVar1 = 1;
    *(int *)(iVar9 + 0x30) = *(int *)(iVar9 + 0x34);
  }
  iVar3 = FUN_0003759c(iVar9,iVar1,uStack_18,param_4);
  if (iVar3 != 0) {
    uVar8 = FUN_000491e8();
    iVar7 = FUN_0004b108(iVar3,0,uVar8);
    iVar6 = 0;
    if (iVar7 != 1) {
      if (iVar7 == 2) {
        iVar7 = FUN_0004bb1a(iVar9,0);
        iVar6 = FUN_0004ccf8(iVar3);
        iVar6 = (iVar7 - iVar6) / 2;
      }
      else if (iVar7 == 3) {
        iVar6 = FUN_0004bb1a(iVar9,0);
        iVar7 = FUN_0004ccf8(iVar3);
        iVar6 = iVar6 - iVar7;
      }
    }
    FUN_0004eb0e(iVar3,iVar6);
    uVar8 = FUN_0004cb3a(iVar9,0);
    iVar7 = FUN_0004cb82(iVar9,0);
    iVar6 = FUN_00046bd6(uVar8);
    iVar4 = FUN_0004baf8(iVar9);
    iVar5 = FUN_0004c924(iVar9,0,100);
    if ((iVar1 == 0) || (iVar5 == 0)) {
      FUN_0003a6ba(iVar9);
    }
    iVar9 = (iVar4 / 2 - iVar6 / 2) - *(int *)(iVar9 + 0x30) * (iVar6 + iVar7);
    if ((iVar1 == 0) || (iVar5 == 0)) {
      FUN_0003c97c(iVar3,0x5e7b9);
      FUN_0004eb3a(iVar3,iVar9);
      return;
    }
    FUN_0003c9f8(auStack_78);
    FUN_0003cb2a(auStack_78,iVar3);
    FUN_0003cafa(auStack_78,0x5e7b9);
    uVar8 = FUN_0004cd44(iVar3);
    FUN_0003cb1e(auStack_78,uVar8,iVar9);
    FUN_0003caea(auStack_78,iVar5);
    FUN_0003cadc(auStack_78,0x5e267);
    FUN_0003cafe(auStack_78,0x3ca83);
    FUN_0003cb6c(auStack_78);
  }
  return;
}

