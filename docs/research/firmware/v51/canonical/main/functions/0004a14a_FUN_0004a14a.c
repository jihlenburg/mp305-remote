/* Address: 0004a14a; name: FUN_0004a14a; body bytes: 8 */

undefined4 FUN_0004a14a(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  if (param_1 != 0) {
    uVar1 = *(undefined4 *)(param_1 + 8);
  }
  return uVar1;
}

