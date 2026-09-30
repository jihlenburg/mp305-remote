/* Address: ram:00057d50; name: FUN_ram_00057d50; body bytes: 54 */

void FUN_ram_00057d50(void)

{
  int *piVar1;
  
  gp = 0x20004000;
  for (piVar1 = (int *)DAT_ram_20001e00; piVar1 != (int *)0x0; piVar1 = (int *)*piVar1) {
    FUN_ram_20000104(piVar1);
  }
  DAT_ram_20001e00 = 0;
  return;
}

