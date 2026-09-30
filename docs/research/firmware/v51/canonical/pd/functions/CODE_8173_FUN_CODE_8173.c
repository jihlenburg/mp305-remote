/* Address: CODE:8173; name: FUN_CODE_8173; body bytes: 61 */

void FUN_CODE_8173(char param_1)

{
  byte bVar1;
  undefined1 *puVar2;
  byte *pbVar3;
  
  if (DAT_INTMEM_ab == '\x12') {
    if ((DAT_INTMEM_ad & 0xe0) != 0x40) {
      return;
    }
    puVar2 = &DAT_EXTMEM_0754;
    bVar1 = DAT_INTMEM_ad;
    FUN_CODE_6221();
    pbVar3 = puVar2 + 1;
    if (*pbVar3 == bVar1) {
      FUN_CODE_6234(param_1 + '\x04');
      if (*pbVar3 == BANK0_R7) {
        return;
      }
      return;
    }
  }
  return;
}

