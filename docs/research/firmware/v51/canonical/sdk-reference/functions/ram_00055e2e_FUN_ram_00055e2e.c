/* Address: ram:00055e2e; name: FUN_ram_00055e2e; body bytes: 80 */

void FUN_ram_00055e2e(int param_1)

{
  int iVar1;
  
  gp = 0x20004000;
  iVar1 = *(int *)(param_1 + 0xe4) + 1;
  *(int *)(param_1 + 0xe4) = iVar1;
  if (iVar1 == 0) {
    *(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + 1;
  }
  if ((*(uint *)(param_1 + 0xe8) & 0x80) != 0) {
    *(undefined4 *)(param_1 + 0xe4) = 1;
    *(undefined4 *)(param_1 + 0xe8) = 0;
  }
  if ((*(byte *)(param_1 + 0x29) & 0x40) != 0) {
    *(short *)(param_1 + 0x44) = *(short *)(param_1 + 0x3e) + *(short *)(param_1 + 0x46);
    *(uint *)(param_1 + 0xa4) = *(uint *)(param_1 + 0xa4) & 0xfffffbff;
  }
  return;
}

