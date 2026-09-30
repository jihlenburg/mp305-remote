/* Address: 00056c2c; name: FUN_00056c2c; body bytes: 206 */

void FUN_00056c2c(uint param_1,undefined4 param_2)

{
  int iVar1;
  
  if ((DAT_1fffab03 == '\0') || (DAT_1fffaad6 == '\0')) {
    if ((DAT_1fffab04 != '\0') && (DAT_1fffaad7 != '\0')) {
      FUN_00050714(DAT_1ffe03d8,param_2);
      if ((int)param_1 < 0x13ed) {
        if ((int)param_1 < 0) {
          param_1 = 0;
        }
      }
      else {
        param_1 = 0x13ec;
      }
      DAT_1fffaae3 = (char)param_2;
      FUN_000507e6(DAT_1ffe03d8,param_1);
      FUN_0004b9de(DAT_1ffe0420,1);
      iVar1 = FUN_0004ccf8();
      FUN_0004eae2(DAT_1ffe0424,(int)(param_1 * (iVar1 + -4)) / 0x13ec);
      if ((int)((uint)DAT_1fffaae4 << 0x1e) < 0) goto LAB_00056cf0;
    }
  }
  else {
    FUN_00050714(DAT_1ffe03d8,param_2);
    if ((int)param_1 < 0xbeb) {
      if ((int)param_1 < 0) {
        param_1 = 0;
      }
    }
    else {
      param_1 = 0xbea;
    }
    DAT_1fffaae2 = (char)param_2;
    FUN_000507e6(DAT_1ffe03d8,param_1);
    FUN_0004b9de(DAT_1ffe0420,1);
    iVar1 = FUN_0004ccf8();
    FUN_0004eae2(DAT_1ffe0424,(int)(param_1 * (iVar1 + -4)) / 0xbea);
    if ((DAT_1fffaae4 & 1) != 0) {
LAB_00056cf0:
      FUN_0005833c(param_1 & 0xffff);
      return;
    }
  }
  return;
}

