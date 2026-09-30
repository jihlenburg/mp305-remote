/* Address: 000567e0; name: FUN_000567e0; body bytes: 146 */

void FUN_000567e0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  uint uVar4;
  undefined8 uVar5;
  undefined4 local_20 [3];
  
  local_20[0] = param_2;
  local_20[1] = param_3;
  local_20[2] = param_4;
  FUN_0004b9de(DAT_1ffe0650,DAT_1ffe032e);
  iVar1 = FUN_000491e8();
  uVar2 = FUN_0004b9de(DAT_1ffe0624,3);
  uVar2 = FUN_0004b9de(uVar2,1);
  FUN_00049974(uVar2,iVar1);
  uVar2 = FUN_0004037c(0xffa600);
  uVar3 = FUN_0004b9de(DAT_1ffe0650,DAT_1ffe032e);
  FUN_0004e8b2(uVar3,uVar2,0);
  uVar4 = 0;
  while( true ) {
    if (*(char *)(iVar1 + uVar4) == 'A') break;
    *(char *)((int)local_20 + uVar4) = *(char *)(iVar1 + uVar4);
    uVar4 = uVar4 + 1 & 0xff;
  }
  uVar5 = FUN_00020160(local_20);
  uVar5 = FUN_0001083c((int)uVar5,(int)((ulonglong)uVar5 >> 0x20),0,0x40c38800);
  FUN_000106ee((int)uVar5,(int)((ulonglong)uVar5 >> 0x20),0,&DAT_40140000);
  uVar4 = FUN_00010a90();
  DAT_1fffac90._2_2_ = (undefined2)(uVar4 / 10);
  (&DAT_1fffa0e8)[DAT_1fffa0c7] = DAT_1fffac90._2_2_;
  return;
}

