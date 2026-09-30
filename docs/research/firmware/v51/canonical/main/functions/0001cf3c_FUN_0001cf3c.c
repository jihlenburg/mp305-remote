/* Address: 0001cf3c; name: FUN_0001cf3c; body bytes: 124 */

void FUN_0001cf3c(undefined2 *param_1,int param_2,uint param_3)

{
  undefined4 uVar1;
  uint uVar2;
  uint uVar3;
  
  uVar2 = 0;
  uVar3 = 0;
  if (param_1 == (undefined2 *)&DAT_40026000) {
    if (param_2 == 0) {
      uVar2 = 0x4af;
    }
  }
  else {
    if (param_1 == &DAT_4003a400) {
      if (param_2 == 3) {
        uVar2 = 0x927b;
        goto LAB_0001cf84;
      }
    }
    else if (param_1 == (undefined2 *)&DAT_4003ac00) {
      if (param_2 == 2) {
        uVar2 = 23999;
      }
      goto LAB_0001cf84;
    }
    if ((param_1 == (undefined2 *)&DAT_40026c00) && (param_2 == 2)) {
      uVar2 = 199;
    }
  }
LAB_0001cf84:
  if (param_3 < 100) {
    if (param_3 == 0) {
      uVar1 = 0x200;
    }
    else {
      uVar3 = (param_3 * uVar2) / 100;
      uVar1 = 0;
    }
  }
  else {
    uVar1 = 0x300;
    uVar3 = uVar2;
  }
  FUN_0001decc(param_1,param_2,uVar1);
  FUN_0001df02(param_1,param_2,uVar3);
  return;
}

