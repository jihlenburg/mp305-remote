/* Address: 00013bc4; name: FUN_00013bc4; body bytes: 32 */

undefined4 FUN_00013bc4(undefined1 *param_1)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  if (param_1 == (undefined1 *)0x0) {
    uVar1 = 0xfffffffd;
  }
  else {
    *param_1 = 1;
    *(undefined4 *)(param_1 + 4) = 0x11101300;
  }
  return uVar1;
}

