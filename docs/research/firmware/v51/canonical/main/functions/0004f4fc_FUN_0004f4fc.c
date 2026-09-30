/* Address: 0004f4fc; name: FUN_0004f4fc; body bytes: 140 */

int FUN_0004f4fc(int *param_1,int *param_2)

{
  char cVar1;
  undefined4 *puVar2;
  int *piVar3;
  undefined4 *puVar4;
  int iVar5;
  int *piVar6;
  int *piVar7;
  int *extraout_r3;
  
  puVar4 = (undefined4 *)param_2[1];
  puVar2 = (undefined4 *)param_2[2];
  if (puVar4 == (undefined4 *)0x0) {
    if (puVar2 != (undefined4 *)0x0) {
      puVar4 = puVar2;
    }
  }
  else if (puVar2 != (undefined4 *)0x0) {
    piVar3 = (int *)thunk_FUN_0004f4f4();
    iVar5 = *param_2;
    if (iVar5 == 0) {
      *extraout_r3 = (int)piVar3;
    }
    else if (*(int **)(iVar5 + 4) == param_2) {
      *(int **)(iVar5 + 4) = piVar3;
    }
    else {
      *(int **)(iVar5 + 8) = piVar3;
    }
    piVar6 = (int *)*piVar3;
    cVar1 = (char)piVar3[3];
    puVar4 = (undefined4 *)piVar3[2];
    piVar7 = piVar3;
    if (piVar6 != param_2) {
      if (puVar4 != (undefined4 *)0x0) {
        *puVar4 = piVar6;
      }
      piVar6[1] = (int)puVar4;
      piVar3[2] = param_2[2];
      *(int **)param_2[2] = piVar3;
      piVar7 = piVar6;
    }
    *piVar3 = *param_2;
    *(char *)(piVar3 + 3) = (char)param_2[3];
    piVar3[1] = param_2[1];
    *(int **)param_2[1] = piVar3;
    param_1 = extraout_r3;
    goto joined_r0x0004f57a;
  }
  cVar1 = (char)param_2[3];
  piVar7 = (int *)*param_2;
  if (puVar4 != (undefined4 *)0x0) {
    *puVar4 = piVar7;
  }
  if (piVar7 == (int *)0x0) {
    *param_1 = (int)puVar4;
  }
  else if ((int *)piVar7[1] == param_2) {
    piVar7[1] = (int)puVar4;
  }
  else {
    piVar7[2] = (int)puVar4;
  }
joined_r0x0004f57a:
  if (cVar1 == '\x01') {
    FUN_0005a0a4(param_1,puVar4,piVar7);
  }
  iVar5 = param_2[4];
  FUN_00046bec(param_2);
  return iVar5;
}

