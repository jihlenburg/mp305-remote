/* Address: ram:0005ef72; name: FUN_ram_0005ef72; body bytes: 1534 */

undefined4 FUN_ram_0005ef72(int param_1)

{
  byte bVar1;
  byte bVar2;
  byte *pbVar3;
  undefined1 uVar4;
  int iVar5;
  uint uVar6;
  byte bVar7;
  ushort uVar8;
  uint uVar9;
  int iVar10;
  byte *pbVar11;
  int *piVar12;
  undefined4 uStack_44;
  undefined4 uStack_40;
  uint uStack_3c;
  uint uStack_38;
  undefined2 uStack_34;
  
  gp = 0x20004000;
  iVar5 = FUN_ram_20001120(*(undefined4 *)(param_1 + 0x78),0,param_1 + 0x15,0);
  if (iVar5 != 0) {
    gp = 0x20004000;
    return 1;
  }
  pbVar11 = *(byte **)(param_1 + 0x78);
  bVar7 = *pbVar11;
  *(byte *)(param_1 + 0xd) = bVar7 & 0xf;
  bVar1 = pbVar11[1];
  *(byte *)(param_1 + 0xe) = bVar1;
  if ((bVar7 & 0xf) != 7) {
    gp = 0x20004000;
    return 0x80;
  }
  bVar7 = pbVar11[2];
  bVar2 = bVar7 >> 6;
  *(byte *)(param_1 + 0x28) = bVar2;
  bVar7 = bVar7 & 0x3f;
  if (bVar1 <= bVar7) {
    gp = 0x20004000;
    return 3;
  }
  if (((byte)(bVar7 + 1) < bVar1) && (bVar2 == 2)) {
    gp = 0x20004000;
    return 5;
  }
  *(byte *)(param_1 + 0x2e) = (bVar1 - 1) - bVar7;
  pbVar3 = pbVar11 + 4;
  if ((pbVar11[3] & 1) != 0) {
    if (*(char *)(param_1 + 0x54) == '\0') {
      *(undefined1 *)(param_1 + 0x54) = 1;
      *(byte *)(param_1 + 0x55) = (byte)((int)(uint)*pbVar11 >> 6) & 1;
      tmos_memcpy(param_1 + 0x56,pbVar3,6);
    }
    else {
      iVar5 = tmos_memcmp(param_1 + 0x56,pbVar3,6);
      if (iVar5 == 0) {
        gp = 0x20004000;
        return 0x11;
      }
    }
    pbVar3 = pbVar11 + 10;
  }
  if ((pbVar11[3] & 2) != 0) {
    if (*(char *)(param_1 + 0x5c) == '\0') {
      *(undefined1 *)(param_1 + 0x5c) = 1;
      *(byte *)(param_1 + 0x5d) = **(byte **)(param_1 + 0x78) >> 7;
      tmos_memcpy(param_1 + 0x5e,pbVar3,6);
    }
    else {
      bVar7 = **(byte **)(param_1 + 0x78);
      if (*(char *)(param_1 + 0x5c) == '\x02') {
        if (-1 < (char)bVar7) {
          gp = 0x20004000;
          return 0x12;
        }
      }
      else if (*(byte *)(param_1 + 0x5d) != bVar7 >> 7) {
        gp = 0x20004000;
        return 0x12;
      }
      iVar5 = tmos_memcmp(param_1 + 0x5e,pbVar3,6);
      if (iVar5 == 0) {
        gp = 0x20004000;
        return 0x12;
      }
    }
    pbVar3 = pbVar3 + 6;
    *(byte *)(param_1 + 0x28) = *(byte *)(param_1 + 0x28) | 4;
  }
  iVar5 = FUN_ram_0005dbe8(param_1);
  if (iVar5 == 0) {
    gp = 0x20004000;
    return 8;
  }
  bVar7 = pbVar11[3];
  if ((bVar7 & 4) != 0) {
    pbVar3 = pbVar3 + 1;
  }
  if ((bVar7 & 8) != 0) {
    if (*(byte *)(param_1 + 0x29) != pbVar3[1] >> 4) {
      gp = 0x20004000;
      return 0x14;
    }
    uVar8 = (pbVar3[1] & 0xf) << 8 | (ushort)*pbVar3;
    if (*(ushort *)(param_1 + 0x2a) != uVar8) {
      *(ushort *)(param_1 + 0x2a) = uVar8;
    }
    pbVar3 = pbVar3 + 2;
  }
  if ((bVar7 & 0x10) != 0) {
    if (bVar2 != 0) {
      gp = 0x20004000;
      return 0x15;
    }
    *(byte *)(param_1 + 0x24) = *pbVar3 & 0x3f;
    uVar8 = (pbVar3[2] & 0x1f) << 8 | (ushort)pbVar3[1];
    *(ushort *)(param_1 + 0x26) = uVar8;
    if ((char)*pbVar3 < '\0') {
      *(ushort *)(param_1 + 0x26) = uVar8 | 0x8000;
    }
    pbVar3 = pbVar3 + 3;
    if (*(short *)(param_1 + 0x26) != 0) {
      *(byte *)(param_1 + 0x28) = *(byte *)(param_1 + 0x28) | 0x20;
    }
  }
  if ((bVar7 & 0x20) == 0) {
    *(undefined2 *)(param_1 + 0x3e) = 0;
    goto LAB_ram_0005f194;
  }
  if (bVar2 != 0) {
    gp = 0x20004000;
    return 0x16;
  }
  tmos_memcpy(&uStack_44,pbVar3,0x12);
  *(undefined2 *)(param_1 + 0x3e) = uStack_44._2_2_;
  if ((*(uint *)(param_1 + 0x1c) & 0xe) == 2) {
    if ((*(byte *)(param_1 + 0x82) & 1) == 0) {
      if (((*(char *)(param_1 + 0xb4) != *(char *)(param_1 + 0x29)) ||
          (*(byte *)(param_1 + 0xb5) != (*(byte *)(param_1 + 0x55) & 1))) ||
         (iVar5 = tmos_memcmp(param_1 + 0xb6,param_1 + 0x56,6), iVar5 != 1)) goto LAB_ram_0005f18c;
      *(undefined1 *)(param_1 + 0xb1) = 0;
      *(undefined2 *)(param_1 + 0xb2) = 1;
LAB_ram_0005f230:
      *(undefined1 *)(param_1 + 0x7c) = 1;
    }
    else {
      for (piVar12 = (int *)DAT_ram_20001de4; piVar12 != (int *)0x0; piVar12 = (int *)*piVar12) {
        if (((*(char *)(piVar12 + 1) == *(char *)(param_1 + 0x29)) &&
            (*(byte *)((int)piVar12 + 5) == (*(byte *)(param_1 + 0x55) & 1))) &&
           (iVar5 = tmos_memcmp((int)piVar12 + 6,param_1 + 0x56,6), iVar5 == 1)) {
          *(undefined1 *)(param_1 + 0xb1) = 0;
          *(undefined2 *)(param_1 + 0xb2) = 1;
          *(undefined1 *)(param_1 + 0xb4) = *(undefined1 *)(param_1 + 0x29);
          *(undefined1 *)(param_1 + 0xb5) = *(undefined1 *)(param_1 + 0x55);
          tmos_memcpy(param_1 + 0xb6,param_1 + 0x56,6);
          goto LAB_ram_0005f230;
        }
      }
LAB_ram_0005f18c:
      if (*(char *)(param_1 + 0x7c) == '\0') goto LAB_ram_0005f192;
    }
    *(byte *)(param_1 + 0xbf) = (byte)(uStack_3c >> 5) & 7;
    *(char *)(param_1 + 0xbc) = *(char *)(param_1 + 0x25) + '\x01';
    *(uint *)(param_1 + 0xac) = uStack_3c & 0x1f;
    *(char *)(param_1 + 0xbd) = (char)*(undefined2 *)(param_1 + 0x3e);
    *(char *)(param_1 + 0xbe) = (char)((ushort)*(undefined2 *)(param_1 + 0x3e) >> 8);
    *(uint *)(param_1 + 0x98) = uStack_38 >> 8;
    *(uint *)(param_1 + 0x94) = uStack_38 << 0x18 | uStack_3c >> 8;
    *(undefined2 *)(param_1 + 0x88) = uStack_34;
    *(undefined4 *)(param_1 + 0xa8) = uStack_40;
    uVar4 = FUN_ram_000582da(param_1 + 0xa8);
    *(undefined1 *)(param_1 + 0x8f) = uVar4;
    if ((uStack_44 & 0x2000) == 0) {
      iVar5 = (uStack_44 & 0x1fff) * 0x1e;
    }
    else {
      iVar5 = (uStack_44 & 0x1fff) * 300;
      if ((uStack_44 & 0x4000) != 0) {
        iVar5 = iVar5 + 0x258000;
      }
    }
    uVar9 = (uint)*(byte *)(param_1 + 0xe);
    if (*(char *)(param_1 + 0x25) == '\x02') {
      iVar10 = (uVar9 + 2) * 8;
      if (DAT_ram_20001e9f == '\0') {
        uVar9 = iVar5 + (iVar10 + 0x4a) * -8;
      }
      else {
        uVar9 = iVar5 + (iVar10 + 0xd7) * -2;
      }
    }
    else if (*(char *)(param_1 + 0x25) == '\x01') {
      uVar9 = iVar5 + (uVar9 + 0xb) * -4;
    }
    else {
      uVar9 = iVar5 + (uVar9 + 10) * -8;
    }
    if (uVar9 - 300 < 0x4afda8) {
      uVar6 = (uint)DAT_ram_20001b8c;
      *(undefined1 *)(param_1 + 0x80) = 0;
      iVar5 = FUN_ram_0006bae2(uVar6 * uVar9,(int)((ulonglong)uVar6 * (ulonglong)uVar9 >> 0x20),
                               1000000,0);
      iVar10 = (*DAT_ram_20001c00)();
      uVar6 = iVar10 + iVar5;
      if ((-1 < DAT_ram_20001bd2) && (0xa8bfffff < uVar6)) {
        uVar6 = uVar6 + 0x57400000;
      }
      *(uint *)(param_1 + 0xa0) = uVar6;
      if ((int)uVar9 < 0x501) {
        if (*(char *)(param_1 + 0x7d) != -1) {
          FUN_ram_00042494();
        }
        iVar5 = (*DAT_ram_20001c00)();
        uVar9 = iVar5 + 1;
        if ((-1 < DAT_ram_20001bd2) && (0xa8bfffff < uVar9)) {
          uVar9 = iVar5 + 0x57400001;
        }
      }
      else {
        if (*(char *)(param_1 + 0x7d) != -1) {
          FUN_ram_00042494();
        }
        uVar9 = *(uint *)(param_1 + 0xa0);
        uVar6 = (uint)DAT_ram_20001bd5;
        if ((DAT_ram_20001bd2 < '\0') || (uVar6 <= uVar9)) {
          uVar9 = uVar9 - uVar6;
        }
        else {
          uVar9 = uVar9 + (-0x57400000 - uVar6);
        }
      }
      FUN_ram_0004201e(&LAB_ram_0005ec12,param_1,uVar9,param_1 + 0x7d,0);
      if (*(char *)(param_1 + 0x7d) != -1) {
        *(undefined2 *)(param_1 + 0x92) = 0xffff;
        *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) | 4;
      }
    }
  }
LAB_ram_0005f192:
  pbVar3 = pbVar3 + 0x12;
LAB_ram_0005f194:
  if ((pbVar11[3] & 0x40) != 0) {
    *(byte *)(param_1 + 0x23) = *pbVar3;
  }
  iVar5 = FUN_ram_0005dd3a(param_1);
  if (iVar5 == 1) {
    if (((bVar2 == 2) && ((*(byte *)(param_1 + 0xf) & 1) != 0)) &&
       (*(char *)(param_1 + 0x54) != '\0')) {
      if (*(char *)(param_1 + 0x11) == '\0') {
        FUN_ram_0005e0de(param_1);
        gp = 0x20004000;
        return 0;
      }
      *(char *)(param_1 + 0x11) = *(char *)(param_1 + 0x11) + -1;
    }
    FUN_ram_00062262();
    FUN_ram_0005dd6c(param_1);
    if ((*(byte *)(param_1 + 0x28) & 0x20) != 0) {
      uVar9 = (uint)*(ushort *)(param_1 + 0x26);
      iVar5 = 0x1e;
      if ((short)*(ushort *)(param_1 + 0x26) < 0) {
        uVar9 = uVar9 & 0x1fff;
        iVar5 = 300;
      }
      iVar5 = uVar9 * iVar5;
      uVar9 = (uint)*(byte *)(param_1 + 0xe);
      if (*(char *)(param_1 + 0x25) == '\x02') {
        iVar10 = (uVar9 + 2) * 8;
        if (DAT_ram_20001e9f == '\0') {
          uVar9 = iVar5 + (iVar10 + 0x4a) * -8;
        }
        else {
          uVar9 = iVar5 + (iVar10 + 0xd7) * -2;
        }
      }
      else if (*(char *)(param_1 + 0x25) == '\x01') {
        uVar9 = iVar5 + (uVar9 + 0xb) * -4;
      }
      else {
        uVar9 = iVar5 + (uVar9 + 10) * -8;
      }
      if (0x4afda8 < uVar9 - 300) {
        gp = 0x20004000;
        return 0x21;
      }
      if (uVar9 < 0x641) {
        *(undefined4 *)(DAT_ram_20001eb0 + 0xc) = 0xd00f;
        iVar5 = DAT_ram_20001eb0;
        fence.i();
        *(undefined4 *)(DAT_ram_20001eb0 + 8) = 0x2000;
        DAT_ram_20001e98 = 0x80;
        *(uint *)(iVar5 + 100) = (uVar9 - 299) * 2;
        *(undefined4 *)(iVar5 + 0xc) = 0xf00f;
        *(undefined1 *)(param_1 + 10) = 0xa5;
        *(ushort *)(param_1 + 0x3c) = (ushort)*(byte *)(param_1 + 0x2e);
      }
    }
  }
  return 0;
}

