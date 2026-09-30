/* Address: 00056120; name: FUN_00056120; body bytes: 162 */

void FUN_00056120(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  if (DAT_1fffa0c7 == 5) {
    uVar1 = FUN_00015a5c(0x54);
    uVar2 = FUN_0004b9de(DAT_1ffe0624,2);
    uVar2 = FUN_0004b9de(uVar2,1);
    FUN_000499de(uVar2,&DAT_000561e0,uVar1);
    uVar1 = FUN_0004b9de(DAT_1ffe0624,2);
    FUN_0004e00e(uVar1,2);
  }
  else {
    uVar1 = FUN_0004b9de(DAT_1ffe0624,2);
    uVar1 = FUN_0004b9de(uVar1,1);
    FUN_000499de(uVar1,&DAT_000561d0,(byte)DAT_1fffac90);
    uVar1 = FUN_0004b9de(DAT_1ffe0624,2);
    FUN_0004aa6e(uVar1,2);
  }
  FUN_000499de(DAT_1ffe066c,&DAT_000561d0,(byte)DAT_1fffac90);
  uVar1 = FUN_0004037c(0xffa600);
  uVar2 = FUN_0004b9de(DAT_1ffe0648,(byte)DAT_1fffac90 - 1);
  FUN_0004e8b2(uVar2,uVar1,0);
  (&DAT_1fffa0c8)[DAT_1fffa0c7] = (byte)DAT_1fffac90;
  return;
}

