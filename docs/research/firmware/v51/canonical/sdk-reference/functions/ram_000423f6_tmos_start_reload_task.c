/* Address: ram:000423f6; name: tmos_start_reload_task; body bytes: 84 */

undefined4 tmos_start_reload_task(undefined4 param_1,undefined4 param_2,uint param_3)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  uint uVar4;
  
  gp = 0x20004000;
  tmos_start_task();
  iVar1 = FUN_ram_00041d8e(param_1,param_2);
  if (iVar1 == 0) {
    uVar3 = 8;
  }
  else {
    uVar4 = DAT_ram_20001b8c * param_3;
    uVar2 = uVar4 + 800;
    uVar3 = FUN_ram_0006bae2(uVar2,(int)((ulonglong)(uint)DAT_ram_20001b8c * (ulonglong)param_3 >>
                                        0x20) + (uint)(uVar2 < uVar4),0x640,0);
    *(undefined4 *)(iVar1 + 4) = uVar3;
    uVar3 = 0;
  }
  return uVar3;
}

