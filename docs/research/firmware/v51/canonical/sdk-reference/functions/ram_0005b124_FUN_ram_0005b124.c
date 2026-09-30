/* Address: ram:0005b124; name: FUN_ram_0005b124; body bytes: 106 */

undefined4 FUN_ram_0005b124(int param_1)

{
  char cVar1;
  char cVar2;
  undefined1 uVar3;
  int iVar4;
  
  gp = 0x20004000;
  *(undefined1 *)(param_1 + 0x15) = 5;
  iVar4 = *(int *)(param_1 + 0x110);
  *(undefined1 *)(iVar4 + 2) = 0x24;
  *(undefined1 *)(iVar4 + 3) = 0;
  cVar1 = *(char *)(param_1 + 0x143);
  if (*(char *)(param_1 + 0x15f) == cVar1) {
    *(undefined1 *)(iVar4 + 3) = 2;
  }
  if (*(char *)(param_1 + 0x15e) == cVar1) {
    *(byte *)(iVar4 + 3) = *(byte *)(iVar4 + 3) | 1;
  }
  cVar2 = *(char *)(param_1 + 0x15d);
  *(char *)(iVar4 + 4) = cVar2;
  uVar3 = *(undefined1 *)(param_1 + 0x15c);
  *(char *)(iVar4 + 5) = cVar1;
  *(undefined1 *)(iVar4 + 6) = uVar3;
  if (((*(byte *)(param_1 + 0x158) & 1) != 0) && (cVar2 != '\0')) {
    *(uint *)(param_1 + 0xa0) = *(uint *)(param_1 + 0xa0) | 0x10000;
  }
  return 0;
}

