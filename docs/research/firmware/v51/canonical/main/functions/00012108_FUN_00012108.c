/* Address: 00012108; name: FUN_00012108; body bytes: 178 */

void FUN_00012108(void)

{
  uint uVar1;
  undefined4 local_28;
  undefined4 uStack_24;
  undefined4 local_20;
  undefined2 local_1c;
  undefined2 local_18;
  short local_16;
  undefined4 local_14;
  
  FUN_0001518c(0x1000);
  FUN_0001de2c(&local_28);
  local_28 = 0;
  uStack_24 = 0x60;
  local_20 = 0;
  local_1c = 0x753;
  FUN_0001ddd2(&DAT_40024000,0,&local_28);
  FUN_0001de0e(&DAT_40024000,4,1);
  local_18 = 0x60;
  local_16 = 6;
  local_14 = 0x1dda1;
  FUN_00016d4c(&local_18);
  uVar1 = (uint)local_16;
  if (-1 < (int)uVar1) {
    (&DAT_e000e280)[uVar1 >> 5] = 1 << (uVar1 & 0x1f);
  }
  uVar1 = (uint)local_16;
  if ((int)uVar1 < 0) {
    (&DAT_e000ed14)[uVar1 & 0xf] = 0xf0;
  }
  else {
    (&DAT_e000e400)[uVar1] = 0xf0;
  }
  uVar1 = (uint)local_16;
  if (-1 < (int)uVar1) {
    (&DAT_e000e100)[uVar1 >> 5] = 1 << (uVar1 & 0x1f);
  }
  FUN_0001de1e(&DAT_40024000,0);
  return;
}

