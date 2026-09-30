/* Address: ram:2000277e; name: FUN_ram_2000277e; body bytes: 128 */

void FUN_ram_2000277e(void)

{
  byte bVar1;
  undefined1 auStack_20 [24];
  
  gp = &DAT_ram_20002000;
  if (((DAT_ram_40003404 & 0xf) != 4) && ((DAT_ram_40003404 & 0xf) != 0xc)) {
    return;
  }
  bVar1 = FUN_ram_0000293c(auStack_20);
  if ((uint)DAT_ram_20004770 + (uint)bVar1 < 0x100) {
    FUN_ram_000078b2(&DAT_ram_20004670 + DAT_ram_20004770,auStack_20,(uint)bVar1);
    DAT_ram_20004770 = bVar1 + DAT_ram_20004770;
    route_main_uart_frame();
    DAT_ram_20004770 = 0;
  }
  return;
}

