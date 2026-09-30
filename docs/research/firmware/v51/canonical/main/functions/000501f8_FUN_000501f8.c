/* Address: 000501f8; name: FUN_000501f8; body bytes: 796 */

void FUN_000501f8(undefined4 param_1,undefined4 param_2)

{
  byte bVar1;
  undefined1 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined4 uVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int *piVar14;
  undefined4 uVar15;
  undefined1 auStack_40 [20];
  undefined4 uStack_2c;
  undefined4 local_28;
  
  uStack_2c = param_1;
  local_28 = param_2;
  iVar3 = FUN_0004b9b2(&DAT_0007ae60,param_2);
  if (iVar3 != 1) {
    return;
  }
  iVar3 = FUN_00046688(local_28);
  iVar4 = FUN_00046698(local_28);
  iVar5 = FUN_0005051c();
  if (iVar3 == 0x13) {
    puVar6 = (undefined4 *)FUN_0004673a(local_28);
    if (*(int *)(iVar4 + 8) == 0) {
      uVar15 = 0;
    }
    else {
      uVar15 = *(undefined4 *)(*(int *)(iVar4 + 8) + 0x20);
    }
    FUN_0003d9ec(auStack_40,iVar4 + 0x84);
    FUN_0003db32(auStack_40,uVar15);
    iVar3 = FUN_0003dcb8(auStack_40,*puVar6,0);
    *(char *)(puVar6 + 1) = (char)iVar3;
    if (iVar3 != 0) {
      return;
    }
    if (iVar5 != 2) {
      return;
    }
    FUN_0003d9ec(auStack_40,iVar4 + 0x74);
    FUN_0003db32(auStack_40,uVar15);
    uVar2 = FUN_0003dcb8(auStack_40,*puVar6,0);
    *(undefined1 *)(puVar6 + 1) = uVar2;
    return;
  }
  if (iVar3 == 1) {
    FUN_00047eec();
    FUN_00048288();
    FUN_0004eef4(iVar4,iVar4 + 0x94,3);
    return;
  }
  if (iVar3 == 2) {
    FUN_0006532e(iVar4,1);
    return;
  }
  uVar15 = 0x100;
  if ((iVar3 == 8) || (iVar3 == 3)) {
    FUN_0006532e(iVar4,0);
    *(byte *)(iVar4 + 0xa0) = *(byte *)(iVar4 + 0xa0) & 0xfe;
    *(undefined4 *)(iVar4 + 0x9c) = 0;
    FUN_0004d3d8(iVar4);
    uVar7 = FUN_0004bbe2(iVar4);
    iVar3 = FUN_000472d4();
    FUN_00047eec();
    iVar5 = FUN_000482e0();
    if (iVar5 == 4) {
      if (iVar3 == 0) {
        return;
      }
      iVar3 = FUN_0005051c(iVar4);
      if (iVar3 == 2) {
        bVar1 = *(byte *)(iVar4 + 0xa0);
        if (-1 < (int)((uint)bVar1 << 0x1e)) {
          *(byte *)(iVar4 + 0xa0) = bVar1 | 2;
          return;
        }
        *(byte *)(iVar4 + 0xa0) = bVar1 & 0xfd;
      }
      FUN_0004743a(uVar7,0);
      return;
    }
    if (iVar5 != 1) {
      return;
    }
    iVar3 = FUN_0003ac70(iVar4);
    if (iVar3 != 0) {
      uVar15 = 0x200;
    }
    FUN_0004aa6e(iVar4,uVar15);
    return;
  }
  if (iVar3 == 0x10) {
    FUN_00047eec();
    iVar3 = FUN_000482e0();
    if ((iVar3 != 4) && (iVar3 != 2)) {
      return;
    }
    *(byte *)(iVar4 + 0xa0) = *(byte *)(iVar4 + 0xa0) & 0xfd;
    return;
  }
  if (iVar3 == 0x2e) {
    iVar3 = FUN_0003ac70(iVar4);
    if (iVar3 == 0) {
      FUN_0004aa6e(iVar4,0x100);
      uVar15 = 0x200;
    }
    else {
      FUN_0004aa6e(iVar4,0x200);
    }
    FUN_0004e00e(iVar4,uVar15);
    FUN_0004de6c(iVar4);
    return;
  }
  if (iVar3 == 0x18) {
    iVar5 = FUN_0004c86a(iVar4,0x30000);
    iVar3 = FUN_0004c8ac(iVar4,0x30000);
    iVar8 = FUN_0004c906(iVar4,0x30000);
    iVar9 = FUN_0004c804(iVar4,0x30000);
    iVar10 = FUN_0004cbd8(iVar4,0x30000);
    iVar11 = FUN_0004cba6(iVar4,0x30000);
    iVar12 = FUN_0004ccf8(iVar4);
    iVar13 = FUN_0004bbec(iVar4);
    if (iVar12 + iVar10 * 2 < iVar13 + iVar11 * 2) {
      iVar12 = FUN_0004ccf8();
      iVar12 = iVar12 + iVar10 * 2;
    }
    else {
      iVar12 = FUN_0004bbec(iVar4);
      iVar12 = iVar12 + iVar11 * 2;
    }
    iVar10 = iVar5;
    if (iVar5 <= iVar3) {
      iVar10 = iVar3;
    }
    iVar11 = iVar8;
    if (iVar8 < iVar9) {
      iVar11 = iVar9;
    }
    if (iVar11 < iVar10) {
      if (iVar3 < iVar5) {
        iVar3 = iVar5;
      }
    }
    else {
      iVar3 = iVar9;
      if (iVar9 <= iVar8) {
        iVar3 = iVar8;
      }
    }
    iVar4 = FUN_0004b03e(iVar4,0x30000);
    iVar4 = iVar3 + (iVar12 >> 1) + 2 + iVar4;
    piVar14 = (int *)FUN_0004673a(local_28);
    if (iVar4 < *piVar14) {
      iVar4 = *piVar14;
    }
    *piVar14 = iVar4;
    return;
  }
  if (iVar3 == 0xe) {
    iVar3 = FUN_00046700(local_28);
    if ((iVar3 == 0x13) || (iVar3 == 0x11)) {
      if ((int)((uint)*(byte *)(iVar4 + 0xa0) << 0x1e) < 0) goto LAB_0005050a;
      iVar3 = thunk_FUN_0003e1e0(iVar4);
      iVar3 = iVar3 + 1;
    }
    else {
      if ((iVar3 != 0x14) && (iVar3 != 0x12)) {
        return;
      }
      if ((int)((uint)*(byte *)(iVar4 + 0xa0) << 0x1e) < 0) {
        iVar3 = thunk_FUN_0003e1c2(iVar4);
        iVar3 = iVar3 + -1;
        goto LAB_000504d6;
      }
      iVar3 = thunk_FUN_0003e1e0();
      iVar3 = iVar3 + -1;
    }
  }
  else {
    if (iVar3 != 0xf) {
      if (iVar3 != 0x1a) {
        return;
      }
      FUN_0002c688(local_28);
      return;
    }
    iVar5 = FUN_0004673e(local_28);
    if ((int)((uint)*(byte *)(iVar4 + 0xa0) << 0x1e) < 0) {
LAB_0005050a:
      iVar3 = thunk_FUN_0003e1c2(iVar4);
      iVar3 = iVar3 + 1;
LAB_000504d6:
      thunk_FUN_0003e222(iVar4,iVar3,1);
      goto LAB_000504e0;
    }
    iVar3 = thunk_FUN_0003e1e0(iVar4);
    iVar3 = iVar3 + iVar5;
  }
  thunk_FUN_0003e26c(iVar4,iVar3,1);
LAB_000504e0:
  FUN_0004e5a6(iVar4,0x20,0);
  return;
}

