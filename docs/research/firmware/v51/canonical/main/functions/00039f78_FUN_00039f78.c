/* Address: 00039f78; name: FUN_00039f78; body bytes: 172 */

void FUN_00039f78(int param_1,int *param_2)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = *(int **)(param_1 + 0x1c);
  *(int *)(param_1 + 0x40) = *param_2;
  *(int *)(param_1 + 0x44) = param_2[1];
  if (((*(byte *)(piVar1 + 0xbc) & 7) == 2) || ((*(byte *)(piVar1 + 0xbc) & 7) == 3)) {
    *param_2 = (*piVar1 - *param_2) + -1;
    param_2[1] = (piVar1[1] - param_2[1]) + -1;
  }
  if (((*(byte *)(piVar1 + 0xbc) & 7) == 1) || ((*(byte *)(piVar1 + 0xbc) & 7) == 3)) {
    iVar2 = param_2[1];
    param_2[1] = *param_2;
    *param_2 = (piVar1[1] - iVar2) + -1;
  }
  FUN_000408b0(*(undefined4 *)(param_1 + 0x1c));
  FUN_00040960(*(undefined4 *)(param_1 + 0x1c));
  if ((*(int *)(param_1 + 0xa4) != 0) &&
     ((*(int *)(param_1 + 0x38) != *param_2 || (*(int *)(param_1 + 0x3c) != param_2[1])))) {
    FUN_0004e7c2(*(int *)(param_1 + 0xa4),*param_2,param_2[1]);
  }
  *(int *)(param_1 + 0x30) = *param_2;
  *(int *)(param_1 + 0x34) = param_2[1];
  *(int *)(param_1 + 0x94) = (int)(short)param_2[4];
  FUN_0003a024(param_1);
  if (*(char *)(param_1 + 8) == '\x01') {
    FUN_0003a0ac(param_1);
  }
  else {
    FUN_0003a318();
  }
  *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(param_1 + 0x30);
  *(undefined4 *)(param_1 + 0x3c) = *(undefined4 *)(param_1 + 0x34);
  return;
}

