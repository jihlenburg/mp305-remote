/* Address: 0005eeac; name: FUN_0005eeac; body bytes: 240 */

/* Recovered from stored Thumb pointer at 00021e64; callback identification is inferred until
   reviewed. */

void FUN_0005eeac(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined1 auStack_78 [72];
  undefined4 local_30;
  undefined4 uStack_2c;
  undefined4 local_28;
  undefined4 uStack_24;
  undefined4 local_20;
  undefined4 uStack_1c;
  
  FUN_0001814c();
  if (DAT_1ffe0247 != '\0') {
    FUN_0001ba58();
    return;
  }
  uVar1 = FUN_0004037c(0xffa600);
  uVar2 = FUN_0004b9de(DAT_1ffe06a4,0);
  FUN_0004e960(uVar2,uVar1,0);
  uVar1 = FUN_00015a5c(0x27);
  FUN_000499de(DAT_1ffe06a8,&DAT_0005efa8,uVar1);
  FUN_0004aa6e(DAT_1ffe06ac,1);
  FUN_0004e84a(DAT_1ffe06b0,0xae,0x2d);
  FUN_0004ac0a(DAT_1ffe06b0,5,0,0xfffffffe);
  uVar1 = FUN_0004b9de(DAT_1ffe06b0,0);
  FUN_0004aa6e(uVar1,1);
  uVar1 = FUN_0004b9de(DAT_1ffe06b0,1);
  FUN_0004e00e(uVar1,1);
  if (DAT_1fffaafb == '\0') {
    uStack_2c = FUN_000375f8();
    local_20 = 0x53ed9;
    uStack_1c = 0x53cf5;
    local_28 = 0;
    uStack_24 = 0x2396d;
    local_30 = DAT_1ffe06a0;
    FUN_0001046a(auStack_78,&DAT_1fffbb28,0x48);
    puVar3 = &DAT_1fffbb18;
  }
  else {
    uStack_2c = FUN_00037604();
    local_20 = 0x53ed9;
    uStack_1c = 0x53cf5;
    local_28 = 0;
    uStack_24 = 0x23969;
    local_30 = DAT_1ffe06a0;
    FUN_0001046a(auStack_78,&DAT_1fffbad0,0x48);
    puVar3 = &DAT_1fffbac0;
  }
  FUN_00058430(*puVar3,puVar3[1],puVar3[2],puVar3[3]);
  DAT_1fffab10 = 1;
  return;
}

