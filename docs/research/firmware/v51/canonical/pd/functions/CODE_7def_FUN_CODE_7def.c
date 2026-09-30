/* Address: CODE:7def; name: FUN_CODE_7def; body bytes: 67 */

void FUN_CODE_7def(char param_1)

{
  FUN_CODE_9f39();
  DAT_EXTMEM_04a4 = FUN_CODE_6255();
  DAT_EXTMEM_04a5 = DAT_EXTMEM_04a4;
  FUN_CODE_9cb7();
  if (DAT_EXTMEM_04a4 != '\x01') {
    if (DAT_EXTMEM_04a4 == '\x04') {
      FUN_CODE_8de3();
      DAT_EXTMEM_04a5 = param_1;
      goto LAB_CODE_7e27;
    }
    if (DAT_EXTMEM_04a4 == '\x05') {
      FUN_CODE_8173();
      DAT_EXTMEM_04a5 = param_1;
      goto LAB_CODE_7e27;
    }
    if (DAT_EXTMEM_04a4 != '\0') goto LAB_CODE_7e27;
    FUN_CODE_8f19();
  }
  FUN_CODE_a277();
  DAT_EXTMEM_04a5 = param_1;
LAB_CODE_7e27:
  FUN_CODE_3800(DAT_EXTMEM_04a5,DAT_EXTMEM_04a4);
  return;
}

