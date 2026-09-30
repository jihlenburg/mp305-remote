/* Address: ram:0005aed8; name: FUN_ram_0005aed8; body bytes: 170 */

undefined4 FUN_ram_0005aed8(int param_1)

{
  byte bVar1;
  undefined1 uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  
  gp = 0x20004000;
  *(undefined1 *)(param_1 + 0x15) = 5;
  iVar3 = *(int *)(param_1 + 0x110);
  iVar5 = *(ushort *)(param_1 + 0x3e) + 8;
  iVar6 = iVar5 * 0x10000;
  *(short *)(param_1 + 0x14c) = (short)((uint)iVar6 >> 0x10);
  *(undefined1 *)(iVar3 + 2) = 0x18;
  bVar1 = *(byte *)(param_1 + 0x14a);
  *(byte *)(iVar3 + 3) = bVar1;
  uVar2 = *(undefined1 *)(param_1 + 0x14b);
  *(undefined1 *)(iVar3 + 5) = 0;
  *(undefined1 *)(iVar3 + 6) = 0;
  *(undefined1 *)(iVar3 + 4) = uVar2;
  if ((*(uint *)(param_1 + 0x148) & 0xffff0000) != 0) {
    *(char *)(iVar3 + 5) = (char)((uint)iVar6 >> 0x10);
    *(char *)(iVar3 + 6) = (char)((uint)iVar5 >> 8);
  }
  uVar4 = (uint)*(ushort *)(param_1 + 0x1ca);
  if ((bVar1 & 4) == 0) {
    if ((bVar1 & 1) == 0) {
      iVar5 = uVar4 - 0x44;
      iVar3 = 4;
    }
    else {
      iVar5 = uVar4 - 0x50;
      iVar3 = 8;
    }
    if (iVar3 == 0) {
      uVar7 = 0xffffffff;
    }
    else {
      uVar7 = iVar5 / iVar3;
    }
  }
  else {
    uVar7 = 0;
    if (uVar4 < 0x350) goto LAB_ram_0005af4c;
    if (*(short *)(param_1 + 0x148) == 0) {
      iVar3 = (int)(uVar4 - 0x178) >> 3;
    }
    else {
      iVar3 = (int)(uVar4 - 0x178) >> 1;
    }
    uVar7 = iVar3 + -0x2b >> 3;
  }
  uVar7 = uVar7 & 0xffff;
LAB_ram_0005af4c:
  uVar4 = (uint)*(ushort *)(param_1 + 0x1c8);
  if (uVar7 < *(ushort *)(param_1 + 0x1c8)) {
    uVar4 = uVar7;
  }
  *(char *)(param_1 + 0x4c) = (char)uVar4;
  *(undefined1 *)(param_1 + 0x10) = 0x59;
  return 0;
}

