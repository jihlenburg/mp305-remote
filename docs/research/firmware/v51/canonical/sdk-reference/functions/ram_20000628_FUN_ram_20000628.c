/* Address: ram:20000628; name: FUN_ram_20000628; body bytes: 1 */

undefined4 FUN_ram_20000628(int param_1)

{
  byte bVar1;
  byte bVar2;
  undefined1 uVar3;
  int iVar4;
  byte bVar5;
  
  gp = 0x20004000;
  iVar4 = *(int *)(param_1 + 0x118);
  if (iVar4 == 0) {
    return 1;
  }
  bVar1 = *(byte *)(param_1 + 0x4c);
  bVar5 = *(byte *)(param_1 + 0xc) & 0xfc;
  *(byte *)(param_1 + 0xc) = bVar5;
  bVar2 = *(byte *)(iVar4 + 9);
  if ((ushort)bVar1 < *(ushort *)(iVar4 + 0xc)) {
    if ((char)bVar2 < '\0') {
      *(byte *)(iVar4 + 9) = bVar2 & 0x7f;
      bVar2 = bVar5 | 2;
      if (*(char *)(iVar4 + 8) == '\x01') {
        bVar2 = bVar5 | 1;
      }
      *(byte *)(param_1 + 0xc) = bVar2;
      *(int *)(iVar4 + 4) = *(int *)(iVar4 + 4) + 2;
    }
    else {
      *(byte *)(param_1 + 0xc) = bVar5 | 1;
    }
    *(byte *)(param_1 + 0x15) = bVar1;
    tmos_memcpy(*(int *)(param_1 + 0x110) + 2,*(undefined4 *)(iVar4 + 4),(ushort)bVar1);
    iVar4 = *(int *)(param_1 + 0x118);
    bVar1 = *(byte *)(param_1 + 0x15);
    *(uint *)(iVar4 + 4) = *(int *)(iVar4 + 4) + (uint)bVar1;
    *(ushort *)(iVar4 + 0xc) = *(short *)(iVar4 + 0xc) - (ushort)bVar1;
    *(undefined1 *)(param_1 + 0x1b) = 2;
  }
  else {
    uVar3 = (undefined1)*(ushort *)(iVar4 + 0xc);
    if ((char)bVar2 < '\0') {
      bVar1 = bVar5 | 2;
      if (*(char *)(iVar4 + 8) == '\x01') {
        bVar1 = bVar5 | 1;
      }
      *(byte *)(param_1 + 0xc) = bVar1;
      *(undefined1 *)(param_1 + 0x15) = uVar3;
      *(undefined1 *)(iVar4 + 9) = 0;
      uVar3 = 1;
    }
    else {
      *(byte *)(param_1 + 0xc) = bVar5 | 1;
      *(undefined1 *)(param_1 + 0x15) = uVar3;
      *(undefined1 *)(iVar4 + 9) = 0;
      tmos_memcpy(*(int *)(param_1 + 0x110) + 2,*(undefined4 *)(iVar4 + 4));
      iVar4 = *(int *)(param_1 + 0x118);
      bVar1 = *(byte *)(param_1 + 0x15);
      *(uint *)(iVar4 + 4) = *(int *)(iVar4 + 4) + (uint)bVar1;
      *(ushort *)(iVar4 + 0xc) = *(short *)(iVar4 + 0xc) - (ushort)bVar1;
      uVar3 = 3;
    }
    *(undefined1 *)(param_1 + 0x1b) = uVar3;
    if (**(int **)(param_1 + 0x118) == 0) {
      gp = 0x20004000;
      return 0;
    }
  }
  if (*(byte *)(param_1 + 0x34) < DAT_ram_20001bce) {
    *(byte *)(param_1 + 0xc) = *(byte *)(param_1 + 0xc) | 0x10;
  }
  return 0;
}

