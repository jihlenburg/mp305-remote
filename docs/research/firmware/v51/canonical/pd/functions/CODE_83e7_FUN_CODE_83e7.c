/* Address: CODE:83e7; name: FUN_CODE_83e7; body bytes: 8 */

/* Inferred entry from 3 raw LCALL encodings. Review control flow before relying on semantics. */

undefined1 FUN_CODE_83e7(undefined1 param_1,char param_2)

{
  char in_PSW;
  
  return *(undefined1 *)CONCAT11(param_2 - (in_PSW >> 7),param_1);
}

