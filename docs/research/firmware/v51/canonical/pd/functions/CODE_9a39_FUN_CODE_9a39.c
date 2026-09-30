/* Address: CODE:9a39; name: FUN_CODE_9a39; body bytes: 22 */

/* Inferred entry from 5 raw LCALL encodings. Review control flow before relying on semantics. */

void FUN_CODE_9a39(void)

{
  undefined1 uVar1;
  
  if ((DAT_INTMEM_cb >> 2 & 1) == 1) {
    if ((DAT_INTMEM_cb >> 3 & 1) == 1) {
      return;
    }
    uVar1 = 2;
  }
  else {
    uVar1 = 1;
  }
  FUN_CODE_578c(uVar1);
  return;
}

