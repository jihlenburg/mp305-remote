/* Address: 00037460; name: FUN_00037460; body bytes: 124 */

undefined8 FUN_00037460(int param_1,undefined1 *param_2,int param_3)

{
  uint uVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  undefined1 *local_20;
  undefined1 *puStack_1c;
  int iStack_18;
  
  iVar4 = 0;
  piVar3 = *(int **)(*(int *)(param_1 + 0x18) + 0xc);
  uVar1 = piVar3[2];
  local_20 = param_2;
  if ((int)((uint)*(ushort *)(*(int *)(param_1 + 0x18) + 0x12) << 0x12) < 0) {
    if ((param_2[piVar3[1]] == 0) || (*(byte *)(uVar1 + param_3) == 0)) goto LAB_000374d8;
    iVar2 = (int)(short)((byte)param_2[piVar3[1]] - 1) *
            (int)(short)(ushort)*(byte *)((int)piVar3 + 0xd) + *piVar3;
    iVar4 = *(byte *)(uVar1 + param_3) - 1;
  }
  else {
    puStack_1c = param_2;
    iStack_18 = param_3;
    if (uVar1 >> 0x1e == 0) {
      iVar5 = *piVar3;
      local_20 = &LAB_0003affc_1;
      iVar2 = FUN_00052d7c(&puStack_1c,iVar5,piVar3[2] & 0x3fffffff,2);
      if (iVar2 == 0) goto LAB_000374d8;
      iVar4 = iVar2 - iVar5 >> 1;
    }
    else {
      if (uVar1 >> 0x1e != 1) goto LAB_000374d8;
      iVar5 = *piVar3;
      local_20 = &LAB_0003afe8_1;
      iVar2 = FUN_00052d7c(&puStack_1c,iVar5,piVar3[2] & 0x3fffffff,4);
      if (iVar2 == 0) goto LAB_000374d8;
      iVar4 = iVar2 - iVar5 >> 2;
    }
    iVar2 = piVar3[1];
  }
  iVar4 = (int)*(char *)(iVar2 + iVar4);
LAB_000374d8:
  return CONCAT44(local_20,iVar4);
}

