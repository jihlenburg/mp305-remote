/* Address: ram:00053cca; name: FUN_ram_00053cca; body bytes: 518 */

void FUN_ram_00053cca(int param_1)

{
  uint *puVar1;
  int iVar2;
  undefined1 *puVar3;
  byte bVar4;
  
  puVar1 = DAT_ram_20001eb0;
  gp = 0x20004000;
  DAT_ram_20001eb0[0x19] = 0xa0;
  if ((*puVar1 & 3) != 0) {
    puVar1[0x14] = puVar1[0x14] & 0xfffffff8;
    *puVar1 = *puVar1 | 8;
  }
  puVar1 = DAT_ram_20001e88;
  DAT_ram_20001e88[0xb] = DAT_ram_20001e88[0xb] & 0xfffffffc | 1;
  DAT_ram_20001eb0[1] = DAT_ram_20001eb0[1] | 1;
  puVar1[0xb] = puVar1[0xb] & 0x81ffffff | (*(byte *)(param_1 + 0x68) & 0x3f) << 0x19;
  puVar1 = DAT_ram_20001e88;
  DAT_ram_40001040 = 0xa8;
  if (*(char *)(param_1 + 0x68) < '\x0e') {
    DAT_ram_40001022 = DAT_ram_40001022 & 0xffef;
  }
  else {
    DAT_ram_40001022 = DAT_ram_40001022 | 0x10;
  }
  *DAT_ram_20001e88 = *DAT_ram_20001e88 & 0xfffffe7f;
  *puVar1 = *puVar1 & 0xfffffe7f | 0x100;
  iVar2 = DAT_ram_20001efc;
  *(uint *)(DAT_ram_20001efc + 8) = *(uint *)(DAT_ram_20001efc + 8) | 0x330000;
  DAT_ram_20001eb0[0x14] = 0xda;
  *(uint *)(iVar2 + 0x2c) = *(uint *)(iVar2 + 0x2c) & 0xfffffffd;
  *puVar1 = *puVar1 & 0xffffff80 | *(byte *)(param_1 + 0x62) & 0x7f;
  puVar1[2] = 0x8e89bed6;
  puVar3 = *(undefined1 **)(param_1 + 0x4c);
  puVar1[1] = 0x555555;
  *(undefined1 *)(param_1 + 0x10) = 7;
  *puVar3 = 7;
  puVar3[2] = 1;
  puVar3[3] = 8;
  *(char *)(*(int *)(param_1 + 0x4c) + 4) = (char)*(undefined2 *)(param_1 + 0x6a);
  *(byte *)(*(int *)(param_1 + 0x4c) + (uint)(byte)puVar3[2] + 4) =
       (byte)((ushort)*(undefined2 *)(param_1 + 0x6a) >> 8) & 0xf | *(char *)(param_1 + 0x61) << 4;
  bVar4 = puVar3[2] + 2;
  puVar3[2] = bVar4;
  if ((int)(uint)*(ushort *)(param_1 + 0x70) <= (int)(0xfe - (uint)bVar4)) {
    tmos_memcpy(bVar4 + 3 + *(int *)(param_1 + 0x4c),*(undefined4 *)(param_1 + 0x78));
    bVar4 = puVar3[2];
    *(byte *)(param_1 + 0x11) = *(char *)(param_1 + 0x70) + '\x01' + (bVar4 & 0x3f);
    puVar3[2] = bVar4;
    if (((*(byte *)(param_1 + 0x35) & 1) != 0) || (*(char *)(param_1 + 0x34) == '\x02')) {
      **(byte **)(param_1 + 0x4c) = **(byte **)(param_1 + 0x4c) | 0x40;
    }
    *(undefined1 *)(*(int *)(param_1 + 0x4c) + 1) = *(undefined1 *)(param_1 + 0x11);
    *(undefined1 *)(param_1 + 0xb) = 0x98;
  }
  DAT_ram_20001eb0[0x1c] = *(uint *)(param_1 + 0x4c);
  FUN_ram_00042570(FUN_ram_00055184,0);
  DAT_ram_20001e97 = 0;
  DAT_ram_20001e98 = 0;
  FUN_ram_200011be(0,*(undefined1 *)(param_1 + 99),*(undefined1 *)(param_1 + 0x11));
  return;
}

