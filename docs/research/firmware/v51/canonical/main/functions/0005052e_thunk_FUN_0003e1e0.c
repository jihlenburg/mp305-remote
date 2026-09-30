/* Address: 0005052e; name: thunk_FUN_0003e1e0; body bytes: 4 */

undefined4 thunk_FUN_0003e1e0(int param_1)

{
  if (*(int *)(param_1 + 0x5c) != -1) {
    return *(undefined4 *)(param_1 + 0x58);
  }
  return *(undefined4 *)(param_1 + 0x2c);
}

