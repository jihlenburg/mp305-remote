/* Address: 0001de2c; name: FUN_0001de2c; body bytes: 28 */

undefined4 FUN_0001de2c(undefined4 *param_1)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  if (param_1 == (undefined4 *)0x0) {
    uVar1 = 0xfffffffd;
  }
  else {
    *param_1 = 0;
    param_1[1] = 0;
    param_1[2] = 0;
    *(undefined2 *)(param_1 + 3) = 0xffff;
  }
  return uVar1;
}

