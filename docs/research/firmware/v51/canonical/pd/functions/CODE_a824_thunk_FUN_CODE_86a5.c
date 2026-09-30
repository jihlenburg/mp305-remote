/* Address: CODE:a824; name: thunk_FUN_CODE_86a5; body bytes: 3 */

void thunk_FUN_CODE_86a5(char param_1)

{
  char cVar1;
  
  FUN_CODE_ae2a(0x4ad);
  FUN_CODE_ab49(0xff);
  cVar1 = (param_1 == '\0') << 7;
  if (param_1 != '\0') {
                    /* WARNING: Subroutine does not return */
    thunk_FUN_CODE_adf3(param_1 + -1,0x4ad);
  }
  FUN_CODE_a335();
  if (cVar1 < '\0') {
                    /* WARNING: Subroutine does not return */
    thunk_FUN_CODE_adf3(0x4ad);
  }
                    /* WARNING: Subroutine does not return */
  thunk_FUN_CODE_adf3(0x4ad);
}

