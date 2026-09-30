/* Address: 000527f0; name: FUN_000527f0; body bytes: 54 */

void FUN_000527f0(int param_1,int param_2,undefined4 param_3)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  uVar1 = FUN_0004cd1e(param_2);
  uVar2 = FUN_0004cd44(param_2);
  *(int *)(param_1 + 0x2c) = param_2;
  FUN_0004e7d8(param_1,*(undefined1 *)(param_2 + 0x2c));
  FUN_0004e496(param_1,uVar1,uVar2,param_3);
  return;
}

