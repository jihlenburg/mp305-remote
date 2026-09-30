/* Address: ram:0006608a; name: FUN_ram_0006608a; body bytes: 320 */

undefined4
FUN_ram_0006608a(undefined4 param_1,uint param_2,uint param_3,uint param_4,uint param_5,
                undefined2 param_6,undefined2 param_7)

{
  undefined2 uVar1;
  int iVar2;
  char cVar3;
  undefined1 uVar4;
  short sVar5;
  uint uVar6;
  
  gp = 0x20004000;
  iVar2 = FUN_ram_00057ba2();
  if (0xc7a < (param_2 - 6 & 0xffff)) {
    gp = 0x20004000;
    return 0x12;
  }
  if (0xc80 < param_3) {
    gp = 0x20004000;
    return 0x12;
  }
  if (param_3 < param_2) {
    gp = 0x20004000;
    return 0x12;
  }
  if (499 < param_4) {
    gp = 0x20004000;
    return 0x12;
  }
  if (0xc80 < param_5) {
    gp = 0x20004000;
    return 0x12;
  }
  if ((int)(param_5 << 3) <= (int)((param_4 + 1) * param_3 * 2)) {
    gp = 0x20004000;
    return 0x12;
  }
  if (iVar2 == 0) {
    gp = 0x20004000;
    return 0x12;
  }
  if ((*(byte *)(iVar2 + 0x11) & 4) == 0) goto LAB_ram_00066164;
  *(byte *)(iVar2 + 0x11) = *(byte *)(iVar2 + 0x11) & 0xfb;
  *(short *)(iVar2 + 0x72) = (short)param_2;
  *(short *)(iVar2 + 0x74) = (short)param_3;
  if (*(char *)(iVar2 + 0xb) == '\0') {
    if ((*(short *)(iVar2 + 0x66) == -1) || (param_2 != param_3)) {
      uVar6 = (uint)*(ushort *)(iVar2 + 0x62);
      if (uVar6 != 0) {
        if (uVar6 == 0) {
          sVar5 = -1;
        }
        else {
          sVar5 = (short)(param_3 / uVar6);
        }
        sVar5 = *(ushort *)(iVar2 + 0x62) * sVar5;
        goto LAB_ram_00066124;
      }
      uVar1 = FUN_ram_00042910(param_2,param_2 + param_3 >> 1);
      *(undefined2 *)(iVar2 + 0x56) = uVar1;
      FUN_ram_00052694(param_3,iVar2 + 0x56);
    }
    else {
      sVar5 = *(short *)(iVar2 + 0x38);
      *(short *)(iVar2 + 0x54) = *(short *)(iVar2 + 0x66);
LAB_ram_00066124:
      *(short *)(iVar2 + 0x56) = sVar5;
    }
    cVar3 = '\x04';
    if (DAT_ram_20001e04 < 4) {
      cVar3 = (char)DAT_ram_20001e04 + '\x01';
    }
    *(char *)(iVar2 + 0x53) = cVar3;
    FUN_ram_00055ef4(iVar2);
    *(short *)(iVar2 + 0x5c) = *(short *)(iVar2 + 0x3e) + 10;
    *(uint *)(iVar2 + 0xa4) = *(uint *)(iVar2 + 0xa4) | 1;
    uVar4 = 0x11;
  }
  else {
    *(uint *)(iVar2 + 0xa8) = *(uint *)(iVar2 + 0xa8) | 0x20;
    uVar4 = 0x10;
  }
  *(undefined1 *)(iVar2 + 0x1d) = uVar4;
LAB_ram_00066164:
  *(undefined2 *)(iVar2 + 0x76) = param_6;
  *(undefined2 *)(iVar2 + 0x78) = param_7;
  *(short *)(iVar2 + 0x58) = (short)param_4;
  *(short *)(iVar2 + 0x5a) = (short)param_5;
  return 0;
}

