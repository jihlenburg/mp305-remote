/* Address: ram:0005480a; name: FUN_ram_0005480a; body bytes: 1436 */

/* WARNING: Removing unreachable block (ram,0x00054b50) */
/* WARNING: Removing unreachable block (ram,0x00054c98) */
/* WARNING: Removing unreachable block (ram,0x00054ae4) */
/* WARNING: Removing unreachable block (ram,0x00054cba) */

void FUN_ram_0005480a(int param_1)

{
  uint *puVar1;
  uint *puVar2;
  byte *pbVar3;
  undefined2 uVar4;
  int iVar5;
  byte bVar6;
  undefined1 uVar7;
  uint uVar8;
  uint uVar9;
  
  puVar1 = DAT_ram_20001eb0;
  gp = 0x20004000;
  if (DAT_ram_20001dfc != 0) {
    return;
  }
  if ((*DAT_ram_20001eb0 & 3) != 0) {
    DAT_ram_20001eb0[0x14] = DAT_ram_20001eb0[0x14] & 0xfffffff8;
    *puVar1 = *puVar1 | 8;
  }
  puVar2 = DAT_ram_20001eb0;
  DAT_ram_20001eb0[0x19] = 0xa0;
  puVar1 = DAT_ram_20001e88;
  DAT_ram_20001e88[0xb] = DAT_ram_20001e88[0xb] & 0xfffffffc | 1;
  *puVar1 = *puVar1 & 0xfffffe7f;
  *puVar1 = *puVar1 & 0xfffffe7f | 0x100;
  iVar5 = DAT_ram_20001efc;
  *(uint *)(DAT_ram_20001efc + 8) = *(uint *)(DAT_ram_20001efc + 8) | 0x330000;
  puVar2[0x14] = 0xda;
  *(uint *)(iVar5 + 0x2c) = *(uint *)(iVar5 + 0x2c) & 0xfffffffd;
  *puVar1 = *puVar1 & 0xffffff80 | *(byte *)(param_1 + 10) & 0x7f;
  bVar6 = *(byte *)(param_1 + 0xe) & 0xf;
  *(byte *)(param_1 + 0x10) = bVar6;
  **(byte **)(param_1 + 0x4c) = bVar6;
  pbVar3 = *(byte **)(param_1 + 0x4c);
  if (bVar6 != 7) {
    if (bVar6 == 1) {
      *(undefined1 *)(param_1 + 0x11) = 0xc;
      if (((*(byte *)(param_1 + 0x35) & 2) == 0) ||
         (*(char *)(*(int *)(param_1 + 0x30) + 0x12) == '\0')) {
        if (*(char *)(param_1 + 0x3d) != '\0') {
          *pbVar3 = *pbVar3 | 0x80;
        }
        pbVar3 = *(byte **)(param_1 + 0x4c);
        uVar4 = 6;
        iVar5 = param_1 + 0x3e;
        goto LAB_ram_00054d64;
      }
      tmos_memcpy(pbVar3 + 8,*(int *)(param_1 + 0x30) + 0x14,6);
      **(byte **)(param_1 + 0x4c) = **(byte **)(param_1 + 0x4c) | 0x80;
    }
    else {
      uVar4 = *(undefined2 *)(param_1 + 0x1c);
      iVar5 = *(int *)(param_1 + 0x28);
      *(byte *)(param_1 + 0x11) = (char)uVar4 + 6U & 0x3f;
LAB_ram_00054d64:
      tmos_memcpy(pbVar3 + 8,iVar5,uVar4);
    }
    tmos_memcpy(*(int *)(param_1 + 0x4c) + 2,param_1 + 0x36,6);
    if ((DAT_ram_20001e28 << 0x11 < 0) && ((*(byte *)(param_1 + 0xe) & 0xe) == 0)) {
      **(byte **)(param_1 + 0x4c) = **(byte **)(param_1 + 0x4c) | 0x20;
    }
    uVar7 = 0x92;
    goto LAB_ram_0005497e;
  }
  pbVar3[3] = 0;
  pbVar3[2] = 1;
  if (*(char *)(param_1 + 0x5f) == '\x03') {
    if (((*(short *)(param_1 + 0x1c) == 0) && (uVar8 = *(uint *)(param_1 + 0x54) & 0xc, uVar8 != 4))
       && ((uVar8 != 0xc || (*(char *)(param_1 + 0x61) != *(char *)(param_1 + 0x7f))))) {
      pbVar3[3] = 1;
      tmos_memcpy(pbVar3 + 4,param_1 + 0x36,6);
      bVar6 = pbVar3[2] + 6;
      pbVar3[2] = bVar6;
      if ((*(byte *)(param_1 + 0x60) & 0x40) != 0) {
        pbVar3[3] = pbVar3[3] | 0x40;
        iVar5 = *(int *)(param_1 + 0x4c);
LAB_ram_00054948:
        *(undefined1 *)((uint)bVar6 + iVar5 + 3) = *(undefined1 *)(param_1 + 0x15);
        pbVar3[2] = pbVar3[2] + 1;
      }
      goto LAB_ram_0005495c;
    }
    pbVar3[3] = 8;
    pbVar3[4] = (byte)*(undefined2 *)(param_1 + 0x6a);
    *(byte *)(*(int *)(param_1 + 0x4c) + 5) =
         (byte)((ushort)*(undefined2 *)(param_1 + 0x6a) >> 8) & 0xf | *(char *)(param_1 + 0x61) << 4
    ;
    uVar8 = (uint)(byte)(pbVar3[2] + 2);
    pbVar3[2] = pbVar3[2] + 2;
    puVar1 = DAT_ram_20001eb0;
    if (DAT_ram_20001dd4 == '\x01') {
      if (*(char *)(param_1 + 100) == '\x02') {
        iVar5 = uVar8 * 0x40 + 0x3d0;
      }
      else {
        iVar5 = (uVar8 + 0xe) * 8;
      }
      bVar6 = *(byte *)(param_1 + 0x18);
      *(short *)(param_1 + 0x72) = (short)iVar5;
      DAT_ram_20001dd4 = '\x02';
      puVar1[2] = 0x1000;
      uVar9 = (((iVar5 + 0xa0) * (uint)bVar6 - 0x50 & 0xffff) + 0x167) / 0x1e;
      uVar4 = (undefined2)uVar9;
      puVar1[0x18] = uVar9 * 0x3c;
    }
    else {
      puVar1 = DAT_ram_20001eb0 + 0x18;
      DAT_ram_20001eb0[0x19] = (DAT_ram_20001eb0[0x18] >> 1 & 0x1f) + DAT_ram_20001eb0[0x19];
      DAT_ram_20001dd4 = '\x03';
      uVar4 = (undefined2)(*puVar1 / 0x3c);
    }
LAB_ram_00054af6:
    pbVar3[3] = pbVar3[3] | 0x10;
    *(byte *)(uVar8 + *(int *)(param_1 + 0x4c) + 3) = *(byte *)(param_1 + 0x62) | 0x40;
    *(char *)(*(int *)(param_1 + 0x4c) + (uint)pbVar3[2] + 4) = (char)uVar4;
    *(byte *)(*(int *)(param_1 + 0x4c) + (uint)pbVar3[2] + 5) =
         (byte)((ushort)uVar4 >> 8) & 0x1f | *(char *)(param_1 + 99) << 5;
    pbVar3[2] = pbVar3[2] + 3;
  }
  else {
    if ((*(char *)(param_1 + 0x5f) != '\x06') || (*(short *)(param_1 + 0x1c) != 0)) {
      pbVar3[3] = 8;
      pbVar3[4] = (byte)*(undefined2 *)(param_1 + 0x6a);
      *(byte *)(*(int *)(param_1 + 0x4c) + 5) =
           (byte)((ushort)*(undefined2 *)(param_1 + 0x6a) >> 8) & 0xf |
           *(char *)(param_1 + 0x61) << 4;
      uVar8 = (uint)(byte)(pbVar3[2] + 2);
      pbVar3[2] = pbVar3[2] + 2;
      puVar1 = DAT_ram_20001eb0;
      if (DAT_ram_20001dd4 == '\x01') {
        if (*(char *)(param_1 + 100) == '\x02') {
          iVar5 = uVar8 * 0x40 + 0x3d0;
        }
        else {
          iVar5 = (uVar8 + 0xf) * 8;
        }
        bVar6 = *(byte *)(param_1 + 0x18);
        *(short *)(param_1 + 0x72) = (short)iVar5;
        DAT_ram_20001dd4 = '\x02';
        puVar1[2] = 0x1000;
        uVar9 = (((iVar5 + 0xa0) * (uint)bVar6 - 0x50 & 0xffff) + 0x167) / 0x1e;
        uVar4 = (undefined2)uVar9;
        puVar1[0x18] = uVar9 * 0x3c;
      }
      else {
        puVar1 = DAT_ram_20001eb0 + 0x18;
        DAT_ram_20001eb0[0x19] = (DAT_ram_20001eb0[0x18] >> 1 & 0x1f) + DAT_ram_20001eb0[0x19];
        DAT_ram_20001dd4 = '\x03';
        uVar4 = (undefined2)(*puVar1 / 0x3c);
      }
      goto LAB_ram_00054af6;
    }
    pbVar3[3] = 1;
    tmos_memcpy(pbVar3 + 4,param_1 + 0x36);
    pbVar3[2] = pbVar3[2] + 6;
    pbVar3[3] = pbVar3[3] | 2;
    if (((*(byte *)(param_1 + 0x35) & 2) == 0) ||
       (*(char *)(*(int *)(param_1 + 0x30) + 0x12) == '\0')) {
      if (*(char *)(param_1 + 0x3d) != '\0') {
        **(byte **)(param_1 + 0x4c) = **(byte **)(param_1 + 0x4c) | 0x80;
      }
      tmos_memcpy(pbVar3 + 10,param_1 + 0x3e,6);
    }
    else {
      tmos_memcpy(pbVar3 + 10,*(int *)(param_1 + 0x30) + 0x14,6);
      **(byte **)(param_1 + 0x4c) = **(byte **)(param_1 + 0x4c) | 0x80;
    }
    bVar6 = pbVar3[2] + 6;
    pbVar3[2] = bVar6;
    if ((*(byte *)(param_1 + 0x60) & 0x40) != 0) {
      iVar5 = *(int *)(param_1 + 0x4c);
      pbVar3[3] = pbVar3[3] | 0x40;
      goto LAB_ram_00054948;
    }
LAB_ram_0005495c:
    DAT_ram_20001dd4 = '\0';
  }
  bVar6 = pbVar3[2];
  *(byte *)(param_1 + 0x11) = (bVar6 & 0x3f) + 1;
  pbVar3[2] = *(char *)(param_1 + 0x5e) << 6 | bVar6;
  uVar7 = 0x94;
LAB_ram_0005497e:
  *(undefined1 *)(param_1 + 0xb) = uVar7;
  if (((*(byte *)(param_1 + 0x35) & 1) != 0) || (*(char *)(param_1 + 0x34) == '\x02')) {
    **(byte **)(param_1 + 0x4c) = **(byte **)(param_1 + 0x4c) | 0x40;
  }
  *(undefined1 *)(*(int *)(param_1 + 0x4c) + 1) = *(undefined1 *)(param_1 + 0x11);
  DAT_ram_20001eb0[1] = DAT_ram_20001eb0[1] | 1;
  DAT_ram_20001e88[0xb] =
       DAT_ram_20001e88[0xb] & 0x81ffffff | (*(byte *)(param_1 + 0x68) & 0x3f) << 0x19;
  puVar1 = DAT_ram_20001e88;
  DAT_ram_40001040 = 0xa8;
  if (*(char *)(param_1 + 0x68) < '\x0e') {
    DAT_ram_40001022 = DAT_ram_40001022 & 0xffef;
  }
  else {
    DAT_ram_40001022 = DAT_ram_40001022 | 0x10;
  }
  DAT_ram_20001e88[2] = 0x8e89bed6;
  puVar1[1] = 0x555555;
  uVar7 = *(undefined1 *)(param_1 + 100);
  DAT_ram_20001eb0[0x1c] = *(uint *)(param_1 + 0x4c);
  FUN_ram_00042570(FUN_ram_00055184,0);
  FUN_ram_0006219c();
  DAT_ram_20001e97 = 0;
  DAT_ram_20001e9b = 2;
  DAT_ram_20001e98 = 0;
  FUN_ram_200011be(0,uVar7,*(undefined1 *)(param_1 + 0x11));
  return;
}

