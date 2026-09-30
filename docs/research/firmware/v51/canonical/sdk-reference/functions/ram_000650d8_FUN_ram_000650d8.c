/* Address: ram:000650d8; name: FUN_ram_000650d8; body bytes: 18 */

void FUN_ram_000650d8(void)

{
  gp = 0x20004000;
  *(uint *)(DAT_ram_20001efc + 4) = *(uint *)(DAT_ram_20001efc + 4) | 0x100;
  return;
}

