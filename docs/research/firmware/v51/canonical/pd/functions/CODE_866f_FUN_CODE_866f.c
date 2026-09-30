/* Address: CODE:866f; name: FUN_CODE_866f; body bytes: 54 */

/* Inferred entry from 4 raw LCALL encodings. Review control flow before relying on semantics. */

void FUN_CODE_866f(void)

{
  char cVar1;
  char in_PSW;
  
  FUN_CODE_a403();
  FUN_CODE_5062(0xa4,4);
  cVar1 = DAT_EXTMEM_04a4;
  if (DAT_EXTMEM_04a4 == '\0') {
    cVar1 = DAT_EXTMEM_04a5;
  }
  if (cVar1 != '\0') {
    FUN_CODE_a335();
    if (in_PSW < '\0') {
      FUN_CODE_6ba4(DAT_EXTMEM_04a4,DAT_EXTMEM_04a5);
    }
    thunk_FUN_CODE_8832(DAT_EXTMEM_04a6,DAT_EXTMEM_04a7,DAT_EXTMEM_04a4,DAT_EXTMEM_04a5);
  }
  return;
}

