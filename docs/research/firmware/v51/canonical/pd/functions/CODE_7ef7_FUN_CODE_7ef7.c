/* Address: CODE:7ef7; name: FUN_CODE_7ef7; body bytes: 43 */

/* Inferred entry from 4 raw LCALL encodings. Review control flow before relying on semantics. */

void FUN_CODE_7ef7(undefined1 param_1,undefined1 param_2)

{
  undefined1 uVar1;
  undefined1 uVar2;
  
  DAT_EXTMEM_04a8 = param_2;
  DAT_EXTMEM_04a9 = param_1;
  FUN_CODE_9894();
  FUN_CODE_ae2a(0x4aa);
  uVar1 = DAT_EXTMEM_04a8;
  uVar2 = FUN_CODE_aa99(DAT_EXTMEM_04a8);
  FUN_CODE_ab49(uVar1,uVar2);
                    /* WARNING: Subroutine does not return */
  thunk_FUN_CODE_adf3(0x4aa,DAT_EXTMEM_04a9);
}

