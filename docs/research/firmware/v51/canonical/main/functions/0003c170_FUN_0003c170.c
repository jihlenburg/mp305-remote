/* Address: 0003c170; name: FUN_0003c170; body bytes: 204 */

void FUN_0003c170(void)

{
  uint uVar1;
  undefined4 local_38;
  undefined4 local_34;
  undefined *puStack_30;
  undefined4 local_2c;
  undefined4 uStack_28;
  undefined4 local_24;
  undefined4 uStack_20;
  undefined4 local_1c;
  undefined2 local_18;
  short local_16;
  undefined4 local_14;
  
  FUN_0001515c(0x20000);
  FUN_00012272(&DAT_40010814,0x137);
  FUN_0001515c(0x4000);
  FUN_000145b8(&local_38);
  local_38 = 0x1000;
  local_34 = 0;
  puStack_30 = &DAT_4001c000;
  local_2c = 0;
  uStack_28 = 1;
  local_24 = 0;
  uStack_20 = 1;
  local_1c = 0;
  FUN_00014558(&DAT_40053000,0,&local_38);
  local_18 = 0x20;
  local_16 = 5;
  local_14 = 0x3c355;
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
  FUN_000145da(&DAT_40053000,1);
  FUN_00014554(&DAT_40053000,1);
  return;
}

