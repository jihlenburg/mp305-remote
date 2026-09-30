/* Address: 00043a86; name: FUN_00043a86; body bytes: 280 */

void FUN_00043a86(int *param_1)

{
  byte bVar1;
  undefined1 uVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  
  iVar6 = param_1[1];
  iVar7 = param_1[2];
  bVar1 = *(byte *)((int)param_1 + 0x1b);
  iVar9 = param_1[4];
  iVar3 = param_1[5];
  iVar11 = param_1[3];
  iVar4 = param_1[6];
  if (iVar9 == 0) {
    if (bVar1 < 0xfd) {
      uVar5 = FUN_00040396(iVar4);
      iVar4 = *param_1;
      for (iVar3 = 0; iVar3 < iVar7; iVar3 = iVar3 + 1) {
        for (iVar9 = 0; iVar9 < iVar6; iVar9 = iVar9 + 1) {
          FUN_00040280(uVar5,iVar4 + iVar9,bVar1);
        }
        iVar4 = iVar4 + iVar11;
      }
    }
    else {
      uVar2 = FUN_00040396(iVar4);
      iVar3 = *param_1;
      for (iVar4 = 0; iVar4 < iVar7; iVar4 = iVar4 + 1) {
        for (iVar9 = 0; iVar9 < iVar6 + -0x10; iVar9 = iVar9 + 0x10) {
          *(undefined1 *)(iVar3 + iVar9) = uVar2;
          iVar10 = iVar3 + iVar9;
          *(undefined1 *)(iVar10 + 1) = uVar2;
          *(undefined1 *)(iVar10 + 2) = uVar2;
          *(undefined1 *)(iVar10 + 3) = uVar2;
          *(undefined1 *)(iVar10 + 4) = uVar2;
          *(undefined1 *)(iVar10 + 5) = uVar2;
          *(undefined1 *)(iVar10 + 6) = uVar2;
          *(undefined1 *)(iVar10 + 7) = uVar2;
          *(undefined1 *)(iVar10 + 8) = uVar2;
          *(undefined1 *)(iVar10 + 9) = uVar2;
          *(undefined1 *)(iVar10 + 10) = uVar2;
          *(undefined1 *)(iVar10 + 0xb) = uVar2;
          *(undefined1 *)(iVar10 + 0xc) = uVar2;
          *(undefined1 *)(iVar10 + 0xd) = uVar2;
          *(undefined1 *)(iVar10 + 0xe) = uVar2;
          *(undefined1 *)(iVar10 + 0xf) = uVar2;
        }
        for (; iVar9 < iVar6; iVar9 = iVar9 + 1) {
          *(undefined1 *)(iVar3 + iVar9) = uVar2;
        }
        iVar3 = iVar3 + iVar11;
      }
    }
  }
  else if (bVar1 < 0xfd) {
    uVar5 = FUN_00040396(iVar4);
    iVar10 = *param_1;
    for (iVar4 = 0; iVar4 < iVar7; iVar4 = iVar4 + 1) {
      for (iVar8 = 0; iVar8 < iVar6; iVar8 = iVar8 + 1) {
        FUN_00040280(uVar5,iVar10 + iVar8,
                     (uint)((int)(short)(ushort)*(byte *)(iVar9 + iVar8) * (int)(short)(ushort)bVar1
                           ) >> 8);
      }
      iVar10 = iVar10 + iVar11;
      iVar9 = iVar9 + iVar3;
    }
  }
  else {
    uVar5 = FUN_00040396(iVar4);
    iVar10 = *param_1;
    for (iVar4 = 0; iVar4 < iVar7; iVar4 = iVar4 + 1) {
      for (iVar8 = 0; iVar8 < iVar6; iVar8 = iVar8 + 1) {
        FUN_00040280(uVar5,iVar10 + iVar8,*(undefined1 *)(iVar9 + iVar8));
      }
      iVar10 = iVar10 + iVar11;
      iVar9 = iVar9 + iVar3;
    }
  }
  return;
}

