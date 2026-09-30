/* Address: ram:00061882; name: FUN_ram_00061882; body bytes: 142 */

undefined4 FUN_ram_00061882(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  gp = 0x20004000;
  iVar2 = DAT_ram_20001e14;
  iVar3 = 0;
  while( true ) {
    iVar1 = iVar2;
    if (iVar1 == 0) {
      return 0;
    }
    if ((*(char *)(iVar1 + 1) == *(char *)(param_1 + 1)) &&
       (iVar2 = tmos_memcmp(iVar1 + 2,param_1 + 2,6), iVar2 == 1)) break;
    iVar2 = *(int *)(iVar1 + 8);
    iVar3 = iVar1;
  }
  iVar2 = *(int *)(iVar1 + 8);
  if (iVar3 != 0) {
    *(int *)(iVar3 + 8) = *(int *)(iVar1 + 8);
    iVar2 = DAT_ram_20001e14;
  }
  DAT_ram_20001e14 = iVar2;
  FUN_ram_20000104(iVar1);
  gp = 0x20004000;
  DAT_ram_20001e10 = DAT_ram_20001e10 + -1;
  return 1;
}

