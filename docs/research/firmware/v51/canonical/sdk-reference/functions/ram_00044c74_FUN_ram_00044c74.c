/* Address: ram:00044c74; name: FUN_ram_00044c74; body bytes: 84 */

undefined4 FUN_ram_00044c74(uint param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined2 local_20;
  undefined1 uStack_1e;
  undefined1 uStack_1d;
  
  gp = 0x20004000;
  iVar1 = FUN_ram_0004df14(param_2);
  if (iVar1 == 0) {
    uVar2 = 0x12;
  }
  else {
    uVar2 = 2;
    if (param_1 < 1000000) {
      tmos_memset(&local_20,0,0x10);
      local_20 = (undefined2)param_1;
      uStack_1e = (undefined1)(param_1 >> 0x10);
      uStack_1d = 0;
      uVar2 = FUN_ram_0004f032(&local_20,param_2);
    }
  }
  return uVar2;
}

