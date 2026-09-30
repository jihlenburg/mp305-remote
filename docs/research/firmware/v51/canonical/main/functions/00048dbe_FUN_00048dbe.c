/* Address: 00048dbe; name: FUN_00048dbe; body bytes: 38 */

void FUN_00048dbe(int param_1)

{
  if (((int)((uint)*(byte *)(param_1 + 0x5c) << 0x1a) < 0) && (*(int *)(param_1 + 0x30) != 0)) {
    FUN_00046bec();
  }
  *(byte *)(param_1 + 0x5c) = *(byte *)(param_1 + 0x5c) & 0xdf;
  *(undefined4 *)(param_1 + 0x30) = 0;
  return;
}

