/* Address: 00012260; name: FUN_00012260; body bytes: 18 */

undefined4 FUN_00012260(undefined2 *param_1)

{
  undefined4 uVar1;
  
  uVar1 = 0xfffffffd;
  if (param_1 != (undefined2 *)0x0) {
    uVar1 = 0;
    *param_1 = 0;
    param_1[1] = 0;
    param_1[2] = 0;
  }
  return uVar1;
}

