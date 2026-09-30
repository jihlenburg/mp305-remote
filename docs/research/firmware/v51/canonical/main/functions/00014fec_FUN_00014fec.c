/* Address: 00014fec; name: FUN_00014fec; body bytes: 96 */

void FUN_00014fec(void)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  
  iVar4 = 0;
  uVar1 = FUN_000159ec();
  uVar2 = FUN_000159f6();
  if ((uVar1 == DAT_1ffe0170) && (uVar3 = (uint)DAT_1ffe0171, uVar2 == uVar3)) {
    if (uVar3 != DAT_1ffe0173) {
      switch((uVar3 | (uint)DAT_1ffe0170 << 1 | ((uint)DAT_1ffe0173 | (uint)DAT_1ffe0172 << 1) << 2)
             & 0xff) {
      case 1:
      case 7:
      case 8:
      case 0xe:
        iVar4 = -1;
        break;
      case 2:
      case 4:
      case 0xb:
      case 0xd:
        iVar4 = 1;
      }
    }
    DAT_1ffe0172 = DAT_1ffe0170;
    DAT_1ffe0173 = DAT_1ffe0171;
    if (iVar4 != 0) {
      DAT_1ffe016e = 1;
    }
    DAT_1ffe0174 = DAT_1ffe0174 + iVar4;
  }
  DAT_1ffe0170 = (char)uVar1;
  DAT_1ffe0171 = (char)uVar2;
  return;
}

