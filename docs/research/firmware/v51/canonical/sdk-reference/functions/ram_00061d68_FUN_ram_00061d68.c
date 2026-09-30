/* Address: ram:00061d68; name: FUN_ram_00061d68; body bytes: 108 */

undefined4 FUN_ram_00061d68(uint param_1)

{
  undefined4 uVar1;
  
  gp = 0x20004000;
  if (param_1 < 0x3d) {
    uVar1 = 5;
    if ((((((param_1 < 0x29) && (uVar1 = 4, param_1 < 0x1d)) && (uVar1 = 3, param_1 < 0x17)) &&
         ((uVar1 = 2, param_1 < 0x13 && (uVar1 = 1, param_1 < 0xf)))) &&
        ((uVar1 = 0, param_1 < 0xd &&
         ((uVar1 = 0xffffffff, param_1 < 0xb && (uVar1 = 0xfffffffd, param_1 < 9)))))) &&
       ((uVar1 = 0xfffffffb, param_1 < 7 &&
        ((uVar1 = 0xfffffff8, param_1 < 4 && (uVar1 = 0xfffffff0, 1 < param_1)))))) {
      uVar1 = 0xfffffff4;
    }
  }
  else {
    uVar1 = 6;
  }
  return uVar1;
}

