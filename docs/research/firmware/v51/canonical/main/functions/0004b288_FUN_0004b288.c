/* Address: 0004b288; name: FUN_0004b288; body bytes: 92 */

void FUN_0004b288(int param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  
  FUN_0004d3d8();
  uVar1 = FUN_0004ba5c(param_1);
  while (iVar2 = FUN_0004bbba(param_1), iVar2 != 0) {
    FUN_000541d4();
  }
  FUN_0004e496(param_1,0,0);
  if (*(int *)(param_1 + 8) != 0) {
    *(undefined4 *)(*(int *)(param_1 + 8) + 0x18) = 0;
    *(undefined4 *)(*(int *)(param_1 + 8) + 0x1c) = 0;
  }
  uVar3 = FUN_0004ba5c(param_1);
  if (uVar3 < uVar1) {
    FUN_0004e5a6(param_1,0x27,0);
    FUN_0004e5a6(param_1,0x29,0);
    return;
  }
  return;
}

