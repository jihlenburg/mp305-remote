/* Address: ram:00055ebc; name: FUN_ram_00055ebc; body bytes: 26 */

int FUN_ram_00055ebc(void)

{
  int iVar1;
  int *piVar2;
  
  gp = 0x20004000;
  iVar1 = 0;
  for (piVar2 = (int *)DAT_ram_20001df0; piVar2 != (int *)0x0; piVar2 = (int *)*piVar2) {
    if (*(char *)((int)piVar2 + 0xb) == '\0') {
      iVar1 = iVar1 + 1;
    }
  }
  return iVar1;
}

