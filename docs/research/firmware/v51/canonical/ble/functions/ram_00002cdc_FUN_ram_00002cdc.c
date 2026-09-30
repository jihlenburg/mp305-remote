/* Address: ram:00002cdc; name: FUN_ram_00002cdc; body bytes: 88 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_ram_00002cdc(undefined4 param_1,undefined2 *param_2)

{
  code *UNRECOVERED_JUMPTABLE;
  uint uVar1;
  undefined4 uVar2;
  
  gp = &DAT_ram_20002000;
  uVar1 = (*_DAT_ram_0004013c)(param_1,&DAT_ram_20003224);
  UNRECOVERED_JUMPTABLE = _DAT_ram_000400d4;
  if ((uVar1 & 1) != 0) {
    *param_2 = DAT_ram_20002c6a;
                    /* WARNING: Could not recover jumptable at 0x00002d24. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar2 = (*UNRECOVERED_JUMPTABLE)(param_1,param_2,0);
    return uVar2;
  }
  return 0x12;
}

