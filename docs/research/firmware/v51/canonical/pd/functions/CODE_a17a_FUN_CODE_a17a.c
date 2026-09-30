/* Address: CODE:a17a; name: FUN_CODE_a17a; body bytes: 13 */

/* Inferred entry from 3 raw LCALL encodings. Review control flow before relying on semantics. */

void FUN_CODE_a17a(void)

{
  if ((DAT_INTMEM_b7 >> 2 & 1) != 1) {
    FUN_CODE_7b82();
    return;
  }
  FUN_CODE_7def();
  return;
}

