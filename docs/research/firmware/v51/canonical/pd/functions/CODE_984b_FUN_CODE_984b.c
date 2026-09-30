/* Address: CODE:984b; name: FUN_CODE_984b; body bytes: 25 */

/* Inferred entry from 4 raw LCALL encodings. Review control flow before relying on semantics. */

void FUN_CODE_984b(void)

{
  char cVar1;
  char in_PSW;
  
  FUN_CODE_a153();
  if (-1 < in_PSW) {
    cVar1 = 'P';
    FUN_CODE_a6a1();
    if (in_PSW < '\0') {
      FUN_CODE_9696();
      if (cVar1 == '\x01') goto LAB_CODE_985d;
    }
    FUN_CODE_8e0b();
    return;
  }
LAB_CODE_985d:
  FUN_CODE_91df();
  return;
}

