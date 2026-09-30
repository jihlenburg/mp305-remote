/* Address: 000477b0; name: FUN_000477b0; body bytes: 162 */

int FUN_000477b0(int *param_1,int param_2,int *param_3)

{
  undefined1 uVar1;
  int iVar2;
  int iVar3;
  undefined1 auStack_30 [4];
  int local_2c;
  undefined1 local_28;
  
  FUN_0004a5f2(param_1,0x4c);
  if (param_2 == 0) {
    iVar2 = 0;
  }
  else {
    param_1[3] = param_2;
    uVar1 = FUN_00047ecc(param_2);
    *(undefined1 *)(param_1 + 4) = uVar1;
    iVar2 = FUN_00047614();
    if ((iVar2 != 0) &&
       ((param_1[0x10] = DAT_2003a53c, param_3 == (int *)0x0 ||
        (*(char *)((int)param_3 + 2) == '\0')))) {
      local_28 = (undefined1)param_1[4];
      local_2c = param_1[3];
      iVar2 = FUN_0003f054(param_1[0x10],auStack_30,0);
      if (iVar2 != 0) {
        iVar3 = FUN_0003f16a();
        param_1[0xb] = *(int *)(iVar3 + 0xc);
        iVar3 = *(int *)(iVar3 + 0x10);
        param_1[0x11] = iVar2;
        *param_1 = iVar3;
        return 1;
      }
    }
    iVar3 = FUN_00038ff0(param_1,param_1 + 8);
    *param_1 = iVar3;
    iVar2 = 0;
    if (iVar3 != 0) {
      if (param_3 == (int *)0x0) {
        param_1[1] = 0;
        *(undefined1 *)(param_1 + 2) = 0;
      }
      else {
        param_1[1] = *param_3;
        *(char *)(param_1 + 2) = (char)param_3[1];
      }
      iVar2 = (**(code **)(iVar3 + 4))(iVar3,param_1);
      if ((((char)param_1[2] != '\0') && (iVar2 == 1)) && (param_1[0xb] != 0)) {
        FUN_0004146e(param_1[0xb],0);
      }
    }
  }
  return iVar2;
}

