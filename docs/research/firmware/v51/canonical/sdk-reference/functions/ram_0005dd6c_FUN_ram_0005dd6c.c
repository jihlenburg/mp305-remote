/* Address: ram:0005dd6c; name: FUN_ram_0005dd6c; body bytes: 494 */

undefined4 FUN_ram_0005dd6c(int param_1)

{
  char cVar1;
  byte bVar2;
  int iVar3;
  byte bVar4;
  int iVar5;
  undefined1 uVar6;
  char cVar7;
  uint uVar8;
  
  gp = 0x20004000;
  if ((*(char *)(param_1 + 0x12) != '\0') &&
     (*(ushort *)(param_1 + 0x40) < *(ushort *)(param_1 + 0x42))) {
    iVar5 = FUN_ram_20000ccc();
    if (iVar5 != 1) {
      gp = 0x20004000;
      return 0;
    }
    cVar7 = *(char *)(param_1 + 0xd);
    iVar5 = *(int *)(param_1 + 0x48);
    if (cVar7 == '\a') {
      cVar7 = *(char *)(param_1 + 0x28);
    }
    *(char *)(iVar5 + 4) = cVar7;
    *(undefined1 *)(iVar5 + 5) = *(undefined1 *)(param_1 + 0x55);
    *(undefined1 *)(iVar5 + 0xc) = *(undefined1 *)(param_1 + 0x29);
    *(undefined2 *)(iVar5 + 0xe) = *(undefined2 *)(param_1 + 0x2a);
    tmos_memcpy(iVar5 + 6,param_1 + 0x56,6);
    *(short *)(param_1 + 0x40) = *(short *)(param_1 + 0x40) + 1;
    *(undefined4 *)(param_1 + 0x48) = **(undefined4 **)(param_1 + 0x48);
  }
  bVar4 = *(byte *)(param_1 + 0xd);
  if (-1 < *(int *)(param_1 + 0x1c) << 0x10) {
    if (bVar4 == 1) {
      uVar6 = *(undefined1 *)(param_1 + 0x55);
      cVar1 = *(char *)(param_1 + 0x15);
      if ((((*(byte *)(DAT_ram_20001dd8 + 0x10) & 2) != 0) && (*(char *)(param_1 + 0x5d) != '\0'))
         && ((*(byte *)(param_1 + 99) & 0xc0) == 0x40)) {
        thunk_FUN_ram_00051bc0(1);
        gp = 0x20004000;
        return 1;
      }
      iVar5 = 0;
      cVar7 = '\0';
      bVar4 = 1;
    }
    else {
      bVar2 = *(byte *)(param_1 + 0xe);
      if (0x25 < bVar2) {
        gp = 0x20004000;
        return 0;
      }
      if (bVar4 == 2) {
        bVar4 = 3;
      }
      else if (bVar4 == 6) {
        bVar4 = 2;
      }
      cVar7 = bVar2 - 6;
      *(byte *)(param_1 + 0x2e) = bVar2 - 6;
      iVar5 = 0;
      if (cVar7 != '\0') {
        iVar5 = *(int *)(param_1 + 0x78) + 8;
      }
      cVar1 = *(char *)(param_1 + 0x15);
      uVar6 = *(undefined1 *)(param_1 + 0x55);
    }
    thunk_FUN_ram_000517d4(bVar4,uVar6,param_1 + 0x56,cVar7,iVar5,(int)cVar1);
    gp = 0x20004000;
    return 1;
  }
  if (6 < bVar4) goto LAB_ram_0005de2a;
  if (0x25 < *(byte *)(param_1 + 0xe)) {
    gp = 0x20004000;
    return 0;
  }
  if (bVar4 == 0) {
    uVar6 = 0x13;
LAB_ram_0005de0e:
    *(undefined1 *)(param_1 + 0x28) = uVar6;
  }
  else {
    if (bVar4 == 1) {
      uVar6 = 0x15;
      goto LAB_ram_0005de0e;
    }
    if (bVar4 == 2) {
      uVar6 = 0x10;
      goto LAB_ram_0005de0e;
    }
    if (bVar4 == 4) {
      uVar6 = 0x1b;
      goto LAB_ram_0005de0e;
    }
    if (bVar4 == 6) {
      uVar6 = 0x12;
      goto LAB_ram_0005de0e;
    }
  }
  *(undefined1 *)(param_1 + 0x29) = 0xff;
  *(undefined2 *)(param_1 + 0x3e) = 0;
  *(undefined1 *)(param_1 + 0x2d) = 0;
  if (bVar4 == 1) {
    *(undefined1 *)(param_1 + 0x2e) = 0;
  }
  else {
    *(byte *)(param_1 + 0x2e) = *(byte *)(param_1 + 0xe) - 6;
  }
LAB_ram_0005de2a:
  uVar8 = (uint)*(byte *)(param_1 + 0x2e);
  iVar5 = 0;
  if (uVar8 != 0) {
    iVar5 = *(int *)(param_1 + 0x78) + (*(byte *)(param_1 + 0xe) - uVar8) + 2;
  }
  if ((*(byte *)(param_1 + 0x28) & 4) == 0) {
    iVar3 = 0;
    uVar6 = 0;
  }
  else {
    iVar3 = param_1 + 0x5e;
    uVar6 = *(undefined1 *)(param_1 + 0x5d);
  }
  FUN_ram_000682c8(*(byte *)(param_1 + 0x28),*(undefined1 *)(param_1 + 0x55),param_1 + 0x56,
                   *(char *)(param_1 + 0x2c) + '\x01',*(undefined1 *)(param_1 + 0x2d),
                   *(undefined1 *)(param_1 + 0x29),(int)*(char *)(param_1 + 0x23),
                   (int)*(char *)(param_1 + 0x15),*(undefined2 *)(param_1 + 0x3e),uVar6,iVar3,uVar8,
                   iVar5);
  return 1;
}

