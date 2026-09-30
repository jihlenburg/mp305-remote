/* Address: 0003aca0; name: FUN_0003aca0; body bytes: 832 */

void FUN_0003aca0(int param_1,int *param_2,int param_3)

{
  char cVar1;
  byte bVar2;
  ushort uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  undefined4 uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  int iVar13;
  int iVar14;
  int local_48;
  int local_40;
  uint local_3c;
  undefined4 local_38;
  undefined4 local_34;
  int iStack_30;
  int *piStack_2c;
  int local_28;
  
  iStack_30 = param_1;
  piStack_2c = param_2;
  local_28 = param_3;
  iVar4 = FUN_0004cd92(param_1,0x60001);
  if (iVar4 != 0) {
    return;
  }
  iVar4 = FUN_0003728c(param_1);
  iVar5 = FUN_00037b0e(param_1);
  if (iVar5 == 0) {
    return;
  }
  if (iVar4 == 0) {
    return;
  }
  iVar6 = FUN_00037284(param_1);
  iVar7 = FUN_00037b06(param_1);
  cVar1 = FUN_0004c924(param_1,0,0x88);
  bVar2 = FUN_0004c924(param_1,0,0x8b);
  local_3c = (uint)bVar2;
  iVar4 = (iVar6 + iVar4) * 4 + -4;
  iVar14 = (*(int *)(param_2[2] + iVar4) + *(int *)(*param_2 + iVar4)) -
           *(int *)(*param_2 + iVar6 * 4);
  iVar4 = (iVar7 + iVar5) * 4 + -4;
  local_40 = (*(int *)(param_2[3] + iVar4) + *(int *)(param_2[1] + iVar4)) -
             *(int *)(param_2[1] + iVar7 * 4);
  iVar4 = FUN_0004c5fa(param_1,0);
  if (iVar4 == 1) {
    if (cVar1 == '\0') {
      cVar1 = '\x02';
    }
    else if (cVar1 == '\x02') {
      cVar1 = '\0';
    }
  }
  iVar4 = param_1 + 0x14;
  local_48 = FUN_0003db28();
  iVar5 = FUN_0003db0a(iVar4);
  if (cVar1 == '\x01') {
    iVar8 = FUN_0004c72c(param_1,0);
    iVar13 = FUN_0004c73e(param_1,0);
    iVar8 = (iVar14 - local_48) / 2 + (iVar8 - iVar13) / 2 + *(int *)(*param_2 + iVar6 * 4);
LAB_0003ae26:
    uVar3 = *(ushort *)(param_1 + 0x2a) & 0xf7ff;
  }
  else {
    if (cVar1 == '\x02') {
      iVar13 = FUN_0004ccf8(param_1);
      iVar6 = *(int *)(*param_2 + iVar6 * 4);
      iVar8 = FUN_0004c73e(param_1,0);
      iVar8 = ((iVar6 + iVar14) - iVar13) - iVar8;
      goto LAB_0003ae26;
    }
    if (cVar1 != '\x03') {
      iVar8 = FUN_0004c72c(param_1,0);
      iVar8 = iVar8 + *(int *)(*param_2 + iVar6 * 4);
      goto LAB_0003ae26;
    }
    iVar8 = FUN_0004c72c(param_1,0);
    iVar8 = iVar8 + *(int *)(*param_2 + iVar6 * 4);
    iVar6 = FUN_0004c72c(param_1,0);
    iVar13 = FUN_0004c73e(param_1,0);
    local_48 = iVar14 - (iVar13 + iVar6);
    uVar3 = *(ushort *)(param_1 + 0x2a) | 0x800;
  }
  *(ushort *)(param_1 + 0x2a) = uVar3;
  if (local_3c == 1) {
    iVar13 = local_40 - iVar5;
    iVar6 = FUN_0004c750(param_1,0);
    iVar14 = FUN_0004c71a(param_1,0);
    iVar6 = *(int *)(param_2[1] + iVar7 * 4) + iVar13 / 2 + (iVar6 - iVar14) / 2;
  }
  else if (local_3c == 2) {
    iVar14 = FUN_0004bbec(param_1);
    iVar7 = local_40 + *(int *)(param_2[1] + iVar7 * 4);
    iVar6 = FUN_0004c71a(param_1,0);
    iVar6 = (iVar7 - iVar14) - iVar6;
  }
  else {
    if (local_3c == 3) {
      iVar6 = FUN_0004c750(param_1,0);
      iVar6 = iVar6 + *(int *)(param_2[1] + iVar7 * 4);
      iVar5 = FUN_0004c750(param_1,0);
      iVar7 = FUN_0004c71a(param_1,0);
      iVar5 = local_40 - (iVar7 + iVar5);
      uVar3 = *(ushort *)(param_1 + 0x2a) | 0x400;
      goto LAB_0003ae5c;
    }
    iVar6 = FUN_0004c750(param_1,0);
    iVar6 = iVar6 + *(int *)(param_2[1] + iVar7 * 4);
  }
  uVar3 = *(ushort *)(param_1 + 0x2a) & 0xfbff;
LAB_0003ae5c:
  *(ushort *)(param_1 + 0x2a) = uVar3;
  iVar7 = FUN_0004ccf8(param_1);
  if ((iVar7 != local_48) || (iVar7 = FUN_0004bbec(param_1), iVar7 != iVar5)) {
    local_40 = *(int *)(param_1 + 0x14);
    local_3c = *(uint *)(param_1 + 0x18);
    local_38 = *(undefined4 *)(param_1 + 0x1c);
    local_34 = *(undefined4 *)(param_1 + 0x20);
    FUN_0004d3d8(param_1);
    FUN_0003de04(iVar4,local_48);
    FUN_0003ddfa(iVar4,iVar5);
    FUN_0004d3d8(param_1);
    FUN_0004e5a6(param_1,0x2e,&local_40);
    uVar9 = FUN_0004bc8c(param_1);
    FUN_0004e5a6(uVar9,0x27,param_1);
  }
  uVar10 = FUN_0004c924(param_1,0,0x6a);
  uVar11 = FUN_0004c924(param_1,0,0x6b);
  iVar4 = FUN_0004ccf8(param_1);
  iVar5 = FUN_0004bbec(param_1);
  if (((uVar10 & 0x7fffffff) >> 0x1d == 1) &&
     (uVar12 = uVar10 & 0x9fffffff, (int)uVar12 < 0x1fffffff)) {
    if (0xfffffff < (int)uVar12) {
      uVar12 = 0xfffffff - uVar12;
    }
    uVar10 = (int)(uVar12 * iVar4) / 100;
  }
  if (((uVar11 & 0x7fffffff) >> 0x1d == 1) &&
     (uVar12 = uVar11 & 0x9fffffff, (int)uVar12 < 0x1fffffff)) {
    if (0xfffffff < (int)uVar12) {
      uVar12 = 0xfffffff - uVar12;
    }
    uVar11 = (int)(iVar5 * uVar12) / 100;
  }
  iVar4 = (iVar8 + uVar10 + *(int *)(local_28 + 8)) - *(int *)(param_1 + 0x14);
  iVar5 = (iVar6 + uVar11 + *(int *)(local_28 + 0xc)) - *(int *)(param_1 + 0x18);
  if (iVar4 == 0 && iVar5 == 0) {
    return;
  }
  FUN_0004d3d8(param_1);
  *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + iVar4;
  *(int *)(param_1 + 0x1c) = *(int *)(param_1 + 0x1c) + iVar4;
  *(int *)(param_1 + 0x18) = *(int *)(param_1 + 0x18) + iVar5;
  *(int *)(param_1 + 0x20) = *(int *)(param_1 + 0x20) + iVar5;
  FUN_0004d3d8(param_1);
  FUN_0004d528(param_1,iVar4,iVar5,0);
  return;
}

