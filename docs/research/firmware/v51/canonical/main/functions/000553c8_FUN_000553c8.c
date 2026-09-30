/* Address: 000553c8; name: FUN_000553c8; body bytes: 132 */

void FUN_000553c8(uint param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  if (DAT_1ffe034c == 0) {
    DAT_1ffe0270 = 0xffff;
  }
  else if (DAT_1ffe0270 != param_1) {
    uVar1 = FUN_0004b9de(DAT_1ffe0350,1);
    FUN_000499de(uVar1,"%02d.%02d",param_1 / 100,param_1 % 100);
    if (DAT_1fffaad1 == '\0') {
      uVar1 = FUN_0004b9de(DAT_1ffe0350,0);
      iVar2 = 0;
    }
    else {
      iVar2 = FUN_0004ccf8(DAT_1ffe0350);
      iVar2 = (int)(param_1 * iVar2) / 0xbea;
      uVar1 = FUN_0004b9de(DAT_1ffe0350,0);
    }
    FUN_0004eae2(uVar1,iVar2);
    FUN_000499de(DAT_1ffe0578,"%02d.%02d V",param_1 / 100,param_1 % 100);
    DAT_1ffe0270 = (ushort)param_1;
  }
  return;
}

