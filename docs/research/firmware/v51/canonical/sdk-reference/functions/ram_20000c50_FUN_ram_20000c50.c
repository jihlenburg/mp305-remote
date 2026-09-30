/* Address: ram:20000c50; name: FUN_ram_20000c50; body bytes: 62 */

int FUN_ram_20000c50(int param_1)

{
  int iVar1;
  int iVar2;
  
  gp = 0x20004000;
  iVar1 = DAT_ram_20001e1c;
  while ((iVar1 != 0 && (iVar2 = FUN_ram_0005d6c6(iVar1 + 0x2a,param_1 + 2), iVar2 != 1))) {
    iVar1 = *(int *)(iVar1 + 0x3c);
  }
  return iVar1;
}

