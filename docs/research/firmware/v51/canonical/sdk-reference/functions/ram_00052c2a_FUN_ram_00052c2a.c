/* Address: ram:00052c2a; name: FUN_ram_00052c2a; body bytes: 1008 */

/* WARNING: Removing unreachable block (ram,0x00052daa) */

void FUN_ram_00052c2a(int param_1)

{
  byte bVar1;
  char cVar2;
  uint *puVar3;
  undefined1 *puVar4;
  undefined1 uVar5;
  int iVar6;
  uint uVar7;
  undefined1 *puVar8;
  
  puVar3 = DAT_ram_20001eb0;
  gp = 0x20004000;
  DAT_ram_20001eb0[0x19] = 0xa0;
  if ((*puVar3 & 3) != 0) {
    puVar3[0x14] = puVar3[0x14] & 0xfffffff8;
    *puVar3 = *puVar3 | 8;
  }
  puVar3 = DAT_ram_20001e88;
  DAT_ram_20001e88[0xb] = DAT_ram_20001e88[0xb] & 0xfffffffc | 1;
  *puVar3 = *puVar3 & 0xfffffe7f;
  *puVar3 = *puVar3 & 0xfffffe7f | 0x100;
  iVar6 = DAT_ram_20001efc;
  *(uint *)(DAT_ram_20001efc + 8) = *(uint *)(DAT_ram_20001efc + 8) | 0x330000;
  DAT_ram_20001eb0[0x14] = 0xda;
  *(uint *)(iVar6 + 0x2c) = *(uint *)(iVar6 + 0x2c) & 0xfffffffd;
  *puVar3 = *puVar3 & 0xffffff80 | *(byte *)(param_1 + 0x7e) & 0x7f;
  uVar5 = FUN_ram_000428ec(1,0x23);
  puVar4 = *(undefined1 **)(param_1 + 0x4c);
  *(undefined1 *)(param_1 + 0x10) = 7;
  *(undefined1 *)(param_1 + 0x7e) = uVar5;
  *puVar4 = 7;
  puVar4[3] = 0;
  puVar4[2] = 1;
  if ((*(uint *)(param_1 + 0x54) & 0x200) != 0) {
    puVar4[3] = 4;
    *(byte *)(*(int *)(param_1 + 0x4c) + 4) =
         *(char *)(param_1 + 0xa6) << 6 | *(byte *)(param_1 + 0xa5);
    puVar4[2] = puVar4[2] + '\x01';
    FUN_ram_00062148(*(undefined1 *)(param_1 + 0xa6),*(undefined1 *)(param_1 + 0xa5),
                     *(undefined1 *)(param_1 + 0xa8),0);
  }
  if ((*(uint *)(param_1 + 0x54) & 0x400) != 0) {
    iVar6 = *(int *)(param_1 + 0x4c);
    puVar4[3] = puVar4[3] | 8;
    *(char *)(iVar6 + (uint)(byte)puVar4[2] + 3) = (char)*(undefined2 *)(param_1 + 0x8a);
    *(byte *)(*(int *)(param_1 + 0x4c) + (uint)(byte)puVar4[2] + 4) =
         (byte)((ushort)*(undefined2 *)(param_1 + 0x8a) >> 8) & 0xf | *(char *)(param_1 + 0x7f) << 4
    ;
    puVar4[2] = puVar4[2] + '\x02';
  }
  puVar3 = DAT_ram_20001eb0;
  bVar1 = puVar4[2];
  if ((int)(0xfd - (uint)bVar1) < (int)(uint)*(ushort *)(param_1 + 0x84)) {
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
    DAT_ram_20001eb0[2] = 0x1000;
    puVar3[0x18] = uVar7 * 0x3c;
    puVar4[3] = puVar4[3] | 0x10;
    *(undefined1 *)(*(int *)(param_1 + 0x4c) + (uint)bVar1 + 3) = *(undefined1 *)(param_1 + 0x7e);
    *(char *)(*(int *)(param_1 + 0x4c) + (uint)(byte)puVar4[2] + 4) = (char)uVar7;
    *(byte *)(*(int *)(param_1 + 0x4c) + (uint)(byte)puVar4[2] + 5) =
         (byte)(uVar7 >> 8) | *(char *)(param_1 + 0x80) << 5;
    puVar4[2] = puVar4[2] + '\x03';
  }
  else {
    DAT_ram_20001dd4 = DAT_ram_20001dd4 & 0xef;
  }
  if ((*(byte *)(param_1 + 0x60) & 0x40) != 0) {
    iVar6 = *(int *)(param_1 + 0x4c);
    puVar4[3] = puVar4[3] | 0x40;
    *(undefined1 *)(iVar6 + (uint)(byte)puVar4[2] + 3) = *(undefined1 *)(param_1 + 0x15);
    puVar4[2] = puVar4[2] + '\x01';
  }
  if (1 < (byte)(*(char *)(param_1 + 0x7c) - 0x10U)) goto LAB_ram_00052eb6;
  puVar8 = (undefined1 *)(*(int *)(param_1 + 0x4c) + (byte)puVar4[2] + 3);
  *puVar8 = 8;
  puVar8[1] = 0x28;
  tmos_memcpy(puVar8 + 2,&DAT_ram_20001e56,5);
  if (*(char *)(param_1 + 0x7c) == '\x10') {
    *(short *)(param_1 + 0x82) = *(short *)(param_1 + 0x88) + 8;
    uVar5 = 0x11;
LAB_ram_00052e96:
    *(undefined1 *)(param_1 + 0x7c) = uVar5;
  }
  else if ((int)((uint)*(ushort *)(param_1 + 0x82) - (uint)*(ushort *)(param_1 + 0x88)) < 3) {
    uVar5 = 0x12;
    goto LAB_ram_00052e96;
  }
  puVar8[7] = *(undefined1 *)(param_1 + 0x82);
  puVar8[8] = (char)((ushort)*(undefined2 *)(param_1 + 0x82) >> 8);
  puVar4[2] = puVar4[2] + '\t';
LAB_ram_00052eb6:
  uVar7 = 0;
  if (*(short *)(param_1 + 0x84) != 0) {
    iVar6 = *(int *)(param_1 + 0x4c) + (byte)puVar4[2] + 3;
    if ((puVar4[3] & 0x10) == 0) {
      tmos_memcpy(iVar6,*(undefined4 *)(param_1 + 0xa0));
      uVar7 = (uint)*(byte *)(param_1 + 0x84);
    }
    else {
      uVar7 = -(uint)(byte)puVar4[2] - 2 & 0xff;
      tmos_memcpy(iVar6,*(undefined4 *)(param_1 + 0xa0),uVar7);
      *(uint *)(param_1 + 0x78) = *(int *)(param_1 + 0xa0) + uVar7;
      *(short *)(param_1 + 0x70) = *(short *)(param_1 + 0x84) - (short)uVar7;
    }
  }
  bVar1 = puVar4[2];
  cVar2 = (char)uVar7 + (bVar1 & 0x3f) + 1;
  *(char *)(param_1 + 0x11) = cVar2;
  puVar4[2] = bVar1;
  *(char *)(*(int *)(param_1 + 0x4c) + 1) = cVar2;
  puVar3 = DAT_ram_20001eb0;
  *(undefined1 *)(param_1 + 0xb) = 0x97;
  puVar3[1] = puVar3[1] & 0xfffffffe;
  DAT_ram_20001e88[0xb] =
       DAT_ram_20001e88[0xb] & 0x81ffffff | (*(byte *)(param_1 + 0x68) & 0x3f) << 0x19;
  puVar3 = DAT_ram_20001e88;
  DAT_ram_40001040 = 0xa8;
  if (*(char *)(param_1 + 0x68) < '\x0e') {
    DAT_ram_40001022 = DAT_ram_40001022 & 0xffef;
  }
  else {
    DAT_ram_40001022 = DAT_ram_40001022 | 0x10;
  }
  DAT_ram_20001e88[2] = *(uint *)(param_1 + 0x8c);
  puVar3[1] = *(uint *)(param_1 + 0x90);
  DAT_ram_20001eb0[0x1c] = *(uint *)(param_1 + 0x4c);
  FUN_ram_0006219c();
  FUN_ram_00042570(FUN_ram_00055184,0);
  DAT_ram_20001e97 = 0;
  DAT_ram_20001e98 = 0;
  FUN_ram_200011be(0,*(undefined1 *)(param_1 + 0x80),*(undefined1 *)(param_1 + 0x11));
  return;
}

