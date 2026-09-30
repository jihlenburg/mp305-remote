/* Address: CODE:8265; name: FUN_CODE_8265; body bytes: 60 */

void FUN_CODE_8265(byte param_1)

{
  DAT_EXTMEM_04a7 = 0;
  DAT_EXTMEM_04a8 = 0;
  DAT_EXTMEM_04a9 = 0;
  DAT_EXTMEM_04a6 = 0x84;
  DAT_EXTMEM_04a6 = FUN_CODE_62ae(BANK0_R7,(param_1 & 0xf) << 3);
  DAT_EXTMEM_04a7 = param_1;
  FUN_CODE_626d(0x4ba,DAT_EXTMEM_04a6,BANK0_R7,BANK0_R3);
  FUN_CODE_908c();
  return;
}

