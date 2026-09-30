/* Address: ram:00061e3a; name: FUN_ram_00061e3a; body bytes: 208 */

bool FUN_ram_00061e3a(uint param_1,uint param_2)

{
  uint *puVar1;
  int iVar2;
  int iVar3;
  
  puVar1 = DAT_ram_20001e88;
  gp = 0x20004000;
  *DAT_ram_20001e88 = *DAT_ram_20001e88 & 0xfffffe7f | 0x80;
  iVar3 = DAT_ram_20001efc;
  *(uint *)(DAT_ram_20001efc + 8) = *(uint *)(DAT_ram_20001efc + 8) & 0xffcdffff;
  iVar2 = DAT_ram_20001eb0;
  *(undefined4 *)(DAT_ram_20001eb0 + 0x50) = 0x80;
  puVar1[2] = 0;
  puVar1[4] = puVar1[4] | 0x3f;
  *puVar1 = *puVar1 & 0xffffcfff;
  puVar1[0x17] = puVar1[0x17] & 0xfffffe00 | param_1 & 0x1ff;
  *(undefined2 *)(puVar1 + 0x16) = 0;
  *(undefined2 *)(puVar1 + 0x18) = 0;
  *(uint *)(iVar3 + 0x2c) = *(uint *)(iVar3 + 0x2c) & 0xfffffffd;
  *puVar1 = *puVar1 & 0xffffff80 | param_2 & 0x7f;
  *(undefined4 *)(iVar2 + 100) = 500;
  *puVar1 = *puVar1 & 0xfffffe7f;
  *puVar1 = *puVar1 & 0xfffffe7f | 0x100;
  *(uint *)(iVar3 + 8) = *(uint *)(iVar3 + 8) | 0x330000;
  *(undefined4 *)(iVar2 + 0x50) = 0xd9;
  puVar1[9] = puVar1[9] | 0x40000;
  do {
    if (*(int *)(iVar2 + 100) == 0) break;
  } while ((ushort)puVar1[0x16] < 10);
  puVar1[9] = puVar1[9] & 0xfffbffff;
  return (ushort)puVar1[0x18] < 4;
}

