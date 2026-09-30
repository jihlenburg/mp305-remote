/* Address: 000177c4; name: FUN_000177c4; body bytes: 178 */

void FUN_000177c4(void)

{
  uint uVar1;
  undefined2 local_40;
  undefined2 local_3e;
  undefined2 local_36;
  undefined2 local_32;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 uStack_24;
  undefined2 local_18;
  short local_16;
  undefined4 local_14;
  
  FUN_0001540c(&local_40);
  local_36 = 0x40;
  local_40 = 1;
  local_32 = 0x1000;
  local_3e = 0;
  FUN_000152e0(7,1,&local_40);
  FUN_00014a54(&local_2c);
  local_2c = 0x80;
  local_28 = 0x30;
  uStack_24 = 0;
  FUN_000149e4(1,&local_2c);
  local_18 = 0;
  local_16 = 4;
  local_14 = 0x149c9;
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
  return;
}

