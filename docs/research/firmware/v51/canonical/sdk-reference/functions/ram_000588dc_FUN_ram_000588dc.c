/* Address: ram:000588dc; name: FUN_ram_000588dc; body bytes: 252 */

void FUN_ram_000588dc(int param_1)

{
  uint *puVar1;
  uint *puVar2;
  int iVar3;
  
  puVar1 = DAT_ram_20001eb0;
  gp = 0x20004000;
  if ((*DAT_ram_20001eb0 & 3) != 0) {
    DAT_ram_20001eb0[0x14] = DAT_ram_20001eb0[0x14] & 0xfffffff8;
    *puVar1 = *puVar1 | 8;
  }
  puVar2 = DAT_ram_20001eb0;
  DAT_ram_20001eb0[1] = DAT_ram_20001eb0[1] | 1;
  puVar1 = DAT_ram_20001e88;
  DAT_ram_20001e88[2] = 0x8e89bed6;
  puVar1[1] = 0x555555;
  puVar2[1] = puVar2[1] | 1;
  *(undefined1 *)(param_1 + 6) = 0xb3;
  DAT_ram_20001e94 = 0;
  DAT_ram_20001e9b = 7;
  DAT_ram_20001e98 = 0;
  FUN_ram_00062030(*(undefined1 *)(param_1 + 0x3c),0xff,0);
  puVar2 = DAT_ram_20001eb0;
  DAT_ram_20001e99 = 0;
  DAT_ram_20001e95 = 0;
  *DAT_ram_20001eb0 = 1;
  puVar1 = DAT_ram_20001e88;
  *DAT_ram_20001e88 = *DAT_ram_20001e88 & 0xfffffe7f;
  *puVar1 = *puVar1 & 0xfffffe7f | 0x100;
  iVar3 = DAT_ram_20001efc;
  *(uint *)(DAT_ram_20001efc + 8) = *(uint *)(DAT_ram_20001efc + 8) | 0x330000;
  puVar2[0x14] = 0xd9;
  *(uint *)(iVar3 + 0x2c) = *(uint *)(iVar3 + 0x2c) & 0xfffffffd;
  *puVar1 = *puVar1 & 0xffffff80 | *(byte *)(param_1 + 0x3b) & 0x7f;
  return;
}

