/* Address: 0003dc3a; name: FUN_0003dc3a; body bytes: 126 */

undefined4 FUN_0003dc3a(int *param_1,int *param_2,int param_3)

{
  int iVar1;
  int local_18;
  int iStack_14;
  
  if ((((*param_2 <= param_1[2]) && (param_2[1] <= param_1[3])) &&
      (local_18 = *param_1, local_18 <= param_2[2])) &&
     (iStack_14 = param_1[1], iStack_14 <= param_2[3])) {
    if ((param_3 != 0) && (iVar1 = FUN_0003dcb8(param_2,&local_18,param_3), iVar1 == 0)) {
      iStack_14 = param_1[1];
      local_18 = param_1[2];
      iVar1 = FUN_0003dcb8(param_2,&local_18,param_3);
      if (iVar1 == 0) {
        iStack_14 = param_1[3];
        local_18 = *param_1;
        iVar1 = FUN_0003dcb8(param_2,&local_18,param_3);
        if (iVar1 == 0) {
          local_18 = param_1[2];
          iStack_14 = param_1[3];
          iVar1 = FUN_0003dcb8(param_2,&local_18,param_3);
          if (iVar1 == 0) {
            return 1;
          }
        }
      }
    }
    return 0;
  }
  return 1;
}

