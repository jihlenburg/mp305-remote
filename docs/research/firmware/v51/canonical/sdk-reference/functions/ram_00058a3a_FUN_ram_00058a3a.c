/* Address: ram:00058a3a; name: FUN_ram_00058a3a; body bytes: 790 */

/* WARNING: Removing unreachable block (ram,0x00058bd6) */
/* WARNING: Removing unreachable block (ram,0x00058cec) */

void FUN_ram_00058a3a(int param_1)

{
  undefined2 uVar1;
  char cVar2;
  int *piVar3;
  byte *pbVar4;
  uint uVar5;
  ushort uVar6;
  byte bVar7;
  undefined4 uVar8;
  int iVar9;
  uint uVar10;
  int iVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  
  gp = 0x20004000;
  if (*(char *)(param_1 + 0x39) == '\b') {
    *(undefined1 *)(param_1 + 6) = 0xb5;
    FUN_ram_00061f0a(*(undefined1 *)(param_1 + 0x3c),0x22);
    uVar12 = (uint)*(byte *)(param_1 + 0x3c);
    if (2 < uVar12) {
      uVar12 = 2;
    }
  }
  else {
    *(undefined1 *)(param_1 + 6) = 0xb4;
    FUN_ram_00061f0a(0,0x22);
    uVar12 = 0;
  }
  pbVar4 = *(byte **)(param_1 + 0x94);
  *(undefined1 *)(param_1 + 8) = 0x22;
  *pbVar4 = 5;
  if ((*(char *)(param_1 + 6) == -0x4c) && (DAT_ram_20001e28 << 0x11 < 0)) {
    *pbVar4 = 0x25;
  }
  pbVar4[1] = 0x22;
  if (*(char *)(param_1 + 100) == '\x02') {
    tmos_memcpy(param_1 + 0x66,*(int *)(param_1 + 0x84) + 0xc,6);
  }
  if (((*(byte *)(param_1 + 0x65) & 1) != 0) || (*(char *)(param_1 + 100) == '\x02')) {
    *pbVar4 = *pbVar4 | 0x40;
  }
  tmos_memcpy(pbVar4 + 2,param_1 + 0x66,6);
  if (*(char *)(param_1 + 0x75) != '\0') {
    *pbVar4 = *pbVar4 | 0x80;
  }
  tmos_memcpy(pbVar4 + 8,param_1 + 0x76,6);
  pbVar4[0xe] = *(byte *)(param_1 + 0x58);
  pbVar4[0xf] = *(byte *)(param_1 + 0x59);
  pbVar4[0x10] = *(byte *)(param_1 + 0x5a);
  pbVar4[0x11] = *(byte *)(param_1 + 0x5b);
  uVar8 = *(undefined4 *)(param_1 + 0x5c);
  pbVar4[0x12] = (byte)uVar8;
  pbVar4[0x14] = (byte)((uint)uVar8 >> 0x10);
  pbVar4[0x13] = (byte)((uint)uVar8 >> 8);
  bVar7 = 2;
  if (uVar12 == 2) {
    bVar7 = 3;
  }
  pbVar4[0x15] = bVar7;
  iVar9 = uVar12 * 2 + param_1;
  iVar11 = *(int *)(param_1 + 0x94);
  pbVar4[0x18] = *(byte *)(iVar9 + 0x50);
  pbVar4[0x19] = (byte)((ushort)*(undefined2 *)(iVar9 + 0x50) >> 8);
  pbVar4[0x1a] = *(byte *)(iVar9 + 0x1a);
  pbVar4[0x1b] = (byte)((ushort)*(undefined2 *)(iVar9 + 0x1a) >> 8);
  uVar1 = *(undefined2 *)(iVar9 + 0x20);
  pbVar4[0x1c] = *(byte *)(iVar9 + 0x20);
  pbVar4[0x1d] = (byte)((ushort)uVar1 >> 8);
  if (DAT_ram_20001e04 == 0) {
    uVar6 = (*(ushort *)(iVar11 + 0x18) >> 3) + 3;
    if (6 < uVar6) {
      uVar6 = 6;
    }
    *(ushort *)(param_1 + 0x4e) = uVar6;
  }
  else {
    *(undefined2 *)(param_1 + 0x4e) = 3;
    iVar9 = DAT_ram_20001df0;
    cVar2 = DAT_ram_20001bd2;
    uVar14 = (uint)DAT_ram_20001b8c;
    uVar12 = ((int)(DAT_ram_20001d8a + 0x22) >> 1) + 0xb;
    do {
      uVar13 = 0xffffffff;
      piVar3 = (int *)iVar9;
      while( true ) {
        uVar6 = *(ushort *)(param_1 + 0x4e);
        if (piVar3 == (int *)0x0) break;
        uVar5 = piVar3[0x24];
        uVar10 = (uVar6 * uVar14 + 400) / 800 + (uVar14 + 400) / 800 + *(int *)(param_1 + 0x60);
        if ((-1 < cVar2) && (0xa8bfffff < uVar10)) {
          uVar10 = uVar10 + 0x57400000;
        }
        if (uVar5 < uVar10) {
          uVar5 = uVar10 - uVar5;
        }
        else {
          uVar5 = uVar5 - uVar10;
          if (uVar5 < uVar12) {
            *(ushort *)(param_1 + 0x4e) = uVar6 + 1;
          }
        }
        if (uVar5 < uVar13) {
          uVar13 = uVar5;
        }
        piVar3 = (int *)*piVar3;
      }
    } while ((uVar13 <= uVar12) &&
            (uVar13 = uVar6 + 1, *(short *)(param_1 + 0x4e) = (short)(uVar13 * 0x10000 >> 0x10),
            (uVar13 & 0xffff) < 6));
  }
  pbVar4[0x16] = *(byte *)(param_1 + 0x4e);
  pbVar4[0x17] = (byte)((ushort)*(undefined2 *)(param_1 + 0x4e) >> 8);
  pbVar4[0x1e] = (byte)DAT_ram_20001e56;
  pbVar4[0x1f] = DAT_ram_20001e56._1_1_;
  pbVar4[0x20] = (byte)DAT_ram_20001e58;
  pbVar4[0x21] = DAT_ram_20001e58._1_1_;
  pbVar4[0x22] = DAT_ram_20001e5a;
  pbVar4[0x23] = *(byte *)(param_1 + 0xc) & 0x1f;
  *(byte *)(iVar11 + 0x23) = DAT_ram_20001d63 << 5 | *(byte *)(iVar11 + 0x23);
  *(uint *)(DAT_ram_20001e88 + 0x2c) =
       *(uint *)(DAT_ram_20001e88 + 0x2c) & 0x81ffffff | (DAT_ram_20001bd0 & 0x3f) << 0x19;
  DAT_ram_40001040 = 0xa8;
  if (DAT_ram_20001bd0 < 0xe) {
    DAT_ram_40001022 = DAT_ram_40001022 & 0xffef;
  }
  else {
    DAT_ram_40001022 = DAT_ram_40001022 | 0x10;
  }
  return;
}

