/* Address: 0001f0e4; name: FUN_0001f0e4; body bytes: 72 */

undefined4 FUN_0001f0e4(int param_1,uint *param_2)

{
  undefined4 uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  
  uVar1 = 0xfffffffd;
  if (param_2 != (uint *)0x0) {
    uVar3 = param_2[2];
    uVar2 = *param_2;
    uVar4 = param_2[5];
    uVar5 = param_2[10];
    *(uint *)(param_1 + 0xc) = param_2[6] | param_2[4] | param_2[8] | param_2[7] | param_2[9];
    *(uint *)(param_1 + 0x10) = uVar2 | uVar3 | uVar4 | 0x600;
    *(uint *)(param_1 + 0x14) = uVar5;
    if (*param_2 == 0) {
      *(uint *)(param_1 + 0x18) = param_2[1];
      uVar1 = FUN_0001f054(param_1,param_2[3]);
    }
    else {
      uVar1 = 0;
    }
  }
  return uVar1;
}

