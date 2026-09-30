/* Address: 00015384; name: FUN_00015384; body bytes: 14 */

void FUN_00015384(int param_1,ushort param_2)

{
  *(ushort *)(&DAT_4005380a + param_1 * 0x10) =
       *(ushort *)(&DAT_4005380a + param_1 * 0x10) | param_2;
  return;
}

