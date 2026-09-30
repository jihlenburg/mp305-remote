/* Address: ram:0005ae46; name: FUN_ram_0005ae46; body bytes: 146 */

undefined4 FUN_ram_0005ae46(int param_1)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  
  gp = 0x20004000;
  iVar2 = *(int *)(param_1 + 0x110);
  *(undefined1 *)(param_1 + 0x15) = 3;
  *(undefined1 *)(iVar2 + 2) = 0x17;
  bVar1 = *(byte *)(param_1 + 0x144);
  *(byte *)(iVar2 + 3) = bVar1;
  *(undefined1 *)(iVar2 + 4) = *(undefined1 *)(param_1 + 0x145);
  bVar1 = bVar1 & *(byte *)(param_1 + 0x14b);
  uVar3 = (uint)*(ushort *)(param_1 + 0x1ca);
  if ((bVar1 & 4) == 0) {
    if ((bVar1 & 1) == 0) {
      iVar5 = uVar3 - 0x44;
      iVar2 = 4;
    }
    else {
      iVar5 = uVar3 - 0x50;
      iVar2 = 8;
    }
    if (iVar2 == 0) {
      uVar4 = 0xffffffff;
    }
    else {
      uVar4 = iVar5 / iVar2;
    }
  }
  else {
    uVar4 = 0;
    if (uVar3 < 0x350) goto LAB_ram_0005ae96;
    if (*(short *)(param_1 + 0x148) == 0) {
      iVar2 = (int)(uVar3 - 0x178) >> 3;
    }
    else {
      iVar2 = (int)(uVar3 - 0x178) >> 1;
    }
    uVar4 = iVar2 + -0x2b >> 3;
  }
  uVar4 = uVar4 & 0xffff;
LAB_ram_0005ae96:
  uVar3 = (uint)*(ushort *)(param_1 + 0x1c8);
  if (uVar4 < *(ushort *)(param_1 + 0x1c8)) {
    uVar3 = uVar4;
  }
  *(undefined1 *)(param_1 + 0x10) = 0x58;
  *(char *)(param_1 + 0x4c) = (char)uVar3;
  *(byte *)(param_1 + 0x29) = *(byte *)(param_1 + 0x29) | 4;
  return 0;
}

