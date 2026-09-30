/* Address: CODE:9000; name: FUN_CODE_9000; body bytes: 35 */

/* Inferred entry from 5 raw LCALL encodings. Review control flow before relying on semantics. */

void FUN_CODE_9000(char param_1)

{
  undefined1 *puVar1;
  
  puVar1 = &DAT_INTMEM_b3;
  DAT_INTMEM_b3 = BANK0_R7;
  FUN_CODE_a521();
  if (param_1 == '\x04') {
    FUN_CODE_1e48();
    *puVar1 = 2;
    return;
  }
  FUN_CODE_a521();
  if (param_1 == '\x03') {
    *(undefined1 *)(DAT_INTMEM_b3 + '#') = 1;
    return;
  }
  FUN_CODE_1e4f();
  return;
}

