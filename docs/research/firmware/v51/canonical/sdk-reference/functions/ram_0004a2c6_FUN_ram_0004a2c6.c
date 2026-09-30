/* Address: ram:0004a2c6; name: FUN_ram_0004a2c6; body bytes: 46 */

int FUN_ram_0004a2c6(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  gp = 0x20004000;
  uVar1 = FUN_ram_0004a2ae(param_2);
  iVar2 = FUN_ram_0004df46(param_1,uVar1,1);
  if ((iVar2 == 5) || (iVar2 == 0xf)) {
    iVar2 = 8;
  }
  return iVar2;
}

