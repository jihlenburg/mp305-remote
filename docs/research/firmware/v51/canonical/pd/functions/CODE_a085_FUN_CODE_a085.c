/* Address: CODE:a085; name: FUN_CODE_a085; body bytes: 14 */

char FUN_CODE_a085(char param_1)

{
  byte bVar1;
  
  bVar1 = FUN_CODE_440b();
  return (param_1 - (((0x13 < bVar1) << 7) >> 7)) + '\x05';
}

