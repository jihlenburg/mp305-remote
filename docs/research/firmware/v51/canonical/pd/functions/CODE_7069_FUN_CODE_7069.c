/* Address: CODE:7069; name: FUN_CODE_7069; body bytes: 104 */

void FUN_CODE_7069(char *param_1,char param_2,byte param_3)

{
  byte bVar1;
  char cVar2;
  char cVar3;
  
  FUN_CODE_82b0();
  if (*param_1 != '\x01') {
    return;
  }
  FUN_CODE_a5f2();
  if (param_3 == 0 && param_2 == '\0') {
    DAT_EXTMEM_04a3 = param_2;
    DAT_EXTMEM_04a4 = param_3;
    return;
  }
  DAT_EXTMEM_04a3 = param_2;
  DAT_EXTMEM_04a4 = param_3;
  FUN_CODE_a12c();
  cVar3 = BANK0_R6;
  bVar1 = BANK0_R7;
  FUN_CODE_a9e2(0,10);
  DAT_EXTMEM_04a5 = param_2;
  DAT_EXTMEM_04a6 = param_3;
  if (*(char *)CONCAT11('\x04' - (((0xb8 < DAT_INTMEM_b3) << 7) >> 7),DAT_INTMEM_b3 + 0x47) == '\0')
  {
    cVar2 = '\0';
    FUN_CODE_82ca(cVar3 - (param_2 - (((bVar1 < param_3) << 7) >> 7)),bVar1 - param_3);
    if (cVar2 < '\0') {
      return;
    }
    cVar3 = -0x80;
    FUN_CODE_82ca(DAT_EXTMEM_04a6 + bVar1);
    if (-1 < cVar3) {
      return;
    }
  }
  FUN_CODE_a646(6);
  return;
}

