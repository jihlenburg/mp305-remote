/* Address: CODE:919d; name: FUN_CODE_919d; body bytes: 33 */

void FUN_CODE_919d(void)

{
  char cVar1;
  char in_PSW;
  
  cVar1 = DAT_INTMEM_b3;
  FUN_CODE_a139();
  if (in_PSW < '\0') {
    FUN_CODE_a6fd();
    if (cVar1 == '\0') {
      FUN_CODE_a533();
      return;
    }
    FUN_CODE_a6fd();
    if (cVar1 == '\x01') {
      return;
    }
  }
  return;
}

