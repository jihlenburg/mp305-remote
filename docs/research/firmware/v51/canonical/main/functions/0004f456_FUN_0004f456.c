/* Address: 0004f456; name: FUN_0004f456; body bytes: 154 */

int * FUN_0004f456(int *param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  if (param_1 == (int *)0x0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  piVar1 = (int *)FUN_0004f400();
  if (piVar1 == (int *)0x0) {
    piVar1 = (int *)FUN_0004a360(0x14);
    if (piVar1 == (int *)0x0) {
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    iVar2 = FUN_0004a360(param_1[2]);
    piVar1[4] = iVar2;
    if (iVar2 == 0) {
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    *(undefined1 *)(piVar1 + 3) = 0;
    piVar1[1] = 0;
    piVar1[2] = 0;
    if (*param_1 == 0) {
      *param_1 = (int)piVar1;
      *piVar1 = 0;
      *(undefined1 *)(piVar1 + 3) = 1;
    }
    else {
      piVar1[4] = param_2;
      iVar5 = *param_1;
      iVar4 = *param_1;
      while (iVar4 != 0) {
        iVar3 = (*(code *)param_1[1])(piVar1[4],*(undefined4 *)(iVar4 + 0x10));
        iVar5 = iVar4;
        if (iVar3 < 0) {
          iVar4 = *(int *)(iVar4 + 4);
        }
        else {
          iVar4 = *(int *)(iVar4 + 8);
        }
      }
      *piVar1 = iVar5;
      *(undefined1 *)(piVar1 + 3) = 0;
      iVar4 = (*(code *)param_1[1])(param_2,*(undefined4 *)(iVar5 + 0x10));
      if (iVar4 < 0) {
        *(int **)(iVar5 + 4) = piVar1;
      }
      else {
        *(int **)(iVar5 + 8) = piVar1;
      }
      FUN_0005a18c(param_1,piVar1);
      piVar1[4] = iVar2;
    }
  }
  return piVar1;
}

