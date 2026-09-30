/* Address: 00057288; name: FUN_00057288; body bytes: 108 */

void FUN_00057288(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  if (DAT_1ffe0864 == 0) {
    uVar1 = FUN_00015a5c(0x46);
    uVar2 = FUN_0004b9de(DAT_1ffe05b0,3);
    uVar2 = FUN_0004b9de(uVar2,1);
    FUN_000499de(uVar2,&LAB_00057310,uVar1);
  }
  else {
    uVar1 = FUN_00015a5c(0x57);
    uVar2 = FUN_0004b9de(DAT_1ffe05b0,3);
    uVar2 = FUN_0004b9de(uVar2,1);
    FUN_000499de(uVar2,"%d %s",(&DAT_1ffe077d)[DAT_1ffe0864],uVar1);
  }
  uVar1 = FUN_0004037c(0xffa600);
  uVar2 = FUN_0004b9de(DAT_1ffe06e4,DAT_1ffe0864);
  FUN_0004e8b2(uVar2,uVar1,0);
  return;
}

