/* Address: 000488a8; name: FUN_000488a8; body bytes: 14 */

void FUN_000488a8(int param_1)

{
  if (param_1 != 0) {
    *(byte *)(param_1 + 10) = *(byte *)(param_1 + 10) | 8;
  }
  return;
}

