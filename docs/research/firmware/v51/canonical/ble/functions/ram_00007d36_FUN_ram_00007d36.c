/* Address: ram:00007d36; name: FUN_ram_00007d36; body bytes: 316 */

undefined4 FUN_ram_00007d36(uint *param_1,int *param_2)

{
  ushort uVar1;
  int *piVar2;
  int iVar3;
  code *pcVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  
  gp = &DAT_ram_20002000;
  uVar1 = *(ushort *)(param_2 + 3);
  if ((uVar1 & 8) == 0) {
    if ((param_2[1] < 1) && (param_2[0x10] < 1)) {
      return 0;
    }
    pcVar4 = (code *)param_2[0xb];
    if (pcVar4 == (code *)0x0) {
      return 0;
    }
    uVar7 = *param_1;
    *param_1 = 0;
    if ((int)((uint)uVar1 << 0x13) < 0) {
      iVar3 = param_2[0x15];
    }
    else {
      iVar3 = (*pcVar4)(param_1,param_2[8],0,1);
      if ((iVar3 == -1) && (uVar6 = *param_1, uVar6 != 0)) {
        if ((uVar6 == 0x1d) || (uVar6 == 0x16)) {
          *param_1 = uVar7;
          return 0;
        }
LAB_ram_00007e5c:
        *(ushort *)(param_2 + 3) = *(ushort *)(param_2 + 3) | 0x40;
        goto LAB_ram_00007d5e;
      }
    }
    if (((*(ushort *)(param_2 + 3) & 4) != 0) && (iVar3 = iVar3 - param_2[1], param_2[0xd] != 0)) {
      iVar3 = iVar3 - param_2[0x10];
    }
    iVar3 = (*(code *)param_2[0xb])(param_1,param_2[8],iVar3,0);
    if ((iVar3 == -1) && ((0x1d < *param_1 || ((0x20400001U >> (*param_1 & 0x1f) & 1) == 0)))) {
      *(ushort *)(param_2 + 3) = *(ushort *)(param_2 + 3) | 0x40;
LAB_ram_00007d5e:
      gp = &DAT_ram_20002000;
      return 0xffffffff;
    }
    param_2[1] = 0;
    *param_2 = param_2[4];
    if (((int)((uint)*(ushort *)(param_2 + 3) << 0x13) < 0) && ((iVar3 != -1 || (*param_1 == 0)))) {
      param_2[0x15] = iVar3;
    }
    piVar2 = (int *)param_2[0xd];
    *param_1 = uVar7;
    if (piVar2 != (int *)0x0) {
      if (piVar2 != param_2 + 0x11) {
        FUN_ram_000081fe(param_1);
      }
      param_2[0xd] = 0;
    }
  }
  else {
    iVar3 = param_2[4];
    if (iVar3 != 0) {
      iVar8 = *param_2;
      *param_2 = iVar3;
      iVar8 = iVar8 - iVar3;
      iVar5 = 0;
      if ((uVar1 & 3) == 0) {
        iVar5 = param_2[5];
      }
      param_2[2] = iVar5;
      for (; 0 < iVar8; iVar8 = iVar8 - iVar5) {
        iVar5 = (*(code *)param_2[10])(param_1,param_2[8],iVar3,iVar8);
        if (iVar5 < 1) goto LAB_ram_00007e5c;
        iVar3 = iVar3 + iVar5;
      }
    }
  }
  return 0;
}

