/* Address: ram:00040efe; name: FUN_ram_00040efe; body bytes: 62 */

int FUN_ram_00040efe(int param_1)

{
  int iVar1;
  int iVar2;
  
  gp = 0x20004000;
  iVar1 = DAT_ram_20001e1c;
  while ((iVar1 != 0 && (iVar2 = (*(code *)&SUB_ram_e009d936)(iVar1 + 0x1a,param_1 + 2), iVar2 != 1)
         )) {
    iVar1 = *(int *)(iVar1 + 0x3c);
  }
  return iVar1;
}

