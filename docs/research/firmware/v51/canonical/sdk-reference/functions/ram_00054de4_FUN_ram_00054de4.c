/* Address: ram:00054de4; name: FUN_ram_00054de4; body bytes: 26 */

int FUN_ram_00054de4(uint param_1)

{
  int *piVar1;
  
  gp = 0x20004000;
  for (piVar1 = (int *)DAT_ram_20001db8;
      (piVar1 != (int *)0x0 && (*(byte *)(piVar1 + 2) != param_1)); piVar1 = (int *)*piVar1) {
  }
  return (int)piVar1;
}

