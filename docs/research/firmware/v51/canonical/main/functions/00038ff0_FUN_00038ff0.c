/* Address: 00038ff0; name: FUN_00038ff0; body bytes: 320 */

int * FUN_00038ff0(int param_1,ushort *param_2)

{
  char cVar1;
  ushort uVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  int *piVar7;
  undefined *puVar8;
  int iVar9;
  undefined *local_40;
  char local_3c;
  undefined4 local_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  int *local_2c;
  
  FUN_0004a5f2(param_2,0xc);
  cVar1 = *(char *)(param_1 + 0x10);
  puVar8 = *(undefined **)(param_1 + 0xc);
  if ((cVar1 == '\0') && (*(int *)(puVar8 + 0x10) == 0)) {
    return (int *)0x0;
  }
  iVar3 = FUN_00047b68();
  iVar9 = param_1 + 0x14;
  if (iVar3 == 0) {
    if (cVar1 != '\x01') goto LAB_00039076;
  }
  else {
    if (cVar1 != '\x01') goto LAB_00039076;
    local_40 = puVar8;
    local_3c = cVar1;
    iVar4 = FUN_0003f054(DAT_2003a540,&local_40,0);
    if (iVar4 != 0) {
      iVar3 = FUN_0003f16a();
      uVar5 = *(undefined4 *)(iVar3 + 0xc);
      uVar6 = *(undefined4 *)(iVar3 + 0x10);
      *(undefined4 *)param_2 = *(undefined4 *)(iVar3 + 8);
      *(undefined4 *)(param_2 + 2) = uVar5;
      *(undefined4 *)(param_2 + 4) = uVar6;
      piVar7 = *(int **)(iVar3 + 0x14);
      FUN_0003f1ca(DAT_2003a540,iVar4,0);
      return piVar7;
    }
  }
  iVar4 = FUN_00046cd8(iVar9,puVar8,2);
  if (iVar4 != 0) {
    return (int *)0x0;
  }
LAB_00039076:
  local_40 = &DAT_2003a530;
  piVar7 = (int *)FUN_0004a118();
  do {
    if (piVar7 == (int *)0x0) {
LAB_000390ac:
      if (cVar1 == '\x01') {
        FUN_00046c30(iVar9);
      }
      if (iVar3 == 0) {
        return piVar7;
      }
      if (cVar1 != '\x01') {
        return piVar7;
      }
      if (piVar7 != (int *)0x0) {
        local_3c = cVar1;
        local_40 = (undefined *)FUN_00050a40(puVar8);
        local_38 = *(undefined4 *)param_2;
        uStack_34 = *(undefined4 *)(param_2 + 2);
        uStack_30 = *(undefined4 *)(param_2 + 4);
        local_2c = piVar7;
        iVar3 = FUN_0003f09e(DAT_2003a540,&local_40,0);
        if (iVar3 == 0) {
          FUN_00046bec(local_40);
          return (int *)0x0;
        }
        FUN_0003f1ca(DAT_2003a540,iVar3,0);
        return piVar7;
      }
      return (int *)0x0;
    }
    if ((*piVar7 != 0) && (piVar7[1] != 0)) {
      FUN_00046f3c(iVar9,0);
      iVar4 = (*(code *)*piVar7)(piVar7,param_1,param_2);
      if (iVar4 == 1) {
        if (param_2[4] == 0) {
          if (*param_2 >> 8 == 0x14) {
            uVar2 = param_2[2] << 1;
          }
          else {
            iVar4 = FUN_00040314();
            uVar2 = (ushort)((uint)param_2[2] * iVar4 + 7 >> 3);
          }
          param_2[4] = uVar2;
        }
        goto LAB_000390ac;
      }
    }
    piVar7 = (int *)FUN_0004a13c(local_40,piVar7);
  } while( true );
}

