/* Address: ram:0004957c; name: FUN_ram_0004957c; body bytes: 54 */

undefined4 FUN_ram_0004957c(undefined4 param_1,int *param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  gp = 0x20004000;
  iVar1 = FUN_ram_00049522();
  if (iVar1 == 0) {
    uVar2 = 2;
  }
  else {
    if (param_2 != (int *)0x0) {
      *param_2 = iVar1;
    }
    uVar2 = 0x17;
    if ((*(char *)(iVar1 + 8) != -2) && (uVar2 = 0, *(char *)(iVar1 + 8) != -1)) {
      uVar2 = 0x16;
    }
  }
  return uVar2;
}

