/* Address: ram:00068ade; name: FUN_ram_00068ade; body bytes: 50 */

void FUN_ram_00068ade(void)

{
  gp = 0x20004000;
  if (DAT_ram_20001aa8 != 0) {
    tmos_msg_deallocate();
    DAT_ram_20001aa8 = 0;
  }
  DAT_ram_20001a86 = DAT_ram_20001a8d;
  return;
}

