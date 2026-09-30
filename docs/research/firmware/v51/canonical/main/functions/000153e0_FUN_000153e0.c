/* Address: 000153e0; name: FUN_000153e0; body bytes: 14 */

void FUN_000153e0(int param_1,ushort param_2)

{
  *(ushort *)(&DAT_40053808 + param_1 * 0x10) =
       *(ushort *)(&DAT_40053808 + param_1 * 0x10) | param_2;
  return;
}

