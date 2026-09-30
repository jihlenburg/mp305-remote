/* Address: ram:00044406; name: FUN_ram_00044406; body bytes: 76 */

undefined4 FUN_ram_00044406(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  code *UNRECOVERED_JUMPTABLE;
  int iVar1;
  undefined4 uVar2;
  
  gp = 0x20004000;
  iVar1 = FUN_ram_0004e132();
  if (iVar1 == 4) {
    if (DAT_ram_200019f4 == (undefined4 *)0x0) {
      gp = 0x20004000;
      return 1;
    }
    UNRECOVERED_JUMPTABLE = (code *)*DAT_ram_200019f4;
  }
  else {
    if (DAT_ram_200019ec == 0) {
      gp = 0x20004000;
      return 1;
    }
    UNRECOVERED_JUMPTABLE = *(code **)(DAT_ram_200019ec + 4);
  }
  if (UNRECOVERED_JUMPTABLE == (code *)0x0) {
    return 1;
  }
                    /* WARNING: Could not recover jumptable at 0x00044436. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  uVar2 = (*UNRECOVERED_JUMPTABLE)(param_2,param_3);
  return uVar2;
}

