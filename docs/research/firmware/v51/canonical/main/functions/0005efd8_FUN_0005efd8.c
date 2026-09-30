/* Address: 0005efd8; name: FUN_0005efd8; body bytes: 104 */

void FUN_0005efd8(void)

{
  undefined4 *puVar1;
  undefined1 auStack_78 [72];
  undefined4 local_30;
  undefined4 uStack_2c;
  undefined4 local_28;
  undefined4 uStack_24;
  undefined4 local_20;
  undefined4 uStack_1c;
  
  FUN_0001814c();
  if (DAT_1fffaafb == '\0') {
    uStack_2c = FUN_000375f8();
    local_20 = 0x53ed9;
    uStack_1c = 0x53cf5;
    local_28 = 0;
    uStack_24 = 0x2396d;
    local_30 = DAT_1ffe06b4;
    FUN_0001046a(auStack_78,&DAT_1fffbb28,0x48);
    puVar1 = &DAT_1fffbb18;
  }
  else {
    uStack_2c = FUN_00037604();
    local_20 = 0x53ed9;
    uStack_1c = 0x53cf5;
    local_28 = 0;
    uStack_24 = 0x23969;
    local_30 = DAT_1ffe06b4;
    FUN_0001046a(auStack_78,&DAT_1fffbad0,0x48);
    puVar1 = &DAT_1fffbac0;
  }
  FUN_00058430(*puVar1,puVar1[1],puVar1[2],puVar1[3]);
  return;
}

