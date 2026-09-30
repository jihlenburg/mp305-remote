/* Address: 00012adc; name: FUN_00012adc; body bytes: 258 */

void FUN_00012adc(void)

{
  ushort uVar1;
  uint uVar2;
  int iVar3;
  short sVar4;
  
  uVar1 = DAT_1fffab68;
  if (DAT_1ffe05b8 != 0) {
    if (DAT_1fffab68 == DAT_1fffab66) {
      return;
    }
    if (DAT_1fffab68 == 0) {
      return;
    }
    uVar2 = 0;
    do {
      if ((uVar1 >> uVar2 & 1) == 0) {
        *(ushort *)(&DAT_1fffa1d8 + (uint)DAT_1fffa34a * 0x24 + uVar2 * 4) =
             *(ushort *)(&DAT_1fffa1d8 + (uint)DAT_1fffa34a * 0x24 + uVar2 * 4) & 0xfff8;
      }
      else if (uVar2 < 5) {
        *(ushort *)(&DAT_1fffa1d8 + (uint)DAT_1fffa34a * 0x24 + uVar2 * 4) =
             (*(ushort *)(&DAT_1fffa1d8 + (uint)DAT_1fffa34a * 0x24 + uVar2 * 4) & 0xfff8) + 1;
      }
      else {
        if (uVar2 == 5) {
          iVar3 = (uint)DAT_1fffa34a * 0x24 + 0x1fffa14c;
          sVar4 = (*(ushort *)(&DAT_1fffa1ec + (uint)DAT_1fffa34a * 0x24) & 0xfff8) + 2;
        }
        else if (uVar2 == 6) {
          iVar3 = (uint)DAT_1fffa34a * 0x24 + 0x1fffa150;
          sVar4 = (*(ushort *)(&DAT_1fffa1f0 + (uint)DAT_1fffa34a * 0x24) & 0xfff8) + 5;
        }
        else if (uVar2 == 7) {
          iVar3 = (uint)DAT_1fffa34a * 0x24 + 0x1fffa154;
          sVar4 = (*(ushort *)(&DAT_1fffa1f4 + (uint)DAT_1fffa34a * 0x24) & 0xfff8) + 3;
        }
        else {
          if (uVar2 != 8) goto LAB_00012bca;
          iVar3 = (uint)DAT_1fffa34a * 0x24 + 0x1fffa158;
          sVar4 = (*(ushort *)(&DAT_1fffa1f8 + (uint)DAT_1fffa34a * 0x24) & 0xfff8) + 4;
        }
        *(short *)(iVar3 + 0xa0) = sVar4;
      }
LAB_00012bca:
      uVar2 = uVar2 + 1 & 0xff;
    } while (uVar2 < 9);
    FUN_0005735c(1);
  }
  DAT_1fffab68 = 0;
  return;
}

