/* Address: 0004e6e2; name: FUN_0004e6e2; body bytes: 224 */

void FUN_0004e6e2(int param_1,int param_2)

{
  ushort uVar1;
  int iVar2;
  undefined4 uVar3;
  int extraout_r2;
  int iVar4;
  undefined8 uVar5;
  
  if (((*(int *)(param_1 + 4) != 0) && (param_2 != 0)) && (*(int *)(param_1 + 4) != param_2)) {
    FUN_0004d3d8(param_1);
    FUN_0004af28(param_2);
    iVar4 = *(int *)(param_1 + 4);
    iVar2 = FUN_0004bc12(param_1);
    while (uVar5 = FUN_0004ba5c(iVar4,iVar2), iVar2 = (int)((ulonglong)uVar5 >> 0x20),
          iVar2 <= (int)uVar5 + -2) {
      *(undefined4 *)(**(int **)(iVar4 + 8) + iVar2 * 4) =
           *(undefined4 *)(**(int **)(iVar4 + 8) + extraout_r2 + iVar2 * 4);
      iVar2 = iVar2 + 1;
    }
    uVar1 = *(short *)(*(int *)(iVar4 + 8) + 0x28) - 1;
    *(ushort *)(*(int *)(iVar4 + 8) + 0x28) = uVar1;
    if (uVar1 == 0) {
      FUN_00046bec(**(undefined4 **)(iVar4 + 8));
      uVar3 = 0;
    }
    else {
      uVar3 = FUN_0004f588(**(undefined4 **)(iVar4 + 8),(uint)uVar1 << 2);
    }
    **(undefined4 **)(iVar4 + 8) = uVar3;
    uVar1 = *(short *)(*(int *)(param_2 + 8) + 0x28) + 1;
    *(ushort *)(*(int *)(param_2 + 8) + 0x28) = uVar1;
    uVar3 = FUN_0004f588(**(undefined4 **)(param_2 + 8),(uint)uVar1 << 2);
    **(undefined4 **)(param_2 + 8) = uVar3;
    iVar2 = FUN_0004ba5c(param_2);
    *(int *)(**(int **)(param_2 + 8) + iVar2 * 4 + -4) = param_1;
    *(int *)(param_1 + 4) = param_2;
    FUN_0004e560(iVar4);
    FUN_0004e5a6(iVar4,0x27,param_1);
    FUN_0004e5a6(iVar4,0x29,0);
    FUN_0004e5a6(param_2,0x27,param_1);
    FUN_0004e5a6(param_2,0x28,0);
    FUN_0004d500(param_1);
    FUN_0004d3d8(param_1);
    return;
  }
  return;
}

