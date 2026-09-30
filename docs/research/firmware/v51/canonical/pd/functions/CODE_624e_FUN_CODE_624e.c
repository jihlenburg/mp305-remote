/* Address: CODE:624e; name: FUN_CODE_624e; body bytes: 7 */

/* Inferred entry from 3 raw LCALL encodings. Review control flow before relying on semantics. */

char FUN_CODE_624e(char param_1)

{
  char in_PSW;
  
  return param_1 - (in_PSW >> 7);
}

