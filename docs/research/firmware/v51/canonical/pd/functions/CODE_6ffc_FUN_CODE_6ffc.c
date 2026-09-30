/* Address: CODE:6ffc; name: FUN_CODE_6ffc; body bytes: 4 */

byte FUN_CODE_6ffc(byte param_1)

{
  byte bVar1;
  
  bVar1 = SADEN;
  SADEN = bVar1 | param_1;
  return param_1;
}

