/* Address: 00048264; name: FUN_00048264; body bytes: 10 */

undefined4 FUN_00048264(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  if (param_1 != 0) {
    uVar1 = *(undefined4 *)(param_1 + 0xa8);
  }
  return uVar1;
}

