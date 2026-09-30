/* Address: 00018170; name: FUN_00018170; body bytes: 116 */

void FUN_00018170(int param_1,int param_2,int param_3,int param_4,int param_5)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  
  uVar1 = (param_3 - param_1) + 1U & 0xffff;
  uVar2 = (param_4 - param_2) + 1U & 0xffff;
  uVar3 = uVar1 * uVar2;
  if (uVar3 < 0x10000) {
    FUN_0003bfbc(param_1,param_2);
    iVar5 = param_5;
  }
  else {
    iVar4 = uVar1 * (uVar2 >> 1);
    uVar1 = param_2 + (uVar2 >> 1);
    iVar5 = param_5 + iVar4 * 2;
    FUN_0003bfbc(param_1,param_2,param_3,uVar1 - 1 & 0xffff);
    FUN_0003c2a4(param_5,iVar4);
    FUN_0003bfbc(param_1,uVar1 & 0xffff,param_3,param_4);
    uVar3 = uVar3 - iVar4;
  }
  FUN_0003c2a4(iVar5,uVar3);
  return;
}

