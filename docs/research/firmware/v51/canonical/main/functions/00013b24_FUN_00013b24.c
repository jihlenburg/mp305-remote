/* Address: 00013b24; name: FUN_00013b24; body bytes: 54 */

undefined4 FUN_00013b24(undefined1 *param_1)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  if (param_1 == (undefined1 *)0x0) {
    uVar1 = 0xfffffffd;
  }
  else {
    *(undefined4 *)(param_1 + 4) = 0;
    param_1[5] = 0x13;
    *(uint *)(param_1 + 4) =
         (((*(uint *)(param_1 + 4) & 0xfffffff) + 0x10000000 & 0xf0ffffff) + 0x1000000 & 0xff0fffff)
         + 0x100000;
    *param_1 = 1;
  }
  return uVar1;
}

