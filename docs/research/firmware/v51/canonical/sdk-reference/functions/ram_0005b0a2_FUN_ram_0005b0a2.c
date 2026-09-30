/* Address: ram:0005b0a2; name: FUN_ram_0005b0a2; body bytes: 130 */

undefined4 FUN_ram_0005b0a2(int param_1)

{
  byte bVar1;
  undefined1 uVar2;
  int iVar3;
  
  gp = 0x20004000;
  iVar3 = *(int *)(param_1 + 0x110);
  *(undefined1 *)(param_1 + 0x15) = 4;
  *(undefined1 *)(iVar3 + 2) = 0x23;
  if ((*(byte *)(param_1 + 0x158) & 4) != 0) {
    bVar1 = *(byte *)(param_1 + 0x15a);
    *(undefined1 *)(iVar3 + 4) = 0;
    *(char *)(iVar3 + 3) = (char)(1 << (bVar1 - 1 & 0x1f));
    goto LAB_ram_0005b0d2;
  }
  if (*(byte *)(param_1 + 0x147) == 2) {
    if (DAT_ram_20001e9f != '\0') {
      uVar2 = 8;
      goto LAB_ram_0005b108;
    }
    *(undefined1 *)(iVar3 + 3) = 4;
  }
  else {
    uVar2 = (undefined1)(1 << (*(byte *)(param_1 + 0x147) & 0x1f));
LAB_ram_0005b108:
    *(undefined1 *)(iVar3 + 3) = uVar2;
  }
  *(undefined1 *)(iVar3 + 4) = *(undefined1 *)(param_1 + 0x165);
LAB_ram_0005b0d2:
  *(undefined1 *)(iVar3 + 5) = *(undefined1 *)(param_1 + 0x143);
  *(byte *)(param_1 + 0x29) = *(byte *)(param_1 + 0x29) | 4;
  *(undefined1 *)(param_1 + 0x10) = 0x85;
  return 0;
}

