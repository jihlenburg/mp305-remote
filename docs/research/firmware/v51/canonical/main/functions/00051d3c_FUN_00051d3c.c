/* Address: 00051d3c; name: FUN_00051d3c; body bytes: 66 */

undefined4 FUN_00051d3c(int param_1,int *param_2,undefined4 param_3,int param_4)

{
  int iVar1;
  undefined4 uVar2;
  byte bVar3;
  int local_18;
  
  bVar3 = 0;
  *param_2 = *param_2 + -1;
  local_18 = param_4;
  while( true ) {
    iVar1 = FUN_00051d84(*param_2 + param_1);
    if (iVar1 == 0) {
      if (*param_2 == 0) {
        return 0;
      }
      *param_2 = *param_2 + -1;
    }
    bVar3 = bVar3 + 1;
    if (iVar1 != 0) break;
    if (3 < bVar3) {
      return 0;
    }
  }
  local_18 = *param_2;
  uVar2 = FUN_00051cb0(param_1,&local_18);
  return uVar2;
}

