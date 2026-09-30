/* Address: 00020dd6; name: FUN_00020dd6; body bytes: 108 */

int FUN_00020dd6(code *param_1,undefined4 param_2,int param_3,undefined4 param_4,int param_5,
                uint param_6,uint param_7,uint param_8)

{
  int iVar1;
  uint uVar2;
  code *pcVar3;
  int iVar4;
  
  iVar1 = param_3;
  uVar2 = param_6;
  pcVar3 = param_1;
  iVar4 = param_3;
  if ((param_8 & 3) == 0) {
    for (; uVar2 < param_7; uVar2 = uVar2 + 1) {
      (*param_1)(0x20,param_2,iVar1,param_4,pcVar3,param_2,iVar4);
      iVar1 = iVar1 + 1;
    }
  }
  while (param_6 != 0) {
    param_6 = param_6 - 1;
    (*param_1)(*(undefined1 *)(param_5 + param_6),param_2,iVar1,param_4,pcVar3,param_2,iVar4);
    iVar1 = iVar1 + 1;
  }
  if ((int)(param_8 << 0x1e) < 0) {
    for (; (uint)(iVar1 - param_3) < param_7; iVar1 = iVar1 + 1) {
      (*param_1)(0x20,param_2,iVar1,param_4,pcVar3,param_2,iVar4);
    }
  }
  return iVar1;
}

