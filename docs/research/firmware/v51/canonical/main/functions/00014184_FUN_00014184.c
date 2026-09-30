/* Address: 00014184; name: FUN_00014184; body bytes: 108 */

void FUN_00014184(void)

{
  undefined1 auStack_28 [18];
  undefined2 local_16;
  undefined1 auStack_14 [2];
  undefined2 local_12;
  
  FUN_000151a4(0x10,1);
  FUN_0001540c(auStack_28);
  local_16 = 0x8000;
  FUN_000152e0(0,0x10,auStack_28);
  FUN_000152e0(0,0x20,auStack_28);
  FUN_000141f4(&DAT_40041000);
  FUN_000142c8(auStack_14);
  local_12 = 0;
  FUN_00014202(&DAT_40041000,0,auStack_14);
  FUN_00014202(&DAT_40041000,1,auStack_14);
  FUN_000142e0();
  FUN_000142be(&DAT_40041000);
  FUN_00014258(0);
  return;
}

