/* Address: 00052958; name: FUN_00052958; body bytes: 8 */

byte FUN_00052958(int param_1)

{
  return *(byte *)(param_1 + 0x14) & 1;
}

