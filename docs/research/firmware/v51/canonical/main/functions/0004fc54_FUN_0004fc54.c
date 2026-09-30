/* Address: 0004fc54; name: FUN_0004fc54; body bytes: 124 */

void FUN_0004fc54(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_0004b9b2(&PTR_DAT_0007ae3c);
  if (iVar1 == 1) {
    iVar1 = FUN_00046688(param_2);
    iVar2 = FUN_00046698(param_2);
    if (iVar1 == 0x1a) {
      if (-1 < *(int *)(iVar2 + 0x48)) {
LAB_0004fc90:
        FUN_0005d8ec(iVar2);
        FUN_0005d148(iVar2);
        if ((*(byte *)(iVar2 + 0x4c) & 1) != 0) {
          FUN_0005d600();
          FUN_0005d2fc(iVar2,param_2);
          return;
        }
        FUN_0005d2fc(iVar2,param_2);
        FUN_0005d600(iVar2,param_2);
        return;
      }
    }
    else if (iVar1 == 0x1d) {
      if (*(int *)(iVar2 + 0x48) < 0) goto LAB_0004fc90;
    }
    else if (iVar1 == 0x18) {
      FUN_00046862(param_2,100);
      return;
    }
  }
  return;
}

