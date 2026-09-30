/* Address: 0001bd22; name: FUN_0001bd22; body bytes: 18 */

undefined4 FUN_0001bd22(undefined4 *param_1)

{
  undefined4 uVar1;
  
  uVar1 = 0xfffffffd;
  if (param_1 != (undefined4 *)0x0) {
    uVar1 = 0;
    *param_1 = 0;
    param_1[1] = 0;
    param_1[2] = 0;
  }
  return uVar1;
}

