/* Address: 0003c838; name: FUN_0003c838; body bytes: 226 */

void FUN_0003c838(void)

{
  undefined4 uVar1;
  undefined *puVar2;
  
  DAT_1fffaadb = DAT_1fffaadb == '\0';
  DAT_1ffe02b4 = 0;
  FUN_000550a0();
  if (DAT_1fffaadb == '\0') {
    puVar2 = &DAT_0007b73c;
  }
  else {
    puVar2 = &DAT_0007b4c0;
  }
  FUN_00047d8e(DAT_1ffe04c0,puVar2);
  if (DAT_1fffaadb == '\0') {
    uVar1 = 6;
  }
  else {
    uVar1 = 7;
  }
  uVar1 = FUN_00015a5c(uVar1);
  FUN_000499de(DAT_1ffe04c4,&DAT_0003c934,uVar1);
  FUN_00057ea0(DAT_1fffaace,1);
  if (DAT_1fffaadb != '\0') {
    FUN_0003df0c(0x24655,0);
    uVar1 = FUN_0004037c(0xff0004);
    FUN_0004e8b2(DAT_1ffe04bc,uVar1,0);
    uVar1 = FUN_0004037c(0xffffff);
    FUN_0004ea90(DAT_1ffe04c4,uVar1,0);
    uVar1 = FUN_0004037c(0xffffff);
    FUN_0004e960(DAT_1ffe04c0,uVar1,0);
    return;
  }
  uVar1 = FUN_0004037c(0xffffff);
  FUN_0004e8b2(DAT_1ffe04bc,uVar1,0);
  uVar1 = FUN_0004037c(0);
  FUN_0004ea90(DAT_1ffe04c4,uVar1,0);
  uVar1 = FUN_0004037c(0);
  FUN_0004e960(DAT_1ffe04c0,uVar1,0);
  if (current_mode == '\0') {
    FUN_0004aa6e(DAT_1ffe0344,0x10);
  }
  FUN_0001cb8c(0xf);
  return;
}

