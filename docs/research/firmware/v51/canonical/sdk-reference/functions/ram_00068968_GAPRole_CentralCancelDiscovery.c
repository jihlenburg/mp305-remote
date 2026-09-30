/* Address: ram:00068968; name: GAPRole_CentralCancelDiscovery; body bytes: 12 */

void GAPRole_CentralCancelDiscovery(void)

{
  gp = 0x20004000;
  FUN_ram_00046806(DAT_ram_20001a7c);
  return;
}

