/* Address: CODE:9261; name: FUN_CODE_9261; body bytes: 32 */

void FUN_CODE_9261(void)

{
  byte bVar1;
  
  bVar1 = (byte)((ushort)DAT_INTMEM_b3 * 0x19);
  FUN_CODE_ab68(BANK0_R6,4,BANK0_R5,bVar1 + 0xbb,
                ((char)((ushort)DAT_INTMEM_b3 * 0x19 >> 8) - (((0x44 < bVar1) << 7) >> 7)) + '\x06',
                1,BANK0_R7);
  return;
}

