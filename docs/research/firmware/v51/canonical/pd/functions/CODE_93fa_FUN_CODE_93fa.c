/* Address: CODE:93fa; name: FUN_CODE_93fa; body bytes: 30 */

/* Inferred entry from 4 raw LCALL encodings. Review control flow before relying on semantics. */

void FUN_CODE_93fa(undefined1 param_1,undefined1 param_2,undefined1 param_3)

{
  DAT_EXTMEM_04ab = BANK0_R5;
  DAT_EXTMEM_04a8 = param_2;
  DAT_EXTMEM_04a9 = param_3;
  DAT_EXTMEM_04aa = param_1;
  FUN_CODE_448a(0xb2,0xa8,4,4);
  FUN_CODE_8faa();
  return;
}

