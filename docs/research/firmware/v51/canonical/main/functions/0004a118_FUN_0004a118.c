/* Address: 0004a118; name: FUN_0004a118; body bytes: 8 */

undefined4 FUN_0004a118(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  if (param_1 != 0) {
    uVar1 = *(undefined4 *)(param_1 + 4);
  }
  return uVar1;
}

