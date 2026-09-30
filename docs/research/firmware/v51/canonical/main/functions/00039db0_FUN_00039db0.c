/* Address: 00039db0; name: FUN_00039db0; body bytes: 450 */

void FUN_00039db0(int param_1,int param_2)

{
  byte bVar1;
  char cVar2;
  char cVar3;
  uint uVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  
  bVar1 = *(byte *)(param_1 + 10);
  if (*(char *)(param_2 + 0x12) == '\x01') {
    if ((int)((uint)bVar1 << 0x1c) < 0) {
      return;
    }
  }
  else if ((int)((uint)bVar1 << 0x1c) < 0) {
    *(undefined4 *)(param_1 + 0xc) = 0;
    *(byte *)(param_1 + 10) = bVar1 & 0xf6;
    *(undefined1 *)(param_1 + 0x9c) = 0;
  }
  iVar6 = *(int *)(param_1 + 0xa0);
  *(undefined4 *)(param_1 + 0xa0) = *(undefined4 *)(param_2 + 8);
  iVar7 = *(int *)(param_1 + 0xa8);
  if (iVar7 == 0) {
    return;
  }
  DAT_2003a474 = FUN_000472e0();
  if (DAT_2003a474 == 0) {
    return;
  }
  uVar4 = FUN_0004cd9c(DAT_2003a474,0x80);
  cVar3 = *(char *)(param_1 + 0x9c);
  *(undefined1 *)(param_1 + 0x9c) = *(undefined1 *)(param_2 + 0x12);
  cVar2 = *(char *)(param_2 + 0x12);
  if ((cVar2 == '\x01') && (cVar3 == '\0')) {
    uVar5 = FUN_00052708();
    *(undefined4 *)(param_1 + 0xc) = uVar5;
    iVar6 = *(int *)(param_2 + 8);
    if (iVar6 == 9) {
LAB_00039e4a:
      FUN_0004743a(iVar7,0);
      FUN_000471d8(iVar7);
      goto LAB_00039ea0;
    }
    if (iVar6 != 0xb) {
      if ((uVar4 ^ 1) == 0) {
        DAT_2003a474 = 0;
        return;
      }
      if (iVar6 == 10) {
        FUN_00047414(iVar7,10);
        iVar6 = FUN_0003a5c8(param_1);
        if (iVar6 != 0) {
          return;
        }
        uVar5 = 1;
LAB_00039f1e:
        iVar6 = FUN_0005e710(uVar5,DAT_2003a470);
        if (iVar6 != 0) {
          DAT_2003a474 = 0;
          return;
        }
        return;
      }
      if (iVar6 == 0x1b) {
        FUN_00047414(iVar7,0x1b);
        iVar6 = FUN_0003a5c8(param_1);
        if (iVar6 != 0) {
          return;
        }
        uVar5 = 0x24;
        goto LAB_00039f1e;
      }
LAB_00039e9a:
      FUN_00047414(iVar7);
      goto LAB_00039ea0;
    }
  }
  else {
    if ((uVar4 ^ 1) == 0) {
      DAT_2003a474 = 0;
      return;
    }
    if (cVar2 != '\x01') {
      if (cVar2 != '\0') {
        DAT_2003a474 = 0;
        return;
      }
      if (cVar3 != '\x01') {
        DAT_2003a474 = 0;
        return;
      }
      *(int *)(param_2 + 8) = iVar6;
      if (iVar6 == 10) {
        iVar6 = FUN_0005e710(8,DAT_2003a470);
        if (iVar6 == 0) {
          return;
        }
        if (((*(byte *)(param_1 + 10) & 1) == 0) &&
           (iVar6 = FUN_0005e710(4,DAT_2003a470), iVar6 == 0)) {
          return;
        }
        iVar6 = FUN_0005e710(7,DAT_2003a470);
        if (iVar6 == 0) {
          return;
        }
      }
      *(undefined4 *)(param_1 + 0xc) = 0;
      *(byte *)(param_1 + 10) = *(byte *)(param_1 + 10) & 0xfe;
      DAT_2003a474 = 0;
      return;
    }
    if (cVar3 != '\x01') {
      DAT_2003a474 = 0;
      return;
    }
    if ((*(int *)(param_2 + 8) == 10) && (iVar6 = FUN_0005e710(2,DAT_2003a470), iVar6 == 0)) {
      return;
    }
    if ((*(byte *)(param_1 + 10) & 1) == 0) {
      uVar4 = FUN_000526fc(*(undefined4 *)(param_1 + 0xc));
      if (*(ushort *)(param_1 + 0x28) < uVar4) {
        *(byte *)(param_1 + 10) = *(byte *)(param_1 + 10) | 1;
        if (*(int *)(param_2 + 8) != 10) {
          DAT_2003a474 = 0;
          return;
        }
        uVar5 = FUN_00052708();
        *(undefined4 *)(param_1 + 0x10) = uVar5;
        uVar5 = 5;
        goto LAB_00039f1e;
      }
      if ((*(byte *)(param_1 + 10) & 1) == 0) {
        DAT_2003a474 = 0;
        return;
      }
    }
    uVar4 = FUN_000526fc(*(undefined4 *)(param_1 + 0x10));
    if (uVar4 <= *(ushort *)(param_1 + 0x2a)) {
      DAT_2003a474 = 0;
      return;
    }
    uVar5 = FUN_00052708();
    *(undefined4 *)(param_1 + 0x10) = uVar5;
    iVar6 = *(int *)(param_2 + 8);
    if (iVar6 == 10) {
      uVar5 = 6;
      goto LAB_00039f1e;
    }
    if (iVar6 == 9) goto LAB_00039e4a;
    if (iVar6 != 0xb) goto LAB_00039e9a;
  }
  FUN_0004743a(iVar7,0);
  FUN_00047298(iVar7);
LAB_00039ea0:
  iVar6 = FUN_0003a5c8(param_1);
  if (iVar6 == 0) {
    DAT_2003a474 = 0;
    return;
  }
  return;
}

