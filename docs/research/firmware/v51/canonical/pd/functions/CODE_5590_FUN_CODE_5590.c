/* Address: CODE:5590; name: FUN_CODE_5590; body bytes: 26 */

byte FUN_CODE_5590(void)

{
  thunk_FUN_CODE_90f3();
  DAT_EXTMEM_04b4 = BANK0_R2;
  DAT_EXTMEM_04b5 = BANK0_R1;
  return *(byte *)CONCAT11(BANK0_R2,BANK0_R1) >> 6;
}

