/* Address: 00054128; name: FUN_00054128; body bytes: 162 */

void FUN_00054128(void)

{
  char cVar1;
  undefined4 *puVar2;
  undefined1 auStack_78 [72];
  undefined4 local_30;
  undefined4 uStack_2c;
  undefined4 local_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 local_1c;
  
  if (DAT_1fffaafb == '\0') {
    local_28 = FUN_000375f8();
    local_1c = 0x53975;
    uStack_24 = 0x2396d;
    uStack_20 = 0x53c95;
    local_30 = DAT_1ffe0330;
    uStack_2c = 0;
    FUN_0001046a(auStack_78,&DAT_1fffbb28,0x48);
    puVar2 = &DAT_1fffbb18;
  }
  else {
    local_28 = FUN_00037604();
    local_1c = 0x53975;
    uStack_24 = 0x23969;
    uStack_20 = 0x53c95;
    local_30 = DAT_1ffe0330;
    uStack_2c = 0;
    FUN_0001046a(auStack_78,&DAT_1fffbad0,0x48);
    puVar2 = &DAT_1fffbac0;
  }
  FUN_00058430(*puVar2,puVar2[1],puVar2[2],puVar2[3]);
  DAT_1ffe02b4 = 0;
  DAT_1fffab0a = '\x01';
  DAT_1fffab0b = 0;
  FUN_0001aebc(0);
  FUN_0001d958();
  cVar1 = DAT_1fffab0a;
  if (DAT_1fffab0a != '\0') {
    FUN_0001af7c();
  }
  enter_critical();
  DAT_1fffa00e = cVar1;
  exit_critical();
  return;
}

