/* Address: ram:0004f840; name: FUN_ram_0004f840; body bytes: 614 */

void FUN_ram_0004f840(undefined2 *param_1)

{
  byte bVar1;
  byte bVar2;
  char cVar3;
  undefined1 uVar4;
  undefined2 uVar5;
  int iVar6;
  undefined4 uVar7;
  uint uVar8;
  ushort uVar9;
  undefined1 auStack_20 [16];
  
  gp = 0x20004000;
  if (*(char *)(param_1 + 1) == '\0') {
    return;
  }
  if (*(char *)((int)param_1 + 3) == 'U') {
    bVar1 = *(byte *)((int)param_1 + 7);
    bVar2 = *(byte *)((int)param_1 + (bVar1 >> 3) + 8);
    FUN_ram_000440ba(param_1 + 0x1e,0x10);
    if (DAT_ram_20001f04 == 0) {
      gp = 0x20004000;
      return;
    }
    if (*(code **)(DAT_ram_20001f04 + 8) == (code *)0x0) {
      gp = 0x20004000;
      return;
    }
    cVar3 = (**(code **)(DAT_ram_20001f04 + 8))
                      (*(int *)(param_1 + 0x40) + 0x80,*(int *)(param_1 + 0x40) + 0x40,
                       param_1 + 0x1e,(int)(uint)bVar2 >> (bVar1 & 7) & 1U | 0x80,auStack_20);
    if (cVar3 != '\0') {
      gp = 0x20004000;
      return;
    }
    tmos_memcpy(param_1 + 0x16,auStack_20,0x10);
    FUN_ram_00050272(param_1);
    uVar4 = 0x56;
LAB_ram_0004f8ca:
    *(undefined1 *)((int)param_1 + 3) = uVar4;
  }
  else {
    if (*(char *)((int)param_1 + 3) == '!') {
      uVar9 = *(ushort *)(*(int *)(param_1 + 0x14) + 4);
      if (((*(int *)(param_1 + 0x40) == 0) && ((uVar9 & 0x100) != 0)) &&
         ((*(ushort *)(*(int *)(param_1 + 0x36) + 0x14) & 0x100) != 0)) {
        uVar4 = 0x27;
      }
      else if (((uVar9 & 0x200) == 0) ||
              ((*(ushort *)(*(int *)(param_1 + 0x36) + 0x14) & 0x200) == 0)) {
        if (((uVar9 & 0x400) == 0) || ((*(ushort *)(*(int *)(param_1 + 0x36) + 0x14) & 0x400) == 0))
        goto LAB_ram_0004f908;
        uVar4 = 0x2b;
      }
      else {
        uVar4 = 0x29;
      }
      *(undefined1 *)((int)param_1 + 3) = uVar4;
    }
LAB_ram_0004f908:
    cVar3 = *(char *)((int)param_1 + 3);
    if (cVar3 == '\'') {
      if (*(int *)(param_1 + 0x38) == 0) {
        iVar6 = FUN_ram_20000040(0x1c,0x53);
        *(int *)(param_1 + 0x38) = iVar6;
        if (iVar6 != 0) {
          tmos_memset(iVar6,0,0x1c);
        }
      }
      iVar6 = *(int *)(param_1 + 0x38);
      if (iVar6 != 0) {
        if (*(char *)(iVar6 + 0x1a) == '\0') {
          uVar4 = FUN_ram_0004e9a0(param_1);
          *(undefined1 *)(iVar6 + 0x1a) = uVar4;
        }
        tmos_memset(*(undefined4 *)(param_1 + 0x38),0,0x10);
        if ((byte)(*(char *)(*(int *)(param_1 + 0x38) + 0x1a) - 1U) < 0x10) {
          FUN_ram_000440ba();
        }
        uVar5 = tmos_rand();
        iVar6 = *(int *)(param_1 + 0x38);
        *(undefined2 *)(iVar6 + 0x10) = uVar5;
        FUN_ram_000440ba(iVar6 + 0x12,8);
        FUN_ram_00050588(*param_1,*(undefined4 *)(param_1 + 0x38));
      }
      uVar4 = 0x28;
    }
    else if (cVar3 == '(') {
      iVar6 = *(int *)(param_1 + 0x38);
      if (iVar6 != 0) {
        FUN_ram_000505e0(*param_1,*(undefined2 *)(iVar6 + 0x10),iVar6 + 0x12);
      }
      uVar9 = *(ushort *)(*(int *)(param_1 + 0x14) + 4);
      if (((uVar9 & 0x200) == 0) || ((*(ushort *)(*(int *)(param_1 + 0x36) + 0x14) & 0x200) == 0)) {
LAB_ram_0004fa70:
        if (((uVar9 & 0x400) == 0) || ((*(ushort *)(*(int *)(param_1 + 0x36) + 0x14) & 0x400) == 0))
        goto LAB_ram_0004fa9e;
        uVar4 = 0x2b;
      }
      else {
        uVar4 = 0x29;
      }
    }
    else {
      if (cVar3 != ')') {
        if (cVar3 == '*') {
          iVar6 = FUN_ram_000443b8();
          uVar7 = FUN_ram_00044398(iVar6 != 1);
          FUN_ram_00050598(*param_1,iVar6 == 1,uVar7);
          uVar9 = *(ushort *)(*(int *)(param_1 + 0x14) + 4);
          goto LAB_ram_0004fa70;
        }
        if (cVar3 == '+') {
          uVar7 = FUN_ram_000443cc();
          FUN_ram_00050618(*param_1,uVar7);
        }
LAB_ram_0004fa9e:
        uVar4 = 0x2f;
        goto LAB_ram_0004f8ca;
      }
      uVar7 = FUN_ram_000443c2();
      FUN_ram_000505d0(*param_1,uVar7);
      uVar4 = 0x2a;
    }
    *(undefined1 *)((int)param_1 + 3) = uVar4;
    iVar6 = FUN_ram_0004df14(*param_1);
    uVar8 = 0x10;
    if (iVar6 != 0) {
      uVar8 = (uint)*(ushort *)(iVar6 + 0xe);
    }
    tmos_start_task(DAT_ram_20001d4f,1,uVar8 << 1);
  }
  return;
}

