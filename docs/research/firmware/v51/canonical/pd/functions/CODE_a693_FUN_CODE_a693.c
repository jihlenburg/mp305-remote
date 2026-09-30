/* Address: CODE:a693; name: FUN_CODE_a693; body bytes: 7 */

byte FUN_CODE_a693(void)

{
  byte bVar1;
  byte in_PSW;
  
  bVar1 = FUN_CODE_628b(0xb0);
  return bVar1 >> 1 | in_PSW & 0x80;
}

