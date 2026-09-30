/* Address: ram:20000226; name: tmos_strlen; body bytes: 20 */

int tmos_strlen(int param_1)

{
  int iVar1;
  
  gp = 0x20004000;
  for (iVar1 = 0; *(char *)(param_1 + iVar1) != '\0'; iVar1 = iVar1 + 1) {
  }
  return iVar1;
}

