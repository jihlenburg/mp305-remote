/* Address: ram:00068676; name: GAPRole_BroadcasterSetCB; body bytes: 10 */

void GAPRole_BroadcasterSetCB(undefined4 param_1)

{
  gp = 0x20004000;
  DAT_ram_20001a78 = param_1;
  return;
}

