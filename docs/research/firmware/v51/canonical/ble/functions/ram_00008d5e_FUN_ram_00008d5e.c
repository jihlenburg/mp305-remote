/* Address: ram:00008d5e; name: FUN_ram_00008d5e; body bytes: 48 */

undefined * FUN_ram_00008d5e(int param_1)

{
  undefined *puVar1;
  
  puVar1 = DAT_ram_20003010;
  gp = &DAT_ram_20002000;
  if (DAT_ram_20003010 != (undefined *)0x0) {
    DAT_ram_20003010 = DAT_ram_20003010 + param_1;
    return puVar1;
  }
  DAT_ram_20003010 = &DAT_ram_20006df0 + param_1;
  return &DAT_ram_20006df0;
}

