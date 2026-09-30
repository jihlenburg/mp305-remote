/* Address: 0004877e; name: FUN_0004877e; body bytes: 50 */

int FUN_0004877e(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  if (param_1 == 0) {
    return 0;
  }
  if (param_2 == 3) {
    iVar2 = *(int *)(param_1 + 0x60);
  }
  else {
    if (param_2 != 0xc) {
      return 0;
    }
    iVar2 = *(int *)(param_1 + 100);
  }
  iVar1 = 0;
  for (; iVar2 != 0; iVar2 = (int)((100 - (uint)*(byte *)(param_1 + 0x25)) * iVar2) / 100) {
    iVar1 = iVar1 + iVar2;
  }
  return iVar1;
}

