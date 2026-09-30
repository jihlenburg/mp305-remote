/* Address: 0004a626; name: FUN_0004a626; body bytes: 146 */

void FUN_0004a626(undefined4 param_1)

{
  char *pcVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  
  iVar2 = FUN_00046688();
  if (iVar2 == 7) {
    iVar2 = FUN_00046698(param_1);
    iVar3 = FUN_0004675a(param_1);
    if ((*(int *)(iVar3 + 0x3c) == iVar2) || (*(int *)(iVar3 + 0x50) == iVar2)) {
      *(undefined1 *)(iVar3 + 0x69) = *(undefined1 *)(iVar3 + 0x68);
      iVar2 = FUN_0004a60a(iVar3,iVar2);
      if (iVar2 == 0) {
        iVar2 = iVar3 + 0x5c;
        uVar4 = FUN_0004a118(iVar2);
        puVar5 = (undefined4 *)FUN_0004a13c(iVar2,uVar4);
        if (puVar5 != (undefined4 *)0x0) {
          FUN_0004a2ac(iVar2,uVar4);
          FUN_00046bec(uVar4);
          pcVar1 = (char *)(iVar3 + 0x68);
          *pcVar1 = *pcVar1 + -1;
          FUN_0004a2ac(iVar2,puVar5);
          *pcVar1 = *pcVar1 + -1;
          FUN_0004a910(iVar3,*puVar5);
          FUN_00046bec(puVar5);
          return;
        }
      }
    }
  }
  return;
}

