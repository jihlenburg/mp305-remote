/* Address: ram:00061bec; name: FUN_ram_00061bec; body bytes: 148 */

undefined4 FUN_ram_00061bec(int param_1,int param_2)

{
  uint *puVar1;
  uint uVar2;
  
  gp = 0x20004000;
  *(uint *)(DAT_ram_20001eb0 + 0x50) = *(uint *)(DAT_ram_20001eb0 + 0x50) & 0xffffff7f;
  *(uint *)(DAT_ram_20001eb0 + 0x50) = *(uint *)(DAT_ram_20001eb0 + 0x50) | 0x80;
  puVar1 = DAT_ram_20001e84;
  uVar2 = *(uint *)(param_2 + 0xec);
  *DAT_ram_20001e84 = param_1 << 5 | 0x80;
  puVar1[4] = uVar2;
  puVar1[5] = *(uint *)(param_2 + 0xf0);
  puVar1[6] = *(uint *)(param_2 + 0xbc);
  puVar1[7] = *(uint *)(param_2 + 0xc0);
  puVar1[8] = *(uint *)(param_2 + 0xc4);
  puVar1[9] = *(uint *)(param_2 + 200);
  puVar1[10] = *(uint *)(param_2 + 0xcc);
  puVar1[0xb] = *(uint *)(param_2 + 0xd0);
  puVar1[0xc] = *(uint *)(param_2 + 0xd4);
  puVar1[0xd] = *(uint *)(param_2 + 0xd8);
  puVar1[2] = *(uint *)(param_2 + 0xdc);
  puVar1[3] = *(uint *)(param_2 + 0xe0);
  *puVar1 = *puVar1 | 0x40;
  DAT_ram_20001e9a = 0x80;
  return 0;
}

