/* Address: ram:0004244a; name: tmos_stop_task; body bytes: 74 */

undefined4 tmos_stop_task(uint param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  gp = 0x20004000;
  iVar1 = FUN_ram_00041d8e();
  if (iVar1 != 0) {
    *(undefined2 *)(iVar1 + 2) = 0;
  }
  tmos_clear_event(param_1,param_2);
  if (DAT_ram_20001b64 == param_1) {
    DAT_ram_20001bb0 = (ushort)param_2 | DAT_ram_20001bb0;
  }
  uVar2 = 0;
  if (iVar1 == 0) {
    uVar2 = 6;
  }
  return uVar2;
}

