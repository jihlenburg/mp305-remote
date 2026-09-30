/* Address: ram:00057ba2; name: FUN_ram_00057ba2; body bytes: 26 */

int FUN_ram_00057ba2(uint param_1)

{
  int *piVar1;
  
  gp = 0x20004000;
  for (piVar1 = (int *)DAT_ram_20001df0;
      (piVar1 != (int *)0x0 && (*(ushort *)(piVar1 + 2) != param_1)); piVar1 = (int *)*piVar1) {
  }
  return (int)piVar1;
}

