/* Address: 00018f48; name: FUN_00018f48; body bytes: 180 */

void FUN_00018f48(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  uVar1 = param_2;
  uVar2 = param_3;
  uVar3 = param_4;
  FUN_00018c52();
  FUN_0001cfc8(param_1,param_1 == 1,1,0,0,uVar1,uVar2,uVar3);
  FUN_0001cd70(param_1,1,0,0,2);
  if (param_1 == 1) {
    FUN_0001cda2(1,1,0,1,1,0,0);
    FUN_0001cde8(1,1,1,0,1,1,0,0);
    FUN_00019116(1,param_2);
  }
  else {
    FUN_0001cda2(param_1,1,0,1,0,0,0);
    FUN_0001cde8(param_1,1,1,0,1,0,0,0);
    FUN_00019086(param_1,param_2);
  }
  FUN_00019046(param_1,param_3);
  FUN_00018ffc(param_1,param_4);
  return;
}

