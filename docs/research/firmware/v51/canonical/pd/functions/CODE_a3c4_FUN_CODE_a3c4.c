/* Address: CODE:a3c4; name: FUN_CODE_a3c4; body bytes: 11 */

/* Inferred entry from 3 raw LCALL encodings. Review control flow before relying on semantics. */

void FUN_CODE_a3c4(char *param_1)

{
  char cVar1;
  
  cVar1 = FUN_CODE_83d4();
  cVar1 = FUN_CODE_83e7(cVar1 + '\a');
  *param_1 = cVar1 + '\x01';
  return;
}

