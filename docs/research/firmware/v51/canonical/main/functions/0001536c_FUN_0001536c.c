/* Address: 0001536c; name: FUN_0001536c; body bytes: 18 */

bool FUN_0001536c(int param_1,ushort param_2)

{
  return (*(ushort *)(&DAT_40053800 + param_1 * 0x10) & param_2) != 0;
}

