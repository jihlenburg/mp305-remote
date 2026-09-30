/* Address: 000426e2; name: FUN_000426e2; body bytes: 168 */

undefined4 FUN_000426e2(int param_1,int param_2,int param_3,int param_4,int param_5)

{
  byte bVar1;
  undefined4 uVar2;
  int iVar3;
  
  param_3 = param_3 - *(int *)(param_5 + 0x20);
  param_2 = param_2 - *(int *)(param_5 + 0x1c);
  iVar3 = (uint)*(byte *)(param_5 + 0x34) << 0x1f;
  if (*(int *)(param_5 + 0x2c) != 0) {
    if (iVar3 != 0) {
      uVar2 = FUN_0003c468();
      return uVar2;
    }
    uVar2 = FUN_0003c5bc();
    return uVar2;
  }
  if (iVar3 != 0) {
    bVar1 = *(byte *)(param_5 + 0x18);
    if ((((bVar1 & 3) != 0) && ((bVar1 & 3) != 1)) && (((bVar1 & 3) != 2 || (-1 < param_3)))) {
      if ((~bVar1 & 3) != 0) {
        return 0;
      }
      if (param_3 < 1) {
        return 0;
      }
    }
    return 1;
  }
  bVar1 = *(byte *)(param_5 + 0x18);
  if ((bVar1 & 3) == 2) {
    return 1;
  }
  if ((~bVar1 & 3) != 0) {
    if (((bVar1 & 3) == 1) && (0 < param_2)) {
      return 1;
    }
    iVar3 = param_2 + param_4;
    if ((bVar1 & 3) == 0) {
      if (iVar3 < 0) {
        return 1;
      }
      iVar3 = -param_2;
      if (iVar3 < 0) {
        return 0;
      }
      if (param_4 <= iVar3) {
        return 2;
      }
      param_2 = param_4 + param_2;
      param_1 = param_1 + iVar3;
    }
    else {
      if (iVar3 < 0) {
        return 0;
      }
      param_2 = -param_2;
      if (param_2 < 0) {
        param_2 = 0;
        if (param_4 < 1) {
          return 0;
        }
      }
      else if (param_4 <= param_2) {
        return 0;
      }
      if (param_4 <= param_2) {
        return 2;
      }
    }
    FUN_0004a602(param_1,param_2,iVar3,param_4,param_4);
    return 2;
  }
  return 1;
}

