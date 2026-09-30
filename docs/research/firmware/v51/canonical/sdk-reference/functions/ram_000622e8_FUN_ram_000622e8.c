/* Address: ram:000622e8; name: FUN_ram_000622e8; body bytes: 172 */

void FUN_ram_000622e8(uint param_1,undefined4 param_2)

{
  uint *puVar1;
  undefined4 *puVar2;
  int iVar3;
  
  gp = 0x20004000;
  FUN_ram_00062030(param_2,0xff,0);
  iVar3 = DAT_ram_20001efc;
  *(uint *)(DAT_ram_20001efc + 0x2c) = *(uint *)(DAT_ram_20001efc + 0x2c) & 0xfffffffd;
  puVar1 = DAT_ram_20001e88;
  *DAT_ram_20001e88 = *DAT_ram_20001e88 & 0xffffff80 | param_1 & 0x7f | 0x40;
  puVar1[2] = 0x71764129;
  puVar1[1] = 0x555555;
  puVar2 = DAT_ram_20001eb0;
  DAT_ram_20001e94 = 0;
  DAT_ram_20001e98 = 0;
  DAT_ram_20001eb0[1] = DAT_ram_20001eb0[1] & 0xfffffffe;
  DAT_ram_20001e99 = 0;
  DAT_ram_20001e95 = 0;
  DAT_ram_20001e9b = 9;
  *puVar2 = 1;
  *puVar1 = *puVar1 & 0xfffffe7f;
  *puVar1 = *puVar1 & 0xfffffe7f | 0x100;
  *(uint *)(iVar3 + 8) = *(uint *)(iVar3 + 8) | 0x330000;
  puVar2[0x14] = 0xd9;
  return;
}

