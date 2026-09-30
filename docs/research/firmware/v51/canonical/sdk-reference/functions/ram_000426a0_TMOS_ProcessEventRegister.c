/* Address: ram:000426a0; name: TMOS_ProcessEventRegister; body bytes: 54 */

uint TMOS_ProcessEventRegister(undefined4 param_1)

{
  uint uVar1;
  
  gp = 0x20004000;
  uVar1 = (uint)DAT_ram_20001b65;
  if (uVar1 < DAT_ram_20001b66) {
    DAT_ram_20001b65 = DAT_ram_20001b65 + 1;
    *(undefined4 *)(uVar1 * 4 + DAT_ram_20001b90) = param_1;
  }
  else {
    uVar1 = 0xff;
  }
  return uVar1;
}

