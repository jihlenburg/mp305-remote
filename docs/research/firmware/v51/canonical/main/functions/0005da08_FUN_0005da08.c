/* Address: 0005da08; name: FUN_0005da08; body bytes: 254 */

void FUN_0005da08(int param_1,int param_2,int *param_3,int *param_4)

{
  char cVar1;
  int iVar2;
  int iVar3;
  uint local_1c;
  uint local_18;
  
  FUN_00051970(&local_1c,*(undefined4 *)(param_2 + 0x1c),*(undefined4 *)(param_2 + 0x20),
               *(undefined4 *)(param_2 + 0x3c),*(undefined4 *)(param_2 + 0x38),0x1fffffff,0);
  cVar1 = *(char *)(param_1 + 0x3c);
  if ((cVar1 == '\x01') || (cVar1 == '\0')) {
    *param_4 = *param_3 - (local_1c >> 1);
    param_4[2] = *param_3 + (local_1c >> 1);
    if (*(char *)(param_1 + 0x3c) != '\x01') {
      iVar3 = FUN_0004c900();
      iVar2 = param_3[1];
      param_4[3] = iVar2 - iVar3;
      param_4[1] = (iVar2 - iVar3) - local_18;
      return;
    }
    iVar3 = FUN_0004c7fe(param_1);
    iVar2 = param_3[1];
    param_4[1] = iVar3 + iVar2;
    iVar3 = iVar3 + iVar2 + local_18;
  }
  else {
    if ((cVar1 == '\x02') || (cVar1 == '\x04')) {
      param_4[1] = param_3[1] - (local_18 >> 1);
      param_4[3] = param_3[1] + (local_18 >> 1);
      if (*(char *)(param_1 + 0x3c) == '\x02') {
        iVar3 = FUN_0004c864(param_1);
        *param_4 = (*param_3 - local_1c) - iVar3;
        iVar3 = FUN_0004c864(param_1,0x20000);
        iVar3 = *param_3 - iVar3;
      }
      else {
        iVar3 = FUN_0004c8a6();
        *param_4 = iVar3 + *param_3;
        iVar3 = FUN_0004c8a6(param_1,0x20000);
        iVar3 = iVar3 + *param_3 + local_1c;
      }
      param_4[2] = iVar3;
      return;
    }
    if ((cVar1 != '\x10') && (cVar1 != '\b')) {
      return;
    }
    iVar2 = *param_3 - (local_1c >> 1);
    *param_4 = iVar2;
    iVar3 = param_3[1] - (local_18 >> 1);
    param_4[1] = iVar3;
    param_4[2] = iVar2 + local_1c;
    iVar3 = local_18 + iVar3;
  }
  param_4[3] = iVar3;
  return;
}

