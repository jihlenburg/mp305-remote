/* Address: 0004a328; name: FUN_0004a328; body bytes: 50 */

int FUN_0004a328(undefined4 param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = FUN_00052bf6(DAT_2003a5d8,param_1);
  uVar1 = DAT_2003a5e0;
  if (iVar2 != 0) {
    iVar3 = FUN_00052b38();
    DAT_2003a5dc = iVar3 + DAT_2003a5dc;
    uVar1 = DAT_2003a5dc;
    if (DAT_2003a5dc <= DAT_2003a5e0) {
      uVar1 = DAT_2003a5e0;
    }
  }
  DAT_2003a5e0 = uVar1;
  return iVar2;
}

