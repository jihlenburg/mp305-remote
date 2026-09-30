/* Address: 0004197c; name: FUN_0004197c; body bytes: 122 */

void FUN_0004197c(int param_1,int param_2)

{
  int iVar1;
  undefined4 *puVar2;
  int *piVar3;
  
  piVar3 = *(int **)(param_2 + 0x4c);
  piVar3[4] = param_1;
  puVar2 = &DAT_2003a544;
  if (DAT_2003a558 != '\0') {
    *(undefined1 *)(param_2 + 0x51) = 100;
    *(undefined1 *)(param_2 + 0x50) = 0;
    while (puVar2 = (undefined4 *)*puVar2, puVar2 != (undefined4 *)0x0) {
      if ((code *)puVar2[4] != (code *)0x0) {
        (*(code *)puVar2[4])(puVar2,param_2);
      }
    }
    return;
  }
  if ((*piVar3 != 0) && (iVar1 = FUN_0004cd84(*piVar3,0x80000), iVar1 != 0)) {
    DAT_2003a558 = 1;
    FUN_0004e5a6(*piVar3,0x1f,param_2);
    DAT_2003a558 = '\0';
  }
  *(undefined1 *)(param_2 + 0x51) = 100;
  *(undefined1 *)(param_2 + 0x50) = 0;
  while (puVar2 = (undefined4 *)*puVar2, puVar2 != (undefined4 *)0x0) {
    if ((code *)puVar2[4] != (code *)0x0) {
      (*(code *)puVar2[4])(puVar2,param_2);
    }
  }
  FUN_000417d4();
  return;
}

