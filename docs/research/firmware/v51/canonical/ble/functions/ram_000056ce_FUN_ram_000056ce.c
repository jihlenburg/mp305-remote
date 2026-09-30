/* Address: ram:000056ce; name: FUN_ram_000056ce; body bytes: 48 */

/* WARNING: Removing unreachable block (ram,0x000056e8) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_ram_000056ce(undefined4 param_1,undefined4 param_2)

{
  uint uVar1;
  
  gp = &DAT_ram_20002000;
  uVar1 = (*_DAT_ram_00040038)();
                    /* WARNING: Could not recover jumptable at 0x000056fc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*_DAT_ram_00040170)(param_2,0,uVar1 % 1000000);
  return;
}

