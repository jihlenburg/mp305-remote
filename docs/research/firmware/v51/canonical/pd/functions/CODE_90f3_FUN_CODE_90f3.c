/* Address: CODE:90f3; name: FUN_CODE_90f3; body bytes: 34 */

char FUN_CODE_90f3(byte param_1)

{
  byte bVar1;
  
  DAT_EXTMEM_04c8 = param_1;
  bVar1 = (byte)((ushort)DAT_INTMEM_b3 * 0x28);
  return ((char)((ushort)DAT_INTMEM_b3 * 0x28 >> 8) - (((0xb2 < bVar1) << 7) >> 7)) + '\x04' +
         ((char)((ushort)param_1 * 4 >> 8) -
         ((CARRY1((byte)((ushort)param_1 * 4),bVar1 + 0x4d) << 7) >> 7));
}

