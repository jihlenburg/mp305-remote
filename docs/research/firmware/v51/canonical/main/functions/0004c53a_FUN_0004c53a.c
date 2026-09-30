/* Address: 0004c53a; name: FUN_0004c53a; body bytes: 18 */

byte FUN_0004c53a(int param_1)

{
  if (*(int *)(param_1 + 8) != 0) {
    return *(byte *)(*(int *)(param_1 + 8) + 0x2a) & 3;
  }
  return 3;
}

