/* Address: 000422d0; name: FUN_000422d0; body bytes: 102 */

undefined4 FUN_000422d0(int *param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  
  iVar1 = *param_1;
  if (iVar1 == 0) {
    uVar2 = FUN_0003db28(param_1 + 1);
    iVar1 = FUN_0003db0a(param_1 + 1);
    iVar3 = FUN_00041788(uVar2,(char)param_1[5]);
    iVar4 = FUN_00041364(uVar2,iVar1,(char)param_1[5],0);
    *param_1 = iVar4;
    if (iVar4 == 0) {
      return 0;
    }
    iVar1 = FUN_000375de(iVar3 * iVar1);
    DAT_2003a54c = iVar1 + DAT_2003a54c;
    iVar1 = FUN_0004035a((char)param_1[5]);
    if (iVar1 != 0) {
      FUN_000411ca(*param_1,0);
    }
    iVar1 = *param_1;
  }
  return *(undefined4 *)(iVar1 + 0x10);
}

