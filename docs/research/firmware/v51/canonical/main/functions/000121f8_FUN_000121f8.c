/* Address: 000121f8; name: FUN_000121f8; body bytes: 16 */

void FUN_000121f8(int param_1,ushort param_2)

{
  *(ushort *)(param_1 + 2) = *(ushort *)(param_1 + 2) & 0xf8ff | param_2 & 0x700;
  return;
}

