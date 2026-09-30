/* Address: CODE:6234; name: FUN_CODE_6234; body bytes: 7 */

/* Inferred entry from 6 raw LCALL encodings. Review control flow before relying on semantics. */

char FUN_CODE_6234(char param_1)

{
  char in_PSW;
  
  return param_1 - (in_PSW >> 7);
}

