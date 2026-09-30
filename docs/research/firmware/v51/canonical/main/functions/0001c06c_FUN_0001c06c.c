/* Address: 0001c06c; name: FUN_0001c06c; body bytes: 38 */

undefined4 FUN_0001c06c(undefined4 *param_1)

{
  undefined4 uVar1;
  
  uVar1 = 0xfffffffd;
  if (param_1 != (undefined4 *)0x0) {
    uVar1 = 0;
    *param_1 = 0;
    param_1[1] = 0;
    param_1[2] = 8;
    param_1[3] = 0;
    param_1[4] = 0;
    param_1[5] = 0;
    param_1[6] = 8;
    param_1[7] = 0x400;
    param_1[8] = 0;
    param_1[9] = 0;
    param_1[10] = 0;
  }
  return uVar1;
}

