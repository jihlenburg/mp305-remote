/* Address: 0004e21c; name: FUN_0004e21c; body bytes: 58 */

void FUN_0004e21c(undefined4 param_1)

{
  int iVar1;
  uint uVar2;
  
  if (DAT_2003a444 != '\0') {
    iVar1 = 0;
    while (iVar1 = FUN_00040914(iVar1), iVar1 != 0) {
      for (uVar2 = 0; uVar2 < *(uint *)(iVar1 + 0x2d0); uVar2 = uVar2 + 1) {
        FUN_0005b22a(param_1,*(undefined4 *)(*(int *)(iVar1 + 0x2b4) + uVar2 * 4));
      }
    }
  }
  return;
}

