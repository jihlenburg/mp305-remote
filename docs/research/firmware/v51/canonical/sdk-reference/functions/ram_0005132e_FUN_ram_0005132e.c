/* Address: ram:0005132e; name: FUN_ram_0005132e; body bytes: 144 */

undefined4 FUN_ram_0005132e(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  gp = 0x20004000;
  iVar1 = FUN_ram_20000040(0x30,0x53);
  if (iVar1 == 0) {
    uVar2 = 0x13;
  }
  else {
    tmos_memset(iVar1,0,0x30);
    FUN_ram_20000298(iVar1,param_1,0x10);
    FUN_ram_20000298(iVar1 + 0x1d,param_2,3);
    uVar2 = LL_Encrypt(iVar1,iVar1 + 0x10,iVar1 + 0x20);
    FUN_ram_20000298(param_3,iVar1 + 0x2d,3);
    FUN_ram_20000104(iVar1);
  }
  return uVar2;
}

