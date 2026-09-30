/* Address: 00035f5a; name: FUN_00035f5a; body bytes: 136 */

int FUN_00035f5a(int *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = FUN_00047eec();
  if (iVar1 != 0) {
    if ((int)((uint)*(byte *)(param_1 + 6) << 0x1e) < 0) {
      return 1;
    }
    if ((*(byte *)(param_1 + 6) & 1) != 0) {
      return 0;
    }
  }
  iVar1 = *(int *)(*param_1 + 8);
  if (iVar1 != 0) {
    iVar1 = iVar1 + 8;
  }
  iVar2 = FUN_000467fc(iVar1,param_1,1);
  if ((((iVar2 == 1) && (-1 < (int)((uint)*(byte *)(param_1 + 6) << 0x1e))) &&
      (iVar2 = FUN_0004b9b2(0,param_1), iVar2 == 1)) &&
     (-1 < (int)((uint)*(byte *)(param_1 + 6) << 0x1e))) {
    iVar1 = FUN_000467fc(iVar1,param_1,0);
    if (((iVar1 == 1) && (-1 < (int)((uint)*(byte *)(param_1 + 6) << 0x1e))) &&
       ((iVar2 = FUN_0004bc8c(*param_1), iVar2 != 0 && (iVar3 = FUN_00035f04(param_1), iVar3 != 0)))
       ) {
      *param_1 = iVar2;
      iVar1 = FUN_00035f5a(param_1);
    }
    return iVar1;
  }
  return iVar2;
}

