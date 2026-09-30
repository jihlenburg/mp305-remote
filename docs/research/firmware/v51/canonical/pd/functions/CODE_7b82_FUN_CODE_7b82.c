/* Address: CODE:7b82; name: FUN_CODE_7b82; body bytes: 72 */

void FUN_CODE_7b82(char param_1)

{
  FUN_CODE_9f29();
  DAT_EXTMEM_04a4 = FUN_CODE_6258(0x752);
  DAT_EXTMEM_04a5 = DAT_EXTMEM_04a4;
  FUN_CODE_9cb7();
  if (DAT_EXTMEM_04a4 != '\x01') {
    if (DAT_EXTMEM_04a4 == '\x02') {
      FUN_CODE_2ed4();
      DAT_EXTMEM_04a5 = param_1;
      goto LAB_CODE_7bc2;
    }
    if (DAT_EXTMEM_04a4 == '\x03') {
      FUN_CODE_a103();
      DAT_EXTMEM_04a5 = param_1;
      goto LAB_CODE_7bc2;
    }
    if (DAT_EXTMEM_04a4 == '\x04') {
      FUN_CODE_93db();
      DAT_EXTMEM_04a5 = param_1;
      goto LAB_CODE_7bc2;
    }
    if (DAT_EXTMEM_04a4 != '\0') goto LAB_CODE_7bc2;
    FUN_CODE_8ef3();
  }
  FUN_CODE_9c57();
  DAT_EXTMEM_04a5 = param_1;
LAB_CODE_7bc2:
  FUN_CODE_6c92(DAT_EXTMEM_04a5);
  return;
}

