/* Address: ram:0004e0bc; name: linkDB_Register; body bytes: 42 */

undefined4 linkDB_Register(undefined4 param_1)

{
  int *piVar1;
  int iVar2;
  
  gp = 0x20004000;
  piVar1 = &DAT_ram_20001d04;
  iVar2 = 0;
  do {
    if (*piVar1 == 0) {
      (&DAT_ram_20001d04)[iVar2] = param_1;
      return 0;
    }
    iVar2 = iVar2 + 1;
    piVar1 = piVar1 + 1;
  } while (iVar2 != 0xc);
  return 0x13;
}

