/* Address: 0003ed78; name: FUN_0003ed78; body bytes: 72 */

undefined4 FUN_0003ed78(int param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  
  if ((param_2 != 0xffff) && (param_2 <= *(uint *)(param_1 + 0x38))) {
    uVar4 = 0;
    iVar1 = 0;
    while (iVar3 = iVar1, uVar4 != param_2) {
      uVar4 = uVar4 + 1;
      iVar2 = thunk_FUN_00050a1a(*(undefined4 *)(*(int *)(param_1 + 0x2c) + (iVar3 + 1) * 4),
                                 &DAT_0003edc0);
      iVar1 = iVar3 + 1;
      if (iVar2 == 0) {
        iVar1 = iVar3 + 2;
      }
    }
    if (*(uint *)(param_1 + 0x38) != uVar4) {
      return *(undefined4 *)(*(int *)(param_1 + 0x2c) + iVar3 * 4);
    }
  }
  return 0;
}

