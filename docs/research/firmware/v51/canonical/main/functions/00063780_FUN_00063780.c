/* Address: 00063780; name: FUN_00063780; body bytes: 74 */

void FUN_00063780(undefined4 *param_1)

{
  undefined1 uVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  
  param_1 = (undefined4 *)*param_1;
  uVar2 = param_1[2];
  uVar3 = FUN_0004c924(*param_1,uVar2 & 0xff0000,*(undefined1 *)(param_1 + 1));
  param_1[3] = uVar3;
  uVar1 = *(undefined1 *)(param_1 + 1);
  *(undefined1 *)(param_1 + 1) = 0;
  FUN_000637cc(*param_1,uVar2 & 0xff0000,uVar1,param_1);
  *(undefined1 *)(param_1 + 1) = uVar1;
  puVar4 = (undefined4 *)FUN_00037c5c(*param_1,param_1[2]);
  FUN_00050ef2(*puVar4,*(undefined1 *)(param_1 + 1),param_1[3]);
  FUN_0004dedc(*param_1,param_1[2],*(undefined1 *)(param_1 + 1));
  return;
}

