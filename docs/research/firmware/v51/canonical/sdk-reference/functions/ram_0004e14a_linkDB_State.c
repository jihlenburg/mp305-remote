/* Address: ram:0004e14a; name: linkDB_State; body bytes: 48 */

bool linkDB_State(int param_1,byte param_2)

{
  bool bVar1;
  int iVar2;
  
  gp = 0x20004000;
  if (param_1 != 0xfffe) {
    iVar2 = FUN_ram_0004df14();
    bVar1 = false;
    if (iVar2 != 0) {
      bVar1 = (param_2 & *(byte *)(iVar2 + 4)) != 0;
    }
    return bVar1;
  }
  return true;
}

