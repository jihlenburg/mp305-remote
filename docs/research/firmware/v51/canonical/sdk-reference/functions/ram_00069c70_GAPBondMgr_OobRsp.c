/* Address: ram:00069c70; name: GAPBondMgr_OobRsp; body bytes: 32 */

undefined4 GAPBondMgr_OobRsp(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  gp = 0x20004000;
  if (param_2 == 0) {
    FUN_ram_0004f118(param_3,param_4,param_1);
  }
  else {
    FUN_ram_000450ea();
  }
  return 0;
}

