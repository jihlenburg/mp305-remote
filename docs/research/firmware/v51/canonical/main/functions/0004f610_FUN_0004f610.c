/* Address: 0004f610; name: FUN_0004f610; body bytes: 120 */

int FUN_0004f610(undefined4 param_1,int param_2,uint param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  uint local_20;
  undefined4 local_1c;
  
  local_20 = param_3;
  local_1c = param_4;
  iVar1 = FUN_0003db8c(param_1,param_2 + 0x14,0);
  if (((iVar1 != 0) && (iVar1 = FUN_0004cd84(param_2,1), iVar1 == 0)) &&
     (iVar1 = FUN_0004bc3e(param_2), iVar1 == 0)) {
    local_20 = local_20 & 0xffffff00;
    local_1c = param_1;
    FUN_0004e5a6(param_2,0x17,&local_20);
    if ((char)local_20 != '\x02') {
      iVar1 = FUN_0004ba5c(param_2);
      do {
        iVar1 = iVar1 + -1;
        if (iVar1 < 0) {
          if ((char)local_20 == '\0') {
            return param_2;
          }
          return 0;
        }
        iVar2 = FUN_0004f610(param_1,*(undefined4 *)(**(int **)(param_2 + 8) + iVar1 * 4));
      } while (iVar2 == 0);
      return iVar2;
    }
  }
  return 0;
}

