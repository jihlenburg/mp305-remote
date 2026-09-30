/* Address: ram:0006bab6; name: FUN_ram_0006bab6; body bytes: 44 */

undefined8 FUN_ram_0006bab6(uint param_1,uint param_2,uint param_3)

{
  uint uVar1;
  
  gp = 0x20004000;
  if (param_3 != 0) {
    if ((int)(0x20 - param_3) < 1) {
      param_2 = param_1 << (param_3 - 0x20 & 0x1f);
      param_1 = 0;
    }
    else {
      uVar1 = param_1 >> (0x20 - param_3 & 0x1f);
      param_1 = param_1 << (param_3 & 0x1f);
      param_2 = param_2 << (param_3 & 0x1f) | uVar1;
    }
  }
  return CONCAT44(param_2,param_1);
}

