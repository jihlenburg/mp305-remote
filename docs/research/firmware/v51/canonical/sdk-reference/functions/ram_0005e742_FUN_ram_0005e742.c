/* Address: ram:0005e742; name: FUN_ram_0005e742; body bytes: 1002 */

undefined4 FUN_ram_0005e742(int param_1)

{
  byte bVar1;
  byte bVar2;
  uint *puVar3;
  undefined4 *puVar4;
  uint uVar5;
  undefined2 uVar6;
  int iVar7;
  undefined4 uVar8;
  byte *pbVar9;
  ushort uVar10;
  int iVar11;
  uint uVar12;
  int iVar13;
  byte *pbVar14;
  byte bVar15;
  
  gp = 0x20004000;
  iVar7 = FUN_ram_20001120(*(undefined4 *)(param_1 + 0x78),0,param_1 + 0x15,0);
  if (iVar7 != 0) {
    gp = 0x20004000;
    return 1;
  }
  pbVar9 = *(byte **)(param_1 + 0x78);
  bVar1 = *pbVar9;
  *(byte *)(param_1 + 0xd) = bVar1 & 0xf;
  bVar15 = pbVar9[1];
  uVar12 = (uint)bVar15;
  *(undefined1 *)(param_1 + 0x54) = 0;
  *(undefined1 *)(param_1 + 0x5c) = 0;
  *(byte *)(param_1 + 0xe) = bVar15;
  if ((bVar1 & 0xf) != 7) {
    gp = 0x20004000;
    return 0x80;
  }
  bVar1 = pbVar9[2];
  *(undefined1 *)(param_1 + 0x28) = 0;
  uVar5 = bVar1 & 0x3f;
  if (uVar12 <= uVar5) {
    gp = 0x20004000;
    return 3;
  }
  if (bVar1 >> 6 != 0) {
    gp = 0x20004000;
    return 5;
  }
  iVar7 = (uVar12 - 1) - uVar5;
  *(char *)(param_1 + 0x2e) = (char)iVar7;
  bVar1 = pbVar9[3];
  if ((bVar1 & 1) != 0) {
    gp = 0x20004000;
    return 0x11;
  }
  if ((bVar1 & 2) != 0) {
    gp = 0x20004000;
    return 0x12;
  }
  if ((bVar1 & 4) == 0) {
    pbVar14 = pbVar9 + 4;
    uVar5 = uVar5 - 1;
  }
  else {
    pbVar14 = pbVar9 + 5;
    uVar5 = uVar5 - 2;
  }
  uVar5 = uVar5 & 0xff;
  bVar15 = 1;
  if ((bVar1 & 8) != 0) {
    if ((*(uint *)(param_1 + 0x1c) & 8) != 0) {
      uVar10 = (pbVar14[1] & 0xf) << 8 | (ushort)*pbVar14;
      if (*(ushort *)(param_1 + 0x92) == uVar10) {
        bVar15 = (*(byte *)(param_1 + 0x82) >> 2 ^ 1) & 1;
      }
      else {
        *(ushort *)(param_1 + 0x92) = uVar10;
      }
    }
    pbVar14 = pbVar14 + 2;
    uVar5 = uVar5 - 2 & 0xff;
  }
  if ((bVar1 & 0x10) == 0) goto LAB_ram_0005e8aa;
  *(byte *)(param_1 + 0x24) = *pbVar14 & 0x3f;
  bVar1 = pbVar14[2];
  bVar2 = pbVar14[1];
  uVar10 = (ushort)((uint)bVar1 << 8) & 0x1f00 | (ushort)bVar2;
  *(ushort *)(param_1 + 0x26) = uVar10;
  if (uVar10 != 0) {
    if ((char)*pbVar14 < '\0') {
      iVar11 = 300;
    }
    else {
      iVar11 = 0x1e;
    }
    if (*(char *)(param_1 + 0xbc) == '\x03') {
      iVar13 = (uVar12 + 2) * 8;
      if (DAT_ram_20001e9f == '\0') {
        iVar13 = iVar13 + 0x4a;
LAB_ram_0005e96a:
        iVar13 = iVar13 << 3;
      }
      else {
        iVar13 = (iVar13 + 0xd7) * 2;
      }
    }
    else {
      if (*(char *)(param_1 + 0xbc) != '\x02') {
        iVar13 = uVar12 + 10;
        goto LAB_ram_0005e96a;
      }
      iVar13 = (uVar12 + 0xb) * 4;
    }
    iVar13 = ((uint)bVar1 << 8 & 0x1f00 | (uint)bVar2) * iVar11 - iVar13;
    if (iVar13 - 300U < 0x515) {
      *(ushort *)(param_1 + 0x3c) = (ushort)iVar7 & 0xff;
      puVar4 = DAT_ram_20001eb0;
      *(undefined1 *)(param_1 + 0x28) = 1;
      puVar4[3] = 0xd00f;
      puVar4 = DAT_ram_20001eb0;
      fence.i();
      DAT_ram_20001eb0[2] = 0x2000;
      DAT_ram_20001e98 = 0x80;
      puVar4[0x19] = (iVar13 + -299) * 2;
      puVar4[3] = 0xf00f;
    }
    else {
      *(undefined1 *)(param_1 + 0x28) = 2;
    }
  }
  pbVar14 = pbVar14 + 3;
  uVar5 = uVar5 - 3 & 0xff;
LAB_ram_0005e8aa:
  uVar8 = 0x16;
  if ((pbVar9[3] & 0x20) == 0) {
    if ((pbVar9[3] & 0x40) != 0) {
      bVar1 = *pbVar14;
      pbVar14 = pbVar14 + 1;
      *(byte *)(param_1 + 0x23) = bVar1;
      uVar5 = uVar5 - 1 & 0xff;
    }
    if (uVar5 != 0) {
      do {
        if ((pbVar14[1] == 0x28) && (*pbVar14 == 8)) {
          *(undefined1 *)(param_1 + 0x7c) = 0x12;
          *(undefined2 *)(param_1 + 0x90) = *(undefined2 *)(pbVar14 + 7);
          tmos_memcpy(param_1 + 0x8a,pbVar14 + 2,5);
        }
        uVar12 = (uint)*pbVar14;
        if (uVar5 <= uVar12) break;
        uVar5 = uVar5 + ~uVar12 & 0xff;
        pbVar14 = pbVar14 + uVar12 + 1;
      } while (uVar5 != 0);
    }
    if (((bVar15 != 0) && ((*(uint *)(param_1 + 0x1c) & 8) != 0)) &&
       ((*(byte *)(param_1 + 0x82) & 2) == 0)) {
      thunk_FUN_ram_00051e6a
                (*(undefined2 *)(param_1 + 0xb2),(int)*(char *)(param_1 + 0x23),
                 (int)*(char *)(param_1 + 0x15),0xff,*(undefined1 *)(param_1 + 0x28),
                 (uint)*(byte *)(param_1 + 0x2e),
                 *(int *)(param_1 + 0x78) +
                 ((uint)*(byte *)(param_1 + 0xe) - (uint)*(byte *)(param_1 + 0x2e)) + 2);
      while (*(char *)(param_1 + 0x28) == '\x01') {
        do {
        } while (DAT_ram_20001eb0[0x19] != 0);
        DAT_ram_20001eb0[3] = 0xd00f;
        puVar4 = DAT_ram_20001eb0;
        fence.i();
        DAT_ram_20001eb0[2] = 0x2000;
        DAT_ram_20001e98 = 0x80;
        puVar4[0x19] = 0x592;
        puVar4[3] = 0xf00f;
        DAT_ram_20001e94 = 0;
        DAT_ram_20001e99 = 0;
        *(undefined1 *)(param_1 + 0x28) = 0;
        DAT_ram_20001e95 = 0;
        *puVar4 = 1;
        puVar3 = DAT_ram_20001e88;
        *DAT_ram_20001e88 = *DAT_ram_20001e88 & 0xfffffe7f;
        *puVar3 = *puVar3 & 0xfffffe7f | 0x100;
        iVar7 = DAT_ram_20001efc;
        *(uint *)(DAT_ram_20001efc + 8) = *(uint *)(DAT_ram_20001efc + 8) | 0x330000;
        puVar4[0x14] = 0xd9;
        *(uint *)(iVar7 + 0x2c) = *(uint *)(iVar7 + 0x2c) & 0xfffffffd;
        *puVar3 = *puVar3 & 0xffffff80 | *(byte *)(param_1 + 0x24) & 0x7f;
        FUN_ram_200010ec();
        FUN_ram_00062262();
        if ((DAT_ram_20001e95 & 1) == 0) {
          uVar6 = *(undefined2 *)(param_1 + 0xb2);
LAB_ram_0005eae4:
          thunk_FUN_ram_00051e6a(uVar6,0x7f,0x7f,0xff,2,0,0);
          break;
        }
        DAT_ram_20001e95 = 0;
        iVar7 = FUN_ram_0005e55c(param_1);
        uVar6 = *(undefined2 *)(param_1 + 0xb2);
        if ((iVar7 != 0) || (*(char *)(param_1 + 0x28) == '\x02')) goto LAB_ram_0005eae4;
        thunk_FUN_ram_00051e6a
                  (uVar6,(int)*(char *)(param_1 + 0x23),(int)*(char *)(param_1 + 0x15),0xff,
                   *(char *)(param_1 + 0x28),(uint)*(byte *)(param_1 + 0x2e),
                   *(int *)(param_1 + 0x78) +
                   ((uint)*(byte *)(param_1 + 0xe) - (uint)*(byte *)(param_1 + 0x2e)) + 2);
      }
    }
    uVar8 = 0;
    if (*(byte *)(param_1 + 0x7c) < 2) {
      *(undefined1 *)(param_1 + 0x7c) = 2;
    }
  }
  return uVar8;
}

