/* Address: ram:00061dd4; name: FUN_ram_00061dd4; body bytes: 102 */

undefined4 FUN_ram_00061dd4(int param_1)

{
  undefined4 uVar1;
  
  gp = 0x20004000;
  if (param_1 < -0xf) {
    uVar1 = 1;
  }
  else {
    uVar1 = 2;
    if ((((((-0xc < param_1) && (uVar1 = 4, -8 < param_1)) && (uVar1 = 7, -5 < param_1)) &&
         ((uVar1 = 9, -3 < param_1 && (uVar1 = 0xb, -1 < param_1)))) &&
        ((uVar1 = 0xd, param_1 != 0 && ((uVar1 = 0xf, param_1 != 1 && (uVar1 = 0x13, param_1 != 2)))
         ))) && ((uVar1 = 0x17, param_1 != 3 &&
                 ((uVar1 = 0x1d, param_1 != 4 && (uVar1 = 0x3d, param_1 == 5)))))) {
      uVar1 = 0x29;
    }
  }
  return uVar1;
}

