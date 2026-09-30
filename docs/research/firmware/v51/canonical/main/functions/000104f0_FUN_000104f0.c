/* Address: 000104f0; name: FUN_000104f0; body bytes: 28 */

int FUN_000104f0(int param_1,int param_2)

{
  byte bVar1;
  int iVar2;
  
  iVar2 = 0;
  while( true ) {
    bVar1 = *(byte *)(param_1 + iVar2);
    if ((bVar1 != *(byte *)(param_2 + iVar2)) || (bVar1 == 0)) break;
    iVar2 = iVar2 + 1;
  }
  return (uint)bVar1 - (uint)*(byte *)(param_2 + iVar2);
}

