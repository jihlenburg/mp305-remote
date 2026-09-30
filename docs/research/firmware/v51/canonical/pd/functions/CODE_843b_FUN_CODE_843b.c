/* Address: CODE:843b; name: FUN_CODE_843b; body bytes: 57 */

void FUN_CODE_843b(char param_1,char param_2)

{
  DAT_EXTMEM_04a3 = param_1;
  if (param_1 != param_2) {
    if (param_1 == '\x02') {
      FUN_CODE_666b(0x5f,7,1,0x4e);
    }
    else if (param_1 == '\x01') {
      FUN_CODE_10a6(0x80);
      FUN_CODE_a5eb();
      FUN_CODE_6aab();
      FUN_CODE_9544();
      FUN_CODE_6ffc(0x80);
    }
    DAT_EXTMEM_0760 = DAT_EXTMEM_04a3;
  }
  return;
}

