/* Address: ram:000424ee; name: tmos_get_task_timer; body bytes: 100 */

undefined4 tmos_get_task_timer(void)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  
  gp = 0x20004000;
  iVar2 = FUN_ram_00041d8e();
  if (iVar2 != 0) {
    uVar1 = *(uint *)(iVar2 + 8);
    uVar3 = (*DAT_ram_20001c00)();
    if ((-1 < DAT_ram_20001bd2) && (uVar1 < uVar3)) {
      uVar1 = uVar1 + 0xa8c00000;
    }
    uVar1 = uVar1 - uVar3;
    if (uVar1 < 0xa6f63c80) {
      uVar4 = FUN_ram_0006bae2(uVar1 * 0x640,(int)((ulonglong)uVar1 * 0x640 >> 0x20),
                               DAT_ram_20001b8c,0);
      gp = 0x20004000;
      return uVar4;
    }
  }
  return 0;
}

