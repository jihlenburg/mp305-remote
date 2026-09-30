/* Address: 00040850; name: FUN_00040850; body bytes: 32 */

void FUN_00040850(int param_1,int param_2)

{
  int iVar1;
  
  if ((param_1 != 0) || (param_1 = DAT_2003a434, DAT_2003a434 != 0)) {
    if (param_2 == 0) {
      iVar1 = -1;
    }
    else {
      iVar1 = 1;
    }
    *(int *)(param_1 + 0x260) = iVar1 + *(int *)(param_1 + 0x260);
  }
  return;
}

