/* Address: CODE:8bc8; name: FUN_CODE_8bc8; body bytes: 43 */

void FUN_CODE_8bc8(void)

{
  byte *pbVar1;
  char cVar2;
  
  if ((DAT_INTMEM_d0 != '\x04') && (DAT_INTMEM_ce != DAT_INTMEM_d1)) {
    FUN_CODE_770c();
    cVar2 = DAT_INTMEM_ce;
    pbVar1 = (byte *)&DAT_INTMEM_ce;
    DAT_INTMEM_ce = DAT_INTMEM_ce + '\x01';
    FUN_CODE_76ec(cVar2);
    cVar2 = *pbVar1 + 0x10;
    if (0xef < *pbVar1) {
      cVar2 = '\0';
      *pbVar1 = 0;
    }
    DAT_INTMEM_d0 = 4;
    FUN_CODE_a449(cVar2);
    return;
  }
  return;
}

