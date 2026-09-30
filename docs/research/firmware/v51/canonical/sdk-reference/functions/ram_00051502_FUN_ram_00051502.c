/* Address: ram:00051502; name: FUN_ram_00051502; body bytes: 150 */

undefined4
FUN_ram_00051502(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  
  gp = 0x20004000;
  iVar1 = FUN_ram_20000040(0x30,0x53);
  if (iVar1 == 0) {
    uVar2 = 0x13;
  }
  else {
    FUN_ram_20000298(iVar1,param_1,0x10);
    FUN_ram_20000298(iVar1 + 0x10,param_2,8);
    FUN_ram_20000298(iVar1 + 0x18,param_3,8);
    uVar2 = LL_Encrypt(iVar1,iVar1 + 0x10,iVar1 + 0x20);
    FUN_ram_20000298(param_4,iVar1 + 0x20,0x10);
    FUN_ram_20000104(iVar1);
  }
  return uVar2;
}

