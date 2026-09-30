/* Address: ram:00050628; name: FUN_ram_00050628; body bytes: 744 */

void FUN_ram_00050628(undefined2 *param_1)

{
  int iVar1;
  char cVar2;
  undefined1 uVar3;
  undefined2 uVar4;
  undefined4 uVar5;
  int iVar6;
  uint uVar7;
  ushort uVar8;
  undefined1 auStack_20 [20];
  
  gp = 0x20004000;
  cVar2 = *(char *)((int)param_1 + 3);
  if (cVar2 == 'S') {
    *(undefined1 *)((int)param_1 + 3) = 0x59;
    uVar7 = 0;
LAB_ram_0005067a:
    if (((DAT_ram_20001f04 != 0) && (*(code **)(DAT_ram_20001f04 + 8) != (code *)0x0)) &&
       (cVar2 = (**(code **)(DAT_ram_20001f04 + 8))
                          (*(int *)(param_1 + 0x40) + 0x80,*(int *)(param_1 + 0x40) + 0x40,
                           param_1 + 0x1e,uVar7,auStack_20), cVar2 == '\0')) {
      tmos_memcpy(param_1 + 0x16,auStack_20,0x10);
      FUN_ram_00050272(param_1);
    }
    return;
  }
  if (cVar2 == 'U') {
    *(undefined1 *)((int)param_1 + 3) = 0x5a;
    uVar7 = (int)(uint)*(byte *)((int)param_1 + (*(byte *)((int)param_1 + 7) >> 3) + 8) >>
            (*(byte *)((int)param_1 + 7) & 7) & 1U | 0x80;
    FUN_ram_000440ba(param_1 + 0x1e,0x10);
    goto LAB_ram_0005067a;
  }
  if (cVar2 == '!') {
    uVar8 = *(ushort *)(*(int *)(param_1 + 0x36) + 0x14);
    if (((*(int *)(param_1 + 0x40) == 0) && ((uVar8 & 1) != 0)) &&
       ((*(ushort *)(*(int *)(param_1 + 0x14) + 4) & 1) != 0)) {
      uVar3 = 0x22;
    }
    else if (((uVar8 & 2) == 0) || ((*(ushort *)(*(int *)(param_1 + 0x14) + 4) & 2) == 0)) {
      if (((uVar8 & 4) == 0) || ((*(ushort *)(*(int *)(param_1 + 0x14) + 4) & 4) == 0))
      goto LAB_ram_000506fe;
      uVar3 = 0x26;
    }
    else {
      uVar3 = 0x24;
    }
    *(undefined1 *)((int)param_1 + 3) = uVar3;
  }
LAB_ram_000506fe:
  cVar2 = *(char *)((int)param_1 + 3);
  if (cVar2 == '\"') {
    if (*(int *)(param_1 + 0x38) == 0) {
      uVar5 = FUN_ram_20000040(0x1c,0x53);
      *(undefined4 *)(param_1 + 0x38) = uVar5;
    }
    iVar1 = *(int *)(param_1 + 0x38);
    if (iVar1 != 0) {
      uVar3 = FUN_ram_0004e9a0(param_1);
      *(undefined1 *)(iVar1 + 0x1a) = uVar3;
      tmos_memset(*(undefined4 *)(param_1 + 0x38),0,0x10);
      if ((byte)(*(char *)(*(int *)(param_1 + 0x38) + 0x1a) - 1U) < 0x10) {
        if (DAT_ram_20001f0f == '\0') {
          FUN_ram_000440ba();
        }
        else {
          tmos_memset(auStack_20,0,0x10);
          tmos_memcpy(auStack_20,&DAT_ram_20001c1c,6);
          LL_Encrypt(auStack_20,auStack_20,*(undefined4 *)(param_1 + 0x38));
        }
      }
      uVar4 = tmos_rand();
      iVar1 = *(int *)(param_1 + 0x38);
      *(undefined2 *)(iVar1 + 0x10) = uVar4;
      FUN_ram_000440ba(iVar1 + 0x12,8);
      FUN_ram_00050588(*param_1,*(undefined4 *)(param_1 + 0x38));
    }
    uVar3 = 0x23;
  }
  else {
    if (cVar2 == '#') {
      iVar1 = *(int *)(param_1 + 0x38);
      if (iVar1 != 0) {
        FUN_ram_000505e0(*param_1,*(undefined2 *)(iVar1 + 0x10),iVar1 + 0x12);
      }
      uVar8 = *(ushort *)(*(int *)(param_1 + 0x36) + 0x14);
      if (((uVar8 & 2) != 0) && ((*(ushort *)(*(int *)(param_1 + 0x14) + 4) & 2) != 0)) {
        uVar3 = 0x24;
        goto LAB_ram_000507a6;
      }
    }
    else {
      if (cVar2 == '$') {
        uVar5 = FUN_ram_000443c2();
        FUN_ram_000505d0(*param_1,uVar5);
        uVar3 = 0x25;
        goto LAB_ram_000507a6;
      }
      if (cVar2 != '%') {
        if (cVar2 == '&') {
          uVar5 = FUN_ram_000443cc();
          FUN_ram_00050618(*param_1,uVar5);
        }
        goto LAB_ram_000508b2;
      }
      iVar1 = FUN_ram_000443b8();
      uVar5 = FUN_ram_00044398(iVar1 == 0);
      FUN_ram_00050598(*param_1,iVar1 != 0,uVar5);
      uVar8 = *(ushort *)(*(int *)(param_1 + 0x36) + 0x14);
    }
    if (((uVar8 & 4) == 0) || ((*(ushort *)(*(int *)(param_1 + 0x14) + 4) & 4) == 0)) {
LAB_ram_000508b2:
      uVar8 = *(ushort *)(*(int *)(param_1 + 0x36) + 0x14);
      if (((*(int *)(param_1 + 0x40) == 0) && ((uVar8 & 0x100) != 0)) &&
         ((*(ushort *)(*(int *)(param_1 + 0x14) + 4) & 0x100) != 0)) {
        uVar3 = 0x27;
      }
      else if (((uVar8 & 0x200) == 0) || ((*(ushort *)(*(int *)(param_1 + 0x14) + 4) & 0x200) == 0))
      {
        if (((uVar8 & 0x400) == 0) || ((*(ushort *)(*(int *)(param_1 + 0x14) + 4) & 0x400) == 0)) {
          uVar3 = 0x2f;
        }
        else {
          uVar3 = 0x2b;
        }
      }
      else {
        uVar3 = 0x29;
      }
      *(undefined1 *)((int)param_1 + 3) = uVar3;
      gp = 0x20004000;
      return;
    }
    uVar3 = 0x26;
  }
LAB_ram_000507a6:
  *(undefined1 *)((int)param_1 + 3) = uVar3;
  iVar1 = FUN_ram_0004df14(*param_1);
  iVar6 = 0x10;
  if (iVar1 != 0) {
    iVar6 = (uint)(*(ushort *)(iVar1 + 0xe) >> 1) + (uint)*(ushort *)(iVar1 + 0xe);
  }
  tmos_start_task(DAT_ram_20001d4f,1,iVar6);
  gp = 0x20004000;
  return;
}

