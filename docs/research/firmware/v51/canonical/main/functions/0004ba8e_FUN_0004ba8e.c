/* Address: 0004ba8e; name: FUN_0004ba8e; body bytes: 38 */

void FUN_0004ba8e(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  FUN_0003d9a4(param_2,param_1 + 0x14);
  if (*(int *)(param_1 + 8) != 0) {
    uVar1 = *(undefined4 *)(*(int *)(param_1 + 8) + 0x20);
    FUN_0003db32(param_2,uVar1,uVar1);
    return;
  }
  return;
}

