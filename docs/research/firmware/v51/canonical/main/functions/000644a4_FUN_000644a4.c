/* Address: 000644a4; name: FUN_000644a4; body bytes: 326 */

void FUN_000644a4(void)

{
  int iVar1;
  undefined4 local_68;
  undefined4 local_64;
  undefined *local_60;
  undefined4 uStack_5c;
  undefined4 local_58;
  undefined4 uStack_54;
  undefined4 local_50;
  undefined4 uStack_4c;
  undefined1 auStack_48 [4];
  undefined4 local_44;
  undefined4 local_3c;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 uStack_2c;
  undefined2 local_1c;
  short local_1a;
  undefined4 local_18;
  undefined2 local_14;
  short local_12;
  undefined4 local_10;
  
  FUN_0001515c(0x4000);
  FUN_0001515c(0x20000);
  FUN_000145b8(&local_68);
  local_68 = 0x1000;
  local_60 = &DAT_4001cc04;
  uStack_5c = 0;
  local_64 = 0;
  local_58 = 1;
  uStack_54 = 0;
  local_50 = 1;
  uStack_4c = 0;
  iVar1 = FUN_00014558(&DAT_40053400,0,&local_68);
  if (iVar1 == 0) {
    local_14 = 0x40;
    local_12 = 0x12;
    local_10 = 0x1dfbd;
    FUN_00016d4c(&local_14);
    FUN_00020090((int)local_12);
    FUN_00020138((int)local_12,0xf);
    FUN_000200de((int)local_12);
    FUN_00012272(&DAT_40010834,0x12e);
    FUN_00014554(&DAT_40053400,1);
    FUN_000145da(&DAT_40053400,1);
  }
  FUN_000151a4(0x100000);
  FUN_0001f12c(auStack_48);
  local_44 = 3;
  local_3c = 0x1c200;
  local_30 = 0;
  uStack_2c = 0x8000;
  local_34 = 0;
  FUN_0001f0e4(&DAT_4001cc00,auStack_48,0);
  FUN_000153b4(3,0x200);
  FUN_000153b4(3,0x100,0x21);
  local_1a = 0x14;
  local_1c = 0x12f;
  local_18 = 0x1ef31;
  FUN_00016d4c(&local_1c);
  FUN_00020090((int)local_1a);
  FUN_00020138((int)local_1a,0xf);
  FUN_000200de((int)local_1a);
  local_1a = 0xe;
  local_1c = 300;
  local_18 = 0x1eef1;
  FUN_00016d1e(&local_1c,0xf);
  local_1a = 0xf;
  local_1c = 0x12d;
  local_18 = 0x1ef0d;
  FUN_00016d1e(&local_1c,0xf);
  FUN_0001efd4(&DAT_4001cc00,0x2c,1);
  return;
}

