/* Address: ram:00046c08; name: FUN_ram_00046c08; body bytes: 26 */

void FUN_ram_00046c08(void)

{
  undefined4 *puVar1;
  
  gp = 0x20004000;
  puVar1 = (undefined4 *)0x0;
  if ((DAT_ram_20001d50 & 8) != 0) {
    puVar1 = &DAT_ram_20001cbc;
  }
  FUN_ram_0004409c(puVar1);
  return;
}

