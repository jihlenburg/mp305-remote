/* Address: ram:0006aa82; name: GAPRole_ObserverStartDevice; body bytes: 38 */

void GAPRole_ObserverStartDevice(int param_1)

{
  gp = 0x20004000;
  if (param_1 != 0) {
    DAT_ram_20001ab8 = param_1;
  }
  FUN_ram_000484e0(DAT_ram_200019cc,2,DAT_ram_20001ac0,0,0,0);
  return;
}

