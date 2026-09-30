/* Address: CODE:9df1; name: FUN_CODE_9df1; body bytes: 18 */

byte FUN_CODE_9df1(void)

{
  byte bVar1;
  byte bVar2;
  
  bVar1 = DAT_INTMEM_b4 & 0xe0;
  bVar2 = (bVar1 < 0x40) << 7;
  if (bVar1 == 0x40) {
    bVar1 = FUN_CODE_628b(0xb7);
    return bVar1 >> 1 | bVar2 & 0x80;
  }
  return bVar1;
}

