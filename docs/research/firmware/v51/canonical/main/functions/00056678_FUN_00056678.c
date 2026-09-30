/* Address: 00056678; name: FUN_00056678; body bytes: 156 */

void FUN_00056678(void)

{
  undefined *puVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  if (DAT_1fffa0c7 == 5) {
    FUN_0004b9de(DAT_1ffe0640,DAT_1ffe032d);
    uVar2 = FUN_000491e8();
    FUN_00020034(&DAT_1ffe02fc,&DAT_00056730,uVar2);
    uVar2 = FUN_0004b9de(DAT_1ffe0624,1);
    uVar2 = FUN_0004b9de(uVar2,1);
    puVar1 = &DAT_1ffe02fc;
  }
  else {
    FUN_0004b9de(DAT_1ffe0640,DAT_1ffe032d);
    puVar1 = (undefined *)FUN_000491e8();
    uVar2 = FUN_0004b9de(DAT_1ffe0624,1);
    uVar2 = FUN_0004b9de(uVar2,1);
  }
  FUN_00049974(uVar2,puVar1);
  uVar2 = FUN_0004037c(0xffa600);
  uVar3 = FUN_0004b9de(DAT_1ffe0640,DAT_1ffe032d);
  FUN_0004e8b2(uVar3,uVar2,0);
  DAT_1fffac94._0_2_ = (&DAT_1ffe07e0)[(uint)DAT_1fffa0c7 * 0xb + (uint)DAT_1ffe032d];
  *(undefined2 *)((int)&DAT_1fffa0dc + (uint)DAT_1fffa0c7 * 2) = (undefined2)DAT_1fffac94;
  return;
}

