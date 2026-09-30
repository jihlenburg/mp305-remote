/* Address: ram:0005649a; name: FUN_ram_0005649a; body bytes: 480 */

/* WARNING: Removing unreachable block (ram,0x0005657e) */

void FUN_ram_0005649a(undefined4 *param_1)

{
  ushort uVar1;
  short sVar2;
  int *piVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  longlong lVar10;
  
  piVar3 = (int *)DAT_ram_20001df0;
  gp = 0x20004000;
  if (DAT_ram_20001e04 < 2) {
    return;
  }
  iVar6 = (uint)*(ushort *)((int)param_1 + 0x1c6) + (uint)*(ushort *)((int)param_1 + 0x1ca) + 0x271;
  lVar10 = FUN_ram_0006bae2((uint)DAT_ram_20001b8c * iVar6,
                            (int)((longlong)iVar6 * (ulonglong)(uint)DAT_ram_20001b8c >> 0x20),
                            1000000,0);
  uVar4 = (uint)lVar10;
  do {
    if ((piVar3 == (int *)0x0) ||
       ((param_1 == piVar3 && (piVar3 = (int *)*param_1, piVar3 == (int *)0x0)))) {
      return;
    }
    if ((*(char *)((int)piVar3 + 0x1d) == '\0') &&
       (uVar7 = piVar3[0x23], uVar7 <= (uint)param_1[0x23])) {
      if ((uint)piVar3[0x24] <= (uint)param_1[0x24]) {
        uVar9 = (uint)DAT_ram_20001b8c;
        uVar5 = param_1[0x24] - piVar3[0x24];
        if (uVar5 < (uVar9 * 0xc80 + 400) / 800) {
          if ((uVar7 < uVar5) && (uVar7 != 0)) {
            uVar5 = uVar5 % uVar7;
          }
          if (uVar5 < uVar4) {
            uVar8 = uVar7 >> 1;
            if (uVar4 < uVar7 >> 1) {
              uVar8 = uVar4;
            }
            iVar6 = FUN_ram_0006bae2((uVar5 + uVar8) * 0x640,
                                     (int)((ulonglong)(uVar5 + uVar8) * 0x640 >> 0x20),uVar9,0);
            if (iVar6 + 1U != 1) {
              uVar1 = *(ushort *)(piVar3 + 0xe);
              uVar7 = (uint)uVar1;
              if (*(char *)((int)piVar3 + 0xb) == '\0') {
                *(ushort *)((int)piVar3 + 0x56) = uVar1;
                *(undefined2 *)(piVar3 + 0x16) = *(undefined2 *)((int)piVar3 + 0x3a);
                *(short *)(piVar3 + 0x15) = (short)(iVar6 + 1U >> 1);
                *(short *)((int)piVar3 + 0x5a) = (short)piVar3[0xf];
                *(undefined1 *)((int)piVar3 + 0x53) = 2;
                sVar2 = *(short *)((int)param_1 + 0x3e);
                *(undefined1 *)(piVar3 + 5) = 1;
                *(short *)(piVar3 + 0x17) = sVar2 + 10;
                piVar3[0x29] = piVar3[0x29] | 1;
                *(undefined1 *)((int)piVar3 + 0x1d) = 4;
              }
              else {
                uVar5 = (uint)*(ushort *)(param_1 + 0xe);
                if (uVar5 < uVar7) {
                  if (uVar7 != 0) {
                    uVar5 = uVar5 % uVar7;
                  }
                  iVar6 = FUN_ram_0006bae2((int)(lVar10 * 0x640),
                                           (int)((ulonglong)(lVar10 * 0x640) >> 0x20),uVar9,0);
                  uVar9 = iVar6 + 1U >> 1;
                  if ((uVar9 <= uVar5) && (uVar5 <= uVar7 - uVar9)) goto LAB_ram_00056600;
                }
                iVar6 = 6;
                if (7 < uVar7) {
                  iVar6 = (uVar1 >> 1) + 3;
                }
                *(short *)((int)piVar3 + 0x72) = (short)iVar6;
                uVar7 = iVar6 << 2;
                if (0xc80 < (uint)(iVar6 << 2)) {
                  uVar7 = 0xc80;
                }
                *(short *)(piVar3 + 0x1d) = (short)uVar7;
                *(undefined2 *)(piVar3 + 0x16) = *(undefined2 *)((int)piVar3 + 0x3a);
                *(short *)((int)piVar3 + 0x5a) = (short)piVar3[0xf];
                *(undefined1 *)((int)piVar3 + 0x1d) = 0x14;
                FUN_ram_0005d5f6((short)piVar3[2],0x80,0x25);
              }
            }
          }
        }
      }
    }
LAB_ram_00056600:
    piVar3 = (int *)*piVar3;
  } while( true );
}

