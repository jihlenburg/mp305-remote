/* Address: ram:0000869e; name: FUN_ram_0000869e; body bytes: 268 */

undefined4
FUN_ram_0000869e(undefined4 param_1,uint *param_2,uint *param_3,undefined4 param_4,code *param_5)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  
  gp = &DAT_ram_20002000;
  uVar5 = param_2[4];
  if ((int)param_2[4] < (int)param_2[2]) {
    uVar5 = param_2[2];
  }
  *param_3 = uVar5;
  if (*(char *)((int)param_2 + 0x43) != '\0') {
    *param_3 = uVar5 + 1;
  }
  if ((*param_2 & 0x20) != 0) {
    *param_3 = *param_3 + 2;
  }
  if ((*param_2 & 6) == 0) {
    iVar1 = 0;
    while( true ) {
      if ((int)(param_2[3] - *param_3) <= iVar1) break;
      iVar6 = (*param_5)(param_1,param_4,(int)param_2 + 0x19,1);
      if (iVar6 == -1) goto LAB_ram_0000875e;
      iVar1 = iVar1 + 1;
    }
  }
  uVar4 = (uint)(*(char *)((int)param_2 + 0x43) != '\0');
  uVar5 = uVar4;
  if ((*param_2 & 0x20) != 0) {
    *(undefined1 *)((int)param_2 + uVar4 + 0x43) = 0x30;
    uVar5 = uVar4 + 2;
    *(undefined1 *)((int)param_2 + uVar4 + 0x44) = *(undefined1 *)((int)param_2 + 0x45);
  }
  iVar1 = (*param_5)(param_1,param_4,(int)param_2 + 0x43,uVar5);
  if (iVar1 == -1) {
LAB_ram_0000875e:
    uVar2 = 0xffffffff;
  }
  else {
    iVar1 = 0;
    if (((*param_2 & 6) == 4) && (iVar1 = param_2[3] - *param_3, iVar1 < 0)) {
      iVar1 = 0;
    }
    if ((int)param_2[4] < (int)param_2[2]) {
      iVar1 = iVar1 + (param_2[2] - param_2[4]);
    }
    for (iVar6 = 0; iVar1 != iVar6; iVar6 = iVar6 + 1) {
      iVar3 = (*param_5)(param_1,param_4,(int)param_2 + 0x1a,1);
      if (iVar3 == -1) goto LAB_ram_0000875e;
    }
    uVar2 = 0;
  }
  return uVar2;
}

