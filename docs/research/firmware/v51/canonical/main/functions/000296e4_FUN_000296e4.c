/* Address: 000296e4; name: FUN_000296e4; body bytes: 184 */

undefined8 FUN_000296e4(int param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int *piVar4;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  
  piVar4 = *(int **)(param_1 + 0x2a8);
  local_20 = param_1;
  local_1c = param_2;
  local_18 = param_3;
  local_14 = param_4;
  while (piVar4[0xe] != 0) {
    FUN_0004194c();
    FUN_000417d4();
  }
  iVar1 = FUN_00040988(param_1);
  if (iVar1 != 0) {
    FUN_000661e0(DAT_2003a430);
  }
  uVar2 = 1;
  *(undefined4 *)(param_1 + 0x30) = 1;
  if (((*(uint *)(param_1 + 0x38) & 1) == 0) || (-1 < *(int *)(param_1 + 0x38) << 0x1e)) {
    uVar2 = 0;
  }
  *(undefined4 *)(param_1 + 0x34) = uVar2;
  iVar1 = *(int *)(param_1 + 0x34);
  if (*(int *)(param_1 + 0x28) != 0) {
    uVar2 = *(undefined4 *)(*piVar4 + 0x10);
    local_20 = *(int *)(param_1 + 0x300) + *(int *)(param_1 + 0x10);
    local_1c = *(int *)(param_1 + 0x304) + *(int *)(param_1 + 0x14);
    local_18 = *(int *)(param_1 + 0x308) + *(int *)(param_1 + 0x10);
    local_14 = *(int *)(param_1 + 0x30c) + *(int *)(param_1 + 0x14);
    FUN_00040acc(param_1,0x3a,&local_20);
    (**(code **)(param_1 + 0x28))(param_1,&local_20,uVar2);
    FUN_00040acc(param_1,0x3b,&local_20);
  }
  iVar3 = FUN_00040988(param_1);
  if ((iVar3 != 0) && ((*(char *)(param_1 + 0x39) != '\x01' || (iVar1 != 0)))) {
    iVar1 = *(int *)(param_1 + 0x1c);
    if (*(int *)(param_1 + 0x24) == iVar1) {
      iVar1 = *(int *)(param_1 + 0x20);
    }
    *(int *)(param_1 + 0x24) = iVar1;
  }
  return CONCAT44(local_1c,local_20);
}

