/* Address: 00050532; name: thunk_FUN_0003e1fc; body bytes: 4 */

undefined4 thunk_FUN_0003e1fc(int param_1)

{
  if (((((*(byte *)(param_1 + 0x70) & 7) == 1) && (*(int *)(param_1 + 0x30) < 0)) &&
      (0 < *(int *)(param_1 + 0x34))) && (*(int *)(param_1 + 0x38) == *(int *)(param_1 + 0x30))) {
    return 1;
  }
  return 0;
}

