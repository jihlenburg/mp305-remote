/* Address: CODE:8954; name: FUN_CODE_8954; body bytes: 47 */

/* Inferred entry from 4 raw LCALL encodings. Review control flow before relying on semantics. */

void FUN_CODE_8954(void)

{
  char cVar1;
  
  _1_5 = _1_4 & 1;
  FUN_CODE_9ec9();
  cVar1 = '\0';
  if (_1_4 == 0) {
    FUN_CODE_90d1(2);
  }
  else {
    FUN_CODE_9a23();
  }
  FUN_CODE_a6c7();
  if (DAT_EXTMEM_04c7 != cVar1) {
    FUN_CODE_9a23(1,0);
  }
  FUN_CODE_a812(DAT_EXTMEM_04c7);
  return;
}

