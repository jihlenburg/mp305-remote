/* Address: 00051c60; name: FUN_00051c60; body bytes: 36 */

int FUN_00051c60(undefined4 param_1,uint param_2)

{
  int iVar1;
  uint local_18;
  
  iVar1 = 0;
  local_18 = 0;
  while (local_18 < param_2) {
    FUN_00051cb0(param_1,&local_18);
    iVar1 = iVar1 + 1;
  }
  return iVar1;
}

