/* Address: 000376f0; name: FUN_000376f0; body bytes: 134 */

int FUN_000376f0(int param_1,undefined4 param_2,uint param_3,undefined4 param_4)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  int local_20;
  undefined4 local_1c;
  uint local_18;
  int local_14;
  
  cVar1 = *(char *)(param_1 + 0x3b);
  local_20 = param_1;
  local_1c = param_2;
  local_18 = param_3;
  local_14 = param_4;
  uVar2 = FUN_00041788(param_2,cVar1);
  if (cVar1 == '\a') {
    iVar3 = 2;
  }
  else if (cVar1 == '\b') {
    iVar3 = 4;
  }
  else if (cVar1 == '\t') {
    iVar3 = 0x10;
  }
  else if (cVar1 == '\n') {
    iVar3 = 0x100;
  }
  else {
    iVar3 = 0;
  }
  uVar2 = (uint)(*(int *)(*(int *)(param_1 + 0x24) + 0xc) + iVar3 * -4) / uVar2;
  if ((int)param_3 < (int)uVar2) {
    uVar2 = param_3;
  }
  local_20 = 0;
  local_18 = 0;
  local_1c = 0;
  uVar4 = uVar2;
  do {
    local_14 = uVar4 - 1;
    FUN_00040acc(DAT_2003a430,0x32,&local_20);
    iVar3 = FUN_0003db0a(&local_20);
    if (iVar3 <= (int)uVar2) {
      if ((int)uVar4 < 1) {
        return 0;
      }
      return local_14 + 1;
    }
    uVar4 = uVar4 - 1;
  } while (0 < (int)uVar4);
  return 0;
}

