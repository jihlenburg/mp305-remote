/* Address: CODE:ad03; name: FUN_CODE_ad03; body bytes: 32 */

/* Inferred entry from 10 raw LCALL encodings. Review control flow before relying on semantics. */

void FUN_CODE_ad03(undefined1 param_1,char param_2)

{
  if (param_2 == '\x01') {
                    /* WARNING: Subroutine does not return */
    FUN_CODE_ad49(param_1);
  }
  if (param_2 == '\0') {
    FUN_CODE_ad3d(param_1);
    return;
  }
  if (param_2 == -2) {
    FUN_CODE_af29(param_1);
    return;
  }
  FUN_CODE_af35(param_1);
  return;
}

