/* Address: 0006078c; name: FUN_0006078c; body bytes: 76 */

undefined4 FUN_0006078c(int *param_1,undefined1 param_2)

{
  byte bVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  
  bVar1 = *(byte *)(param_1 + 2);
  iVar6 = *param_1;
  if (bVar1 == 0xff) {
    for (iVar4 = 0; cVar2 = *(char *)(iVar6 + iVar4 * 8), cVar2 != '\0'; iVar4 = iVar4 + 1) {
      iVar3 = FUN_00050c04(cVar2,param_2);
      if (iVar3 != 0) {
        return 1;
      }
    }
  }
  else {
    for (uVar5 = 0; uVar5 < *(byte *)(param_1 + 2); uVar5 = uVar5 + 1) {
      iVar4 = FUN_00050c04(*(undefined1 *)(iVar6 + (uint)bVar1 * 4 + uVar5),param_2);
      if (iVar4 != 0) {
        return 1;
      }
    }
  }
  return 0;
}

