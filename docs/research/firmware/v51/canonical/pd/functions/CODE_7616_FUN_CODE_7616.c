/* Address: CODE:7616; name: FUN_CODE_7616; body bytes: 85 */

/* Inferred entry from 9 raw LCALL encodings. Review control flow before relying on semantics. */

void FUN_CODE_7616(void)

{
  char cVar1;
  undefined1 uVar2;
  byte bVar3;
  
  DAT_EXTMEM_04ac = DAT_INTMEM_c9;
  if (_1_4 == '\0') {
    _1_1 = 0;
    DAT_INTMEM_c9 = (&DAT_CODE_b831)[DAT_INTMEM_b3] & DAT_INTMEM_c9;
  }
  else {
    bVar3 = DAT_INTMEM_c9;
    DAT_INTMEM_c9 = (&DAT_CODE_b831)[DAT_INTMEM_b3] & DAT_INTMEM_c9;
    FUN_CODE_a6fd();
    bVar3 = (&DAT_CODE_b835)[bVar3];
    cVar1 = DAT_INTMEM_b3 + 1;
    while (cVar1 = cVar1 + -1, cVar1 != '\0') {
      bVar3 = bVar3 << 1;
    }
    DAT_INTMEM_c9 = bVar3 | DAT_INTMEM_c9;
    FUN_CODE_1006(DAT_INTMEM_b3);
  }
  if (_1_4 == '\0') {
    uVar2 = 0xe1;
  }
  else {
    uVar2 = 0xda;
  }
  FUN_CODE_87aa(uVar2,0xb7,0xff);
  return;
}

