/* Address: 0005db06; name: FUN_0005db06; body bytes: 694 */

void FUN_0005db06(int param_1,int param_2,int param_3,int *param_4,int *param_5)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int local_a8;
  int local_a4;
  int local_a0;
  int local_9c;
  int local_98;
  int local_94;
  int local_90;
  undefined1 auStack_8c [48];
  uint local_5c;
  int local_4c;
  int iStack_34;
  int iStack_30;
  int local_2c;
  int *piStack_28;
  
  iStack_34 = param_1;
  iStack_30 = param_2;
  local_2c = param_3;
  piStack_28 = param_4;
  FUN_00042462(auStack_8c);
  FUN_0004cff4(param_1,0,auStack_8c);
  iVar7 = 0;
  iVar5 = 0;
  if (local_2c == 0) {
    iVar7 = FUN_0004c6f0(param_1,&LAB_00050000);
  }
  else {
    iVar5 = FUN_0004c6f0(param_1,0x20000);
  }
  cVar1 = *(char *)(param_1 + 0x3c);
  if ((((cVar1 != '\x02') && (cVar1 != '\x04')) && (cVar1 != '\x01')) && (cVar1 != '\0')) {
    if ((cVar1 != '\x10') && (cVar1 != '\b')) {
      return;
    }
    FUN_0004bab4(param_1,&local_9c);
    uVar2 = FUN_0003db28(&local_9c);
    uVar3 = FUN_0003db0a(&local_9c);
    if (uVar2 >> 1 < uVar3 >> 1) {
      uVar2 = FUN_0003db28();
    }
    else {
      uVar2 = FUN_0003db0a(&local_9c);
    }
    uVar2 = uVar2 >> 1;
    local_a8 = local_9c + uVar2;
    local_a4 = local_98 + uVar2;
    iVar6 = (uint)(param_2 * 10 * *(int *)(param_1 + 0x50)) /
            ((*(ushort *)(param_1 + 0x48) & 0x7fff) - 1) + *(int *)(param_1 + 0x54) * 10;
    if (*(char *)(param_1 + 0x3c) == '\b') {
      if (local_2c == 0) {
        iVar5 = iVar7;
      }
      iVar5 = -iVar5;
    }
    else if (local_2c == 0) {
      iVar5 = iVar7;
    }
    *param_4 = local_a8 + (uVar2 - local_5c);
    param_4[1] = local_a4;
    FUN_0004f292(param_4,iVar6,0x100,0x100,&local_a8,0);
    *param_5 = local_a8 + iVar5 + (uVar2 - local_5c);
    param_5[1] = local_a4;
    FUN_0004f292(param_5,iVar6,0x100,0x100,&local_a8,0);
    return;
  }
  iVar6 = FUN_0004c6a8(param_1,0);
  iVar4 = FUN_0004c900(param_1,0);
  iVar4 = iVar4 + iVar6;
  local_a4 = FUN_0004c7fe(param_1,0);
  local_a4 = local_a4 + iVar6;
  local_98 = FUN_0004c8a6(param_1,0);
  local_98 = local_98 + iVar6;
  local_a8 = FUN_0004c864(param_1,0);
  local_a8 = local_a8 + iVar6;
  local_4c = FUN_0004c8a6(param_1,&LAB_00050000);
  local_9c = FUN_0004c864(param_1,&LAB_00050000);
  local_94 = FUN_0004c900(param_1,&LAB_00050000);
  local_90 = FUN_0004c7fe(param_1,&LAB_00050000);
  cVar1 = *(char *)(param_1 + 0x3c);
  if (cVar1 == '\x02') {
    iVar8 = (*(int *)(param_1 + 0x1c) + (local_5c >> 1)) - local_98;
    iVar6 = local_94 + iVar4 + *(int *)(param_1 + 0x18);
LAB_0005dc6e:
    if (local_2c != 0) goto LAB_0005dc7a;
  }
  else {
    if (cVar1 != '\x04') {
      if (cVar1 == '\x01') {
        iVar8 = *(int *)(param_1 + 0x14) + local_98 + local_4c;
        iVar6 = *(int *)(param_1 + 0x18) + iVar4 + (local_5c >> 1);
      }
      else {
        iVar8 = *(int *)(param_1 + 0x14) + local_a8 + local_9c;
        iVar6 = (*(int *)(param_1 + 0x20) + (local_5c >> 1)) - local_a4;
        if ((cVar1 == '\0') || (cVar1 == '\x04')) goto LAB_0005dc4c;
      }
      goto LAB_0005dc6e;
    }
    iVar8 = *(int *)(param_1 + 0x14) + local_a8 + (local_5c >> 1);
    iVar6 = *(int *)(param_1 + 0x18) + local_94 + iVar4;
LAB_0005dc4c:
    if (local_2c != 0) {
      iVar5 = -iVar5;
      goto LAB_0005dc7a;
    }
    iVar7 = -iVar7;
  }
  iVar5 = iVar7;
LAB_0005dc7a:
  iVar7 = (*(ushort *)(param_1 + 0x48) & 0x7fff) - 1;
  local_a0 = iVar5;
  if ((cVar1 == '\x02') || (cVar1 == '\x04')) {
    iVar5 = *(int *)(param_1 + 0x20) - (local_a4 + local_90);
    if ((iVar7 != param_2) && (iVar6 = iVar5, param_2 != 0)) {
      iVar6 = FUN_0004bbec(param_1);
      iVar6 = iVar5 - ((iVar6 - (local_90 + iVar4 + local_a4 + local_94)) * param_2) / iVar7;
    }
    *param_4 = iVar8 + -1;
    param_4[1] = iVar6;
    *param_5 = (iVar8 + -1) - local_a0;
    param_5[1] = iVar6;
  }
  else {
    if (iVar7 == param_2) {
      iVar8 = *(int *)(param_1 + 0x1c) - (local_a8 + local_9c);
    }
    else if (param_2 != 0) {
      iVar5 = FUN_0004ccf8(param_1);
      iVar8 = iVar8 + ((iVar5 - (local_9c + local_a8 + local_98 + local_4c)) * param_2) / iVar7;
    }
    *param_4 = iVar8;
    param_4[1] = iVar6;
    *param_5 = iVar8;
    param_5[1] = param_4[1] + local_a0;
  }
  return;
}

