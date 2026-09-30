/* Address: CODE:908c; name: FUN_CODE_908c; body bytes: 28 */

void FUN_CODE_908c(undefined1 param_1,undefined1 param_2)

{
  short sVar1;
  
  sVar1 = CONCAT11(DAT_EXTMEM_0750,DAT_EXTMEM_0751);
  *(undefined1 *)(sVar1 + 2) = param_1;
  *(undefined1 *)(sVar1 + 3) = param_2;
                    /* WARNING: Subroutine does not return */
  thunk_FUN_CODE_adf3(0x4ba,BANK0_R7);
}

