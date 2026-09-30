/* Address: 000402d2; name: FUN_000402d2; body bytes: 34 */

uint FUN_000402d2(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  uint uVar2;
  
  uVar1 = FUN_0004029c();
  uVar2 = FUN_000403d2(uVar1,param_1,param_2);
  return uVar2 & 0xffffff;
}

