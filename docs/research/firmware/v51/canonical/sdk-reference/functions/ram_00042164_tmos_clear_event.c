/* Address: ram:00042164; name: tmos_clear_event; body bytes: 48 */

undefined4 tmos_clear_event(uint param_1,ushort param_2)

{
  ushort *puVar1;
  
  gp = 0x20004000;
  if (param_1 < DAT_ram_20001b65) {
    puVar1 = (ushort *)(DAT_ram_20001bb4 + param_1 * 2);
    *puVar1 = ~param_2 & *puVar1;
    return 0;
  }
  return 3;
}

