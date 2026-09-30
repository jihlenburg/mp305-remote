/* Address: CODE:a377; name: FUN_CODE_a377; body bytes: 11 */

byte FUN_CODE_a377(void)

{
  byte bVar1;
  
  bVar1 = FIFLG1;
  FIFLG1 = bVar1 & ~(&DAT_CODE_b8f0)[DAT_INTMEM_b3];
  return ~(&DAT_CODE_b8f0)[DAT_INTMEM_b3];
}

