/* Address: 00050a74; name: FUN_00050a74; body bytes: 74 */

undefined4 FUN_00050a74(int *param_1,uint param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  
  uVar5 = (uint)*(byte *)(param_1 + 2);
  iVar2 = *param_1;
  if (uVar5 == 0xff) {
    iVar4 = 0;
    while (uVar5 = (uint)*(byte *)(iVar2 + iVar4 * 8), uVar5 != 0) {
      if (uVar5 == param_2) {
        uVar1 = *(undefined4 *)(iVar2 + iVar4 * 8 + 4);
        goto LAB_00050ab0;
      }
      iVar4 = iVar4 + 1;
    }
  }
  else {
    for (uVar3 = 0; uVar3 < uVar5; uVar3 = uVar3 + 1) {
      if (*(byte *)(iVar2 + uVar5 * 4 + uVar3) == param_2) {
        uVar1 = *(undefined4 *)(iVar2 + uVar3 * 4);
LAB_00050ab0:
        *param_3 = uVar1;
        return 1;
      }
    }
  }
  return 0;
}

