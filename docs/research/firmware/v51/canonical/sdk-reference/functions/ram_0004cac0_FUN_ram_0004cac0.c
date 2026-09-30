/* Address: ram:0004cac0; name: FUN_ram_0004cac0; body bytes: 94 */

undefined4 FUN_ram_0004cac0(short *param_1,short *param_2,uint param_3)

{
  short sVar1;
  undefined4 uVar2;
  
  gp = 0x20004000;
  if (param_3 < 2) {
    uVar2 = 1;
  }
  else {
    sVar1 = *param_2;
    *param_1 = sVar1;
    if (sVar1 == 1) {
      param_1[1] = param_2[1];
      return 0;
    }
    uVar2 = 0;
    if (sVar1 == 2) {
      param_1[1] = param_2[1];
      param_1[2] = param_2[2];
      return uVar2;
    }
  }
  return uVar2;
}

