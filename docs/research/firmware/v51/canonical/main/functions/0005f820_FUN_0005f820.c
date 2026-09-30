/* Address: 0005f820; name: FUN_0005f820; body bytes: 148 */

void FUN_0005f820(void)

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
  
  FUN_0001814c();
  iVar1 = FUN_0004fe9c();
  if (iVar1 == DAT_1ffe0590) {
    return;
  }
  if (DAT_1ffe0247 != '\0') {
    FUN_0001ba58();
    return;
  }
  if (DAT_1fffaafb == '\x01') {
    uStack_2c = FUN_00037604();
    local_20 = 0x53ed9;
    uStack_1c = 0x53cf5;
    local_28 = 0;
    uStack_24 = 0x23969;
    local_30 = DAT_1ffe0478;
    FUN_0001046a(auStack_78,&DAT_1fffbad0,0x48);
    puVar2 = &DAT_1fffbac0;
  }
  else {
    uStack_2c = FUN_000375f8();
    local_20 = 0x53ed9;
    uStack_1c = 0x53cf5;
    local_28 = 0;
    uStack_24 = 0x2396d;
    local_30 = DAT_1ffe0478;
    FUN_0001046a(auStack_78,&DAT_1fffbb28,0x48);
    puVar2 = &DAT_1fffbb18;
  }
  FUN_00058430(*puVar2,puVar2[1],puVar2[2],puVar2[3]);
  FUN_00018114(DAT_1ffe0348);
  return;
}

