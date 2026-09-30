/* Address: 00042a98; name: FUN_00042a98; body bytes: 1064 */

void FUN_00042a98(undefined4 param_1,int param_2,int *param_3)

{
  byte bVar1;
  bool bVar2;
  bool bVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  bool bVar8;
  undefined4 uVar9;
  int *piVar10;
  bool bVar11;
  undefined4 uVar12;
  undefined1 uVar13;
  int local_60;
  int local_5c;
  int local_58;
  int local_54;
  uint local_50;
  undefined4 uStack_4c;
  int local_48 [3];
  int local_3c;
  int local_38;
  int local_34;
  undefined4 local_30;
  int iStack_2c;
  int *local_28;
  
  if (((*(int *)(param_2 + 0x5c) == 0) || (*(byte *)(param_2 + 0x6c) < 3)) ||
     ((*(int *)(param_2 + 0x5c) == 1 &&
      (((*(int *)(param_2 + 0x68) < 1 && (*(int *)(param_2 + 0x60) == 0)) &&
       (*(int *)(param_2 + 100) == 0)))))) {
    bVar8 = false;
  }
  else {
    bVar8 = true;
  }
  bVar1 = *(byte *)(param_2 + 0x20);
  if ((*(byte *)(param_2 + 0x3b) < 3) || (*(int *)(param_2 + 0x30) == 0)) {
    bVar2 = false;
  }
  else {
    bVar2 = true;
  }
  if (((*(byte *)(param_2 + 0x48) < 3) || (*(int *)(param_2 + 0x44) == 0)) ||
     (((int)((uint)*(byte *)(param_2 + 0x49) << 0x1a) < 0 ||
      ((*(byte *)(param_2 + 0x49) & 0x1f) == 0)))) {
    bVar3 = false;
  }
  else {
    bVar3 = true;
  }
  if ((*(byte *)(param_2 + 0x58) < 3) || (*(int *)(param_2 + 0x50) == 0)) {
    bVar11 = false;
  }
  else {
    bVar11 = true;
  }
  uVar13 = 1;
  if (bVar1 == 0xff) {
    if ((*(byte *)(param_2 + 0x2f) & 7) != 0) {
      for (uVar4 = 0; uVar4 < *(byte *)(param_2 + 0x2e); uVar4 = uVar4 + 1) {
        if (*(char *)(uVar4 * 5 + param_2 + 0x27) != -1) goto LAB_00042b42;
      }
    }
  }
  else {
LAB_00042b42:
    uVar13 = 0;
  }
  local_30 = param_1;
  iStack_2c = param_2;
  local_28 = param_3;
  if (bVar8) {
    iVar5 = FUN_00040c36(param_1,param_3);
    iVar6 = FUN_0004a318(0x38);
    *(int *)(iVar5 + 0x4c) = iVar6;
    local_60 = iVar5 + 0x18;
    FUN_0003db32(local_60,*(undefined4 *)(param_2 + 0x68),*(undefined4 *)(param_2 + 0x68));
    FUN_0003db32(local_60,*(undefined4 *)(param_2 + 0x5c),*(undefined4 *)(param_2 + 0x5c));
    FUN_0003ddd6(local_60,*(undefined4 *)(param_2 + 0x60),*(undefined4 *)(param_2 + 100));
    FUN_0001046a(iVar6,param_2,0x1c);
    *(undefined4 *)(iVar6 + 0x14) = 0x38;
    *(undefined4 *)(iVar6 + 0x1c) = *(undefined4 *)(param_2 + 0x1c);
    *(undefined2 *)(iVar6 + 0x20) = *(undefined2 *)(param_2 + 0x59);
    *(undefined1 *)(iVar6 + 0x22) = *(undefined1 *)(param_2 + 0x5b);
    *(undefined4 *)(iVar6 + 0x24) = *(undefined4 *)(param_2 + 0x5c);
    *(undefined4 *)(iVar6 + 0x28) = *(undefined4 *)(param_2 + 0x68);
    *(undefined1 *)(iVar6 + 0x34) = *(undefined1 *)(param_2 + 0x6c);
    *(undefined4 *)(iVar6 + 0x2c) = *(undefined4 *)(param_2 + 0x60);
    *(undefined4 *)(iVar6 + 0x30) = *(undefined4 *)(param_2 + 100);
    *(undefined1 *)(iVar6 + 0x35) = uVar13;
    *(undefined1 *)(iVar5 + 4) = 3;
    FUN_0004197c(local_30,iVar5);
  }
  if (2 < bVar1) {
    local_60 = *local_28;
    local_5c = local_28[1];
    local_58 = local_28[2];
    local_54 = local_28[3];
    if (((1 < *(int *)(param_2 + 0x44)) && (0xfc < *(byte *)(param_2 + 0x48))) &&
       (*(int *)(param_2 + 0x1c) != 0)) {
      local_60 = local_60 - ((int)((uint)*(byte *)(param_2 + 0x49) << 0x1d) >> 0x1f);
      local_5c = local_5c - ((int)((uint)*(byte *)(param_2 + 0x49) << 0x1e) >> 0x1f);
      local_58 = local_58 + ((int)((uint)*(byte *)(param_2 + 0x49) << 0x1c) >> 0x1f);
      local_54 = local_54 - (*(byte *)(param_2 + 0x49) & 1);
    }
    iVar5 = FUN_00040c36(local_30,&local_60);
    iVar6 = FUN_0004a318(0x30);
    FUN_00041964();
    *(int *)(iVar5 + 0x4c) = iVar6;
    FUN_0001046a(iVar6,param_2,0x1c);
    *(undefined4 *)(iVar6 + 0x14) = 0x30;
    *(undefined4 *)(iVar6 + 0x1c) = *(undefined4 *)(param_2 + 0x1c);
    *(undefined2 *)(iVar6 + 0x21) = *(undefined2 *)(param_2 + 0x21);
    *(undefined1 *)(iVar6 + 0x23) = *(undefined1 *)(param_2 + 0x23);
    uVar9 = *(undefined4 *)(param_2 + 0x28);
    uVar12 = *(undefined4 *)(param_2 + 0x2c);
    *(undefined4 *)(iVar6 + 0x24) = *(undefined4 *)(param_2 + 0x24);
    *(undefined4 *)(iVar6 + 0x28) = uVar9;
    *(undefined4 *)(iVar6 + 0x2c) = uVar12;
    *(undefined1 *)(iVar6 + 0x20) = *(undefined1 *)(param_2 + 0x20);
    *(undefined1 *)(iVar5 + 4) = 1;
    FUN_0004197c(local_30,iVar5);
  }
  if (!bVar2) goto LAB_00042dd4;
  iVar5 = FUN_00047ecc(*(undefined4 *)(param_2 + 0x30));
  if ((iVar5 == 0) || (iVar5 == 1)) {
    iVar6 = FUN_0004775c(*(undefined4 *)(param_2 + 0x30),&local_54);
    if (iVar6 != 1) goto LAB_00042dd4;
    if ((iVar5 != 0) && (iVar5 != 1)) goto LAB_00042cba;
    piVar10 = local_28;
    if (*(char *)(param_2 + 0x3d) == '\0') {
      local_48[2] = (local_50 & 0xffff) - 1;
      local_48[0] = 0;
      local_3c = (local_50 >> 0x10) - 1;
      local_48[1] = 0;
      local_60 = 0;
      FUN_0003d7de(local_28,local_48,9,0);
      piVar10 = local_48;
    }
    iVar5 = FUN_00040c36(local_30,piVar10);
    iVar6 = FUN_0004a318(0x6c);
    FUN_00041b74();
    *(int *)(iVar5 + 0x4c) = iVar6;
    FUN_0001046a(iVar6,param_2,0x1c);
    *(undefined4 *)(iVar6 + 0x14) = 0x6c;
    *(undefined4 *)(iVar6 + 0x1c) = *(undefined4 *)(param_2 + 0x30);
    *(undefined1 *)(iVar6 + 0x4c) = *(undefined1 *)(param_2 + 0x3b);
    *(undefined2 *)(iVar6 + 0x48) = *(undefined2 *)(param_2 + 0x38);
    *(undefined1 *)(iVar6 + 0x4a) = *(undefined1 *)(param_2 + 0x3a);
    *(undefined1 *)(iVar6 + 0x4b) = *(undefined1 *)(param_2 + 0x3c);
    *(ushort *)(iVar6 + 0x4c) =
         *(ushort *)(iVar6 + 0x4c) & 0xdfff | (*(byte *)(param_2 + 0x3d) & 1) << 0xd;
    *(int *)(iVar6 + 0x20) = local_54;
    *(uint *)(iVar6 + 0x24) = local_50;
    *(undefined4 *)(iVar6 + 0x28) = uStack_4c;
    *(undefined4 *)(iVar6 + 100) = *(undefined4 *)(param_2 + 0x1c);
    uVar13 = 5;
  }
  else {
    if (iVar5 == 3) goto LAB_00042dd4;
    FUN_0004a5ea(&local_54,0xc);
LAB_00042cba:
    local_60 = 0;
    local_5c = 0x1fffffff;
    local_58 = 0;
    FUN_00051970(&local_38,*(undefined4 *)(param_2 + 0x30),*(undefined4 *)(param_2 + 0x34),0);
    local_48[0] = 0;
    local_48[2] = local_38 + -1;
    local_48[1] = 0;
    local_3c = local_34 + -1;
    local_60 = 0;
    FUN_0003d7de(local_28,local_48,9,0);
    iVar5 = FUN_00040c36(local_30,local_48);
    iVar6 = FUN_0004a318(0x54);
    FUN_00041db4();
    *(int *)(iVar5 + 0x4c) = iVar6;
    FUN_0001046a(iVar6,param_2,0x1c);
    *(undefined4 *)(iVar6 + 0x14) = 0x54;
    *(undefined2 *)(iVar6 + 0x2c) = *(undefined2 *)(param_2 + 0x38);
    *(undefined1 *)(iVar6 + 0x2e) = *(undefined1 *)(param_2 + 0x3a);
    *(undefined4 *)(iVar6 + 0x20) = *(undefined4 *)(param_2 + 0x34);
    *(undefined4 *)(iVar6 + 0x1c) = *(undefined4 *)(param_2 + 0x30);
    uVar13 = 4;
  }
  *(undefined1 *)(iVar5 + 4) = uVar13;
  FUN_0004197c(local_30,iVar5);
LAB_00042dd4:
  if (bVar3) {
    iVar5 = FUN_00040c36(local_30,local_28);
    iVar6 = FUN_0004a318(0x2c);
    *(int *)(iVar5 + 0x4c) = iVar6;
    FUN_0001046a(iVar6,param_2,0x1c);
    *(undefined4 *)(iVar6 + 0x14) = 0x2c;
    *(undefined4 *)(iVar6 + 0x1c) = *(undefined4 *)(param_2 + 0x1c);
    *(undefined2 *)(iVar6 + 0x20) = *(undefined2 *)(param_2 + 0x3e);
    *(undefined1 *)(iVar6 + 0x22) = *(undefined1 *)(param_2 + 0x40);
    *(undefined1 *)(iVar6 + 0x28) = *(undefined1 *)(param_2 + 0x48);
    *(undefined4 *)(iVar6 + 0x24) = *(undefined4 *)(param_2 + 0x44);
    *(byte *)(iVar6 + 0x29) = *(byte *)(param_2 + 0x49) & 0x1f;
    *(undefined1 *)(iVar5 + 4) = 2;
    FUN_0004197c(local_30,iVar5);
  }
  if (bVar11) {
    local_60 = *local_28;
    local_5c = local_28[1];
    local_58 = local_28[2];
    local_54 = local_28[3];
    FUN_0003db32(&local_60,*(int *)(param_2 + 0x50) + *(int *)(param_2 + 0x54));
    iVar5 = FUN_00040c36(local_30,&local_60);
    iVar6 = FUN_0004a318(0x2c);
    *(int *)(iVar5 + 0x4c) = iVar6;
    FUN_0003db32(iVar5 + 0x18,*(undefined4 *)(param_2 + 0x50),*(undefined4 *)(param_2 + 0x50));
    FUN_0003db32(iVar5 + 0x18,*(undefined4 *)(param_2 + 0x54),*(undefined4 *)(param_2 + 0x54));
    FUN_0001046a(iVar6,param_2,0x1c);
    *(undefined4 *)(iVar6 + 0x14) = 0x2c;
    iVar7 = 0x7fff;
    if (*(int *)(param_2 + 0x1c) != 0x7fff) {
      iVar7 = *(int *)(param_2 + 0x50) + *(int *)(param_2 + 0x1c) + *(int *)(param_2 + 0x54);
    }
    *(int *)(iVar6 + 0x1c) = iVar7;
    *(undefined2 *)(iVar6 + 0x20) = *(undefined2 *)(param_2 + 0x4a);
    *(undefined1 *)(iVar6 + 0x22) = *(undefined1 *)(param_2 + 0x4c);
    *(undefined1 *)(iVar6 + 0x28) = *(undefined1 *)(param_2 + 0x58);
    *(undefined4 *)(iVar6 + 0x24) = *(undefined4 *)(param_2 + 0x50);
    *(undefined1 *)(iVar6 + 0x29) = 0xf;
    *(undefined1 *)(iVar5 + 4) = 2;
    FUN_0004197c(local_30,iVar5);
  }
  return;
}

