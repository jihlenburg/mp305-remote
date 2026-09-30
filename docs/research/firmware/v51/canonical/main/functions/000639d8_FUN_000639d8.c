/* Address: 000639d8; name: FUN_000639d8; body bytes: 468 */

void FUN_000639d8(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6,
                 int param_7,int param_8,int param_9,int param_10,int param_11)

{
  byte bVar1;
  short sVar2;
  short sVar3;
  int iVar4;
  int iVar5;
  undefined1 uVar6;
  uint uVar7;
  int iVar8;
  undefined4 *puVar9;
  uint uVar10;
  int iVar11;
  undefined4 *puVar12;
  int iVar13;
  undefined4 uVar14;
  int iVar15;
  int local_68;
  
  iVar13 = 0;
  do {
    if (param_9 <= iVar13) {
      return;
    }
    uVar10 = param_5 + (iVar13 * param_7 >> 8);
    uVar7 = param_6 + (iVar13 * param_8 >> 8);
    iVar4 = (int)uVar10 >> 8;
    iVar5 = (int)uVar7 >> 8;
    if ((((iVar4 < 0) || (param_2 <= iVar4)) || (iVar5 < 0)) || (param_3 <= iVar5)) {
      *(undefined4 *)(param_10 + iVar13 * 4) = 0;
    }
    else {
      uVar10 = uVar10 & 0xff;
      uVar7 = uVar7 & 0xff;
      if (uVar10 < 0x80) {
        iVar15 = -1;
        iVar11 = 0x7f - uVar10;
      }
      else {
        iVar15 = 1;
        iVar11 = uVar10 - 0x80;
      }
      if (uVar7 < 0x80) {
        iVar8 = 0x7f - uVar7;
        local_68 = -1;
      }
      else {
        iVar8 = uVar7 - 0x80;
        local_68 = 1;
      }
      puVar9 = (undefined4 *)(iVar5 * param_4 + param_1 + iVar4 * 4);
      puVar12 = (undefined4 *)(param_10 + iVar13 * 4);
      uVar14 = *puVar9;
      *puVar12 = uVar14;
      sVar3 = (short)iVar8;
      sVar2 = (short)iVar11;
      if (((param_11 == 0) || (iVar4 + iVar15 < 0)) ||
         ((param_2 + -1 < iVar4 + iVar15 ||
          ((iVar5 + local_68 < 0 || (param_3 + -1 < iVar5 + local_68)))))) {
        if (((iVar4 == 0) && (iVar15 < 0)) || ((iVar4 == param_2 + -1 && (0 < iVar15)))) {
          bVar1 = *(byte *)((int)puVar12 + 3);
          sVar3 = sVar2;
        }
        else {
          if (((iVar5 != 0) || (-1 < local_68)) && ((iVar5 != param_3 + -1 || (local_68 < 1))))
          goto LAB_00063ba0;
          bVar1 = *(byte *)((int)puVar12 + 3);
        }
        uVar6 = (undefined1)((uint)((int)(short)(ushort)bVar1 * (int)(short)(0x7f - sVar3)) >> 7);
      }
      else {
        uVar7 = puVar9[iVar15];
        uVar10 = *(uint *)(local_68 * param_4 + (int)puVar9);
        if (uVar10 >> 0x18 == 0) {
          *(char *)((int)puVar12 + 3) =
               (char)((uint)((int)(short)(ushort)*(byte *)((int)puVar12 + 3) *
                            (int)(short)(0xff - sVar3)) >> 8);
        }
        else {
          iVar5 = FUN_0003ff18(uVar14,uVar10);
          if (iVar5 == 0) {
            if (*(byte *)((int)puVar12 + 3) != 0) {
              *(char *)((int)puVar12 + 3) =
                   (char)((uint)((int)(short)(ushort)(byte)(uVar10 >> 0x18) * (int)sVar3 +
                                (int)(short)(ushort)*(byte *)((int)puVar12 + 3) *
                                (int)(short)(0xff - sVar3)) >> 8);
            }
            uVar14 = FUN_0004045a(uVar10 & 0xffffff | iVar8 << 0x18,*puVar12);
            *puVar12 = uVar14;
          }
        }
        if (uVar7 >> 0x18 != 0) {
          iVar5 = FUN_0003ff18(*puVar12,uVar7);
          if (iVar5 == 0) {
            if (*(byte *)((int)puVar12 + 3) != 0) {
              *(char *)((int)puVar12 + 3) =
                   (char)((uint)((int)(short)(ushort)(byte)(uVar7 >> 0x18) * (int)sVar2 +
                                (int)(short)(ushort)*(byte *)((int)puVar12 + 3) *
                                (int)(short)(0xff - sVar2)) >> 8);
            }
            uVar14 = FUN_0004045a(uVar7 & 0xffffff | iVar11 << 0x18,*puVar12);
            *puVar12 = uVar14;
          }
          goto LAB_00063ba0;
        }
        uVar6 = (undefined1)
                ((uint)((int)(short)(ushort)*(byte *)((int)puVar12 + 3) * (int)(short)(0xff - sVar2)
                       ) >> 8);
      }
      *(undefined1 *)((int)puVar12 + 3) = uVar6;
    }
LAB_00063ba0:
    iVar13 = iVar13 + 1;
  } while( true );
}

