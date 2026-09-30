/* Address: 0004bbe2; name: FUN_0004bbe2; body bytes: 10 */

undefined4 FUN_0004bbe2(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  if (*(int *)(param_1 + 8) != 0) {
    uVar1 = *(undefined4 *)(*(int *)(param_1 + 8) + 4);
  }
  return uVar1;
}

