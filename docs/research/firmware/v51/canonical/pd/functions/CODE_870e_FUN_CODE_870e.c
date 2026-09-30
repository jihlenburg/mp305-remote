/* Address: CODE:870e; name: FUN_CODE_870e; body bytes: 52 */

void FUN_CODE_870e(char param_1)

{
  byte in_PSW;
  byte bVar1;
  undefined1 *puVar2;
  
  bVar1 = in_PSW & 0xdd;
  DAT_EXTMEM_04a9 = BANK0_R5 & 0xf | param_1 << 4;
  puVar2 = &DAT_EXTMEM_04a9;
  FUN_CODE_a085();
  FUN_CODE_7f77(3,*puVar2,BANK0_R2,BANK0_R1);
  if ((char)bVar1 < '\0') {
    DAT_INTMEM_a7 = DAT_EXTMEM_04a9;
    DAT_INTMEM_a9 = BANK0_R7;
    FUN_CODE_a638(1,1);
  }
  return;
}

