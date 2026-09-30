/* Address: 0003dfb4; name: FUN_0003dfb4; body bytes: 146 */

short FUN_0003dfb4(uint param_1,uint param_2)

{
  ushort uVar1;
  short sVar2;
  uint uVar3;
  uint uVar4;
  bool bVar5;
  
  bVar5 = (int)param_1 < 0;
  if (bVar5) {
    param_1 = -param_1;
  }
  uVar4 = (uint)bVar5;
  if ((int)param_2 < 0) {
    param_2 = -param_2;
    uVar4 = uVar4 + 2;
  }
  if (param_2 < param_1) {
    param_1 = (param_2 * 0x2d) / param_1;
    uVar4 = uVar4 + 0x10;
  }
  else {
    param_1 = (param_1 * 0x2d) / param_2;
  }
  uVar3 = param_1 & 0xff;
  if (uVar3 < 0x17) {
    uVar1 = (ushort)(1 < uVar3);
    if (5 < uVar3) {
      uVar1 = uVar1 + 1;
    }
    if (9 < uVar3) {
      uVar1 = uVar1 + 1;
    }
    if (uVar3 < 0xf) goto LAB_0003e01e;
  }
  else {
    uVar1 = (ushort)(uVar3 < 0x2d);
    if (uVar3 < 0x2a) {
      uVar1 = uVar1 + 1;
    }
    if (uVar3 < 0x26) {
      uVar1 = uVar1 + 1;
    }
    if (0x20 < uVar3) goto LAB_0003e01e;
  }
  uVar1 = uVar1 + 1;
LAB_0003e01e:
  sVar2 = uVar1 + (short)param_1;
  if ((int)(uVar4 << 0x1b) < 0) {
    sVar2 = 0x5a - sVar2;
  }
  if ((int)(uVar4 << 0x1e) < 0) {
    if (uVar4 << 0x1f == 0) {
      sVar2 = 0xb4 - sVar2;
    }
    else {
      sVar2 = sVar2 + 0xb4;
    }
  }
  else if (uVar4 << 0x1f != 0) {
    sVar2 = 0x168 - sVar2;
  }
  return sVar2;
}

