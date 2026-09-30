/* Address: ram:00053848; name: FUN_ram_00053848; body bytes: 76 */

void FUN_ram_00053848(int param_1)

{
  code *UNRECOVERED_JUMPTABLE;
  int iVar1;
  
  gp = 0x20004000;
  DAT_ram_20001dd4 = 0;
  *(undefined1 *)(param_1 + 0xb) = 0x91;
  UNRECOVERED_JUMPTABLE = DAT_ram_20001e78;
  if (DAT_ram_20001e78 != (code *)0x0) {
    iVar1 = tmos_get_task_timer(DAT_ram_20001b67,1);
                    /* WARNING: Could not recover jumptable at 0x0005388a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (*UNRECOVERED_JUMPTABLE)(iVar1 * 0x271);
    return;
  }
  return;
}

