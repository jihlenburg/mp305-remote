/* Address: 00046ca0; name: FUN_00046ca0; body bytes: 38 */

undefined * FUN_00046ca0(int param_1)

{
  char cVar1;
  int iVar2;
  
  iVar2 = FUN_00050a64();
  while( true ) {
    if (iVar2 == 0) {
      return &DAT_00046cc8;
    }
    cVar1 = *(char *)(param_1 + iVar2);
    if (cVar1 == '.') {
      return (undefined *)(iVar2 + param_1 + 1);
    }
    if (cVar1 == '/') {
      return &DAT_00046cc8;
    }
    if (cVar1 == '\\') break;
    iVar2 = iVar2 + -1;
  }
  return &DAT_00046cc8;
}

