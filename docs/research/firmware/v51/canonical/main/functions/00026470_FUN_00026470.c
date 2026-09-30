/* Address: 00026470; name: FUN_00026470; body bytes: 280 */

void FUN_00026470(undefined4 param_1,undefined4 param_2,int param_3)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  uVar3 = 0xffa600;
  uVar1 = uVar3;
  if (param_3 != 1) {
    uVar1 = 0x333333;
  }
  uVar1 = FUN_0004037c(uVar1);
  uVar2 = FUN_0004b9de(param_1,param_2);
  FUN_0004e8b2(uVar2,uVar1,0);
  if (param_3 != 1) {
    uVar3 = 0;
  }
  uVar1 = FUN_0004037c(uVar3);
  uVar3 = FUN_0004b9de(param_1,param_2);
  FUN_0004e8e6(uVar3,uVar1,0);
  uVar1 = 0xffffff;
  if (param_3 == 1) {
    uVar3 = 0;
  }
  else {
    uVar3 = uVar1;
    if (param_3 == 2) {
      uVar3 = 0x999999;
    }
  }
  uVar3 = FUN_0004037c(uVar3);
  uVar2 = FUN_0004b9de(param_1,param_2);
  uVar2 = FUN_0004b9de(uVar2,0);
  FUN_0004ea90(uVar2,uVar3,0);
  if (param_3 == 1) {
    uVar3 = 0;
  }
  else {
    uVar3 = uVar1;
    if (param_3 == 2) {
      uVar3 = 0x999999;
    }
  }
  uVar3 = FUN_0004037c(uVar3);
  uVar2 = FUN_0004b9de(param_1,param_2);
  uVar2 = FUN_0004b9de(uVar2,1);
  FUN_0004ea90(uVar2,uVar3,0);
  if (param_3 == 1) {
    uVar3 = 0;
  }
  else {
    uVar3 = uVar1;
    if (param_3 == 2) {
      uVar3 = 0x999999;
    }
  }
  uVar3 = FUN_0004037c(uVar3);
  uVar2 = FUN_0004b9de(param_1,param_2);
  uVar2 = FUN_0004b9de(uVar2,2);
  FUN_0004ea90(uVar2,uVar3,0);
  if (param_3 == 1) {
    uVar1 = 0;
  }
  else if (param_3 == 2) {
    uVar1 = 0x999999;
  }
  uVar1 = FUN_0004037c(uVar1);
  uVar3 = FUN_0004b9de(param_1,param_2);
  uVar3 = FUN_0004b9de(uVar3,3);
  FUN_0004ea90(uVar3,uVar1,0);
  return;
}

