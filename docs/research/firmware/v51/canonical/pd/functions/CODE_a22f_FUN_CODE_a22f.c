/* Address: CODE:a22f; name: FUN_CODE_a22f; body bytes: 12 */

/* Inferred entry from 7 raw LCALL encodings. Review control flow before relying on semantics. */

void FUN_CODE_a22f(undefined1 param_1)

{
  undefined1 uVar1;
  char *pcVar2;
  
  uVar1 = FUN_CODE_83d4();
  pcVar2 = (char *)(CONCAT11(param_1,uVar1) + 1);
  *pcVar2 = *pcVar2 + '\x01';
  return;
}

