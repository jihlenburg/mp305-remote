/* Address: 0004e0e6; name: FUN_0004e0e6; body bytes: 16 */

void FUN_0004e0e6(int param_1,ushort param_2)

{
  if (*(ushort *)(param_1 + 0x28) != (*(ushort *)(param_1 + 0x28) & ~param_2)) {
    FUN_000654c4();
    return;
  }
  return;
}

