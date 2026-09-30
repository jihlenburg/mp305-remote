/* Address: 00051ad4; name: FUN_00051ad4; body bytes: 82 */

undefined4 FUN_00051ad4(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  if (param_1 != 0) {
    if (((((0x51ff < param_1 - 0x4e00U) && (0x5d < param_1 - 0xff01U)) && (0x3f < param_1 - 0x3000U)
         ) && ((0x7f < param_1 - 0x2e80U && (0x2f < param_1 - 0x31c0U)))) &&
       ((0xbf < param_1 - 0x3040U && ((0xf < param_1 - 0xfe10U && (0x1f < param_1 - 0xfe30U)))))) {
      return 0;
    }
    uVar1 = 1;
  }
  return uVar1;
}

