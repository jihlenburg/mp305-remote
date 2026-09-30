/* Address: 0003a5e0; name: FUN_0003a5e0; body bytes: 138 */

void FUN_0003a5e0(char *param_1,int param_2)

{
  int iVar1;
  
  param_1[10] = param_1[10] | 2;
  if (DAT_2003a470 == param_1) {
    DAT_2003a474 = 0;
  }
  if ((*param_1 != '\x01') && (*param_1 != '\x02')) {
    return;
  }
  if ((((param_2 == 0) || (*(int *)(param_1 + 0x74) == param_2)) &&
      (param_1[0x74] = '\0', param_1[0x75] = '\0', param_1[0x76] = '\0', param_1[0x77] = '\0',
      param_2 == 0)) || (*(int *)(param_1 + 0x68) == param_2)) {
    iVar1 = *(int *)(param_1 + 0x68);
    if (iVar1 != 0) {
      param_1[0x68] = '\0';
      param_1[0x69] = '\0';
      param_1[0x6a] = '\0';
      param_1[0x6b] = '\0';
      FUN_0004e5a6(iVar1,0x14,param_1);
      FUN_0004883e(param_1,0x14,iVar1);
    }
    if (param_2 != 0) goto LAB_0003a634;
LAB_0003a63a:
    param_1[0x6c] = '\0';
    param_1[0x6d] = '\0';
    param_1[0x6e] = '\0';
    param_1[0x6f] = '\0';
    if (param_2 != 0) goto LAB_0003a63e;
LAB_0003a644:
    iVar1 = *(int *)(param_1 + 0x70);
    if (iVar1 != 0) {
      param_1[0x70] = '\0';
      param_1[0x71] = '\0';
      param_1[0x72] = '\0';
      param_1[0x73] = '\0';
      FUN_0004e5a6(iVar1,0x14,param_1);
      FUN_0004883e(param_1,0x14,0);
    }
    if (param_2 == 0) goto LAB_0003a664;
  }
  else {
LAB_0003a634:
    if (*(int *)(param_1 + 0x6c) == param_2) goto LAB_0003a63a;
LAB_0003a63e:
    if (*(int *)(param_1 + 0x70) == param_2) goto LAB_0003a644;
  }
  if (*(int *)(param_1 + 0x78) != param_2) {
    return;
  }
LAB_0003a664:
  param_1[0x78] = '\0';
  param_1[0x79] = '\0';
  param_1[0x7a] = '\0';
  param_1[0x7b] = '\0';
  return;
}

