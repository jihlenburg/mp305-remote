/* Address: ram:00003f76; name: FUN_ram_00003f76; body bytes: 54 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_ram_00003f76(void)

{
  undefined1 *puVar1;
  
  gp = &DAT_ram_20002000;
  (*_DAT_ram_0004017c)(DAT_ram_20002f36);
  puVar1 = (undefined1 *)FUN_ram_00001d1a(&DAT_ram_20002f30,0,6);
  *puVar1 = 1;
  return 0;
}

