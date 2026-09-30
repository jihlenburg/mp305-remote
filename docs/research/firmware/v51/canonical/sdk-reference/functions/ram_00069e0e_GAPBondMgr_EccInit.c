/* Address: ram:00069e0e; name: GAPBondMgr_EccInit; body bytes: 10 */

void GAPBondMgr_EccInit(undefined4 param_1)

{
  gp = 0x20004000;
  DAT_ram_20001f04 = param_1;
  return;
}

