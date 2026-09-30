/* Address: ram:0004b654; name: FUN_ram_0004b654; body bytes: 104 */

int FUN_ram_0004b654(undefined4 param_1,uint param_2,undefined4 param_3)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  
  gp = 0x20004000;
  if ((param_2 & 0x10) != 0) {
    uVar1 = FUN_ram_0004a2ae(param_3);
    iVar2 = FUN_ram_0004df46(param_1,uVar1,1);
    if ((iVar2 == 5) || (iVar2 == 0xf)) {
      iVar2 = 8;
    }
    return iVar2;
  }
  if ((param_2 & 4) == 0) {
    if ((param_2 & 0x40) == 0) {
      gp = 0x20004000;
      return (uint)((param_2 & 1) == 0) << 1;
    }
    uVar3 = FUN_ram_0004a2ae(param_3);
    uVar1 = 0;
  }
  else {
    uVar3 = FUN_ram_0004a2ae(param_3);
    uVar1 = 1;
  }
  iVar2 = FUN_ram_0004df46(param_1,uVar3,uVar1);
  return iVar2;
}

