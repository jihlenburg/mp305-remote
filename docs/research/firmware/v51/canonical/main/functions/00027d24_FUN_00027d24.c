/* Address: 00027d24; name: FUN_00027d24; body bytes: 146 */

void FUN_00027d24(undefined4 param_1)

{
  undefined1 auStack_48 [4];
  undefined4 local_44;
  undefined4 local_3c;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 uStack_2c;
  undefined2 local_1c;
  undefined2 local_1a;
  undefined4 local_18;
  
  FUN_000151a4(0x4000000);
  FUN_0001f12c(auStack_48);
  local_44 = 1;
  local_30 = 0;
  uStack_2c = 0x8000;
  local_34 = 0;
  local_3c = param_1;
  FUN_0001f0e4(&DAT_40021000,auStack_48,0);
  FUN_000153b4(0,0x200,0x26);
  FUN_000153b4(0,0x400,0x27);
  local_1a = 0;
  local_1c = 0x186;
  local_18 = 0x1f02d;
  FUN_00016cb6(&local_1c,0xf);
  local_1a = 1;
  local_1c = 0x187;
  local_18 = 0x1f049;
  FUN_00016cb6(&local_1c,0xf);
  FUN_0001efd4(&DAT_40021000,0x2c,1);
  DAT_1ffe014c = 0;
  DAT_1ffe0148 = 0;
  FUN_0001049c(&DAT_1fff8a8c,0x200);
  return;
}

