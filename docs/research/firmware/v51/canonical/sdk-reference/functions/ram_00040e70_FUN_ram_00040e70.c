/* Address: ram:00040e70; name: FUN_ram_00040e70; body bytes: 80 */

int FUN_ram_00040e70(int param_1)

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
       (iVar2 = FUN_ram_000404da(param_1 + 2,iVar1 + 4,6), iVar2 == 1)) break;
    iVar1 = *(int *)(iVar1 + 0x3c);
  }
  gp = 0x20004000;
  return iVar1;
}

