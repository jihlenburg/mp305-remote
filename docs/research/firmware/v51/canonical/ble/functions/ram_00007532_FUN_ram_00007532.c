/* Address: ram:00007532; name: FUN_ram_00007532; body bytes: 54 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_ram_00007532(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                     undefined4 param_5)

{
  gp = &DAT_ram_20002000;
  (*_DAT_ram_0004004c)(&DAT_ram_20002e85,param_1,4,param_4,param_5,_DAT_ram_0004004c);
  FUN_ram_000074d2();
                    /* WARNING: Could not recover jumptable at 0x00007566. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*_DAT_ram_00040174)(0x306,0x1f,&DAT_ram_20002e78);
  return;
}

