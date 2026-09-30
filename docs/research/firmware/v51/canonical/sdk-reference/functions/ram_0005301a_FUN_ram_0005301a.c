/* Address: ram:0005301a; name: FUN_ram_0005301a; body bytes: 530 */

/* WARNING: Removing unreachable block (ram,0x00053110) */

void FUN_ram_0005301a(int param_1)

{
  byte bVar1;
  char cVar2;
  uint *puVar3;
  undefined1 *puVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  
  iVar5 = DAT_ram_20001eb0;
  gp = 0x20004000;
  *(undefined4 *)(DAT_ram_20001eb0 + 100) = 0xa0;
  puVar3 = DAT_ram_20001e88;
  DAT_ram_20001e88[0xb] = DAT_ram_20001e88[0xb] & 0xfffffffc | 1;
  *puVar3 = *puVar3 & 0xfffffe7f;
  *puVar3 = *puVar3 & 0xfffffe7f | 0x100;
  iVar6 = DAT_ram_20001efc;
  *(uint *)(DAT_ram_20001efc + 8) = *(uint *)(DAT_ram_20001efc + 8) | 0x330000;
  *(undefined4 *)(iVar5 + 0x50) = 0xda;
  *(uint *)(iVar6 + 0x2c) = *(uint *)(iVar6 + 0x2c) & 0xfffffffd;
  *puVar3 = *puVar3 & 0xffffff80 | *(byte *)(param_1 + 0x7e) & 0x7f;
  puVar4 = *(undefined1 **)(param_1 + 0x4c);
  *(undefined1 *)(param_1 + 0x10) = 7;
  *puVar4 = 7;
  puVar4[3] = 0;
  puVar4[2] = 1;
  if ((*(uint *)(param_1 + 0x54) & 0x400) != 0) {
    puVar4[3] = 8;
    *(char *)(*(int *)(param_1 + 0x4c) + 4) = (char)*(undefined2 *)(param_1 + 0x8a);
    *(byte *)(*(int *)(param_1 + 0x4c) + (uint)(byte)puVar4[2] + 4) =
         (byte)((ushort)*(undefined2 *)(param_1 + 0x8a) >> 8) & 0xf | *(char *)(param_1 + 0x7f) << 4
    ;
    puVar4[2] = puVar4[2] + '\x02';
  }
  iVar5 = DAT_ram_20001eb0;
  bVar1 = puVar4[2];
  if ((int)(0xfe - (uint)bVar1) < (int)(uint)*(ushort *)(param_1 + 0x70)) {
    if (*(char *)(param_1 + 0x80) == '\x02') {
      iVar6 = 0x4290;
    }
    else {
      iVar6 = 0x428;
      if (*(char *)(param_1 + 0x80) != '\x01') {
        iVar6 = 0x848;
      }
    }
    uVar7 = (iVar6 + 0x1b7U) / 0x1e;
    DAT_ram_20001dd4 = DAT_ram_20001dd4 | 0x10;
    *(undefined4 *)(DAT_ram_20001eb0 + 8) = 0x1000;
    *(uint *)(iVar5 + 0x60) = uVar7 * 0x3c;
    puVar4[3] = puVar4[3] | 0x10;
    *(undefined1 *)(*(int *)(param_1 + 0x4c) + (uint)bVar1 + 3) = *(undefined1 *)(param_1 + 0x7e);
    *(char *)(*(int *)(param_1 + 0x4c) + (uint)(byte)puVar4[2] + 4) = (char)uVar7;
    *(byte *)(*(int *)(param_1 + 0x4c) + (uint)(byte)puVar4[2] + 5) =
         (byte)(uVar7 >> 8) | *(char *)(param_1 + 0x80) << 5;
    puVar4[2] = puVar4[2] + '\x03';
  }
  uVar7 = 0;
  if (*(short *)(param_1 + 0x70) != 0) {
    iVar5 = *(int *)(param_1 + 0x4c) + (byte)puVar4[2] + 3;
    if ((puVar4[3] & 0x10) == 0) {
      tmos_memcpy(iVar5,*(undefined4 *)(param_1 + 0x78));
      uVar7 = (uint)*(byte *)(param_1 + 0x70);
      *(undefined2 *)(param_1 + 0x70) = 0;
    }
    else {
      uVar7 = -(uint)(byte)puVar4[2] - 2 & 0xff;
      tmos_memcpy(iVar5,*(undefined4 *)(param_1 + 0x78),uVar7);
      *(uint *)(param_1 + 0x78) = *(int *)(param_1 + 0x78) + uVar7;
      *(short *)(param_1 + 0x70) = *(short *)(param_1 + 0x70) - (short)uVar7;
    }
  }
  bVar1 = puVar4[2];
  cVar2 = (char)uVar7 + (bVar1 & 0x3f) + 1;
  *(char *)(param_1 + 0x11) = cVar2;
  puVar4[2] = bVar1;
  *(char *)(*(int *)(param_1 + 0x4c) + 1) = cVar2;
  *(undefined1 *)(param_1 + 0xb) = 0x97;
  DAT_ram_20001e97 = 0;
  DAT_ram_20001e98 = 0;
  FUN_ram_200011be(0,*(undefined1 *)(param_1 + 0x80),*(undefined1 *)(param_1 + 0x11));
  return;
}

