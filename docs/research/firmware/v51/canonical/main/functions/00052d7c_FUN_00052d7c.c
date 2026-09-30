/* Address: 00052d7c; name: FUN_00052d7c; body bytes: 74 */

int FUN_00052d7c(undefined4 param_1,int param_2,uint param_3,int param_4,code *param_5)

{
  int iVar1;
  int iVar2;
  
  do {
    while( true ) {
      if (param_3 == 0) {
        return 0;
      }
      iVar2 = (param_3 >> 1) * param_4 + param_2;
      iVar1 = (*param_5)(param_1,iVar2);
      if (iVar1 < 1) break;
      param_2 = iVar2 + param_4;
      param_3 = ((param_3 >> 1) - ((int)(param_3 << 0x1f) >> 0x1f)) - 1;
    }
    param_3 = param_3 >> 1;
  } while (iVar1 < 0);
  return iVar2;
}

