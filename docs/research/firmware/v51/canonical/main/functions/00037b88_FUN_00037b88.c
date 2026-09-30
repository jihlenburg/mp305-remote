/* Address: 00037b88; name: FUN_00037b88; body bytes: 78 */

undefined4 FUN_00037b88(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 local_1c [2];
  
  iVar1 = FUN_0003759c();
  if (iVar1 == 0) {
    local_1c[0] = 0;
  }
  else {
    uVar2 = FUN_0004cb3a(param_1,0x40000);
    uVar3 = FUN_0004cb5e(param_1,0x40000);
    uVar4 = FUN_000491e8(iVar1);
    FUN_00051970(local_1c,uVar4,uVar2,uVar3,0,0x1fffffff,0);
  }
  return local_1c[0];
}

