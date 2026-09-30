/* Address: 0005eb4c; name: FUN_0005eb4c; body bytes: 138 */

void FUN_0005eb4c(void)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined1 auStack_78 [72];
  undefined4 local_30;
  undefined4 uStack_2c;
  undefined4 local_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 local_1c;
  
  FUN_0001814c();
  DAT_1fffaad3 = 1;
  FUN_0004eb0e(DAT_1ffe05a8,0);
  if (DAT_1fffaafb == '\0') {
    local_28 = FUN_000375f8();
    local_1c = 0x53975;
    uStack_24 = 0x2396d;
    uStack_20 = 0x53c95;
    local_30 = DAT_1ffe0330;
    uStack_2c = 0;
    FUN_0001046a(auStack_78,&DAT_1fffbb28,0x48);
    puVar1 = &DAT_1fffbb18;
  }
  else {
    local_28 = FUN_00037604();
    local_1c = 0x53975;
    uStack_24 = 0x23969;
    uStack_20 = 0x53c95;
    local_30 = DAT_1ffe0330;
    uStack_2c = 0;
    FUN_0001046a(auStack_78,&DAT_1fffbad0,0x48);
    puVar1 = &DAT_1fffbac0;
  }
  FUN_00058430(*puVar1,puVar1[1],puVar1[2],puVar1[3]);
  uVar2 = FUN_0004b9de(DAT_1ffe05b0,0);
  FUN_0004e4b2(uVar2,0);
  DAT_1ffe02b4 = 0;
  return;
}

