/* Address: ram:00044cd6; name: FUN_ram_00044cd6; body bytes: 396 */

void FUN_ram_00044cd6(int param_1,int param_2,undefined4 param_3,uint param_4,int param_5,
                     int param_6,int param_7,int param_8)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  byte bVar4;
  
  gp = 0x20004000;
  iVar1 = FUN_ram_0004df14(param_3);
  if (iVar1 == 0) {
    gp = 0x20004000;
    return;
  }
  if (param_1 == 0) {
    if ((param_4 & 4) == 0) {
      bVar4 = *(byte *)(iVar1 + 4) & 0xfd | 0x10;
    }
    else {
      bVar4 = *(byte *)(iVar1 + 4) | 0x12;
    }
    *(byte *)(iVar1 + 4) = bVar4;
    if ((((param_5 == 0) && (param_6 == 0)) && (param_7 == 0)) && (param_8 == 0)) {
      *(byte *)(iVar1 + 4) = bVar4 & 0xfb;
    }
    else {
      *(byte *)(iVar1 + 4) = bVar4 | 4;
      if (param_8 != 0) {
        *(undefined4 *)(iVar1 + 0x28) = *(undefined4 *)(param_8 + 0x10);
        tmos_memcpy(iVar1 + 0x18,param_8,0x10);
      }
      if (param_2 == 0) {
        if (param_5 == 0) goto LAB_ram_00044d2e;
        iVar2 = param_5;
        if (*(int *)(iVar1 + 0x2c) != 0) {
          FUN_ram_20000104();
        }
      }
      else {
        if (param_6 == 0) goto LAB_ram_00044d2e;
        iVar2 = param_6;
        if (*(int *)(iVar1 + 0x2c) != 0) {
          FUN_ram_20000104();
        }
      }
      uVar3 = FUN_ram_2000023a(iVar2,0x1c);
      *(undefined4 *)(iVar1 + 0x2c) = uVar3;
    }
  }
LAB_ram_00044d2e:
  iVar1 = *(int *)(iVar1 + 0x38);
  if (iVar1 == 0) {
    return;
  }
  if (param_5 != 0) {
    if (*(int *)(iVar1 + 0x20) == 0) {
      uVar3 = FUN_ram_20000040(0x1c,0x4713);
      *(undefined4 *)(iVar1 + 0x20) = uVar3;
    }
    if (*(int *)(iVar1 + 0x20) != 0) {
      tmos_memcpy(*(int *)(iVar1 + 0x20),param_5,0x1c);
    }
  }
  if (param_7 != 0) {
    if (*(int *)(iVar1 + 0x24) == 0) {
      uVar3 = FUN_ram_20000040(0x16,0x4712);
      *(undefined4 *)(iVar1 + 0x24) = uVar3;
    }
    if (*(int *)(iVar1 + 0x24) != 0) {
      tmos_memcpy(*(int *)(iVar1 + 0x24),param_7,0x16);
    }
  }
  if (param_8 != 0) {
    if (*(int *)(iVar1 + 0x28) == 0) {
      uVar3 = FUN_ram_20000040(0x14,0x4711);
      *(undefined4 *)(iVar1 + 0x28) = uVar3;
    }
    if (*(int *)(iVar1 + 0x28) != 0) {
      tmos_memcpy(*(int *)(iVar1 + 0x28),param_8,0x14);
    }
  }
  FUN_ram_00044504(param_1,param_3,param_4,param_6);
  return;
}

