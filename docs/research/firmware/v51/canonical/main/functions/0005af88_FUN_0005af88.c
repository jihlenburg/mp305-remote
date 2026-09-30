/* Address: 0005af88; name: FUN_0005af88; body bytes: 132 */

void FUN_0005af88(void)

{
  undefined4 *puVar1;
  undefined1 auStack_80 [72];
  undefined4 local_38;
  undefined4 uStack_34;
  undefined4 local_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  
  remote_granted = 1;
  if (DAT_1fffaafb == '\0') {
    local_30 = FUN_000375f8();
    uStack_2c = 0x2396d;
    uStack_28 = 0x53c95;
    uStack_24 = 0x53975;
    local_38 = DAT_1ffe0330;
    uStack_34 = 0;
    FUN_0001046a(auStack_80,&DAT_1fffbb28,0x48);
    puVar1 = &DAT_1fffbb18;
  }
  else {
    local_30 = FUN_00037604();
    uStack_2c = 0x23969;
    uStack_28 = 0x53c95;
    uStack_24 = 0x53975;
    local_38 = DAT_1ffe0330;
    uStack_34 = 0;
    FUN_0001046a(auStack_80,&DAT_1fffbad0,0x48);
    puVar1 = &DAT_1fffbac0;
  }
  FUN_00058430(*puVar1,puVar1[1],puVar1[2],puVar1[3]);
  DAT_1ffe02b4 = 0;
  remote_request = 1;
  DAT_1fff9550 = DAT_1fff9550 | 4;
  return;
}

