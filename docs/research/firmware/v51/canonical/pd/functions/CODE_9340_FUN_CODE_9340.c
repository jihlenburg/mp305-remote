/* Address: CODE:9340; name: FUN_CODE_9340; body bytes: 31 */

/* Inferred entry from 5 raw LCALL encodings. Review control flow before relying on semantics. */

void FUN_CODE_9340(void)

{
  if (DAT_INTMEM_b3 == '\x01') {
    _1_0 = _1_4 & 1;
  }
  if (DAT_INTMEM_b3 == '\0') {
    _0_7 = _1_4 & 1;
  }
  if (_1_4 != 0) {
    FUN_CODE_87aa(4,0xb8,0xff);
  }
  return;
}

