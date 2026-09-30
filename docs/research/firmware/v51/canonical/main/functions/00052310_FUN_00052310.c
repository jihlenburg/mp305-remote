/* Address: 00052310; name: FUN_00052310; body bytes: 10 */

uint FUN_00052310(int param_1)

{
  return (*(byte *)(param_1 + 0x70) & 0xf) >> 3;
}

