/* Address: 00050c48; name: FUN_00050c48; body bytes: 128 */

undefined4 FUN_00050c48(int *param_1,uint param_2)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  
  uVar2 = (uint)*(byte *)(param_1 + 2);
  if (uVar2 != 0xff) {
    if (uVar2 == 0) {
      return 0;
    }
    iVar7 = *param_1;
    iVar6 = iVar7 + uVar2 * 4;
    for (uVar4 = 0; uVar4 < uVar2; uVar4 = uVar4 + 1) {
      if (*(byte *)(iVar6 + uVar4) == param_2) {
        iVar3 = FUN_0004a318((uVar2 - 1) * 5);
        if (iVar3 == 0) {
          return 0;
        }
        *param_1 = iVar3;
        bVar1 = (char)param_1[2] - 1;
        *(byte *)(param_1 + 2) = bVar1;
        iVar5 = 0;
        for (uVar2 = 0; uVar2 <= *(byte *)(param_1 + 2); uVar2 = uVar2 + 1) {
          if (*(byte *)(iVar6 + uVar2) != param_2) {
            *(undefined4 *)(iVar3 + iVar5 * 4) = *(undefined4 *)(iVar7 + uVar2 * 4);
            *(undefined1 *)(iVar3 + (uint)bVar1 * 4 + iVar5) = *(undefined1 *)(iVar6 + uVar2);
            iVar5 = iVar5 + 1;
          }
        }
        FUN_00046bec(iVar7);
        return 1;
      }
    }
  }
  return 0;
}

