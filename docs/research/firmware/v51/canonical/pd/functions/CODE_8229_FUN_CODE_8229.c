/* Address: CODE:8229; name: FUN_CODE_8229; body bytes: 60 */

/* Inferred entry from 8 raw LCALL encodings. Review control flow before relying on semantics. */

void FUN_CODE_8229(void)

{
  byte bVar1;
  byte in_PSW;
  byte bVar2;
  
  DAT_EXTMEM_203a = DAT_EXTMEM_203a & (&DAT_CODE_b900)[DAT_INTMEM_b3];
  DAT_EXTMEM_2038 = DAT_EXTMEM_2038 & (&DAT_CODE_b900)[DAT_INTMEM_b3];
  bVar2 = in_PSW & 0xdd;
  FUN_CODE_33d6();
  bVar1 = FUN_CODE_a94d(0x5f);
  bVar2 = bVar2 & 0xdd;
  FUN_CODE_a9ae(0x5f,bVar1 & 0x77);
  FUN_CODE_a335();
  if ((char)bVar2 < '\0') {
    FUN_CODE_9454();
    return;
  }
  FUN_CODE_9472();
  return;
}

