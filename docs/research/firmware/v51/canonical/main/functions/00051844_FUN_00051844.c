/* Address: 00051844; name: FUN_00051844; body bytes: 284 */

int FUN_00051844(char *param_1,int param_2,int param_3,int param_4,uint param_5,int *param_6)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  int local_40;
  int local_3c [2];
  char *pcStack_34;
  int local_30;
  int local_2c;
  int local_28;
  
  if ((param_1 != (char *)0x0) && (*param_1 != '\0')) {
    if (param_2 == 0) {
      return 0;
    }
    local_28 = param_4;
    if ((param_5 & 1) != 0) {
      local_28 = 0x1fffffff;
    }
    local_40 = 0;
    local_3c[0] = 0;
    uVar9 = 0;
    iVar5 = 0;
    iVar8 = -1;
    pcStack_34 = param_1;
    local_30 = param_2;
    local_2c = param_3;
    uVar1 = FUN_00051cb0(param_1,&local_40);
    local_3c[0] = local_40;
    iVar4 = 0;
    iVar7 = 0;
    while (local_40 = local_3c[0], param_1[iVar4] != '\0') {
      uVar9 = FUN_00051cb0(param_1,local_3c);
      iVar6 = iVar7 + 1;
      iVar2 = FUN_00046b72(local_30,uVar1,uVar9);
      iVar5 = iVar5 + iVar2;
      if (0 < iVar2) {
        iVar5 = iVar5 + local_2c;
      }
      if ((iVar8 == -1) && (local_28 < iVar5 - local_2c)) {
        iVar8 = iVar4;
      }
      if ((uVar1 == 10) || (uVar1 == 0xd)) {
LAB_000518f4:
        if (((iVar4 == 0) && (iVar8 == -1)) && (param_6 != (int *)0x0)) {
          *param_6 = iVar5;
        }
        break;
      }
      for (uVar3 = 0; (&DAT_00051964)[uVar3] != '\0'; uVar3 = uVar3 + 1 & 0xff) {
        if ((byte)(&DAT_00051964)[uVar3] == uVar1) goto LAB_000518f4;
      }
      iVar4 = FUN_00051ad4(uVar9);
      iVar7 = iVar6;
      if ((iVar4 != 0) || (iVar4 = FUN_00051ad4(uVar1), iVar4 != 0)) {
        *param_6 = iVar5;
        iVar4 = local_40;
        break;
      }
      iVar4 = local_40;
      uVar1 = uVar9;
      if ((param_6 != (int *)0x0) && (iVar8 == -1)) {
        *param_6 = iVar5;
      }
    }
    if (iVar8 == -1) {
      if (iVar7 != 0) {
        if (uVar1 != 0xd) {
          return iVar4;
        }
        if (uVar9 != 10) {
          return iVar4;
        }
      }
      return local_40;
    }
    if ((int)(param_5 << 0x1d) < 0) {
      return iVar8;
    }
    if (param_6 != (int *)0x0) {
      *param_6 = 0;
    }
  }
  return 0;
}

