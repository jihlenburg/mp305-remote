/* Address: CODE:979a; name: FUN_CODE_979a; body bytes: 25 */

/* Inferred entry from 3 raw LCALL encodings. Review control flow before relying on semantics. */

void FUN_CODE_979a(void)

{
  undefined1 uVar1;
  
  if ((DAT_INTMEM_cb >> 2 & 1) == 0) {
    if ((DAT_INTMEM_cb >> 3 & 1) == 0) {
      return;
    }
    uVar1 = 2;
  }
  else {
    uVar1 = 1;
  }
  FUN_CODE_7398(uVar1);
  return;
}

