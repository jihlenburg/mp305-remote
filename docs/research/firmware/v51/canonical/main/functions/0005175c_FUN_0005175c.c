/* Address: 0005175c; name: FUN_0005175c; body bytes: 226 */

int FUN_0005175c(char *param_1,int param_2,undefined4 param_3,int param_4,int *param_5,uint param_6)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  int local_30;
  int local_2c;
  
  if (param_5 != (int *)0x0) {
    *param_5 = 0;
  }
  if (((param_1 == (char *)0x0) || (*param_1 == '\0')) || (param_2 == 0)) {
    local_30 = 0;
  }
  else {
    iVar5 = 0;
    if ((param_6 & 3) == 0) {
      iVar6 = param_4;
      if ((param_6 & 1) != 0) {
        iVar6 = 0x1fffffff;
      }
      local_30 = 0;
      local_2c = param_4;
      do {
        if ((param_1[local_30] == '\0') || (iVar6 < 1)) goto LAB_00051810;
        uVar2 = param_6;
        if (local_30 == 0) {
          uVar2 = param_6 | 4;
        }
        local_2c = 0;
        iVar3 = FUN_00051844(param_1 + local_30,param_2,param_3,iVar6,uVar2,&local_2c);
        iVar6 = iVar6 - local_2c;
        iVar5 = iVar5 + local_2c;
        if (iVar3 == 0) goto LAB_00051810;
        local_30 = local_30 + iVar3;
        if ((*param_1 == '\n') || (*param_1 == '\r')) goto LAB_00051810;
      } while ((param_1[local_30] != '\n') && (param_1[local_30] != '\r'));
      local_30 = local_30 + 1;
LAB_00051810:
      if (local_30 == 0) {
        uVar4 = FUN_00051cb0(param_1,&local_30);
        if (param_5 == (int *)0x0) {
          return local_30;
        }
        iVar5 = FUN_00046b72(param_2,uVar4,0);
      }
      else if (param_5 == (int *)0x0) {
        return local_30;
      }
      *param_5 = iVar5;
    }
    else {
      for (local_30 = 0; (cVar1 = param_1[local_30], cVar1 != '\n' && (cVar1 != '\r'));
          local_30 = local_30 + 1) {
        if (cVar1 == '\0') goto LAB_000517a6;
      }
      local_30 = local_30 + 1;
LAB_000517a6:
      if (param_5 != (int *)0x0) {
        *param_5 = -1;
      }
    }
  }
  return local_30;
}

