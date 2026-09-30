/* Address: 0005a18c; name: FUN_0005a18c; body bytes: 142 */

void FUN_0005a18c(int *param_1,int *param_2)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  int *piVar4;
  
  do {
    while( true ) {
      piVar3 = (int *)*param_2;
      if ((piVar3 == (int *)0x0) || (*(char *)(piVar3 + 3) != '\0')) {
        *(undefined1 *)(*param_1 + 0xc) = 1;
        return;
      }
      piVar4 = (int *)*piVar3;
      iVar1 = piVar4[1];
      if ((int *)iVar1 != piVar3) break;
      iVar1 = piVar4[2];
      if ((iVar1 == 0) || (*(char *)(iVar1 + 0xc) != '\0')) {
        piVar2 = piVar3;
        if ((int *)piVar3[2] == param_2) {
          FUN_0005a21a(param_1,piVar3);
          piVar2 = param_2;
          param_2 = piVar3;
        }
        *(undefined1 *)(piVar2 + 3) = 1;
        *(undefined1 *)(piVar4 + 3) = 0;
        FUN_0005a244(param_1,piVar4);
      }
      else {
LAB_0005a20c:
        *(undefined1 *)(iVar1 + 0xc) = 1;
        *(undefined1 *)(piVar3 + 3) = 1;
        *(undefined1 *)(piVar4 + 3) = 0;
        param_2 = piVar4;
      }
    }
    if ((iVar1 != 0) && (*(char *)(iVar1 + 0xc) == '\0')) goto LAB_0005a20c;
    piVar2 = piVar3;
    if ((int *)piVar3[1] == param_2) {
      FUN_0005a244(param_1,piVar3);
      piVar2 = param_2;
      param_2 = piVar3;
    }
    *(undefined1 *)(piVar2 + 3) = 1;
    *(undefined1 *)(piVar4 + 3) = 0;
    FUN_0005a21a(param_1,piVar4);
  } while( true );
}

