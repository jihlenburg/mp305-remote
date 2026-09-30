/* Address: 0003e1e0; name: FUN_0003e1e0; body bytes: 14 */

undefined4 FUN_0003e1e0(int param_1)

{
  if (*(int *)(param_1 + 0x5c) != -1) {
    return *(undefined4 *)(param_1 + 0x58);
  }
  return *(undefined4 *)(param_1 + 0x2c);
}

