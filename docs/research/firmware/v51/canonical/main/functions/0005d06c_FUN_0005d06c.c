/* Address: 0005d06c; name: FUN_0005d06c; body bytes: 172 */

/* Recovered from stored Thumb pointer at 00022674; callback identification is inferred until
   reviewed. */

void FUN_0005d06c(void)

{
  int iVar1;
  undefined4 *puVar2;
  undefined1 auStack_78 [72];
  undefined4 local_30;
  undefined4 uStack_2c;
  undefined4 local_28;
  undefined4 uStack_24;
  undefined4 local_20;
  undefined4 uStack_1c;
  
  iVar1 = FUN_0004675a();
  if (iVar1 == DAT_1ffe0398) {
    FUN_0004aa6e();
    FUN_0004e00e(DAT_1ffe0460,1);
    FUN_0004e00e(DAT_1ffe0464,1);
  }
  else {
    FUN_0004e00e(DAT_1ffe045c,1);
    FUN_0004aa6e(DAT_1ffe0460,1);
    FUN_0004aa6e(DAT_1ffe0464,1);
  }
  FUN_0001814c();
  if (DAT_1fffaafb == '\x01') {
    uStack_2c = FUN_00037604();
    local_20 = 0x53ed9;
    uStack_1c = 0x53cf5;
    local_28 = 0;
    uStack_24 = 0x23969;
    local_30 = DAT_1ffe0450;
    FUN_0001046a(auStack_78,&DAT_1fffbad0,0x48);
    puVar2 = &DAT_1fffbac0;
  }
  else {
    uStack_2c = FUN_000375f8();
    local_20 = 0x53ed9;
    uStack_1c = 0x53cf5;
    local_28 = 0;
    uStack_24 = 0x2396d;
    local_30 = DAT_1ffe0450;
    FUN_0001046a(auStack_78,&DAT_1fffbb28,0x48);
    puVar2 = &DAT_1fffbb18;
  }
  FUN_00058430(*puVar2,puVar2[1],puVar2[2],puVar2[3]);
  return;
}

