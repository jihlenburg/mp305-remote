/* Address: 0001df1c; name: FUN_0001df1c; body bytes: 34 */

undefined4 FUN_0001df1c(undefined1 *param_1)

{
  undefined4 uVar1;
  
  uVar1 = 0xfffffffd;
  if (param_1 != (undefined1 *)0x0) {
    uVar1 = 0;
    *param_1 = 0;
    param_1[1] = 0;
    param_1[2] = 0;
    param_1[3] = 2;
    *(undefined2 *)(param_1 + 4) = 0;
    *(undefined2 *)(param_1 + 6) = 0;
    *(undefined4 *)(param_1 + 8) = 0xffff;
    param_1[0xc] = 0;
  }
  return uVar1;
}

