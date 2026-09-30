/* Address: ram:00068642; name: GAPRole_BroadcasterStartDevice; body bytes: 52 */

undefined4 GAPRole_BroadcasterStartDevice(int param_1)

{
  undefined4 uVar1;
  
  gp = 0x20004000;
  if (DAT_ram_20001f20 == 0) {
    if (param_1 != 0) {
      DAT_ram_20001a78 = param_1;
    }
    uVar1 = FUN_ram_000484e0(DAT_ram_200019cc,DAT_ram_20001f48,0,0,0,0);
    return uVar1;
  }
  return 0x11;
}

