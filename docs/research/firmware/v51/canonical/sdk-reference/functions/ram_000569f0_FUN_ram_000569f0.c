/* Address: ram:000569f0; name: FUN_ram_000569f0; body bytes: 926 */

/* WARNING: Removing unreachable block (ram,0x00056b64) */
/* WARNING: Removing unreachable block (ram,0x00056b12) */
/* WARNING: Removing unreachable block (ram,0x00056d22) */
/* WARNING: Removing unreachable block (ram,0x00056b68) */

undefined4 FUN_ram_000569f0(int param_1)

{
  byte bVar1;
  ushort uVar2;
  undefined1 uVar3;
  short sVar4;
  undefined2 uVar5;
  uint uVar6;
  uint uVar7;
  
  gp = 0x20004000;
  if (*(char *)(param_1 + 10) == '\0') {
    return 1;
  }
  *(short *)(param_1 + 0x7e) = *(short *)(param_1 + 0x7e) + 1;
  bVar1 = *(byte *)(param_1 + 0xf);
  *(undefined1 *)(param_1 + 0x18) = 0;
  if ((bVar1 & 2) == 0) {
    if (*(ushort *)(param_1 + 0x3e) < 6) {
      gp = 0x20004000;
      return 0;
    }
    uVar3 = FUN_ram_00056968(param_1,0x3e);
    *(undefined1 *)(param_1 + 0x2a) = uVar3;
    gp = 0x20004000;
    return 2;
  }
  if ((bVar1 & 0x20) != 0) {
    *(byte *)(param_1 + 0xf) = bVar1 & 0xdf;
    *(undefined1 *)(param_1 + 0x2a) = 0;
    *(uint *)(param_1 + 0xa0) = *(uint *)(param_1 + 0xa0) | 4;
    if (*(char *)(param_1 + 0xb) == '\x01') {
      if (*(uint *)(param_1 + 0x94) == 0) {
        uVar6 = 0xffffffff;
      }
      else {
        uVar6 = ((uint)*(ushort *)(param_1 + 0x38) * 0x4e2) / *(uint *)(param_1 + 0x94);
      }
      uVar6 = uVar6 + DAT_ram_20001bd4 + 0x50;
      *(short *)(param_1 + 0x82) = (short)(uVar6 * 0x10000 >> 0x10);
      *(ushort *)(param_1 + 0x80) =
           (short)((uVar6 & 0xffff) << 1) + (ushort)*(byte *)(param_1 + 0x35) * 0x4e2;
    }
  }
  if ((*(byte *)(param_1 + 0x11) & 1) != 0) {
    if ((uint)*(ushort *)(param_1 + 0x5c) == (uint)*(ushort *)(param_1 + 0x3e)) {
      *(undefined2 *)(param_1 + 0x5e) = *(undefined2 *)(param_1 + 0x3a);
      *(ushort *)(param_1 + 0x3c) = *(ushort *)(param_1 + 0x5a);
      *(undefined1 *)(param_1 + 0x35) = *(undefined1 *)(param_1 + 0x53);
      *(undefined2 *)(param_1 + 0x36) = *(undefined2 *)(param_1 + 0x54);
      *(undefined2 *)(param_1 + 0x3a) = *(undefined2 *)(param_1 + 0x58);
      FUN_ram_00042194(*(undefined1 *)(param_1 + 0x28),(uint)*(ushort *)(param_1 + 0x5a) * 0x10 + -2
                      );
      *(undefined2 *)(param_1 + 0x7e) = 0;
      uVar6 = (uint)*(ushort *)(param_1 + 0x36);
      if (*(char *)(param_1 + 0xb) == '\0') {
        uVar6 = (uVar6 * DAT_ram_20001b8c + 400) / 800 + *(int *)(param_1 + 0x90) + 0x14;
        if ((-1 < DAT_ram_20001bd2) && (0xa8bfffff < uVar6)) {
          uVar6 = uVar6 + 0x57400000;
        }
        *(uint *)(param_1 + 0x90) = uVar6;
        *(undefined2 *)(param_1 + 0x38) = *(undefined2 *)(param_1 + 0x56);
        if (*(char *)(param_1 + 0x1d) != '\0') {
          FUN_ram_00055fb6(param_1);
        }
      }
      else {
        uVar2 = *(ushort *)(param_1 + 0x56);
        if ((*(byte *)(param_1 + 0x174) & 8) != 0) {
          if (uVar2 == 0) {
            sVar4 = -1;
          }
          else {
            sVar4 = (short)((int)(((uint)*(ushort *)(param_1 + 0x176) -
                                  (uint)*(ushort *)(param_1 + 0x3e)) *
                                 (uint)*(ushort *)(param_1 + 0x38)) / (int)(uint)uVar2);
          }
          *(ushort *)(param_1 + 0x176) = sVar4 + *(ushort *)(param_1 + 0x3e);
        }
        if (uVar6 != 0) {
          uVar6 = (DAT_ram_20001b8c * uVar6 + 400) / 800 + *(int *)(param_1 + 0x90);
          if ((-1 < DAT_ram_20001bd2) && (0xa8bfffff < uVar6)) {
            uVar6 = uVar6 + 0x57400000;
          }
          *(uint *)(param_1 + 0x90) = uVar6;
        }
        *(ushort *)(param_1 + 0x38) = uVar2;
      }
      uVar6 = (uint)DAT_ram_20001b8c;
      *(undefined2 *)(param_1 + 0x22) = 0;
      uVar7 = *(ushort *)(param_1 + 0x38) * uVar6;
      *(uint *)(param_1 + 0x8c) = uVar7 / 800;
      if (uVar6 == 0) {
        uVar5 = 0xffff;
      }
      else {
        uVar5 = (undefined2)(((uVar7 % 800) * 0x4e2) / uVar6);
      }
      *(undefined2 *)(param_1 + 0x20) = uVar5;
      *(undefined2 *)(param_1 + 0x24) = *(undefined2 *)(param_1 + 0x3e);
      *(byte *)(param_1 + 0xf) = *(byte *)(param_1 + 0xf) | 0x20;
      *(byte *)(param_1 + 0x11) = *(byte *)(param_1 + 0x11) & 0xfe;
    }
    else if ((int)(((uint)*(ushort *)(param_1 + 0x5c) - (uint)*(ushort *)(param_1 + 0x3e)) * 0x10000
                  ) < 0) goto LAB_ram_00056d5a;
  }
  if ((*(byte *)(param_1 + 0x11) & 2) != 0) {
    if ((int)(((uint)*(ushort *)(param_1 + 0x12e) - (uint)*(ushort *)(param_1 + 0x3e)) * 0x10000) <
        0) goto LAB_ram_00056d5a;
    if ((uint)*(ushort *)(param_1 + 0x12e) == (uint)*(ushort *)(param_1 + 0x3e)) {
      *(undefined4 *)(param_1 + 0x138) = 0;
      *(undefined4 *)(param_1 + 0x13c) = 0;
      tmos_memcpy(param_1 + 0x138,param_1 + 0x128,5);
      uVar3 = FUN_ram_000582da(param_1 + 0x138);
      *(undefined1 *)(param_1 + 0x12d) = uVar3;
      *(byte *)(param_1 + 0x11) = *(byte *)(param_1 + 0x11) & 0xfd;
    }
  }
  if ((*(byte *)(param_1 + 0x11) & 0x10) == 0) goto LAB_ram_00056c6a;
  if ((int)(((uint)*(ushort *)(param_1 + 0x14c) - (uint)*(ushort *)(param_1 + 0x3e)) * 0x10000) < 0)
  {
LAB_ram_00056d5a:
    uVar3 = FUN_ram_00056968(param_1,0x28);
    *(undefined1 *)(param_1 + 0x2a) = uVar3;
    gp = 0x20004000;
    return 0x28;
  }
  if ((uint)*(ushort *)(param_1 + 0x14c) != (uint)*(ushort *)(param_1 + 0x3e))
  goto LAB_ram_00056c6a;
  *(byte *)(param_1 + 0x11) = *(byte *)(param_1 + 0x11) & 0xef;
  bVar1 = *(byte *)(param_1 + 0x14a);
  if (bVar1 != 0) {
    if ((bVar1 & 2) == 0) {
      if ((bVar1 & 4) == 0) {
        *(undefined1 *)(param_1 + 0x146) = 0;
        goto LAB_ram_00056c2e;
      }
      uVar3 = 2;
    }
    else {
      uVar3 = 1;
    }
    *(undefined1 *)(param_1 + 0x146) = uVar3;
  }
LAB_ram_00056c2e:
  bVar1 = *(byte *)(param_1 + 0x14b);
  if (bVar1 != 0) {
    if ((bVar1 & 2) == 0) {
      if ((bVar1 & 4) == 0) {
        *(undefined1 *)(param_1 + 0x147) = 0;
        goto LAB_ram_00056c42;
      }
      uVar3 = 2;
    }
    else {
      uVar3 = 1;
    }
    *(undefined1 *)(param_1 + 0x147) = uVar3;
  }
LAB_ram_00056c42:
  FUN_ram_00055ca8(param_1);
  if (*(char *)(param_1 + 0x7a) != '\0') {
    *(uint *)(param_1 + 0xa0) = *(uint *)(param_1 + 0xa0) | 0x100;
  }
  *(undefined1 *)(param_1 + 0x2a) = 0;
  *(uint *)(param_1 + 0xa0) = *(uint *)(param_1 + 0xa0) | 0x200;
LAB_ram_00056c6a:
  if ((((*(byte *)(param_1 + 0x11) & 0x20) != 0) &&
      (uVar6 = (uint)*(ushort *)
                      (*(int *)(DAT_ram_20001db0 + 0x28) +
                       (uint)*(byte *)(DAT_ram_20001db0 + 4) * 0x58 + 0x1c),
      -1 < (int)((uVar6 - *(ushort *)(param_1 + 0x3e)) * 0x10000))) &&
     (*(ushort *)(param_1 + 0x14c) == uVar6)) {
    *(byte *)(param_1 + 0x11) = *(byte *)(param_1 + 0x11) & 0xdf;
  }
  if (((*(byte *)(param_1 + 0x29) & 0x40) != 0) &&
     (*(short *)(param_1 + 0x44) == *(short *)(param_1 + 0x3e))) {
    if (*(char *)(param_1 + 0x10) == 'J') {
      *(undefined1 *)(param_1 + 0x10) = 1;
    }
    *(uint *)(param_1 + 0xa4) = *(uint *)(param_1 + 0xa4) | 0x400;
  }
  return 0;
}

