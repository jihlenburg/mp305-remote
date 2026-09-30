/* Address: CODE:6000; name: FUN_CODE_6000; body bytes: 43 */

void FUN_CODE_6000(char param_1,char param_2,undefined1 param_3,undefined1 param_4)

{
  DAT_EXTMEM_04b2 = param_4;
  DAT_EXTMEM_04b3 = param_3;
  DAT_EXTMEM_04b4 = param_1;
  DAT_EXTMEM_04b5 = param_2;
  FUN_CODE_9894();
  FUN_CODE_ae2a(0x4b7);
  if (DAT_EXTMEM_04b5 == '\0' && DAT_EXTMEM_04b4 == '\0') {
                    /* WARNING: Subroutine does not return */
    FUN_CODE_adf3(0x4b7,DAT_EXTMEM_04b5);
  }
                    /* WARNING: Subroutine does not return */
  FUN_CODE_adf3(0x4b7,DAT_EXTMEM_04b5);
}

