/* Address: 00050518; name: thunk_FUN_0003e1c2; body bytes: 4 */

undefined4 thunk_FUN_0003e1c2(int param_1)

{
  if ((*(byte *)(param_1 + 0x70) & 7) != 2) {
    return *(undefined4 *)(param_1 + 0x30);
  }
  if (*(int *)(param_1 + 0x6c) != -1) {
    return *(undefined4 *)(param_1 + 0x68);
  }
  return *(undefined4 *)(param_1 + 0x38);
}

