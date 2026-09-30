/* Address: ram:0004aede; name: FUN_ram_0004aede; body bytes: 54 */

undefined4 FUN_ram_0004aede(undefined4 param_1,undefined2 *param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined2 auStack_12 [5];
  
  gp = 0x20004000;
  iVar1 = GATT_FindHandle(*param_2,auStack_12);
  if (iVar1 == 0) {
    uVar2 = 1;
  }
  else {
    uVar2 = FUN_ram_0004ae74(param_1,*(undefined1 *)(iVar1 + 8),auStack_12[0],param_2);
  }
  return uVar2;
}

