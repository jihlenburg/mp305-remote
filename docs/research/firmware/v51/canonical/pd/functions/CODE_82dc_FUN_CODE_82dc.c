/* Address: CODE:82dc; name: FUN_CODE_82dc; body bytes: 59 */

undefined1 FUN_CODE_82dc(char *param_1,undefined1 param_2)

{
  if (((_1_4 == '\0') || (param_2 = DAT_INTMEM_b3, FUN_CODE_507b(), *param_1 == '\x02')) &&
     ((_1_4 == '\x01' || (param_2 = DAT_INTMEM_b3, FUN_CODE_5088(), *param_1 == '\x02')))) {
    _1_5 = 1;
    FUN_CODE_9cca();
  }
  else {
    FUN_CODE_9c91();
  }
  FUN_CODE_919d();
  DAT_EXTMEM_04ad = param_2;
  FUN_CODE_7c57();
  return DAT_EXTMEM_04ad;
}

