/* Address: ram:00047a9e; name: FUN_ram_00047a9e; body bytes: 84 */

void FUN_ram_00047a9e(int param_1)

{
  undefined1 *puVar1;
  
  gp = 0x20004000;
  if (DAT_ram_200019e4 != (undefined1 *)0x0) {
    puVar1 = (undefined1 *)tmos_msg_allocate(3);
    if (puVar1 != (undefined1 *)0x0) {
      *puVar1 = 0xd0;
      puVar1[1] = (char)param_1;
      puVar1[2] = 3;
      tmos_msg_send(*DAT_ram_200019e4,puVar1);
    }
    if (param_1 != 0) {
      FUN_ram_00046d4a();
      return;
    }
  }
  return;
}

