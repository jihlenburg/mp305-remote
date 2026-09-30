/* Address: 00046688; name: FUN_00046688; body bytes: 8 */

ushort FUN_00046688(int param_1)

{
  return *(ushort *)(param_1 + 8) & 0x7fff;
}

