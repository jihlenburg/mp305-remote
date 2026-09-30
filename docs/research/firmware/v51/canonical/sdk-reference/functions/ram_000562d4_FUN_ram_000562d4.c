/* Address: ram:000562d4; name: FUN_ram_000562d4; body bytes: 454 */

void FUN_ram_000562d4(int *param_1)

{
  ushort uVar1;
  int *piVar2;
  uint uVar3;
  int *piVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  int *piVar8;
  int *piVar9;
  int iVar10;
  uint uVar11;
  
  gp = 0x20004000;
  if ((1 < DAT_ram_20001e04) && (piVar4 = DAT_ram_20001df0, (param_1[0x42] & 2U) != 0)) {
    for (; piVar4 != (int *)0x0; piVar4 = (int *)*piVar4) {
      if (*(char *)((int)piVar4 + 0x1d) != '\0') {
        gp = 0x20004000;
        return;
      }
    }
    piVar2 = (int *)0x0;
    uVar11 = 0xffffffff;
    uVar5 = ((int)(*(ushort *)(param_1 + 0x72) + 0x22) >> 1) + 0xb;
    uVar3 = 0xffffffff;
    piVar4 = (int *)0x0;
    piVar9 = DAT_ram_20001df0;
    while ((piVar9 != (int *)0x0 &&
           ((piVar8 = piVar9, piVar9 != param_1 ||
            (piVar8 = (int *)*piVar9, (int *)*piVar9 != (int *)0x0))))) {
      uVar6 = piVar8[0x24];
      uVar7 = param_1[0x24];
      if (uVar6 < uVar7) {
        uVar7 = uVar7 - uVar6;
        uVar6 = piVar8[0x23];
        if ((uVar6 < uVar7) && (uVar6 != 0)) {
          uVar7 = uVar7 % uVar6;
        }
        if ((uVar7 < uVar11) && (uVar11 = uVar7, uVar7 < uVar5)) {
          piVar2 = piVar8;
        }
      }
      else {
        uVar6 = uVar6 - uVar7;
        uVar7 = param_1[0x23];
        if ((uVar7 < uVar6) && (uVar7 != 0)) {
          uVar6 = uVar6 % uVar7;
        }
        if ((uVar6 < uVar3) && (uVar3 = uVar6, uVar6 < uVar5)) {
          piVar4 = piVar8;
        }
      }
      piVar9 = (int *)*piVar8;
    }
    if (piVar2 != (int *)0x0) {
      uVar1 = *(ushort *)(piVar2 + 0xe);
      uVar3 = (uint)uVar1;
      if (*(char *)((int)piVar2 + 0xb) == '\0') {
        *(ushort *)((int)piVar2 + 0x56) = uVar1;
        *(undefined1 *)((int)piVar2 + 0x53) = 2;
        *(ushort *)(piVar2 + 0x17) =
             (*(short *)((int)piVar2 + 0x3e) + *(ushort *)((int)piVar2 + 0x5e) + 0x10) -
             (*(ushort *)((int)piVar2 + 0x5e) & 7);
        *(undefined2 *)(piVar2 + 0x16) = *(undefined2 *)((int)piVar2 + 0x3a);
        *(short *)((int)piVar2 + 0x5a) = (short)piVar2[0xf];
        FUN_ram_00055ef4(piVar2);
        piVar2[0x29] = piVar2[0x29] | 1;
        *(undefined1 *)(piVar2 + 5) = 1;
        *(undefined1 *)((int)piVar2 + 0x1d) = 3;
        gp = 0x20004000;
        return;
      }
      uVar11 = (uint)*(ushort *)(param_1 + 0xe);
      if (uVar3 != 0) {
        uVar11 = uVar11 % uVar3;
      }
      if (uVar11 != 0) {
        gp = 0x20004000;
        return;
      }
      iVar10 = 6;
      if (7 < uVar3) {
        iVar10 = (uVar1 >> 1) + 3;
      }
      *(short *)((int)piVar2 + 0x72) = (short)iVar10;
      uVar3 = iVar10 << 2;
      if (0xc80 < (uint)(iVar10 << 2)) {
        uVar3 = 0xc80;
      }
      *(short *)(piVar2 + 0x1d) = (short)uVar3;
      *(undefined2 *)(piVar2 + 0x16) = *(undefined2 *)((int)piVar2 + 0x3a);
      *(short *)((int)piVar2 + 0x5a) = (short)piVar2[0xf];
      *(undefined1 *)((int)piVar2 + 0x1d) = 0x12;
      FUN_ram_0005d5f6((short)piVar2[2],0x80,0x25);
      return;
    }
    if (piVar4 != (int *)0x0) {
      uVar3 = (uint)*(ushort *)(param_1 + 0xe);
      uVar11 = (uint)*(ushort *)(piVar4 + 0xe);
      if (uVar3 != 0) {
        uVar11 = uVar11 % uVar3;
      }
      if ((uVar11 == 0) && ((char)param_1[7] < '\0')) {
        iVar10 = 6;
        if (7 < uVar3) {
          iVar10 = (*(ushort *)(param_1 + 0xe) >> 1) + 3;
        }
        *(short *)((int)param_1 + 0x72) = (short)iVar10;
        uVar3 = iVar10 << 2;
        if (0xc80 < (uint)(iVar10 << 2)) {
          uVar3 = 0xc80;
        }
        *(short *)(param_1 + 0x1d) = (short)uVar3;
        *(undefined2 *)(param_1 + 0x16) = *(undefined2 *)((int)param_1 + 0x3a);
        *(short *)((int)param_1 + 0x5a) = (short)param_1[0xf];
        *(undefined1 *)((int)param_1 + 0x1d) = 0x13;
        FUN_ram_0005d5f6((short)param_1[2],0x80,0x25);
      }
    }
  }
  *(undefined1 *)(param_1 + 7) = 0;
  return;
}

