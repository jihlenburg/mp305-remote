/* Address: ram:000451b2; name: GAP_SetParamValue; body bytes: 108 */

undefined4 GAP_SetParamValue(uint param_1,uint param_2)

{
  undefined4 uVar1;
  
  gp = 0x20004000;
  if (param_1 < 0x40) {
    uVar1 = 2;
    if (param_2 != 0xffff) {
      if (param_1 == 0x11) {
        thunk_FUN_ram_0006577e(param_2);
      }
      else if (param_1 == 0x3a) {
        thunk_FUN_ram_0006599c(param_2);
      }
      else if (param_1 == 0x3b) {
        thunk_FUN_ram_0006517c(param_2 & 0xff);
      }
      (&DAT_ram_20001c24)[param_1] = (short)param_2;
      uVar1 = 0;
    }
    return uVar1;
  }
  return 2;
}

