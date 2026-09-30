/* Address: ram:00048602; name: FUN_ram_00048602; body bytes: 76 */

int FUN_ram_00048602(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 auStack_24 [4];
  
  gp = 0x20004000;
  iVar1 = FUN_ram_0004957c(param_1,auStack_24);
  if ((iVar1 == 0) && (iVar1 = FUN_ram_00043800(param_1,param_2), iVar1 == 0)) {
    FUN_ram_0004972e(auStack_24[0],0,0x13,&LAB_ram_000437f6,param_3);
  }
  return iVar1;
}

