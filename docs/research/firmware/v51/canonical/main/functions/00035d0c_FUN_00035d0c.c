/* Address: 00035d0c; name: FUN_00035d0c; body bytes: 398 */

int FUN_00035d0c(int param_1,int param_2,int param_3,int param_4,int param_5)

{
  bool bVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  iVar3 = FUN_0004cd84(param_1,0x20,param_3,param_4,param_4);
  if (iVar3 == 0) {
    if (param_4 + param_2 < 0) {
      param_2 = -param_4;
    }
    if (param_3 - param_2 < 0) {
      param_2 = param_3;
    }
  }
  else {
    if (param_5 == 3) {
      iVar3 = FUN_0004bef4(param_1);
    }
    else {
      iVar3 = FUN_0004bf04();
    }
    bVar2 = false;
    bVar1 = false;
    if (iVar3 == 0) {
      if ((param_4 < 0) || (param_3 < 0)) {
        if (param_2 < 0) {
          param_2 = param_2 + -2;
        }
        if (0 < param_2) {
          param_2 = param_2 + 2;
        }
        param_2 = (int)(param_2 + ((uint)(param_2 >> 0x1f) >> 0x1e)) >> 2;
      }
    }
    else {
      iVar5 = 0;
      if (param_5 == 3) {
        if (iVar3 == 1) {
          iVar5 = FUN_0004c882(param_1,0);
          iVar5 = iVar5 + *(int *)(param_1 + 0x14);
        }
        else if (iVar3 == 2) {
          iVar5 = FUN_0004c8c4(param_1,0);
          iVar5 = *(int *)(param_1 + 0x1c) - iVar5;
        }
        else if (iVar3 == 3) {
          iVar5 = FUN_0004c882(param_1,0);
          iVar3 = FUN_0004c8c4(param_1,0);
          iVar6 = *(int *)(param_1 + 0x14);
          iVar4 = FUN_0003db28(param_1 + 0x14);
          iVar5 = iVar5 + iVar6 + ((iVar4 - iVar5) - iVar3) / 2;
        }
        iVar3 = FUN_00036328(param_1,iVar5 + 1,0x1fffffff,0);
        iVar5 = FUN_00036328(param_1,0xe0000001,iVar5,0);
      }
      else {
        if (iVar3 == 1) {
          iVar5 = FUN_0004c91e(param_1,0);
          iVar5 = iVar5 + *(int *)(param_1 + 0x18);
        }
        else if (iVar3 == 2) {
          iVar5 = FUN_0004c81c(param_1,0);
          iVar5 = *(int *)(param_1 + 0x20) - iVar5;
        }
        else if (iVar3 == 3) {
          iVar5 = FUN_0004c91e(param_1,0);
          iVar3 = FUN_0004c81c(param_1,0);
          iVar6 = *(int *)(param_1 + 0x18);
          iVar4 = FUN_0003db0a(param_1 + 0x14);
          iVar5 = iVar5 + iVar6 + ((iVar4 - iVar5) - iVar3) / 2;
        }
        iVar3 = FUN_0003642c(param_1,iVar5,0x1fffffff,0);
        iVar5 = FUN_0003642c(param_1,0xe0000001,iVar5,0);
      }
      bVar1 = iVar3 == 0x1fffffff;
      if (iVar5 == 0x1fffffff) {
        bVar2 = true;
      }
    }
    if (bVar2 || bVar1) {
      if (param_2 < 0) {
        param_2 = param_2 + -2;
      }
      if (0 < param_2) {
        param_2 = param_2 + 2;
      }
      param_2 = (int)(param_2 + ((uint)(param_2 >> 0x1f) >> 0x1e)) >> 2;
    }
  }
  return param_2;
}

