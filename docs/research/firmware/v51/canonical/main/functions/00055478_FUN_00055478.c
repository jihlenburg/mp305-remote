/* Address: 00055478; name: FUN_00055478; body bytes: 162 */

void FUN_00055478(uint param_1)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  uint uVar4;
  
  if (DAT_1ffe034c == 0) {
    DAT_1ffe027c = 0xffff;
    DAT_1ffe027e = 0;
  }
  else {
    uVar2 = param_1;
    if (DAT_1fffab76 < param_1) {
      uVar2 = (uint)DAT_1fffab76;
    }
    iVar1 = FUN_0004ccf8(DAT_1ffe0360);
    uVar4 = (int)(uVar2 * iVar1) / (int)(uint)DAT_1fffab76 & 0xffff;
    uVar2 = (uint)DAT_1ffe027e;
    if ((uVar2 != uVar4) || (DAT_1ffe027c == 0xffff)) {
      if (uVar4 + 0x14 < uVar2) {
        uVar4 = uVar2 - 0x14 & 0xffff;
      }
      uVar3 = FUN_0004b9de(DAT_1ffe0360,0);
      FUN_0004eae2(uVar3,uVar4);
      DAT_1ffe027e = (ushort)uVar4;
    }
    if (DAT_1ffe027c != param_1) {
      FUN_000499de(DAT_1ffe056c,"%01d.%03d A",param_1 / 1000,param_1 % 1000);
      DAT_1ffe027c = (ushort)param_1;
    }
  }
  return;
}

