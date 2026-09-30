/* Address: 00050abe; name: FUN_00050abe; body bytes: 72 */

undefined4 FUN_00050abe(int *param_1,uint param_2,undefined4 *param_3)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  
  uVar5 = (uint)*(byte *)(param_1 + 2);
  iVar1 = *param_1;
  if (uVar5 == 0xff) {
    iVar4 = 0;
    while (uVar5 = (uint)*(byte *)(iVar1 + iVar4 * 8), uVar5 != 0) {
      if (uVar5 == param_2) {
        uVar2 = *(undefined4 *)(iVar1 + iVar4 * 8 + 4);
        goto LAB_00050af6;
      }
      iVar4 = iVar4 + 1;
    }
  }
  else {
    for (uVar3 = 0; uVar3 < uVar5; uVar3 = uVar3 + 1) {
      if (*(byte *)(iVar1 + uVar5 * 4 + uVar3) == param_2) {
        uVar2 = *(undefined4 *)(iVar1 + uVar3 * 4);
LAB_00050af6:
        *param_3 = uVar2;
        return 1;
      }
    }
  }
  return 0;
}

