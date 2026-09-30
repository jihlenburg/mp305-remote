/* Address: ram:2000188a; name: FUN_ram_2000188a; body bytes: 1 */

void FUN_ram_2000188a(void)

{
  int iVar1;
  
  gp = 0x20004000;
  iVar1 = 150000;
  while ((-1 < *(int *)(DAT_ram_20001efc + 0x90) << 5 ||
         (-1 < *(int *)(DAT_ram_20001efc + 0x90) << 6))) {
    iVar1 = iVar1 + -1;
    if (iVar1 == 0) {
      return;
    }
  }
  gp = 0x20004000;
  return;
}

