/* Address: ram:00066ade; name: FUN_ram_00066ade; body bytes: 74 */

undefined4 FUN_ram_00066ade(int param_1)

{
  char *pcVar1;
  
  gp = 0x20004000;
  DAT_ram_20001d94 = param_1 * 0x640;
  for (pcVar1 = DAT_ram_20001e1c; pcVar1 != (char *)0x0; pcVar1 = *(char **)(pcVar1 + 0x3c)) {
    if (*pcVar1 != -1) {
      FUN_ram_00042194(*pcVar1,DAT_ram_20001d94);
    }
  }
  return 0;
}

