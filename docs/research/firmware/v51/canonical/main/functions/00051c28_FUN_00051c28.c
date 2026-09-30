/* Address: 00051c28; name: FUN_00051c28; body bytes: 50 */

int FUN_00051c28(int param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  uVar3 = 0;
  for (iVar2 = 0; (uVar3 < param_2 && (*(char *)(param_1 + iVar2) != '\0')); iVar2 = iVar2 + iVar1)
  {
    iVar1 = FUN_00051d84(param_1 + iVar2);
    if (iVar1 == 0) {
      iVar1 = 1;
    }
    uVar3 = uVar3 + 1;
  }
  return iVar2;
}

