/* Address: CODE:55c0; name: FUN_CODE_55c0; body bytes: 66 */

void FUN_CODE_55c0(void)

{
  char in_PSW;
  
  FUN_CODE_ae2a(0x53b);
  DAT_EXTMEM_0545 = 0;
  DAT_EXTMEM_0546 = 0;
  DAT_EXTMEM_0547 = 0;
  DAT_EXTMEM_0548 = 0x20;
  FUN_CODE_5459();
  if (-1 < in_PSW) {
    DAT_EXTMEM_0549 = 0;
    DAT_EXTMEM_054a = 0;
                    /* WARNING: Subroutine does not return */
    FUN_CODE_adf3(0x53e);
  }
  if ((DAT_EXTMEM_0544 & 1) != 1) {
    while( true ) {
      FUN_CODE_5459();
      if (in_PSW < '\0') break;
      FUN_CODE_5693();
      FUN_CODE_53f3();
      FUN_CODE_5481();
    }
  }
                    /* WARNING: Subroutine does not return */
  thunk_FUN_CODE_adf3(0x53e);
}

