/* Address: ram:0005dd3a; name: FUN_ram_0005dd3a; body bytes: 50 */

bool FUN_ram_0005dd3a(int param_1)

{
  int iVar1;
  
  gp = 0x20004000;
  if (*(char *)(param_1 + 0x54) == '\0') {
    return true;
  }
  if ((*(byte *)(param_1 + 0x10) & 1) != 0) {
    iVar1 = FUN_ram_20000d70(*(undefined4 *)(param_1 + 0x54),*(undefined4 *)(param_1 + 0x58));
    return iVar1 != 0;
  }
  return true;
}

