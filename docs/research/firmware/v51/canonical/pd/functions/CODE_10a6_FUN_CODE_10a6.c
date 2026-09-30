/* Address: CODE:10a6; name: FUN_CODE_10a6; body bytes: 5 */

byte FUN_CODE_10a6(byte param_1)

{
  byte bVar1;
  
  bVar1 = SADEN;
  SADEN = bVar1 & ~param_1;
  return ~param_1;
}

