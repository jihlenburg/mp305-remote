/* Address: 000516ec; name: FUN_000516ec; body bytes: 60 */

void FUN_000516ec(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  
  if (param_1 != 0) {
    iVar1 = FUN_00050a64();
    uVar2 = FUN_00051c28(param_1,param_2);
    iVar3 = FUN_00051c28(param_1 + uVar2,param_3);
    for (; uVar2 <= (uint)(iVar1 - iVar3); uVar2 = uVar2 + 1) {
      *(undefined1 *)(param_1 + uVar2) = *(undefined1 *)(param_1 + uVar2 + iVar3);
    }
  }
  return;
}

