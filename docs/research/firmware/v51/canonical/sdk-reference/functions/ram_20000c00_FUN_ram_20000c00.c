/* Address: ram:20000c00; name: FUN_ram_20000c00; body bytes: 1 */

int FUN_ram_20000c00(int param_1)

{
  int iVar1;
  int iVar2;
  
  gp = 0x20004000;
  iVar1 = DAT_ram_20001e1c;
  while( true ) {
    if (iVar1 == 0) {
      return 0;
    }
    if ((*(byte *)(iVar1 + 3) == (*(byte *)(param_1 + 1) & 1)) &&
       (iVar2 = tmos_memcmp(param_1 + 2,iVar1 + 4,6), iVar2 == 1)) break;
    iVar1 = *(int *)(iVar1 + 0x3c);
  }
  gp = 0x20004000;
  return iVar1;
}

