/* Address: ram:20000dbc; name: FUN_ram_20000dbc; body bytes: 1 */

undefined4 FUN_ram_20000dbc(byte *param_1,byte *param_2,undefined1 *param_3)

{
  uint *puVar1;
  
  gp = 0x20004000;
  *(uint *)(DAT_ram_20001eb0 + 0x50) = *(uint *)(DAT_ram_20001eb0 + 0x50) & 0xffffff7f;
  FUN_ram_0006219c();
  *(uint *)(DAT_ram_20001eb0 + 0x50) = *(uint *)(DAT_ram_20001eb0 + 0x50) | 0x80;
  puVar1 = DAT_ram_20001e84;
  *DAT_ram_20001e84 = 0;
  puVar1[10] = (uint)param_1[1] * 0x100 + (uint)param_1[2] * 0x10000 + (uint)*param_1 +
               (uint)param_1[3] * 0x1000000;
  puVar1[0xb] = (uint)param_1[5] * 0x100 + (uint)param_1[6] * 0x10000 + (uint)param_1[4] +
                (uint)param_1[7] * 0x1000000;
  puVar1[0xc] = (uint)param_1[9] * 0x100 + (uint)param_1[10] * 0x10000 + (uint)param_1[8] +
                (uint)param_1[0xb] * 0x1000000;
  puVar1[0xd] = (uint)param_1[0xd] * 0x100 + (uint)param_1[0xe] * 0x10000 + (uint)param_1[0xc] +
                (uint)param_1[0xf] * 0x1000000;
  puVar1[6] = (uint)param_2[1] * 0x100 + (uint)param_2[2] * 0x10000 + (uint)*param_2 +
              (uint)param_2[3] * 0x1000000;
  puVar1[7] = (uint)param_2[5] * 0x100 + (uint)param_2[6] * 0x10000 + (uint)param_2[4] +
              (uint)param_2[7] * 0x1000000;
  puVar1[8] = (uint)param_2[9] * 0x100 + (uint)param_2[10] * 0x10000 + (uint)param_2[8] +
              (uint)param_2[0xb] * 0x1000000;
  puVar1[9] = (uint)param_2[0xd] * 0x100 + (uint)param_2[0xe] * 0x10000 + (uint)param_2[0xc] +
              (uint)param_2[0xf] * 0x1000000;
  puVar1[1] = puVar1[1] & 0xfffffffd;
  puVar1[1] = puVar1[1] | 1;
  *puVar1 = *puVar1 | 1;
  do {
  } while ((DAT_ram_20001e84[1] & 1) != 0);
  *param_3 = (char)DAT_ram_20001e84[6];
  param_3[1] = (char)(DAT_ram_20001e84[6] >> 8);
  param_3[2] = (char)(DAT_ram_20001e84[6] >> 0x10);
  param_3[3] = (char)(DAT_ram_20001e84[6] >> 0x18);
  puVar1 = DAT_ram_20001e84;
  param_3[4] = (char)DAT_ram_20001e84[7];
  param_3[5] = (char)(puVar1[7] >> 8);
  param_3[6] = (char)(puVar1[7] >> 0x10);
  param_3[7] = (char)(puVar1[7] >> 0x18);
  param_3[8] = (char)puVar1[8];
  param_3[9] = (char)(puVar1[8] >> 8);
  param_3[10] = (char)(puVar1[8] >> 0x10);
  param_3[0xb] = (char)(puVar1[8] >> 0x18);
  param_3[0xc] = (char)puVar1[9];
  param_3[0xd] = (char)(puVar1[9] >> 8);
  param_3[0xe] = (char)(puVar1[9] >> 0x10);
  param_3[0xf] = (char)(puVar1[9] >> 0x18);
  return 0;
}

