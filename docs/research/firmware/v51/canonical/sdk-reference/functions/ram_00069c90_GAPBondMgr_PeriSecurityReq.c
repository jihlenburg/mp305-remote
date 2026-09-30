/* Address: ram:00069c90; name: GAPBondMgr_PeriSecurityReq; body bytes: 32 */

void GAPBondMgr_PeriSecurityReq(undefined4 param_1)

{
  gp = 0x20004000;
  DAT_ram_200019ca = DAT_ram_200019ca | 0x80;
  FUN_ram_00045036(param_1,DAT_ram_20001a98);
  return;
}

