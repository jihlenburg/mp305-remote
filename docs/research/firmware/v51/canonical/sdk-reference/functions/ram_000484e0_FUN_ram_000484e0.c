/* Address: ram:000484e0; name: FUN_ram_000484e0; body bytes: 214 */

int FUN_ram_000484e0(undefined4 param_1,char param_2,undefined4 param_3,undefined4 param_4,
                    undefined4 param_5,undefined4 param_6)

{
  int iVar1;
  
  gp = 0x20004000;
  switch(param_2 + -1) {
  case '\0':
    iVar1 = FUN_ram_0004428e(param_1,1);
    if (iVar1 == 0) {
      FUN_ram_00047e7a();
    }
    break;
  case '\x01':
    iVar1 = FUN_ram_0004428e(param_1,2);
    if (iVar1 == 0) {
      FUN_ram_00046ca0(param_3);
    }
    break;
  default:
    iVar1 = 2;
    break;
  case '\x03':
    iVar1 = FUN_ram_0004428e(param_1,4);
    if (iVar1 != 0) {
      gp = 0x20004000;
      return iVar1;
    }
    FUN_ram_000441f4(param_4,param_5,param_6);
    goto LAB_ram_0004855c;
  case '\a':
    iVar1 = FUN_ram_0004428e(param_1,8);
    if (iVar1 == 0) {
      FUN_ram_000441f4(param_4,param_5,param_6);
      FUN_ram_00046ca0(param_3);
      FUN_ram_00046c08();
      FUN_ram_0004f568();
    }
    break;
  case '\v':
    iVar1 = FUN_ram_0004428e(param_1,0xc);
    if (iVar1 != 0) {
      gp = 0x20004000;
      return iVar1;
    }
    FUN_ram_000441f4(param_4,param_5,param_6);
    FUN_ram_00046ca0(param_3);
    FUN_ram_00046c08();
    FUN_ram_0004f568();
LAB_ram_0004855c:
    iVar1 = 0;
    FUN_ram_00047e7a();
    FUN_ram_000479dc();
    FUN_ram_0004f588();
  }
  return iVar1;
}

