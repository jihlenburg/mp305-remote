/* Address: ram:00069c32; name: GAPBondMgr_PasscodeRsp; body bytes: 62 */

/* WARNING: Removing unreachable block (ram,0x00069c48) */

int GAPBondMgr_PasscodeRsp(undefined4 param_1,int param_2,uint param_3)

{
  int iVar1;
  
  gp = 0x20004000;
  if (param_2 == 0) {
    iVar1 = FUN_ram_00044c74(param_3 % 1000000,param_1);
    if (iVar1 != 0) {
      FUN_ram_000450ea(param_1,1);
    }
  }
  else {
    FUN_ram_000450ea();
    iVar1 = 0;
  }
  return iVar1;
}

