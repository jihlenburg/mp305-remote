/* Address: ram:0006aad0; name: GAPRole_ObserverCancelDiscovery; body bytes: 12 */

void GAPRole_ObserverCancelDiscovery(void)

{
  gp = 0x20004000;
  FUN_ram_00046806(DAT_ram_200019cc);
  return;
}

