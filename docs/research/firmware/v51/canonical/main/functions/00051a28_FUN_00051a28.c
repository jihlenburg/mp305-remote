/* Address: 00051a28; name: FUN_00051a28; body bytes: 88 */

undefined8 FUN_00051a28(char *param_1,uint param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  uint local_28;
  int iStack_24;
  uint local_20;
  
  local_28 = param_2;
  if ((param_1 == (char *)0x0) || (param_3 == 0)) {
    iVar2 = 0;
  }
  else {
    iVar2 = 0;
    if (*param_1 != '\0') {
      iVar2 = 0;
      local_20 = 0;
      iStack_24 = param_3;
      if (param_2 != 0) {
        while (local_20 < param_2) {
          FUN_0005172c(param_1,&local_28,&iStack_24,&local_20);
          iVar1 = FUN_00046b72(param_3,local_28,iStack_24);
          if (0 < iVar1) {
            iVar2 = iVar1 + iVar2 + param_4;
          }
        }
        if (0 < iVar2) {
          iVar2 = iVar2 - param_4;
        }
      }
    }
  }
  return CONCAT44(local_28,iVar2);
}

