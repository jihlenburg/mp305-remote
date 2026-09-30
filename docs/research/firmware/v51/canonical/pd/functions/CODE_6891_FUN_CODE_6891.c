/* Address: CODE:6891; name: FUN_CODE_6891; body bytes: 71 */

void FUN_CODE_6891(char param_1)

{
  DAT_EXTMEM_04a8 = param_1;
  FUN_CODE_a757();
  FUN_CODE_90d1(0x7f,0xff);
  FUN_CODE_60b4();
  DAT_EXTMEM_04ae = 0;
  DAT_EXTMEM_04a9 = 0;
  if (DAT_EXTMEM_04a8 != '\0') {
    FUN_CODE_3409(-DAT_EXTMEM_04a8);
    FUN_CODE_ad6d(0x4aa);
                    /* WARNING: Subroutine does not return */
    FUN_CODE_ad49(0x4aa,BANK0_R3);
  }
  FUN_CODE_56a8(0,0,0);
  return;
}

