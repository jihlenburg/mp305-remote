/* Address: 00051c88; name: FUN_00051c88; body bytes: 34 */

int FUN_00051c88(int param_1)

{
  int iVar1;
  int local_18;
  
  iVar1 = 0;
  local_18 = 0;
  while (*(char *)(param_1 + local_18) != '\0') {
    FUN_00051cb0(param_1,&local_18);
    iVar1 = iVar1 + 1;
  }
  return iVar1;
}

