/* Address: 0003a318; name: FUN_0003a318; body bytes: 610 */

void FUN_0003a318(int param_1)

{
  short sVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int *piVar7;
  int iVar8;
  short sVar9;
  undefined4 *local_80;
  undefined4 uStack_7c;
  undefined4 local_78;
  undefined4 local_74;
  
  if ((((int)((uint)*(byte *)(param_1 + 10) << 0x1c) < 0) ||
      (*(int *)(param_1 + 0x38) != *(int *)(param_1 + 0x30))) ||
     (*(int *)(param_1 + 0x3c) != *(int *)(param_1 + 0x34))) {
    piVar7 = (int *)(param_1 + 0x78);
    uVar2 = FUN_00040890();
    iVar3 = FUN_00058760(uVar2,param_1 + 0x30);
    if (*piVar7 != iVar3) {
      FUN_0004e5a6(iVar3,0x15,param_1);
      iVar4 = FUN_0003a5c8(param_1);
      if (iVar4 != 0) {
        return;
      }
      FUN_0004883e(param_1,0x15,iVar3);
      iVar4 = FUN_0003a5c8(param_1);
      if (iVar4 != 0) {
        return;
      }
      FUN_0004e5a6(*piVar7,0x16,param_1);
      iVar4 = FUN_0003a5c8(param_1);
      if (iVar4 != 0) {
        return;
      }
      FUN_0004883e(param_1,0x16,*piVar7);
      iVar4 = FUN_0003a5c8(param_1);
      if (iVar4 != 0) {
        return;
      }
      *piVar7 = iVar3;
    }
    if ((int)((uint)*(byte *)(param_1 + 10) << 0x1c) < 0) {
      FUN_0004e5a6(*(undefined4 *)(param_1 + 0x68),3,DAT_2003a470);
      iVar3 = FUN_0003a5c8(param_1);
      if (iVar3 != 0) {
        return;
      }
      *(undefined4 *)(param_1 + 0x68) = 0;
      *(undefined4 *)(param_1 + 0x6c) = 0;
      *(undefined4 *)(param_1 + 0xc) = 0;
      *(undefined4 *)(param_1 + 0x10) = 0;
      *(byte *)(param_1 + 10) = *(byte *)(param_1 + 10) & 0xf7;
    }
  }
  DAT_2003a474 = *(int *)(param_1 + 0x68);
  iVar3 = *(int *)(param_1 + 0x70);
  if (((*(char *)(param_1 + 9) == '\x02') && (*(int *)(param_1 + 0x20) != 0)) &&
     (iVar4 = FUN_00052958(), iVar4 == 0)) {
    FUN_00052a74(*(undefined4 *)(param_1 + 0x20));
  }
  if (DAT_2003a474 != 0) {
    iVar4 = FUN_0004cd9c(DAT_2003a474,0x80);
    if (iVar4 != 1) {
      iVar4 = FUN_0005e710(8,DAT_2003a470);
      if (iVar4 == 0) {
        return;
      }
      if (iVar3 == 0) {
        if (((*(byte *)(param_1 + 10) & 1) == 0) &&
           (iVar4 = FUN_0005e710(4,DAT_2003a470), iVar4 == 0)) {
          return;
        }
        iVar4 = FUN_0005e710(7,DAT_2003a470);
        if (iVar4 == 0) {
          return;
        }
      }
      else {
        FUN_0004e5a6(iVar3,10,DAT_2003a470);
        iVar4 = FUN_0003a5c8(param_1);
        if (iVar4 != 0) {
          return;
        }
      }
    }
    *(undefined4 *)(param_1 + 0x68) = 0;
    *(undefined4 *)(param_1 + 0xc) = 0;
    *(undefined4 *)(param_1 + 0x10) = 0;
    if (iVar3 == 0) {
      return;
    }
    sVar9 = 0;
    iVar8 = 0x100;
    local_78 = 0;
    local_74 = 0;
    iVar4 = iVar3;
    do {
      sVar1 = FUN_0004c924(iVar4,0,0x6e);
      sVar9 = sVar1 + sVar9;
      iVar5 = FUN_0004c924(iVar4,0,0x6c);
      if (iVar5 < 1) {
        iVar5 = 1;
      }
      iVar6 = FUN_0004c924(iVar4,0,0x6d);
      if (iVar6 < 1) {
        iVar6 = 1;
      }
      iVar8 = iVar8 * iVar5 * 0x100 >> 0x10;
      iVar5 = iVar8 * iVar6 * 0x100 >> 0x10;
      iVar4 = FUN_0004bc8c(iVar4);
    } while (iVar4 != 0);
    if (((sVar9 != 0) || (iVar5 != 0x100)) || (iVar8 != 0x100)) {
      iVar4 = (int)(short)(0x10000 / iVar8);
      iVar8 = (int)(short)(0x10000 / iVar5);
      uStack_7c = 0;
      local_80 = &local_78;
      FUN_0004f292(param_1 + 0x58,(int)-sVar9,iVar4,iVar8);
      uStack_7c = 0;
      local_80 = &local_78;
      FUN_0004f292(param_1 + 0x60,(int)-sVar9,iVar4,iVar8);
    }
  }
  if (iVar3 == 0) {
    return;
  }
  if (*(int *)(param_1 + 0xc0) == 0) {
    if (param_1 == 0) {
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    FUN_0003c9f8(&local_80);
    FUN_0003cb2a(&local_80,param_1);
    FUN_0003caea(&local_80,0x400);
    FUN_0003cb1e(&local_80,0,0x400);
    FUN_0003cafa(&local_80,0x3a671);
    FUN_0003cadc(&local_80,0x3a6a5);
    FUN_0003cae6(&local_80,0x3a6a5);
    FUN_0003cb0a(&local_80,0xffffffff);
    uVar2 = FUN_0003cb6c(&local_80);
    *(undefined4 *)(param_1 + 0xc0) = uVar2;
  }
  FUN_0003a5c8(param_1);
  return;
}

