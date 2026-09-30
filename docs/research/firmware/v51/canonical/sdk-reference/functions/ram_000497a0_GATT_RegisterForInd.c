/* Address: ram:000497a0; name: GATT_RegisterForInd; body bytes: 10 */

void GATT_RegisterForInd(undefined1 param_1)

{
  gp = 0x20004000;
  DAT_ram_20001a38 = param_1;
  return;
}

