/* Address: ram:00069302; name: FUN_ram_00069302; body bytes: 78 */

void FUN_ram_00069302(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  
  gp = 0x20004000;
  iVar1 = FUN_ram_0004df14();
  if (iVar1 != 0) {
    iVar2 = DAT_ram_20001ab0;
    if (*(char *)(iVar1 + 0xc) == '\b') {
      iVar2 = DAT_ram_20001aac;
    }
    if ((iVar2 != 0) && (*(code **)(iVar2 + 4) != (code *)0x0)) {
                    /* WARNING: Could not recover jumptable at 0x0006933c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)(iVar2 + 4))(param_1,param_2,param_3);
      return;
    }
  }
  return;
}

