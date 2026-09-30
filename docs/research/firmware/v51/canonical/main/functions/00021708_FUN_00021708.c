/* Address: 00021708; name: FUN_00021708; body bytes: 88 */

undefined8 FUN_00021708(int param_1,int *param_2,int *param_3,int param_4,int param_5)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int local_28;
  int *local_24;
  int *piStack_20;
  int iStack_1c;
  
  local_28 = param_1;
  local_24 = param_2;
  piStack_20 = param_3;
  iStack_1c = param_4;
  iVar1 = FUN_0003db4c(&local_28,param_3,param_2);
  if (iVar1 != 0) {
    iVar1 = (int)local_24 - param_3[1];
    iVar4 = local_28 - *param_3;
    iVar6 = (local_28 + param_4) - *param_2;
    uVar2 = FUN_0003db28(&local_28);
    for (uVar3 = 0; uVar3 < uVar2; uVar3 = uVar3 + 1) {
      uVar5 = (uint)*(byte *)(iVar6 + uVar3) +
              (uint)*(byte *)(iVar4 + param_5 * iVar1 + param_1 + uVar3);
      if (0xff < uVar5) {
        uVar5 = 0xff;
      }
      *(char *)(iVar6 + uVar3) = (char)uVar5;
    }
  }
  return CONCAT44(local_24,local_28);
}

