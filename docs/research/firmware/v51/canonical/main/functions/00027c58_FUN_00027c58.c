/* Address: 00027c58; name: FUN_00027c58; body bytes: 154 */

void FUN_00027c58(void)

{
  undefined4 *puVar1;
  undefined1 auStack_78 [72];
  undefined4 local_30;
  undefined4 uStack_2c;
  undefined4 local_28;
  undefined4 uStack_24;
  undefined4 local_20;
  undefined4 uStack_1c;
  
  DAT_1ffe024b = DAT_1ffe024b + 1;
  if (7 < DAT_1ffe024b) {
    FUN_0001814c();
    DAT_1fffaad8 = 1;
    DAT_1ffe024b = 0;
    DAT_1fff942c = 0;
    DAT_1fff942d = 0;
    DAT_1fff942e = 0;
    DAT_1fff942f = 0;
    DAT_1fff9550 = DAT_1fff9550 | 0x2000;
    DAT_1fff9bbc = 1;
    if (DAT_1fffaafb == '\x01') {
      uStack_2c = FUN_00037604();
      local_20 = 0x53ed9;
      uStack_1c = 0x53cf5;
      local_28 = 0;
      uStack_24 = 0x23969;
      local_30 = DAT_1ffe0550;
      FUN_0001046a(auStack_78,&DAT_1fffbad0,0x48);
      puVar1 = &DAT_1fffbac0;
    }
    else {
      uStack_2c = FUN_000375f8();
      local_20 = 0x53ed9;
      uStack_1c = 0x53cf5;
      local_28 = 0;
      uStack_24 = 0x2396d;
      local_30 = DAT_1ffe0550;
      FUN_0001046a(auStack_78,&DAT_1fffbb28,0x48);
      puVar1 = &DAT_1fffbb18;
    }
    FUN_00058430(*puVar1,puVar1[1],puVar1[2],puVar1[3]);
  }
  return;
}

