/* Address: CODE:8ea7; name: FUN_CODE_8ea7; body bytes: 38 */

char FUN_CODE_8ea7(byte param_1,byte param_2)

{
  byte bVar1;
  
  bVar1 = 2 - (((param_2 < 0x9e) << 7) >> 7);
  if (param_1 < bVar1) {
    return param_1 - bVar1;
  }
  bVar1 = 7 - (((param_2 < 0xba) << 7) >> 7);
  if (param_1 < bVar1) {
    return param_1 - bVar1;
  }
  return param_1 - ('\x0e' - (((param_2 < 0xe5) << 7) >> 7));
}

