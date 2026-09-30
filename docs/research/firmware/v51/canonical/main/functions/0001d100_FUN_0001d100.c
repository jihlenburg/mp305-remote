/* Address: 0001d100; name: FUN_0001d100; body bytes: 226 */

void FUN_0001d100(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  undefined1 auStack_78 [72];
  undefined4 local_30;
  undefined4 uStack_2c;
  undefined4 local_28;
  undefined4 uStack_24;
  undefined4 local_20;
  undefined4 uStack_1c;
  
  FUN_0001814c();
  if (param_1 == 0) {
    uVar1 = FUN_0004b9de(DAT_1ffe046c,0);
    FUN_00047d8e(uVar1,&DAT_000821ac);
    uVar1 = 0xff0004;
  }
  else {
    if (param_1 != 1) goto LAB_0001d172;
    uVar1 = FUN_0004b9de(DAT_1ffe046c,0);
    FUN_00047d8e(uVar1,&DAT_0007e054);
    uVar1 = 0xffa600;
  }
  uVar2 = FUN_0004037c(uVar1);
  uVar3 = FUN_0004b9de(DAT_1ffe046c,0);
  FUN_0004e960(uVar3,uVar2,0);
  uVar1 = FUN_0004037c(uVar1);
  FUN_0004e8b2(DAT_1ffe0474,uVar1,0);
  uVar1 = FUN_0004b9de(DAT_1ffe0474,0);
  FUN_00047d8e(uVar1,&DAT_0007e0ec);
LAB_0001d172:
  FUN_000499de(DAT_1ffe0470,&DAT_0001d200,param_2);
  if (DAT_1fffaafb == '\x01') {
    uStack_2c = FUN_00037604();
    local_20 = 0x53ed9;
    uStack_1c = 0x53cf5;
    local_28 = 0;
    uStack_24 = 0x23969;
    local_30 = DAT_1ffe0468;
    FUN_0001046a(auStack_78,&DAT_1fffbad0,0x48);
    puVar4 = &DAT_1fffbac0;
  }
  else {
    uStack_2c = FUN_000375f8();
    local_20 = 0x53ed9;
    uStack_1c = 0x53cf5;
    local_28 = 0;
    uStack_24 = 0x2396d;
    local_30 = DAT_1ffe0468;
    FUN_0001046a(auStack_78,&DAT_1fffbb28,0x48);
    puVar4 = &DAT_1fffbb18;
  }
  FUN_00058430(*puVar4,puVar4[1],puVar4[2],puVar4[3]);
  return;
}

