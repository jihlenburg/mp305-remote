/* Address: 0003aa70; name: FUN_0003aa70; body bytes: 176 */

void FUN_0003aa70(int param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int local_40;
  int local_3c;
  int local_38;
  int local_34;
  int local_30;
  int local_2c;
  
  if ((param_2 != 0xffff) && (param_2 < *(uint *)(param_1 + 0x38))) {
    FUN_0003d9da(&local_40,*(int *)(param_1 + 0x30) + param_2 * 0x10);
    FUN_0004bb3c(param_1,&local_30);
    iVar1 = FUN_0004c8ca(param_1,0);
    iVar2 = FUN_0004c822(param_1,0);
    FUN_0004bb48(param_1);
    iVar3 = FUN_0004089c();
    if (iVar1 <= iVar3 / 10) {
      iVar1 = iVar3 / 10;
    }
    if (iVar2 <= iVar3 / 10) {
      iVar2 = iVar3 / 10;
    }
    local_40 = local_40 + (local_30 - iVar1);
    local_3c = local_3c + (local_2c - iVar2);
    local_38 = local_30 + local_38 + iVar1;
    local_34 = local_34 + local_2c + iVar2;
    if ((*(uint *)(param_1 + 0x40) == param_2) &&
       ((int)((uint)*(ushort *)(*(int *)(param_1 + 0x34) + param_2 * 2) << 0x15) < 0)) {
      iVar1 = FUN_0003db0a(&local_40);
      local_3c = local_3c - iVar1;
    }
    FUN_0004d40e(param_1,&local_40);
  }
  return;
}

