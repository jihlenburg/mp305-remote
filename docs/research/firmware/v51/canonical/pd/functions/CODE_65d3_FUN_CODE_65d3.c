/* Address: CODE:65d3; name: FUN_CODE_65d3; body bytes: 83 */

void FUN_CODE_65d3(byte param_1,undefined1 param_2)

{
  undefined1 uVar1;
  char cVar2;
  undefined1 *puVar3;
  
  DAT_EXTMEM_04ac = param_2;
  FUN_CODE_ae2a(0x4ae);
  DAT_EXTMEM_04b1 = 0x80;
  DAT_EXTMEM_04ad = param_1;
  DAT_EXTMEM_04b2 = param_1;
  FUN_CODE_9f39();
  cVar2 = FUN_CODE_6255();
  if (cVar2 != '\x01') {
    return;
  }
  if (DAT_EXTMEM_04ad < 0x1b) {
                    /* WARNING: Subroutine does not return */
    FUN_CODE_adf3(0x4ae,DAT_EXTMEM_04b1,DAT_EXTMEM_04b2);
  }
  puVar3 = &DAT_EXTMEM_0754;
  uVar1 = DAT_EXTMEM_04ac;
  FUN_CODE_6221(DAT_EXTMEM_04ad);
  puVar3[1] = uVar1;
                    /* WARNING: Subroutine does not return */
  FUN_CODE_adf3(0x4ae);
}

