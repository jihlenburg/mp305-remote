/* Address: 0001540c; name: FUN_0001540c; body bytes: 36 */

undefined4 FUN_0001540c(undefined2 *param_1)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  if (param_1 == (undefined2 *)0x0) {
    uVar1 = 0xfffffffd;
  }
  else {
    *param_1 = 0;
    param_1[1] = 0;
    param_1[3] = 0;
    param_1[9] = 0;
    param_1[4] = 0;
    param_1[5] = 0;
    param_1[6] = 0;
    param_1[7] = 0;
    param_1[2] = 0;
    param_1[8] = 0;
  }
  return uVar1;
}

