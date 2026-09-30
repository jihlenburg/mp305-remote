/* Address: 0001051e; name: FUN_0001051e; body bytes: 50 */

void FUN_0001051e(int param_1,int param_2,uint param_3)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  uVar3 = 0;
  while( true ) {
    if (param_3 <= uVar3) {
      return;
    }
    iVar1 = FUN_00010bf0(*(undefined1 *)(param_1 + uVar3));
    iVar2 = FUN_00010bf0(*(undefined1 *)(param_2 + uVar3));
    if (iVar1 != iVar2) break;
    if (*(char *)(param_1 + uVar3) == '\0') {
      return;
    }
    uVar3 = uVar3 + 1;
  }
  return;
}

