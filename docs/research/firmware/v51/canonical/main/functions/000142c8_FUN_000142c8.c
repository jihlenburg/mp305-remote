/* Address: 000142c8; name: FUN_000142c8; body bytes: 22 */

undefined4 FUN_000142c8(undefined2 *param_1)

{
  undefined4 uVar1;
  
  uVar1 = 0xfffffffd;
  if (param_1 != (undefined2 *)0x0) {
    *param_1 = 0;
    param_1[1] = 0;
    *(undefined1 *)(param_1 + 2) = 1;
    uVar1 = 0;
  }
  return uVar1;
}

