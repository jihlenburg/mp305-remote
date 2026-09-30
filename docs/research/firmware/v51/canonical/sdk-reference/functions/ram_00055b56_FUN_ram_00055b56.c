/* Address: ram:00055b56; name: FUN_ram_00055b56; body bytes: 338 */

undefined4 FUN_ram_00055b56(int param_1)

{
  ushort uVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  
  gp = 0x20004000;
  uVar6 = (uint)*(ushort *)(param_1 + 0x1c0);
  if ((uint)*(ushort *)(param_1 + 0x1b4) < (uint)*(ushort *)(param_1 + 0x1c0)) {
    uVar6 = (uint)*(ushort *)(param_1 + 0x1b4);
  }
  uVar7 = (uint)*(ushort *)(param_1 + 0x1c2);
  if ((uint)*(ushort *)(param_1 + 0x1b6) < (uint)*(ushort *)(param_1 + 0x1c2)) {
    uVar7 = (uint)*(ushort *)(param_1 + 0x1b6);
  }
  uVar1 = *(ushort *)(param_1 + 0x1bc);
  if (*(ushort *)(param_1 + 0x1b8) < *(ushort *)(param_1 + 0x1bc)) {
    uVar1 = *(ushort *)(param_1 + 0x1b8);
  }
  uVar8 = (uint)*(ushort *)(param_1 + 0x1be);
  if ((uint)*(ushort *)(param_1 + 0x1ba) < (uint)*(ushort *)(param_1 + 0x1be)) {
    uVar8 = (uint)*(ushort *)(param_1 + 0x1ba);
  }
  if (*(char *)(param_1 + 0x147) == '\x02') {
    uVar3 = 0xa90;
    if (0xa8f < uVar7) goto LAB_ram_00055be8;
  }
  else if ((*(int *)(param_1 + 0x100) << 0x14 < 0) || (uVar3 = 0x848, uVar7 < 0x849))
  goto LAB_ram_00055be8;
  uVar7 = uVar3;
LAB_ram_00055be8:
  if (*(char *)(param_1 + 0x146) == '\x02') {
    iVar4 = (uVar6 & 0xff) * 0x40;
    iVar5 = iVar4 + 0x4fc;
    if (uVar7 <= iVar4 + 0x3cfU) {
      iVar5 = uVar7 + 300;
    }
    uVar3 = (uint)*(ushort *)(param_1 + 0x38) * 0x4e2 - iVar5;
    if ((int)uVar8 < (int)uVar3) {
      uVar3 = uVar8;
    }
    uVar8 = uVar3 & 0xffff;
    if ((uVar3 & 0xffff) < 0xa90) {
      uVar8 = 0xa90;
    }
  }
  else if ((-1 < *(int *)(param_1 + 0x100) << 0x14) && (0x848 < uVar8)) {
    uVar8 = 0x848;
  }
  if (((((uint)*(ushort *)(param_1 + 0x1c4) == (uVar6 & 0xff)) &&
       (*(ushort *)(param_1 + 0x1c6) == uVar7)) && (*(ushort *)(param_1 + 0x1c8) == (uVar1 & 0xff)))
     && (*(ushort *)(param_1 + 0x1ca) == uVar8)) {
    *(undefined1 *)(param_1 + 0x7a) = 0;
    FUN_ram_00055afc();
    uVar2 = 2;
  }
  else {
    *(undefined1 *)(param_1 + 0x7a) = 1;
    *(short *)(param_1 + 0x1c4) = (short)(uVar6 & 0xff);
    *(short *)(param_1 + 0x1c6) = (short)uVar7;
    *(ushort *)(param_1 + 0x1c8) = uVar1 & 0xff;
    *(short *)(param_1 + 0x1ca) = (short)uVar8;
    FUN_ram_00055afc();
    uVar2 = 0;
  }
  return uVar2;
}

