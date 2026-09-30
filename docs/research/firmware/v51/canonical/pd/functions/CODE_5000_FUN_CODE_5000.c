/* Address: CODE:5000; name: FUN_CODE_5000; body bytes: 73 */

/* Inferred entry from 3 raw LCALL encodings. Review control flow before relying on semantics. */

void FUN_CODE_5000(byte param_1,undefined1 param_2,undefined1 param_3)

{
  undefined1 uVar1;
  undefined1 uVar2;
  byte bVar3;
  
  param_1 = param_1 | *(byte *)(CONCAT11(param_2,param_3) + 2) >> 2;
  uVar1 = BANK0_R6;
  FUN_CODE_aed0(0,0x32);
  bVar3 = *(byte *)(CONCAT11(DAT_EXTMEM_04b4,DAT_EXTMEM_04b5) + 2) & 3;
  uVar2 = *(undefined1 *)(CONCAT11(DAT_EXTMEM_04b4,DAT_EXTMEM_04b5) + 3);
  DAT_EXTMEM_04b6 = uVar1;
  DAT_EXTMEM_04b7 = param_1;
  FUN_CODE_aed0(0,10);
  DAT_EXTMEM_04b8 = bVar3;
  DAT_EXTMEM_04b9 = uVar2;
  return;
}

