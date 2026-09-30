/* Address: ram:00055e7e; name: FUN_ram_00055e7e; body bytes: 62 */

void FUN_ram_00055e7e(int param_1)

{
  int iVar1;
  
  gp = 0x20004000;
  iVar1 = *(int *)(param_1 + 0xec) + 1;
  *(int *)(param_1 + 0xec) = iVar1;
  if (iVar1 == 0) {
    *(int *)(param_1 + 0xf0) = *(int *)(param_1 + 0xf0) + 1;
  }
  if ((*(uint *)(param_1 + 0xf0) & 0x80) != 0) {
    *(undefined4 *)(param_1 + 0xec) = 1;
    *(undefined4 *)(param_1 + 0xf0) = 0;
  }
  if ((*(byte *)(param_1 + 0x29) & 0x40) != 0) {
    *(byte *)(param_1 + 0x29) = *(byte *)(param_1 + 0x29) | 0x20;
  }
  return;
}

