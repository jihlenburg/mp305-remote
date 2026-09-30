/* Address: 000417d4; name: FUN_000417d4; body bytes: 68 */

void FUN_000417d4(void)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  bVar1 = false;
  for (iVar2 = FUN_00040914(0); iVar2 != 0; iVar2 = FUN_00040914(iVar2)) {
    for (iVar4 = *(int *)(iVar2 + 0x2a8); iVar4 != 0; iVar4 = *(int *)(iVar4 + 0x40)) {
      iVar3 = FUN_0004181c(iVar2,iVar4);
      if (iVar3 != 0) {
        bVar1 = true;
      }
    }
    if (!bVar1) {
      DAT_2003a550 = 1;
    }
  }
  return;
}

