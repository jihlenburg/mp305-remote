/* Address: ram:0004a274; name: FUN_ram_0004a274; body bytes: 34 */

int FUN_ram_0004a274(uint param_1)

{
  int *piVar1;
  
  gp = 0x20004000;
  piVar1 = (int *)DAT_ram_20001a48;
  while( true ) {
    if (piVar1 == (int *)0x0) {
      return 0;
    }
    if (*(ushort *)(piVar1[2] + 10) == param_1) break;
    piVar1 = (int *)*piVar1;
  }
  return (int)(piVar1 + 1);
}

