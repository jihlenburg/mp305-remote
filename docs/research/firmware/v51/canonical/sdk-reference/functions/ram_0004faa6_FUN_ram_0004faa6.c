/* Address: ram:0004faa6; name: FUN_ram_0004faa6; body bytes: 136 */

void FUN_ram_0004faa6(int param_1)

{
  ushort uVar1;
  int iVar2;
  
  gp = 0x20004000;
  iVar2 = *(int *)(param_1 + 0x34);
  uVar1 = *(ushort *)(*(int *)(iVar2 + 0x6c) + 0x14);
  if (((((uVar1 & 0x100) == 0) || ((*(ushort *)(*(int *)(iVar2 + 0x28) + 4) & 0x100) == 0)) &&
      (((uVar1 & 0x200) == 0 || ((*(ushort *)(*(int *)(iVar2 + 0x28) + 4) & 0x200) == 0)))) &&
     (((uVar1 & 0x400) == 0 || ((*(ushort *)(*(int *)(iVar2 + 0x28) + 4) & 0x400) == 0)))) {
    *(undefined1 *)(iVar2 + 3) = 0x2f;
  }
  else {
    *(undefined1 *)(iVar2 + 3) = 0x21;
    FUN_ram_0004f840(iVar2);
    if (*(char *)(iVar2 + 3) != '/') {
      return;
    }
  }
  FUN_ram_0004e5a2(*(undefined2 *)(param_1 + 2),0);
  return;
}

