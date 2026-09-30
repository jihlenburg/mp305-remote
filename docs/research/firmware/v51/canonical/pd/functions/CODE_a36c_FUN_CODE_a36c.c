/* Address: CODE:a36c; name: FUN_CODE_a36c; body bytes: 11 */

/* Inferred entry from 4 raw LCALL encodings. Review control flow before relying on semantics. */

void FUN_CODE_a36c(byte *param_1,byte param_2)

{
  byte bVar1;
  
  bVar1 = FUN_CODE_3491();
  *param_1 = bVar1 & ~param_2;
  return;
}

