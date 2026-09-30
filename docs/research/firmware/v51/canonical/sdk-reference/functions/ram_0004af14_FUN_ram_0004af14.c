/* Address: ram:0004af14; name: FUN_ram_0004af14; body bytes: 86 */

undefined4 FUN_ram_0004af14(undefined4 param_1,byte param_2,undefined4 param_3)

{
  undefined4 uVar1;
  
  gp = 0x20004000;
  if ((param_2 & 0x20) != 0) {
    uVar1 = FUN_ram_0004a2c6(param_1,param_3);
    return uVar1;
  }
  if (((param_2 & 8) == 0) && (-1 < (char)param_2)) {
    uVar1 = 0;
    if ((param_2 & 2) == 0) {
      uVar1 = 3;
    }
    return uVar1;
  }
  uVar1 = FUN_ram_0004a2ae(param_3);
  uVar1 = FUN_ram_0004df46(param_1,uVar1,(param_2 & 8) != 0);
  return uVar1;
}

