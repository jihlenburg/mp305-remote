/* Address: 0001dee4; name: FUN_0001dee4; body bytes: 30 */

undefined4 FUN_0001dee4(undefined4 *param_1)

{
  undefined4 uVar1;
  
  uVar1 = 0xfffffffd;
  if (param_1 != (undefined4 *)0x0) {
    *param_1 = 0xffff;
    *(undefined2 *)(param_1 + 1) = 1;
    *(undefined2 *)((int)param_1 + 6) = 0;
    *(undefined2 *)(param_1 + 2) = 3;
    *(undefined2 *)((int)param_1 + 10) = 3;
    uVar1 = 0;
  }
  return uVar1;
}

