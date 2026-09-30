/* Address: ram:00053ed0; name: FUN_ram_00053ed0; body bytes: 2362 */

/* WARNING: Removing unreachable block (ram,0x00054346) */
/* WARNING: Removing unreachable block (ram,0x0005407a) */
/* WARNING: Removing unreachable block (ram,0x0005437a) */
/* WARNING: Removing unreachable block (ram,0x000544b8) */
/* WARNING: Removing unreachable block (ram,0x000546e4) */
/* WARNING: Removing unreachable block (ram,0x00054166) */

void FUN_ram_00053ed0(int param_1)

{
  char cVar1;
  uint *puVar2;
  undefined1 *puVar3;
  int iVar4;
  byte bVar5;
  uint uVar6;
  char cVar7;
  uint uVar8;
  int iVar9;
  uint uVar10;
  uint uStack_34;
  undefined4 uStack_30;
  uint uStack_2c;
  uint uStack_28;
  undefined2 uStack_24;
  
  iVar4 = DAT_ram_20001eb0;
  gp = 0x20004000;
  *(undefined4 *)(DAT_ram_20001eb0 + 100) = 0xa0;
  puVar2 = DAT_ram_20001e88;
  DAT_ram_20001e88[0xb] = DAT_ram_20001e88[0xb] & 0xfffffffc | 1;
  *puVar2 = *puVar2 & 0xfffffe7f;
  *puVar2 = *puVar2 & 0xfffffe7f | 0x100;
  iVar9 = DAT_ram_20001efc;
  *(uint *)(DAT_ram_20001efc + 8) = *(uint *)(DAT_ram_20001efc + 8) | 0x330000;
  *(undefined4 *)(iVar4 + 0x50) = 0xda;
  *(uint *)(iVar9 + 0x2c) = *(uint *)(iVar9 + 0x2c) & 0xfffffffd;
  *puVar2 = *puVar2 & 0xffffff80 | *(byte *)(param_1 + 0x62) & 0x7f;
  puVar3 = *(undefined1 **)(param_1 + 0x4c);
  *(undefined1 *)(param_1 + 0x10) = 7;
  *puVar3 = 7;
  puVar3[3] = 0;
  puVar3[2] = 1;
  bVar5 = *(byte *)(param_1 + 0x5f);
  if ((bVar5 == 3) || (bVar5 == 6)) {
    puVar3[3] = 1;
    tmos_memcpy(puVar3 + 4,param_1 + 0x36,6);
    puVar3[2] = puVar3[2] + '\x06';
    if (*(char *)(param_1 + 0x5f) == '\x06') {
      puVar3[3] = puVar3[3] | 2;
      if (((*(byte *)(param_1 + 0x35) & 2) == 0) ||
         (*(char *)(*(int *)(param_1 + 0x30) + 0x12) == '\0')) {
        if (*(char *)(param_1 + 0x3d) != '\0') {
          **(byte **)(param_1 + 0x4c) = **(byte **)(param_1 + 0x4c) | 0x80;
        }
        tmos_memcpy(puVar3 + 10,param_1 + 0x3e,6);
      }
      else {
        tmos_memcpy(puVar3 + 10,*(int *)(param_1 + 0x30) + 0x14,6);
        **(byte **)(param_1 + 0x4c) = **(byte **)(param_1 + 0x4c) | 0x80;
      }
      puVar3[2] = puVar3[2] + '\x06';
    }
    puVar3[3] = puVar3[3] | 8;
    *(char *)(*(int *)(param_1 + 0x4c) + (uint)(byte)puVar3[2] + 3) =
         (char)*(undefined2 *)(param_1 + 0x6a);
    *(byte *)(*(int *)(param_1 + 0x4c) + (uint)(byte)puVar3[2] + 4) =
         (byte)((ushort)*(undefined2 *)(param_1 + 0x6a) >> 8) & 0xf | *(char *)(param_1 + 0x61) << 4
    ;
    bVar5 = puVar3[2] + 2;
    puVar3[2] = bVar5;
    iVar4 = DAT_ram_20001eb0;
    if (*(ushort *)(param_1 + 0x1c) == 0) {
      uVar8 = 0;
      uVar10 = 0;
    }
    else {
      iVar9 = -2;
      if ((*(byte *)(param_1 + 0x60) & 0x40) != 0) {
        iVar9 = -3;
      }
      uVar10 = iVar9 - (uint)bVar5 & 0xff;
      if ((*(uint *)(param_1 + 0x54) & 4) != 0) {
        uVar10 = uVar10 - 0x12 & 0xff;
      }
      uVar8 = 0;
      if (uVar10 < *(ushort *)(param_1 + 0x1c)) {
        uVar10 = uVar10 - 3 & 0xff;
        if (*(char *)(param_1 + 99) == '\x02') {
          iVar9 = 0x4290;
        }
        else {
          iVar9 = 0x428;
          if (*(char *)(param_1 + 99) != '\x01') {
            iVar9 = 0x848;
          }
        }
        uVar8 = (iVar9 + 0x1b7U) / 0x1e;
        DAT_ram_20001dd4 = DAT_ram_20001dd4 | 0x10;
        *(undefined4 *)(DAT_ram_20001eb0 + 8) = 0x1000;
        *(uint *)(iVar4 + 0x60) = uVar8 * 0x3c;
        puVar3[3] = puVar3[3] | 0x10;
        *(undefined1 *)((uint)bVar5 + *(int *)(param_1 + 0x4c) + 3) =
             *(undefined1 *)(param_1 + 0x62);
        *(char *)(*(int *)(param_1 + 0x4c) + (uint)(byte)puVar3[2] + 4) = (char)uVar8;
        *(byte *)(*(int *)(param_1 + 0x4c) + (uint)(byte)puVar3[2] + 5) =
             *(char *)(param_1 + 99) << 5 | (byte)(uVar8 >> 8);
        puVar3[2] = puVar3[2] + '\x03';
        *(uint *)(param_1 + 0x78) = *(int *)(param_1 + 0x28) + uVar10;
        *(short *)(param_1 + 0x70) = *(short *)(param_1 + 0x1c) - (short)uVar10;
      }
    }
    iVar4 = DAT_ram_20001eb0;
    uVar6 = *(uint *)(param_1 + 0x54) & 0xc;
    if ((uVar6 == 4) || ((uVar6 == 0xc && (*(char *)(param_1 + 0x61) == *(char *)(param_1 + 0x7f))))
       ) {
      if ((*(uint *)(param_1 + 0x54) & 8) == 0) {
        cVar7 = *(char *)(param_1 + 99);
        if ((puVar3[3] & 0x10) == 0) {
          iVar9 = (uint)*(ushort *)(param_1 + 0x1c) + (uint)(byte)puVar3[2];
          if (cVar7 == '\x02') {
            iVar9 = iVar9 * 0x40 + 2000;
          }
          else if (cVar7 == '\x01') {
            iVar9 = (iVar9 + 0x1f) * 4;
          }
          else {
            iVar9 = (iVar9 + 0x1e) * 8;
          }
          uVar8 = (iVar9 + 0x545U) / 0x1e;
          DAT_ram_20001dd5 = DAT_ram_20001dd5 | 1;
          *(undefined4 *)(DAT_ram_20001eb0 + 8) = 0x8000;
          *(uint *)(iVar4 + 0x6c) = uVar8 * 0x3c;
          *(char *)(param_1 + 0x80) = cVar7;
          *(undefined1 *)(param_1 + 0x7f) = *(undefined1 *)(param_1 + 0x61);
        }
        else {
          uVar6 = (uint)*(ushort *)(param_1 + 0x70);
          if (cVar7 == '\x02') {
            iVar4 = uVar6 * 0x40 + 0x3d0;
          }
          else if (cVar7 == '\x01') {
            iVar4 = (uVar6 + 0x16) * 4;
          }
          else {
            iVar4 = (uVar6 + 0xe) * 8;
          }
          uVar8 = (uVar8 * 0x1e + iVar4 + 0x2b1) / 0x1e;
        }
      }
      else {
        uVar6 = *(uint *)(param_1 + 0x94);
        uVar8 = (*DAT_ram_20001c00)();
        if ((-1 < DAT_ram_20001bd2) && (uVar6 < uVar8)) {
          uVar6 = uVar6 + 0xa8c00000;
        }
        iVar4 = FUN_ram_0006bae2((uVar6 - uVar8) * 1000000,
                                 (int)((ulonglong)(uVar6 - uVar8) * 1000000 >> 0x20),
                                 DAT_ram_20001b8c,0);
        if (iVar4 < 0x13b) goto LAB_ram_00054202;
        uVar8 = (iVar4 + 0xf) / 0x1e;
      }
      tmos_memset(&uStack_34,0,0x12);
      uStack_34 = uStack_34 & 0xe000 | uVar8 & 0x1fff | (uint)*(ushort *)(param_1 + 0x86) << 0x10;
      uStack_30 = *(undefined4 *)(param_1 + 0x98);
      uStack_2c = (DAT_ram_20001d63 & 7) << 5 | *(uint *)(param_1 + 0x9c) & 0x1f |
                  *(uint *)(param_1 + 0x8c) << 8;
      uStack_28 = *(uint *)(param_1 + 0x8c) >> 0x18 | *(int *)(param_1 + 0x90) << 8;
      uStack_24 = *(undefined2 *)(param_1 + 0x88);
      tmos_memcpy(*(int *)(param_1 + 0x4c) + (byte)puVar3[2] + 3,&uStack_34,0x12);
      puVar3[3] = puVar3[3] | 0x20;
      puVar3[2] = puVar3[2] + '\x12';
    }
LAB_ram_00054202:
    if ((*(byte *)(param_1 + 0x60) & 0x40) != 0) {
      iVar4 = *(int *)(param_1 + 0x4c);
      puVar3[3] = puVar3[3] | 0x40;
      *(undefined1 *)(iVar4 + (uint)(byte)puVar3[2] + 3) = *(undefined1 *)(param_1 + 0x15);
      puVar3[2] = puVar3[2] + '\x01';
    }
    if (*(ushort *)(param_1 + 0x1c) != 0) {
      if (uVar10 < *(ushort *)(param_1 + 0x1c)) {
        tmos_memcpy(*(int *)(param_1 + 0x4c) + (byte)puVar3[2] + 3,*(undefined4 *)(param_1 + 0x28),
                    uVar10);
      }
      else {
        tmos_memcpy();
        uVar10 = (uint)*(byte *)(param_1 + 0x1c);
      }
      goto LAB_ram_0005423c;
    }
LAB_ram_0005423a:
    uVar10 = 0;
  }
  else {
    if ((bVar5 - 2 & 0xfd) == 0) {
      puVar3[3] = 1;
      tmos_memcpy(puVar3 + 4,param_1 + 0x36,6);
      cVar7 = puVar3[2];
      puVar3[2] = cVar7 + 6U;
      puVar3[3] = puVar3[3] | 8;
      uVar10 = 0;
      *(char *)((uint)(byte)(cVar7 + 6U) + *(int *)(param_1 + 0x4c) + 3) =
           (char)*(undefined2 *)(param_1 + 0x6a);
      *(byte *)(*(int *)(param_1 + 0x4c) + (uint)(byte)puVar3[2] + 4) =
           (byte)((ushort)*(undefined2 *)(param_1 + 0x6a) >> 8) & 0xf |
           *(char *)(param_1 + 0x61) << 4;
      bVar5 = puVar3[2] + 2;
      puVar3[2] = bVar5;
      iVar4 = DAT_ram_20001eb0;
      if (*(char *)(param_1 + 0x5f) == '\x04') {
        iVar9 = -2;
        if ((*(byte *)(param_1 + 0x60) & 0x40) != 0) {
          iVar9 = -3;
        }
        uVar10 = iVar9 - (uint)bVar5 & 0xff;
        if (uVar10 < *(ushort *)(param_1 + 0x1c)) {
          uVar10 = uVar10 - 3 & 0xff;
          if (*(char *)(param_1 + 99) == '\x02') {
            iVar9 = 0x4290;
          }
          else {
            iVar9 = 0x428;
            if (*(char *)(param_1 + 99) != '\x01') {
              iVar9 = 0x848;
            }
          }
          uVar8 = (iVar9 + 0x1b7U) / 0x1e;
          DAT_ram_20001dd4 = DAT_ram_20001dd4 | 0x10;
          *(undefined4 *)(DAT_ram_20001eb0 + 8) = 0x1000;
          *(uint *)(iVar4 + 0x60) = uVar8 * 0x3c;
          puVar3[3] = puVar3[3] | 0x10;
          *(undefined1 *)((uint)bVar5 + *(int *)(param_1 + 0x4c) + 3) =
               *(undefined1 *)(param_1 + 0x62);
          *(char *)(*(int *)(param_1 + 0x4c) + (uint)(byte)puVar3[2] + 4) = (char)uVar8;
          *(byte *)(*(int *)(param_1 + 0x4c) + (uint)(byte)puVar3[2] + 5) =
               (byte)(uVar8 >> 8) | *(char *)(param_1 + 99) << 5;
          puVar3[2] = puVar3[2] + '\x03';
          *(uint *)(param_1 + 0x78) = *(int *)(param_1 + 0x28) + uVar10;
          *(short *)(param_1 + 0x70) = *(short *)(param_1 + 0x1c) - (short)uVar10;
        }
      }
      if ((*(byte *)(param_1 + 0x60) & 0x40) != 0) {
        puVar3[3] = puVar3[3] | 0x40;
        *(undefined1 *)(*(int *)(param_1 + 0x4c) + (uint)(byte)puVar3[2] + 3) =
             *(undefined1 *)(param_1 + 0x15);
        puVar3[2] = puVar3[2] + '\x01';
      }
      if ((*(char *)(param_1 + 0x5f) == '\x04') && (*(ushort *)(param_1 + 0x1c) != 0)) {
        if (uVar10 < *(ushort *)(param_1 + 0x1c)) {
          tmos_memcpy(*(int *)(param_1 + 0x4c) + (byte)puVar3[2] + 3,*(undefined4 *)(param_1 + 0x28)
                      ,uVar10);
        }
        else {
          tmos_memcpy();
          uVar10 = (uint)*(byte *)(param_1 + 0x1c);
        }
      }
      else {
        uVar10 = 0;
      }
      cVar1 = *(char *)(param_1 + 0x5f);
      cVar7 = '\x04';
    }
    else {
      if ((bVar5 & 0xfb) != 1) goto LAB_ram_0005423a;
      puVar3[3] = 1;
      tmos_memcpy(puVar3 + 4,param_1 + 0x36,6);
      puVar3[2] = puVar3[2] + '\x06';
      puVar3[3] = puVar3[3] | 2;
      if (*(char *)(param_1 + 0x3d) != '\0') {
        **(byte **)(param_1 + 0x4c) = **(byte **)(param_1 + 0x4c) | 0x80;
      }
      if (((*(byte *)(param_1 + 0x35) & 2) == 0) ||
         (*(char *)(*(int *)(param_1 + 0x30) + 0x12) == '\0')) {
        if (*(char *)(param_1 + 0x3d) != '\0') {
          **(byte **)(param_1 + 0x4c) = **(byte **)(param_1 + 0x4c) | 0x80;
        }
        tmos_memcpy(puVar3 + 10,param_1 + 0x3e,6);
      }
      else {
        tmos_memcpy(puVar3 + 10,*(int *)(param_1 + 0x30) + 0x14,6);
        **(byte **)(param_1 + 0x4c) = **(byte **)(param_1 + 0x4c) | 0x80;
      }
      cVar7 = puVar3[2];
      puVar3[2] = cVar7 + 6U;
      puVar3[3] = puVar3[3] | 8;
      uVar10 = 0;
      *(char *)((uint)(byte)(cVar7 + 6U) + *(int *)(param_1 + 0x4c) + 3) =
           (char)*(undefined2 *)(param_1 + 0x6a);
      *(byte *)(*(int *)(param_1 + 0x4c) + (uint)(byte)puVar3[2] + 4) =
           (byte)((ushort)*(undefined2 *)(param_1 + 0x6a) >> 8) & 0xf |
           *(char *)(param_1 + 0x61) << 4;
      bVar5 = puVar3[2] + 2;
      puVar3[2] = bVar5;
      iVar4 = DAT_ram_20001eb0;
      if (*(char *)(param_1 + 0x5f) == '\x01') {
        iVar9 = -2;
        if ((*(byte *)(param_1 + 0x60) & 0x40) != 0) {
          iVar9 = -3;
        }
        uVar10 = iVar9 - (uint)bVar5 & 0xff;
        if (uVar10 < *(ushort *)(param_1 + 0x1c)) {
          uVar10 = uVar10 - 3 & 0xff;
          if (*(char *)(param_1 + 99) == '\x02') {
            iVar9 = 0x4290;
          }
          else {
            iVar9 = 0x428;
            if (*(char *)(param_1 + 99) != '\x01') {
              iVar9 = 0x848;
            }
          }
          uVar8 = (iVar9 + 0x1b7U) / 0x1e;
          DAT_ram_20001dd4 = DAT_ram_20001dd4 | 0x10;
          *(undefined4 *)(DAT_ram_20001eb0 + 8) = 0x1000;
          *(uint *)(iVar4 + 0x60) = uVar8 * 0x3c;
          puVar3[3] = puVar3[3] | 0x10;
          *(undefined1 *)((uint)bVar5 + *(int *)(param_1 + 0x4c) + 3) =
               *(undefined1 *)(param_1 + 0x62);
          *(char *)(*(int *)(param_1 + 0x4c) + (uint)(byte)puVar3[2] + 4) = (char)uVar8;
          *(byte *)(*(int *)(param_1 + 0x4c) + (uint)(byte)puVar3[2] + 5) =
               (byte)(uVar8 >> 8) | *(char *)(param_1 + 99) << 5;
          puVar3[2] = puVar3[2] + '\x03';
          *(uint *)(param_1 + 0x78) = *(int *)(param_1 + 0x28) + uVar10;
          *(short *)(param_1 + 0x70) = *(short *)(param_1 + 0x1c) - (short)uVar10;
        }
      }
      if ((*(byte *)(param_1 + 0x60) & 0x40) != 0) {
        puVar3[3] = puVar3[3] | 0x40;
        *(undefined1 *)(*(int *)(param_1 + 0x4c) + (uint)(byte)puVar3[2] + 3) =
             *(undefined1 *)(param_1 + 0x15);
        puVar3[2] = puVar3[2] + '\x01';
      }
      if ((*(char *)(param_1 + 0x5f) == '\x01') && (*(ushort *)(param_1 + 0x1c) != 0)) {
        if (uVar10 < *(ushort *)(param_1 + 0x1c)) {
          tmos_memcpy(*(int *)(param_1 + 0x4c) + (byte)puVar3[2] + 3,*(undefined4 *)(param_1 + 0x28)
                      ,uVar10);
        }
        else {
          tmos_memcpy();
          uVar10 = (uint)*(byte *)(param_1 + 0x1c);
        }
      }
      else {
        uVar10 = 0;
      }
      cVar1 = *(char *)(param_1 + 0x5f);
      cVar7 = '\x01';
    }
    if (cVar1 == cVar7) {
      DAT_ram_20001dd4 = DAT_ram_20001dd4 & 0xf0 | 5;
    }
    else {
      DAT_ram_20001dd4 = DAT_ram_20001dd4 & 0xf0 | 6;
    }
  }
LAB_ram_0005423c:
  bVar5 = puVar3[2];
  *(byte *)(param_1 + 0x11) = (char)uVar10 + (bVar5 & 0x3f) + 1;
  puVar3[2] = *(char *)(param_1 + 0x5e) << 6 | bVar5;
  if (((*(byte *)(param_1 + 0x35) & 1) != 0) || (*(char *)(param_1 + 0x34) == '\x02')) {
    **(byte **)(param_1 + 0x4c) = **(byte **)(param_1 + 0x4c) | 0x40;
  }
  *(undefined1 *)(*(int *)(param_1 + 0x4c) + 1) = *(undefined1 *)(param_1 + 0x11);
  *(undefined1 *)(param_1 + 0xb) = 0x96;
  *(undefined4 *)(DAT_ram_20001eb0 + 0x70) = *(undefined4 *)(param_1 + 0x4c);
  FUN_ram_00042570(FUN_ram_00055184,0);
  DAT_ram_20001e97 = 0;
  DAT_ram_20001e98 = 0;
  *(uint *)(DAT_ram_20001eb0 + 4) = *(uint *)(DAT_ram_20001eb0 + 4) | 1;
  FUN_ram_200011be(0,*(undefined1 *)(param_1 + 99),*(undefined1 *)(param_1 + 0x11));
  return;
}

