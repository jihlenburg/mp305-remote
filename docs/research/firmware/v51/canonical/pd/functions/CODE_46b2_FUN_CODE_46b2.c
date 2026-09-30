/* Address: CODE:46b2; name: FUN_CODE_46b2; body bytes: 25 */

/* Inferred entry from 3 raw LCALL encodings. Review control flow before relying on semantics. */

byte FUN_CODE_46b2(void)

{
  byte bVar1;
  
  bVar1 = DAT_EXTMEM_04aa >> 7;
  FUN_CODE_acf0(0x1c,bVar1,bVar1,bVar1,DAT_EXTMEM_04aa);
  return bVar1 | 2;
}

