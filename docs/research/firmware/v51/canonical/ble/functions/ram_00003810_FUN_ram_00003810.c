/* Address: ram:00003810; name: FUN_ram_00003810; body bytes: 62 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_ram_00003810(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                     undefined4 param_5)

{
  gp = &DAT_ram_20002000;
  (*_DAT_ram_0004004c)(&DAT_ram_20003e84,param_1,param_2,param_4,param_5,_DAT_ram_0004004c);
  DAT_ram_20003e80 = &vstvec;
  DAT_ram_20003e82 = (short)param_2;
  DAT_ram_20004088 = 1;
  return;
}

