/* Address: CODE:1d8d; name: FUN_CODE_1d8d; body bytes: 11 */

/* Inferred entry from 10 raw LCALL encodings. Review control flow before relying on semantics. */

void FUN_CODE_1d8d(short param_1,undefined1 *param_2)

{
  *(undefined1 *)(param_1 + 1) = *param_2;
  *(undefined1 *)(param_1 + 2) = param_2['\x01'];
  return;
}

