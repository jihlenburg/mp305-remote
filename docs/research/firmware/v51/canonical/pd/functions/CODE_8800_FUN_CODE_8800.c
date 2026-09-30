/* Address: CODE:8800; name: FUN_CODE_8800; body bytes: 50 */

byte FUN_CODE_8800(undefined1 param_1,undefined1 param_2,undefined1 param_3)

{
  byte bVar1;
  undefined1 uVar2;
  undefined1 *puVar3;
  
  bVar1 = SADEN;
  DAT_EXTMEM_04c8 = bVar1 & 0x80;
  puVar3 = &DAT_EXTMEM_04c8;
  bVar1 = SADEN;
  SADEN = bVar1 & 0x7f;
  DAT_EXTMEM_04c7 = param_3;
  if (DAT_INTMEM_a4 < 0x20) {
    uVar2 = BANK0_R3;
    FUN_CODE_848e(DAT_INTMEM_a4 - 0x20);
    puVar3[1] = uVar2;
    FUN_CODE_8474(DAT_EXTMEM_04c7,CONCAT11(param_1,param_2) + 2);
  }
  bVar1 = SADEN;
  SADEN = bVar1 | DAT_EXTMEM_04c8;
  return DAT_EXTMEM_04c8;
}

