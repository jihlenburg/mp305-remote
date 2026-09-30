/* Address: 0003a6ba; name: FUN_0003a6ba; body bytes: 144 */

void FUN_0003a6ba(int param_1)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  
  if ((*(byte *)(param_1 + 0x3c) & 3) == 1) {
    uVar1 = *(uint *)(param_1 + 0x2c) / *(uint *)(param_1 + 0x38);
    uVar6 = (*(uint *)(param_1 + 0x38) >> 1) * uVar1 +
            (*(uint *)(param_1 + 0x30) - uVar1 * (*(uint *)(param_1 + 0x30) / uVar1));
    *(uint *)(param_1 + 0x30) = uVar6;
    *(uint *)(param_1 + 0x34) =
         (*(uint *)(param_1 + 0x38) >> 1) * uVar1 + (uVar6 - uVar1 * (uVar6 / uVar1));
    uVar2 = FUN_0004cb3a(param_1,0);
    iVar3 = FUN_0004cb82(param_1,0);
    iVar4 = FUN_00046bd6(uVar2);
    iVar5 = FUN_0004baf8(param_1);
    uVar2 = FUN_0003759c(param_1);
    FUN_0004eb3a(uVar2,(iVar5 / 2 - iVar4 / 2) - (iVar4 + iVar3) * *(int *)(param_1 + 0x30));
    return;
  }
  return;
}

