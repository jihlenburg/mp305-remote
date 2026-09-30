/* Address: 0004b40e; name: FUN_0004b40e; body bytes: 28 */

void FUN_0004b40e(int *param_1)

{
  int iVar1;
  
  iVar1 = *param_1;
  while( true ) {
    if (*(code **)(iVar1 + 8) != (code *)0x0) {
      (**(code **)(iVar1 + 8))(iVar1,param_1);
    }
    iVar1 = *(int *)*param_1;
    if (iVar1 == 0) break;
    *param_1 = iVar1;
  }
  return;
}

