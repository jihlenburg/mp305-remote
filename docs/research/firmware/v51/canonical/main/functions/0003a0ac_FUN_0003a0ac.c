/* Address: 0003a0ac; name: FUN_0003a0ac; body bytes: 612 */

void FUN_0003a0ac(int param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  
  DAT_2003a474 = *(int *)(param_1 + 0x68);
  if ((int)((uint)*(byte *)(param_1 + 10) << 0x1c) < 0) {
    return;
  }
  uVar7 = *(undefined4 *)(DAT_2003a470 + 0x1c);
  if (((DAT_2003a474 == 0) ||
      ((*(int *)(param_1 + 0x70) == 0 && (iVar1 = FUN_0004cd84(DAT_2003a474,0x2000), iVar1 == 0))))
     && (DAT_2003a474 = FUN_00058760(uVar7,param_1 + 0x30), *(int *)(param_1 + 0x70) != 0)) {
    if (*(int *)(param_1 + 0xc0) != 0) {
      FUN_0003c97c(param_1,0x3a671);
      *(undefined4 *)(param_1 + 0xc0) = 0;
    }
    FUN_000485a4(param_1);
    iVar1 = FUN_0003a5c8(param_1);
    if (iVar1 != 0) {
      return;
    }
  }
  if (DAT_2003a474 != *(int *)(param_1 + 0x68)) {
    *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(param_1 + 0x30);
    *(undefined4 *)(param_1 + 0x3c) = *(undefined4 *)(param_1 + 0x34);
    iVar1 = *(int *)(param_1 + 0x78);
    if ((iVar1 != 0) && (iVar1 != DAT_2003a474)) {
      FUN_0004e5a6(iVar1,0x16,param_1);
      iVar1 = FUN_0003a5c8(param_1);
      if (iVar1 != 0) {
        return;
      }
      FUN_0004883e(param_1,0x16,*(undefined4 *)(param_1 + 0x78));
      iVar1 = FUN_0003a5c8(param_1);
      if (iVar1 != 0) {
        return;
      }
      *(int *)(param_1 + 0x78) = DAT_2003a474;
    }
    if (*(int *)(param_1 + 0x68) != 0) {
      FUN_0004e5a6(*(int *)(param_1 + 0x68),3,DAT_2003a470);
      iVar1 = FUN_0003a5c8(param_1);
      if (iVar1 != 0) {
        return;
      }
    }
    *(int *)(param_1 + 0x68) = DAT_2003a474;
    *(int *)(param_1 + 0x6c) = DAT_2003a474;
    if (DAT_2003a474 != 0) {
      uVar7 = FUN_00052708();
      *(undefined4 *)(param_1 + 0xc) = uVar7;
      *(byte *)(param_1 + 10) = *(byte *)(param_1 + 10) & 0xfe;
      *(undefined4 *)(param_1 + 0x50) = 0;
      *(undefined4 *)(param_1 + 0x54) = 0;
      *(undefined4 *)(param_1 + 0x70) = 0;
      *(undefined1 *)(param_1 + 0x98) = 0;
      *(undefined4 *)(param_1 + 0x8c) = 0;
      *(undefined4 *)(param_1 + 0x90) = 0;
      *(byte *)(param_1 + 0x99) = *(byte *)(param_1 + 0x99) & 0xfc;
      *(undefined4 *)(param_1 + 0x48) = 0;
      *(undefined4 *)(param_1 + 0x4c) = 0;
      iVar1 = FUN_0004cd9c(DAT_2003a474,0x80);
      if (iVar1 != 1) {
        if ((*(int *)(param_1 + 0x78) != DAT_2003a474) &&
           (iVar1 = FUN_0005e710(0x15,DAT_2003a470), iVar1 == 0)) {
          return;
        }
        iVar1 = FUN_0005e710(1,DAT_2003a470);
        if (iVar1 == 0) {
          return;
        }
      }
      if ((int)((uint)*(byte *)(DAT_2003a470 + 10) << 0x1c) < 0) {
        return;
      }
      FUN_000398a4();
      iVar1 = FUN_0003a5c8(param_1);
      if (iVar1 != 0) {
        return;
      }
    }
  }
  iVar1 = *(int *)(param_1 + 0x30) - *(int *)(param_1 + 0x38);
  *(int *)(param_1 + 0x48) = iVar1;
  iVar2 = *(int *)(param_1 + 0x34) - *(int *)(param_1 + 0x3c);
  *(int *)(param_1 + 0x4c) = iVar2;
  iVar6 = (*(int *)(param_1 + 0x58) + iVar1) / 2;
  *(int *)(param_1 + 0x58) = iVar6;
  iVar5 = (*(int *)(param_1 + 0x5c) + iVar2) / 2;
  *(int *)(param_1 + 0x5c) = iVar5;
  *(int *)(param_1 + 0x60) = iVar6;
  *(int *)(param_1 + 100) = iVar5;
  if (iVar1 < 1) {
    iVar1 = -iVar1;
  }
  if (iVar1 <= (int)(uint)*(byte *)(param_1 + 0x24)) {
    if (iVar2 < 1) {
      iVar2 = -iVar2;
    }
    if (iVar2 <= (int)(uint)*(byte *)(param_1 + 0x24)) goto LAB_0003a24c;
  }
  *(byte *)(param_1 + 0x99) = *(byte *)(param_1 + 0x99) | 2;
LAB_0003a24c:
  if (DAT_2003a474 != 0) {
    uVar3 = FUN_0004cd9c(DAT_2003a474,0x80);
    uVar3 = uVar3 ^ 1;
    if (((uVar3 == 0) || (iVar1 = FUN_0005e710(2,DAT_2003a470), iVar1 != 0)) &&
       (-1 < (int)((uint)*(byte *)(DAT_2003a470 + 10) << 0x1c))) {
      FUN_00048428(param_1);
      iVar1 = FUN_0003a5c8(param_1);
      if (iVar1 == 0) {
        FUN_00039c98(param_1);
        iVar1 = FUN_0003a5c8(param_1);
        if (iVar1 == 0) {
          if (((*(char *)(param_1 + 9) == '\x02') && (*(int *)(param_1 + 0x20) != 0)) &&
             (iVar1 = FUN_00052958(), iVar1 != 0)) {
            FUN_00052aae(*(undefined4 *)(param_1 + 0x20));
          }
          if (*(int *)(param_1 + 0x70) == 0) {
            if ((*(byte *)(param_1 + 10) & 1) == 0) {
              uVar4 = FUN_000526fc(*(undefined4 *)(param_1 + 0xc));
              if (*(ushort *)(DAT_2003a470 + 0x28) < uVar4) {
                if ((uVar3 != 0) && (iVar1 = FUN_0005e710(5), iVar1 == 0)) {
                  return;
                }
                *(byte *)(param_1 + 10) = *(byte *)(param_1 + 10) | 1;
                uVar7 = FUN_00052708();
                *(undefined4 *)(param_1 + 0x10) = uVar7;
              }
              if (*(int *)(param_1 + 0x70) != 0) {
                return;
              }
              if ((*(byte *)(param_1 + 10) & 1) == 0) {
                return;
              }
            }
            uVar4 = FUN_000526fc(*(undefined4 *)(param_1 + 0x10));
            if ((*(ushort *)(DAT_2003a470 + 0x2a) < uVar4) &&
               ((uVar3 == 0 || (iVar1 = FUN_0005e710(6), iVar1 != 0)))) {
              uVar7 = FUN_00052708();
              *(undefined4 *)(param_1 + 0x10) = uVar7;
            }
          }
        }
      }
    }
  }
  return;
}

