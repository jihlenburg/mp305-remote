/* Address: 0004f26c; name: FUN_0004f26c; body bytes: 20 */

void FUN_0004f26c(undefined4 *param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  uVar1 = *param_1;
  uVar2 = param_1[1];
  uVar3 = param_2[1];
  *param_1 = *param_2;
  param_1[1] = uVar3;
  *param_2 = uVar1;
  param_2[1] = uVar2;
  return;
}

