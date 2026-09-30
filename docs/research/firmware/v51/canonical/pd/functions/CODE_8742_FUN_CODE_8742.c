/* Address: CODE:8742; name: FUN_CODE_8742; body bytes: 52 */

byte FUN_CODE_8742(void)

{
  byte bVar1;
  
  bVar1 = DAT_INTMEM_a4;
  if ((DAT_INTMEM_a4 != 0) && (bVar1 = DAT_INTMEM_a4 - 0x21, DAT_INTMEM_a4 < 0x21)) {
    bVar1 = (byte)((ushort)DAT_INTMEM_a5 * 7);
    FUN_CODE_a90e(0xb2,bVar1 + 4,
                  (char)((ushort)DAT_INTMEM_a5 * 7 >> 8) - (((0xfb < bVar1) << 7) >> 7),1,0,0,0,7);
    DAT_INTMEM_a5 = DAT_INTMEM_a5 + 1 & 0x1f;
    DAT_INTMEM_a4 = DAT_INTMEM_a4 - 1;
    return DAT_INTMEM_a5;
  }
  return bVar1;
}

