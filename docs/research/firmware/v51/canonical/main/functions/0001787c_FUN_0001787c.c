/* Address: 0001787c; name: FUN_0001787c; body bytes: 358 */

void FUN_0001787c(void)

{
  int iVar1;
  undefined4 local_70;
  undefined4 local_6c;
  undefined *local_68;
  undefined4 uStack_64;
  undefined4 local_60;
  undefined4 uStack_5c;
  undefined4 local_58;
  undefined4 uStack_54;
  undefined1 auStack_50 [4];
  undefined4 local_4c;
  undefined4 local_44;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 uStack_34;
  undefined2 local_24;
  short local_22;
  undefined4 local_20;
  undefined2 local_1c;
  short local_1a;
  undefined4 local_18;
  
  DAT_1fff9bb5 = 0x41;
  DAT_1fff9bb6 = 0x8c;
  DAT_1fff9baa = 3000;
  DAT_1fff9bac = 0;
  DAT_1fff9bbe = 0;
  FUN_000644a4();
  FUN_0001515c(0x8000);
  FUN_0001515c(0x20000);
  FUN_000145b8(&local_70);
  local_70 = 0x1000;
  local_68 = &DAT_4001d404;
  uStack_64 = 0;
  local_6c = 0;
  local_60 = 1;
  uStack_5c = 0;
  local_58 = 1;
  uStack_54 = 0;
  iVar1 = FUN_00014558(&DAT_40053400,1,&local_70);
  if (iVar1 == 0) {
    local_1c = 0x41;
    local_1a = 0x13;
    local_18 = 0x1dfdd;
    FUN_00016d4c(&local_1c);
    FUN_00020090((int)local_1a);
    FUN_00020138((int)local_1a,0xf);
    FUN_000200de((int)local_1a);
    FUN_00012272(&DAT_40010838,0x14e);
    FUN_00014554(&DAT_40053400,1);
    FUN_000145da(&DAT_40053400,2,1);
  }
  FUN_000151a4(0x400000);
  FUN_0001f12c(auStack_50);
  local_4c = 3;
  local_3c = 0;
  local_38 = 0;
  uStack_34 = 0x8000;
  local_44 = 0x1c200;
  FUN_0001f0e4(&DAT_4001d400,auStack_50,0);
  FUN_000153b4(2,1,0x20);
  FUN_000153b4(2,2,0x21);
  local_22 = 0x15;
  local_24 = 0x14f;
  local_20 = 0x1ef81;
  FUN_00016d4c(&local_24);
  FUN_00020090((int)local_22);
  FUN_00020138((int)local_22,0xf);
  FUN_000200de((int)local_22);
  local_22 = 0x10;
  local_24 = 0x14c;
  local_20 = 0x1ef41;
  FUN_00016d1e(&local_24,0xf);
  local_22 = 0x11;
  local_24 = 0x14d;
  local_20 = 0x1ef5d;
  FUN_00016d1e(&local_24,0xf);
  FUN_0001efd4(&DAT_4001d400,0x24,1);
  return;
}

