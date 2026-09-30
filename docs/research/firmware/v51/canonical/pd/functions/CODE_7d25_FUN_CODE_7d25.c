/* Address: CODE:7d25; name: FUN_CODE_7d25; body bytes: 68 */

void FUN_CODE_7d25(char param_1)

{
  byte bVar1;
  
  bVar1 = SADEN;
  SADEN = bVar1 & 0xf9;
  if (param_1 == '\x01') {
    DAT_EXTMEM_203a = DAT_EXTMEM_203a | 0x30;
    DAT_EXTMEM_203b = DAT_EXTMEM_203b | 0x40;
    DAT_EXTMEM_2038 = DAT_EXTMEM_2038 & 0xcf;
    DAT_EXTMEM_2039 = DAT_EXTMEM_2039 & 0xb3;
    DAT_EXTMEM_0764 = 0;
  }
  else if (param_1 == '\0') {
    DAT_EXTMEM_203a = DAT_EXTMEM_203a | 3;
    DAT_EXTMEM_203b = DAT_EXTMEM_203b | 3;
    FUN_CODE_a47b(0x2038);
    DAT_EXTMEM_0763 = 0;
  }
  bVar1 = SADEN;
  SADEN = bVar1 | 6;
  return;
}

