/* Address: ram:0005b020; name: FUN_ram_0005b020; body bytes: 130 */

undefined4 FUN_ram_0005b020(int param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  
  gp = 0x20004000;
  iVar2 = *(int *)(param_1 + 0x110);
  iVar1 = *(int *)(DAT_ram_20001db0 + 0x28) + (uint)*(byte *)(DAT_ram_20001db0 + 4) * 0x58;
  *(undefined1 *)(param_1 + 0x15) = 9;
  *(undefined1 *)(iVar2 + 2) = 0x20;
  uVar3 = (uint)*(ushort *)(param_1 + 0x1c6) + (uint)*(ushort *)(param_1 + 0x1ca) + 300;
  if (uVar3 < *(uint *)(iVar1 + 0x34)) {
    uVar3 = *(uint *)(iVar1 + 0x34);
  }
  *(char *)(iVar2 + 3) = (char)uVar3;
  *(char *)(iVar2 + 4) = (char)(uVar3 >> 8);
  *(char *)(iVar2 + 5) = (char)(uVar3 >> 0x10);
  uVar4 = *(undefined4 *)(iVar1 + 0x38);
  *(char *)(iVar2 + 6) = (char)uVar4;
  *(char *)(iVar2 + 7) = (char)((uint)uVar4 >> 8);
  *(char *)(iVar2 + 8) = (char)((uint)uVar4 >> 0x10);
  *(undefined1 *)(iVar2 + 9) = *(undefined1 *)(iVar1 + 0x1c);
  *(undefined1 *)(iVar2 + 10) = *(undefined1 *)(iVar1 + 0x1d);
  *(undefined1 *)(param_1 + 0x10) = 0x7c;
  return 0;
}

