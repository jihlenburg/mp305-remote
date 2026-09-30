/* Address: 00037d4c; name: FUN_00037d4c; body bytes: 382 */

void FUN_00037d4c(void)

{
  byte bVar1;
  char cVar2;
  undefined2 local_30;
  undefined2 local_2e;
  undefined2 local_26;
  
  FUN_00015398(8,0);
  FUN_000152a8(2,0x4000,0);
  FUN_000152a8(2,0x8000,0);
  FUN_000152a8(7,1,0);
  FUN_000152a8(7,2,0);
  FUN_000153b4(7,1,0);
  FUN_0001540c(&local_30);
  local_30 = 0;
  local_2e = 2;
  FUN_000152e0(0,0x8000,&local_30);
  FUN_000152e0(2,8,&local_30);
  FUN_000152e0(0,4,&local_30);
  FUN_000152e0(1,0x40,&local_30);
  FUN_000152e0(0,2,&local_30);
  FUN_000152e0(2,0x10,&local_30);
  FUN_000152e0(0,0x80,&local_30);
  FUN_0001540c(&local_30);
  local_30 = 1;
  local_2e = 0;
  FUN_000152e0(1,0x200,&local_30);
  FUN_00014494(0);
  FUN_000181e4(1);
  FUN_0001bce4(0);
  FUN_0001bcd0(0);
  FUN_000144a8(0);
  FUN_00016c56(0);
  FUN_0001f23c(0);
  FUN_00018a40(1);
  FUN_0001540c(&local_30);
  local_30 = 1;
  local_26 = 0x40;
  local_2e = 0;
  FUN_000152e0(2,0x200,&local_30);
  FUN_000152e0(2,0x2000,&local_30);
  FUN_000152e0(2,0x4000,&local_30);
  FUN_000152e0(2,0x8000,&local_30);
  FUN_000152e0(2,0x80,&local_30);
  FUN_000152e0(1,0x8000,&local_30);
  FUN_000152e0(7,1,&local_30);
  FUN_000152e0(0,0x1000,&local_30);
  FUN_000152e0(7,2,&local_30);
  bVar1 = FUN_000159f6();
  cVar2 = FUN_000159ec();
  DAT_1ffe016c = bVar1 | cVar2 << 1;
  FUN_00014af0();
  FUN_00014acc();
  FUN_000177c4();
  return;
}

