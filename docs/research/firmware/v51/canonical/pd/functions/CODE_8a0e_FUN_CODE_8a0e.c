/* Address: CODE:8a0e; name: FUN_CODE_8a0e; body bytes: 45 */

void FUN_CODE_8a0e(void)

{
  if (DAT_INTMEM_be != '\t') {
LAB_CODE_8a37:
    FUN_CODE_a521();
    return;
  }
  if (DAT_INTMEM_c0 == '\x02') {
    _1_4 = 1;
  }
  else {
    if (DAT_INTMEM_c0 != '\x04') {
      if (DAT_INTMEM_c0 == '\x05') {
LAB_CODE_8a2b:
        FUN_CODE_9e89();
        return;
      }
      if (DAT_INTMEM_c0 != '\v') {
        if (DAT_INTMEM_c0 != '\x03') goto LAB_CODE_8a37;
        goto LAB_CODE_8a2b;
      }
    }
    _1_4 = 0;
  }
  FUN_CODE_82dc();
  return;
}

