/* Address: ram:00056dec; name: FUN_ram_00056dec; body bytes: 1988 */

/* WARNING: Removing unreachable block (ram,0x00057498) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_ram_00056dec(int param_1)

{
  char cVar1;
  undefined1 uVar2;
  undefined4 uVar3;
  byte bVar4;
  ushort uVar5;
  short sVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  undefined8 uVar11;
  uint uStack_28;
  uint uStack_24;
  
  gp = 0x20004000;
  uVar7 = *(uint *)(param_1 + 0xa0);
  if (uVar7 != 0) {
    if ((uVar7 & 2) != 0) {
      *(uint *)(param_1 + 0xa0) = uVar7 & 0xfffffffd;
      FUN_ram_0005d5f6(*(undefined2 *)(param_1 + 8),0x80,6);
    }
    if ((*(uint *)(param_1 + 0xa0) & 4) != 0) {
      *(uint *)(param_1 + 0xa0) = *(uint *)(param_1 + 0xa0) & 0xfffffffb;
      if ((*(byte *)(param_1 + 0x29) & 0x40) != 0) {
        *(uint *)(param_1 + 0xa4) = *(uint *)(param_1 + 0xa4) | 0x400;
        FUN_ram_00055d70(param_1);
      }
      if (*(char *)(param_1 + 0xb) == '\x01') {
        if (*(uint *)(param_1 + 0x94) == 0) {
          uVar7 = 0xffffffff;
        }
        else {
          uVar7 = ((uint)*(ushort *)(param_1 + 0x38) * 0x4e2) / *(uint *)(param_1 + 0x94);
        }
        uVar7 = uVar7 + DAT_ram_20001bd4 + 0x50;
        *(short *)(param_1 + 0x82) = (short)(uVar7 * 0x10000 >> 0x10);
        *(short *)(param_1 + 0x80) = (short)((uVar7 & 0xffff) << 1);
        uVar2 = 0x80;
        if (*(char *)(param_1 + 0x2a) != '\0') {
          uVar2 = 0x40;
        }
        *(undefined1 *)(param_1 + 0x1c) = uVar2;
        if (*(char *)(param_1 + 0x14) == '\0') {
          *(byte *)(param_1 + 0x29) = *(byte *)(param_1 + 0x29) | 1;
        }
        if (*(short *)(param_1 + 0x60) == 0) {
          FUN_ram_0005d5f6(*(undefined2 *)(param_1 + 8),0x80,3);
        }
        *(undefined2 *)(param_1 + 0x60) = 0;
      }
      else {
        *(undefined1 *)(param_1 + 0x1c) = 0x40;
        if (*(char *)(param_1 + 0x14) == '\0') {
          *(byte *)(param_1 + 0x29) = *(byte *)(param_1 + 0x29) | 1;
        }
        if (*(short *)(param_1 + 0x60) == 0) {
          FUN_ram_0005d5f6(*(undefined2 *)(param_1 + 8),0x80,3);
        }
      }
      *(undefined1 *)(param_1 + 0x14) = 0;
      *(undefined1 *)(param_1 + 0x1d) = 0;
    }
    if ((*(uint *)(param_1 + 0xa0) & 8) != 0) {
      *(uint *)(param_1 + 0xa0) = *(uint *)(param_1 + 0xa0) & 0xfffffff7;
      FUN_ram_0005d5f6(*(undefined2 *)(param_1 + 8),0x80,5);
      *(byte *)(param_1 + 0x29) = *(byte *)(param_1 + 0x29) | 4;
    }
    if ((*(uint *)(param_1 + 0xa0) & 0x10) != 0) {
      *(uint *)(param_1 + 0xa0) = *(uint *)(param_1 + 0xa0) & 0xffffffef;
      uVar3 = 8;
      if (*(char *)(param_1 + 0x4b) != '\0') {
        *(undefined1 *)(param_1 + 0x4b) = 0;
        uVar3 = 0x30;
      }
      FUN_ram_0005d5f6(*(undefined2 *)(param_1 + 8),0x81,uVar3);
      if ((*(char *)(param_1 + 0x4a) != '\0') && ((*(uint *)(param_1 + 0x108) & 0x10) != 0)) {
        FUN_ram_00055976(param_1,(*(ushort *)(param_1 + 0x48) & 0xfff) << 4);
      }
      *(byte *)(param_1 + 0x29) = *(byte *)(param_1 + 0x29) | 1;
    }
    if ((*(uint *)(param_1 + 0xa0) & 0x40) != 0) {
      *(uint *)(param_1 + 0xa0) = *(uint *)(param_1 + 0xa0) & 0xffffffbf;
      if ((8 < *(byte *)(param_1 + 0x4d)) && (*(char *)(param_1 + 0xb) == '\0')) {
        *(uint *)(param_1 + 0xa4) = *(uint *)(param_1 + 0xa4) | 0x10;
      }
      FUN_ram_0005d5f6(*(undefined2 *)(param_1 + 8),0x81,0xc);
    }
    if ((*(uint *)(param_1 + 0xa0) & 0x20) != 0) {
      *(uint *)(param_1 + 0xa0) = *(uint *)(param_1 + 0xa0) & 0xffffffdf;
      if ((*(char *)(param_1 + 0xb) == '\0') && ((*(uint *)(param_1 + 0x10c) & 0x80) != 0)) {
        *(uint *)(param_1 + 0xa4) = *(uint *)(param_1 + 0xa4) | 0x400000;
      }
      if ((*(uint *)(param_1 + 0x108) & 0x20) == 0) {
        uVar7 = *(uint *)(param_1 + 0xa4) & 0xfffff7ff;
LAB_ram_00057010:
        *(uint *)(param_1 + 0xa4) = uVar7;
      }
      else if (*(char *)(param_1 + 0xb) == '\0') {
        if (*(char *)(param_1 + 0x147) == '\x02') {
          uVar5 = 0xa90;
        }
        else {
          uVar5 = 0x148;
        }
        if (uVar5 < *(ushort *)(param_1 + 0x1b6)) {
          *(uint *)(param_1 + 0xa4) = *(uint *)(param_1 + 0xa4) | 0x800;
        }
        if (*(char *)(param_1 + 0x146) == '\x02') {
          uVar5 = 0xa90;
        }
        else {
          uVar5 = 0x148;
        }
        if (uVar5 < *(ushort *)(param_1 + 0x1ba)) {
          uVar7 = *(uint *)(param_1 + 0xa4) | 0x800;
          goto LAB_ram_00057010;
        }
      }
      FUN_ram_0005d5f6(*(undefined2 *)(param_1 + 8),0x80,4);
      *(byte *)(param_1 + 0x29) = *(byte *)(param_1 + 0x29) | 1;
    }
    if ((*(uint *)(param_1 + 0xa0) & 0x100) != 0) {
      *(uint *)(param_1 + 0xa0) = *(uint *)(param_1 + 0xa0) & 0xfffffeff;
      *(undefined1 *)(param_1 + 0x7a) = 0;
      FUN_ram_0005d5f6(*(undefined2 *)(param_1 + 8),0x80,7);
      *(byte *)(param_1 + 0x29) = *(byte *)(param_1 + 0x29) | 1;
    }
    if ((*(uint *)(param_1 + 0xa0) & 0x80) != 0) {
      *(uint *)(param_1 + 0xa0) = *(uint *)(param_1 + 0xa0) & 0xffffff7f;
      FUN_ram_0005d5f6(*(undefined2 *)(param_1 + 8),0x81,0x57);
    }
    if ((*(uint *)(param_1 + 0xa0) & 0x200) != 0) {
      *(uint *)(param_1 + 0xa0) = *(uint *)(param_1 + 0xa0) & 0xfffffdff;
      *(undefined1 *)(param_1 + 0x1e) = 0;
      *(undefined1 *)(param_1 + 0x143) =
           *(undefined1 *)((uint)*(byte *)(param_1 + 0x146) + param_1 + 0x166);
      uVar2 = FUN_ram_00061dd4();
      *(undefined1 *)(param_1 + 0x142) = uVar2;
      FUN_ram_00055afc(param_1);
      FUN_ram_0005d5f6(*(undefined2 *)(param_1 + 8),0x80,0xc);
      *(byte *)(param_1 + 0x29) = *(byte *)(param_1 + 0x29) | 1;
    }
    if ((int)(*(uint *)(param_1 + 0xa0) << 0x12) < 0) {
      *(uint *)(param_1 + 0xa0) = *(uint *)(param_1 + 0xa0) & 0xffffdfff;
    }
    if (*(int *)(param_1 + 0xa0) << 0x10 < 0) {
      uVar7 = FUN_ram_00042866(DAT_ram_20001d63,*(undefined1 *)(param_1 + 0x2f));
      *(uint *)(param_1 + 0x94) = uVar7;
      if (uVar7 == 0) {
        sVar6 = -1;
      }
      else {
        sVar6 = (short)(((uint)*(ushort *)(param_1 + 0x38) * 0x4e2) / uVar7);
      }
      *(ushort *)(param_1 + 0x82) = sVar6 + DAT_ram_20001bd4 + 0x50;
      *(byte *)(param_1 + 0x29) = *(byte *)(param_1 + 0x29) | 1;
      *(uint *)(param_1 + 0xa0) = *(uint *)(param_1 + 0xa0) & 0xffff7fff;
    }
    if ((*(uint *)(param_1 + 0xa0) & 1) != 0) {
      *(byte *)(param_1 + 0x29) = *(byte *)(param_1 + 0x29) | 1;
      uVar2 = FUN_ram_00056968(param_1,*(undefined1 *)(param_1 + 0x52));
      *(undefined1 *)(param_1 + 0x2a) = uVar2;
    }
  }
  iVar8 = (int)*(char *)(param_1 + 0x161);
  if (iVar8 != 0) {
    cVar1 = *(char *)(param_1 + 0x32);
    if (cVar1 - iVar8 < 7) {
      if (iVar8 - cVar1 < 7) goto LAB_ram_0005718c;
      *(uint *)(param_1 + 0xa4) = *(uint *)(param_1 + 0xa4) | 0x100000;
      uVar2 = 5;
    }
    else {
      *(uint *)(param_1 + 0xa4) = *(uint *)(param_1 + 0xa4) | 0x100000;
      uVar2 = 0xfb;
    }
    *(undefined1 *)(param_1 + 0x165) = uVar2;
    *(char *)(param_1 + 0x161) = cVar1;
  }
LAB_ram_0005718c:
  bVar4 = *(byte *)(param_1 + 0x16a);
  if ((bVar4 & 2) == 0) goto LAB_ram_00057234;
  iVar8 = (int)*(char *)(param_1 + 0x32);
  if (iVar8 < *(char *)(param_1 + 0x162)) {
    *(uint *)(param_1 + 0xa4) = *(uint *)(param_1 + 0xa4) | 0x100000;
    *(undefined1 *)(param_1 + 0x165) = 4;
  }
  if (*(char *)(param_1 + 0x163) < iVar8) {
    *(uint *)(param_1 + 0xa4) = *(uint *)(param_1 + 0xa4) | 0x100000;
    *(undefined1 *)(param_1 + 0x165) = 0xfc;
  }
  if (*(char *)(param_1 + 0x160) != 0x7f) {
    iVar8 = (*(char *)(param_1 + 0x160) - iVar8) * 0x1000000 >> 0x18;
    if ((iVar8 < (int)((uint)*(byte *)(param_1 + 0x16d) - (uint)*(byte *)(param_1 + 0x16e))) &&
       ((bVar4 & 0x10) == 0)) {
      bVar4 = bVar4 & 0x8f | 0x10;
    }
    else if (((int)((uint)*(byte *)(param_1 + 0x16b) + (uint)*(byte *)(param_1 + 0x16c)) < iVar8) &&
            ((bVar4 & 0x40) == 0)) {
      bVar4 = bVar4 & 0x8f | 0x40;
    }
    else {
      if (((iVar8 < (int)((uint)*(byte *)(param_1 + 0x16d) + (uint)*(byte *)(param_1 + 0x16e))) ||
          ((int)((uint)*(byte *)(param_1 + 0x16b) - (uint)*(byte *)(param_1 + 0x16c)) < iVar8)) ||
         ((bVar4 & 0x20) != 0)) goto LAB_ram_00057212;
      bVar4 = bVar4 & 0x8f | 0x20;
    }
    *(byte *)(param_1 + 0x16a) = bVar4;
    *(short *)(param_1 + 0x172) = *(short *)(param_1 + 0x170) + 1;
  }
LAB_ram_00057212:
  if ((*(short *)(param_1 + 0x172) != 0) &&
     (sVar6 = *(short *)(param_1 + 0x172) + -1, *(short *)(param_1 + 0x172) = sVar6, sVar6 == 0)) {
    FUN_ram_0005d5f6(*(undefined2 *)(param_1 + 8),0x80,0x20);
  }
LAB_ram_00057234:
  if (*(char *)(param_1 + 10) != '\0') {
    if (((*(int *)(param_1 + 0x120) != 0) && (*(char *)(param_1 + 0x1a) == '\0')) &&
       (iVar8 = FUN_ram_0005d5f6(*(undefined2 *)(param_1 + 8),0x80,0), iVar8 == 0)) {
      *(undefined1 *)(param_1 + 0x1a) = 1;
    }
    if (*(short *)(param_1 + 0x42) != 0) {
      FUN_ram_0005d5f6(*(undefined2 *)(param_1 + 8),0x81,0x13);
    }
  }
  if (((((*(byte *)(param_1 + 0x174) & 0x10) != 0) &&
       (*(byte *)(param_1 + 0x174) = *(byte *)(param_1 + 0x174) & 0xef,
       (*(uint *)(param_1 + 0xa4) & 2) == 0)) && (*(char *)(param_1 + 0x10) != '\x15')) &&
     ((*(byte *)(param_1 + 0x11) & 2) == 0)) {
    iVar8 = 0;
    uVar10 = 0;
    uVar7 = 0;
    do {
      uVar9 = 3 << (((int)(char)iVar8 & 3U) << 1);
      if (uVar9 != (*(byte *)(((int)(char)iVar8 >> 2) + param_1 + 0x17d) & uVar9)) {
        uVar11 = FUN_ram_0006bab6(1,0,iVar8);
        uVar10 = uVar10 | (uint)uVar11;
        uVar7 = uVar7 | (uint)((ulonglong)uVar11 >> 0x20);
      }
      iVar8 = iVar8 + 1;
    } while (iVar8 != 0x25);
    uStack_28 = *(uint *)(param_1 + 0x138) & uVar10;
    uStack_24 = *(uint *)(param_1 + 0x13c) & uVar7;
    uVar7 = FUN_ram_000582da(&uStack_28);
    if (uVar7 <= *(byte *)(param_1 + 0x135)) {
      uStack_28 = 0xffffffff;
      uStack_24 = 1;
      FUN_ram_200012e0((int)((*(byte *)(param_1 + 0x32) - 10) * 0x1000000) >> 0x18,&uStack_28);
    }
    if ((*(uint *)(param_1 + 0x138) != uStack_28) || (*(uint *)(param_1 + 0x13c) != uStack_24)) {
      tmos_memcpy(param_1 + 0x128,&uStack_28,5);
      *(uint *)(param_1 + 0xa4) = *(uint *)(param_1 + 0xa4) | 2;
    }
  }
  if ((*(byte *)(param_1 + 0x174) & 9) == 9) {
    uVar5 = *(ushort *)(param_1 + 0x3e);
    if (((uint)*(ushort *)(param_1 + 0x176) <= (uint)uVar5) &&
       (-1 < (int)(((uint)uVar5 - (uint)*(ushort *)(param_1 + 0x176)) * 0x10000))) {
      *(byte *)(param_1 + 0x174) = *(byte *)(param_1 + 0x174) & 0xf7;
      if (*(ushort *)(param_1 + 0x38) == 0) {
        sVar6 = -1;
      }
      else {
        sVar6 = (short)(((uint)*(byte *)(param_1 + 0x175) * 0xa0) /
                       (uint)*(ushort *)(param_1 + 0x38));
      }
      *(ushort *)(param_1 + 0x176) = sVar6 + uVar5 + 1;
      *(uint *)(param_1 + 0xa4) = *(uint *)(param_1 + 0xa4) | 0x800000;
    }
  }
  if (*(byte *)(param_1 + 0x29) != 0) {
    if ((*(byte *)(param_1 + 0x29) & 4) != 0) {
      FUN_ram_000559cc(param_1,64000,*(undefined1 *)(param_1 + 0x10));
      *(byte *)(param_1 + 0x29) = *(byte *)(param_1 + 0x29) & 0xfb;
    }
    if ((*(byte *)(param_1 + 0x29) & 1) != 0) {
      if (*(char *)(param_1 + 0x27) != -1) {
        FUN_ram_00042494();
        *(undefined1 *)(param_1 + 0x27) = 0xff;
      }
      *(byte *)(param_1 + 0x29) = *(byte *)(param_1 + 0x29) & 0xfe;
    }
    if ((*(byte *)(param_1 + 0x29) & 2) != 0) {
      FUN_ram_00042194(*(undefined1 *)(param_1 + 0x28),(uint)*(ushort *)(param_1 + 0x3c) * 0x10 + -2
                      );
      *(byte *)(param_1 + 0x29) = *(byte *)(param_1 + 0x29) & 0xfd;
    }
    if ((*(byte *)(param_1 + 0x29) & 8) != 0) {
      FUN_ram_000559cc(param_1,*(short *)(param_1 + 0x3c) * 0x10 + -2,3);
      *(byte *)(param_1 + 0x29) = *(byte *)(param_1 + 0x29) & 0xf7;
    }
    if ((*(byte *)(param_1 + 0x29) & 0x10) != 0) {
      *(byte *)(param_1 + 0x29) = *(byte *)(param_1 + 0x29) & 0x8f;
      FUN_ram_00042494(*(undefined1 *)(param_1 + 0x26));
      *(undefined1 *)(param_1 + 0x26) = 0xff;
    }
    if ((*(byte *)(param_1 + 0x29) & 0x20) != 0) {
      *(byte *)(param_1 + 0x29) = *(byte *)(param_1 + 0x29) & 0xdf;
      FUN_ram_00042194(*(undefined1 *)(param_1 + 0x26),(uint)*(ushort *)(param_1 + 0x48) << 4);
    }
  }
  if ((*(byte *)(param_1 + 0x1c) & 0xc0) != 0) {
    if (*(char *)(param_1 + 0xb) == '\x01') {
      FUN_ram_000562d4();
    }
    else {
      FUN_ram_000561de(param_1);
    }
  }
  if ((*(ushort *)(param_1 + 0x3e) != 0) && ((uint)*(ushort *)(param_1 + 0x3e) % 100 == 0)) {
    if (((DAT_ram_20001e7c & 2) != 0) && (DAT_ram_20001bec != (code *)0x0)) {
      (*DAT_ram_20001bec)(9,CONCAT22(DAT_ram_20001d70,_DAT_ram_20001d72));
      (*DAT_ram_20001bec)(10,DAT_ram_20001d6e);
      (*DAT_ram_20001bec)(0xb,(int)*(short *)(param_1 + 0x30));
      (*DAT_ram_20001bec)(0xc,(int)*(char *)(param_1 + 0x32));
    }
    DAT_ram_20001d6e = 0;
    _DAT_ram_20001d70 = 0;
  }
  return;
}

