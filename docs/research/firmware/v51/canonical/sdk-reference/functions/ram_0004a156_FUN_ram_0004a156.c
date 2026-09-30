/* Address: ram:0004a156; name: FUN_ram_0004a156; body bytes: 30 */

undefined4 FUN_ram_0004a156(uint param_1)

{
  int *piVar1;
  
  gp = 0x20004000;
  piVar1 = (int *)DAT_ram_20001a54;
  while( true ) {
    if (piVar1 == (int *)0x0) {
      return 0;
    }
    if (*(ushort *)(piVar1 + 1) == param_1) break;
    piVar1 = (int *)*piVar1;
  }
  return piVar1[2];
}

