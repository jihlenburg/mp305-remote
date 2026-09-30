/* Address: CODE:9719; name: FUN_CODE_9719; body bytes: 26 */

char FUN_CODE_9719(byte param_1,byte param_2)

{
  byte bVar1;
  
  bVar1 = 8 - (((param_2 < 0xd3) << 7) >> 7);
  if (param_1 < bVar1) {
    return param_1 - bVar1;
  }
  return param_1 - ('\x0e' - (((param_2 < 0xe5) << 7) >> 7));
}

