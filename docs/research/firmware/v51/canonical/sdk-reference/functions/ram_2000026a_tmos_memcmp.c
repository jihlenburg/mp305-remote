/* Address: ram:2000026a; name: tmos_memcmp; body bytes: 46 */

undefined4 tmos_memcmp(int param_1,int param_2,int param_3)

{
  int iVar1;
  
  gp = 0x20004000;
  if (((param_1 != 0) && (param_2 != 0)) && (param_3 != 0)) {
    iVar1 = 0;
    do {
      if (*(char *)(param_1 + iVar1) != *(char *)(param_2 + iVar1)) {
        gp = 0x20004000;
        return 0;
      }
      iVar1 = iVar1 + 1;
    } while (param_3 != iVar1);
  }
  return 1;
}

