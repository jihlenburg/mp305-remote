/* Address: 0005836c; name: FUN_0005836c; body bytes: 106 */

void FUN_0005836c(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  uint uVar3;
  
  if (DAT_1fffaafe == 0) {
    uVar1 = 0x42;
  }
  else if (DAT_1fffaafe == 1) {
    uVar1 = 0x43;
  }
  else if (DAT_1fffaafe == 2) {
    uVar1 = 0x44;
  }
  else {
    if (DAT_1fffaafe != 3) goto LAB_0001c5cc;
    uVar1 = 0x45;
  }
  uVar1 = FUN_00015a5c(uVar1);
  uVar2 = FUN_0004b9de(DAT_1ffe05b0,1);
  uVar2 = FUN_0004b9de(uVar2,1);
  FUN_000499de(uVar2,&DAT_000583e0,uVar1);
LAB_0001c5cc:
  uVar1 = FUN_0004037c(0xffa600);
  uVar2 = FUN_0004b9de(DAT_1ffe06d4,DAT_1fffaafe);
  FUN_0004e8b2(uVar2,uVar1,0);
  uVar3 = (uint)DAT_1fffaafe;
  if (3 < uVar3) {
    uVar3 = 3;
  }
  DAT_1fffa0b1 = (&stack0xfffffff8)[uVar3];
  return;
}

