/* Address: 00054e80; name: FUN_00054e80; body bytes: 122 */

void FUN_00054e80(uint param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  if (DAT_1ffe04f4 == 0) {
    DAT_1ffe0272 = 0xffff;
  }
  else if (DAT_1ffe0272 != param_1) {
    uVar1 = FUN_0004b9de(DAT_1ffe050c,1);
    FUN_000499de(uVar1,"%02d.%02d",param_1 / 100,param_1 % 100);
    if (DAT_1fffaad1 == '\0') {
      uVar1 = FUN_0004b9de(DAT_1ffe050c,0);
      iVar2 = 0;
    }
    else {
      iVar2 = FUN_0004ccf8(DAT_1ffe050c);
      iVar2 = (int)(param_1 * iVar2) / 0xbea;
      uVar1 = FUN_0004b9de(DAT_1ffe050c,0);
    }
    FUN_0004eae2(uVar1,iVar2);
    DAT_1ffe0272 = (ushort)param_1;
  }
  return;
}

