/* Address: ram:00069c04; name: FUN_ram_00069c04; body bytes: 46 */

void FUN_ram_00069c04(undefined4 param_1)

{
  gp = 0x20004000;
  DAT_ram_20001aac = param_1;
  GAP_SetParamValue(0x18,DAT_ram_20001a8e);
  FUN_ram_0004bd10(DAT_ram_20001a8e);
  return;
}

