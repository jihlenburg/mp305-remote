/* Address: 00058a9c; name: FUN_00058a9c; body bytes: 146 */

undefined8
FUN_00058a9c(undefined4 param_1,uint param_2,uint param_3,uint param_4,int param_5,int param_6,
            int param_7)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  char *pcVar4;
  int iVar5;
  uint local_28;
  uint uStack_24;
  undefined4 uStack_20;
  
  bVar1 = false;
  iVar5 = 0;
  uStack_24 = param_3;
  if (param_2 == 0) {
    local_28 = 0x30;
    uStack_20 = param_4;
    iVar2 = FUN_00058b2e(param_1,&local_28,param_5,param_6);
  }
  else {
    uVar3 = param_2;
    if (((param_4 != 0) && (param_3 == 10)) && ((int)param_2 < 0)) {
      bVar1 = true;
      uVar3 = -param_2;
    }
    uStack_20 = param_4 & 0xffffff;
    pcVar4 = (char *)((int)&uStack_20 + 3);
    for (; uVar3 != 0; uVar3 = uVar3 / param_3) {
      iVar2 = uVar3 - param_3 * (uVar3 / param_3);
      if (9 < iVar2) {
        iVar2 = iVar2 + param_7 + -0x3a;
      }
      pcVar4 = pcVar4 + -1;
      *pcVar4 = (char)iVar2 + '0';
    }
    local_28 = param_2;
    if (bVar1) {
      if ((param_5 == 0) || (-1 < param_6 << 0x1e)) {
        pcVar4 = pcVar4 + -1;
        *pcVar4 = '-';
      }
      else {
        FUN_00058a6c(param_1,0x2d);
        iVar5 = 1;
        param_5 = param_5 + -1;
      }
    }
    iVar2 = FUN_00058b2e(param_1,pcVar4,param_5,param_6);
    iVar2 = iVar2 + iVar5;
  }
  return CONCAT44(local_28,iVar2);
}

