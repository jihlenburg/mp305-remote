/* Address: 00058b2e; name: FUN_00058b2e; body bytes: 116 */

int FUN_00058b2e(undefined4 param_1,char *param_2,int param_3,uint param_4)

{
  char *pcVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  
  iVar3 = 0;
  uVar4 = 0x20;
  if (0 < param_3) {
    iVar2 = 0;
    for (pcVar1 = param_2; *pcVar1 != '\0'; pcVar1 = pcVar1 + 1) {
      iVar2 = iVar2 + 1;
    }
    if (iVar2 < param_3) {
      param_3 = param_3 - iVar2;
    }
    else {
      param_3 = 0;
    }
    if ((int)(param_4 << 0x1e) < 0) {
      uVar4 = 0x30;
    }
  }
  if ((param_4 & 1) == 0) {
    for (; 0 < param_3; param_3 = param_3 + -1) {
      FUN_00058a6c(param_1,uVar4);
      iVar3 = iVar3 + 1;
    }
  }
  for (; *param_2 != '\0'; param_2 = param_2 + 1) {
    FUN_00058a6c(param_1);
    iVar3 = iVar3 + 1;
  }
  for (; 0 < param_3; param_3 = param_3 + -1) {
    FUN_00058a6c(param_1,uVar4);
    iVar3 = iVar3 + 1;
  }
  return iVar3;
}

