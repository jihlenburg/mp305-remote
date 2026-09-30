/* Address: ram:0004ae74; name: FUN_ram_0004ae74; body bytes: 106 */

int FUN_ram_0004ae74(undefined4 param_1,byte param_2,undefined4 param_3,int param_4)

{
  int iVar1;
  undefined4 uVar2;
  
  gp = 0x20004000;
  if ((param_2 & 0x20) != 0) {
    iVar1 = FUN_ram_0004a2c6(param_1,param_3);
    return iVar1;
  }
  if (((param_2 & 8) == 0) && (-1 < (char)param_2)) {
    if ((param_2 & 2) == 0) {
      gp = 0x20004000;
      return 3;
    }
  }
  else {
    uVar2 = FUN_ram_0004a2ae(param_3);
    iVar1 = FUN_ram_0004df46(param_1,uVar2,(param_2 & 8) != 0);
    if (iVar1 != 0) {
      if (*(char *)(param_4 + 9) == '\0') {
        gp = 0x20004000;
        return iVar1;
      }
      if (*(char *)(param_4 + 8) == '\0') {
        gp = 0x20004000;
        return iVar1;
      }
    }
  }
  return 0;
}

