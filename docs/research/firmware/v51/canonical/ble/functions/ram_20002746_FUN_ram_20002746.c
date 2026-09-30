/* Address: ram:20002746; name: FUN_ram_20002746; body bytes: 44 */

void FUN_ram_20002746(void)

{
  undefined1 auStack_10 [16];
  
  gp = &DAT_ram_20002000;
  if (((DAT_ram_40003004 & 0xf) != 4) && ((DAT_ram_40003004 & 0xf) != 0xc)) {
    return;
  }
  FUN_ram_00002844(auStack_10);
  return;
}

