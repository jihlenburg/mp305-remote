/* Address: CODE:8ef3; name: FUN_CODE_8ef3; body bytes: 38 */

void FUN_CODE_8ef3(undefined1 param_1,char param_2)

{
  undefined1 uVar1;
  undefined1 *puVar2;
  
  FUN_CODE_9f29();
  puVar2 = (undefined1 *)(CONCAT11(param_1,param_2) + 1);
  *puVar2 = 0;
  FUN_CODE_6215(param_2);
  *puVar2 = 0;
  puVar2 = puVar2 + 1;
  *puVar2 = 0;
  uVar1 = FUN_CODE_629e();
  puVar2 = puVar2 + 1;
  *puVar2 = uVar1;
  FUN_CODE_6217(param_2 + '\x04');
  *puVar2 = 0;
  *(undefined1 *)CONCAT11(param_1,param_2) = 1;
  return;
}

