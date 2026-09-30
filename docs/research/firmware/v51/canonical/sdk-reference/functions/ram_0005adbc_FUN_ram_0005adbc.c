/* Address: ram:0005adbc; name: FUN_ram_0005adbc; body bytes: 138 */

undefined4 FUN_ram_0005adbc(int param_1)

{
  byte bVar1;
  byte bVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  
  gp = 0x20004000;
  iVar3 = *(int *)(param_1 + 0x110);
  *(undefined1 *)(param_1 + 0x15) = 3;
  *(undefined1 *)(iVar3 + 2) = 0x16;
  bVar1 = *(byte *)(param_1 + 0x144);
  *(byte *)(iVar3 + 3) = bVar1;
  bVar2 = *(byte *)(param_1 + 0x145);
  *(byte *)(iVar3 + 4) = bVar2;
  uVar4 = (uint)*(ushort *)(param_1 + 0x1ca);
  if ((bVar1 & 4) == 0) {
    if ((bVar2 & 1) == 0) {
      iVar6 = uVar4 - 0x44;
      iVar3 = 4;
    }
    else {
      iVar6 = uVar4 - 0x50;
      iVar3 = 8;
    }
    if (iVar3 == 0) {
      uVar5 = 0xffffffff;
    }
    else {
      uVar5 = iVar6 / iVar3;
    }
  }
  else {
    uVar5 = 0;
    if (uVar4 < 0x350) goto LAB_ram_0005ae04;
    if (*(short *)(param_1 + 0x148) == 0) {
      iVar3 = (int)(uVar4 - 0x178) >> 3;
    }
    else {
      iVar3 = (int)(uVar4 - 0x178) >> 1;
    }
    uVar5 = iVar3 + -0x2b >> 3;
  }
  uVar5 = uVar5 & 0xffff;
LAB_ram_0005ae04:
  uVar4 = (uint)*(ushort *)(param_1 + 0x1c8);
  if (uVar5 < *(ushort *)(param_1 + 0x1c8)) {
    uVar4 = uVar5;
  }
  *(char *)(param_1 + 0x4c) = (char)uVar4;
  *(byte *)(param_1 + 0x29) = *(byte *)(param_1 + 0x29) | 4;
  *(undefined1 *)(param_1 + 0x10) = 0x55;
  return 0;
}

