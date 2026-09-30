/* Address: 000143d0; name: FUN_000143d0; body bytes: 174 */

void FUN_000143d0(void)

{
  uint uVar1;
  
  uVar1 = 0;
  do {
    FUN_0003bc70(&DAT_1fffa354 + uVar1 * 0x10,&DAT_00014484);
    (&DAT_1fffa3f4)[uVar1] = 0;
    (&DAT_1fffa3fe)[uVar1] = 0;
    FUN_0001bdf6(uVar1 * 0x1000 + 0x162000);
    uVar1 = uVar1 + 1 & 0xff;
  } while (uVar1 < 10);
  FUN_0003bc70(&DAT_1fffa354,"Test1");
  DAT_1fffa3f4 = 6;
  DAT_1fffa3fe = 1;
  DAT_1fffa409 = 1;
  FUN_000142fc(0,5000,3000,100);
  FUN_000142fc(1,9000,3000,100);
  FUN_000142fc(2,15000,3000,100);
  FUN_000142fc(3,20000,3000,100);
  FUN_000142fc(4,30000,3000,100);
  FUN_000142fc(5,0,0);
  FUN_0001bf3a(0x162000,&DAT_1fffa414,0x4b0);
  return;
}

