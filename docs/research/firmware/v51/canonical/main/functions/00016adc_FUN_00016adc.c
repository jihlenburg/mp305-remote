/* Address: 00016adc; name: FUN_00016adc; body bytes: 26 */

undefined4 FUN_00016adc(undefined4 *param_1)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  if (param_1 == (undefined4 *)0x0) {
    uVar1 = 0xfffffffd;
  }
  else {
    param_1[1] = 50000;
    param_1[2] = 0;
    *param_1 = 0;
  }
  return uVar1;
}

