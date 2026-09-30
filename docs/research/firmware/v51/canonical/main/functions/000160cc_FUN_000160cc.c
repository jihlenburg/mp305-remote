/* Address: 000160cc; name: FUN_000160cc; body bytes: 226 */

/* Recovered from stored Thumb pointer at 0001634c; callback identification is inferred until
   reviewed. */

void FUN_000160cc(void)

{
  int iVar1;
  undefined4 uVar2;
  int in_r3;
  int local_18;
  
  local_18 = in_r3;
  iVar1 = FUN_00016932(&DAT_4004e400,1);
  if (iVar1 == 1) {
    FUN_00016830(&DAT_4004e400,0x1001);
    FUN_00016988(&DAT_4004e400,0x1010,1);
    if (DAT_1fff8f38 == '\0') {
      FUN_00016988(&DAT_4004e400,8,1);
      uVar2 = 0;
    }
    else {
      if (DAT_1fff8f48 == 1) {
        FUN_000166dc(&DAT_4004e400,0x400);
      }
      FUN_00016988(&DAT_4004e400,0x40,1);
      uVar2 = 1;
    }
    FUN_00016360(DAT_1fff8f3b,uVar2);
  }
  iVar1 = FUN_00016932(&DAT_4004e400,0x1000);
  if (iVar1 == 1) {
    FUN_00016830(&DAT_4004e400,0x1000);
    FUN_00016988(&DAT_4004e400,0x10c8,0);
    FUN_00016928(&DAT_4004e400);
  }
  iVar1 = FUN_00016932(&DAT_4004e400,0x10);
  if (iVar1 == 1) {
    FUN_00016830(&DAT_4004e400,0x10);
    FUN_00016988(&DAT_4004e400,0x10d8,0);
    FUN_00016834(&DAT_4004e400,0);
    local_18 = 0;
    if (DAT_1fff8f38 == '\x01') {
      uVar2 = 2;
    }
    else {
      uVar2 = 1;
    }
    FUN_000670cc(0x656b3,DAT_1fff8f5c,uVar2,&local_18);
    if (local_18 != 0) {
      DAT_e000ed04 = 0x10000000;
      DataSynchronizationBarrier(0xf);
      InstructionSynchronizationBarrier(0xf);
    }
  }
  return;
}

