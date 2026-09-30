/* Address: 0005aa24; name: FUN_0005aa24; body bytes: 120 */

void FUN_0005aa24(undefined4 param_1,int param_2)

{
  bool bVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  
  if ((param_2 != 0) || (param_2 = FUN_00040928(DAT_2003a430), param_2 != 0)) {
    FUN_0005a7ac(param_1,param_2);
    while (iVar3 = FUN_0004bc8c(param_2), iVar3 != 0) {
      bVar1 = false;
      uVar2 = FUN_0004ba5c();
      for (uVar4 = 0; uVar4 < uVar2; uVar4 = uVar4 + 1) {
        if (bVar1) {
          FUN_0005a7ac(param_1);
        }
        else if (*(int *)(**(int **)(iVar3 + 8) + uVar4 * 4) == param_2) {
          bVar1 = true;
        }
      }
      FUN_0004e5a6(iVar3,0x1c,param_1);
      FUN_0004e5a6(iVar3,0x1d,param_1);
      FUN_0004e5a6(iVar3,0x1e,param_1);
      param_2 = iVar3;
    }
  }
  return;
}

