/* Address: CODE:726d; name: FUN_CODE_726d; body bytes: 102 */

void FUN_CODE_726d(char param_1,char param_2)

{
  DAT_EXTMEM_04ad = param_1;
  if (param_1 != param_2) {
    FUN_CODE_97b3(0,param_1,0);
    if (DAT_EXTMEM_04ad == '\x02') {
      FUN_CODE_a6b5();
      FUN_CODE_9645();
      thunk_FUN_CODE_7bca(1);
    }
    else if (DAT_EXTMEM_04ad == '\x03') {
      FUN_CODE_1026();
      FUN_CODE_666b(DAT_INTMEM_b3 + 0x12,'\a' - (((0xed < DAT_INTMEM_b3) << 7) >> 7),1,0x4a);
    }
    else if (DAT_EXTMEM_04ad == '\x04') {
      FUN_CODE_9864();
      if ((DAT_EXTMEM_0af4 == '\0') && (DAT_EXTMEM_0af2 == '\0')) {
        FUN_CODE_84ad();
      }
    }
    else if (DAT_EXTMEM_04ad == '\x01') {
      FUN_CODE_8b72();
    }
    FUN_CODE_a52a(DAT_EXTMEM_04ad);
  }
  return;
}

