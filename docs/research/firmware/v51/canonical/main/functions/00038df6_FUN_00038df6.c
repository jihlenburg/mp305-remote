/* Address: 00038df6; name: FUN_00038df6; body bytes: 66 */

uint FUN_00038df6(undefined4 param_1)

{
  int iVar1;
  uint uVar2;
  byte bVar3;
  
  uVar2 = 0;
  FUN_00038e78(param_1,0);
  bVar3 = 0;
  do {
    uVar2 = (uVar2 & 0x7f) * 2;
    FUN_00038e40(param_1);
    FUN_000144fc(5);
    iVar1 = FUN_00038e96(param_1);
    if (iVar1 != 0) {
      uVar2 = uVar2 + 1;
    }
    FUN_00038e38(param_1);
    FUN_000144fc(10);
    bVar3 = bVar3 + 1;
  } while (bVar3 < 8);
  return uVar2;
}

