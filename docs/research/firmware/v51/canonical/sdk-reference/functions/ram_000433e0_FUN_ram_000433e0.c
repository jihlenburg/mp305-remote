/* Address: ram:000433e0; name: FUN_ram_000433e0; body bytes: 72 */

int FUN_ram_000433e0(undefined4 param_1,undefined4 param_2,uint param_3,byte *param_4)

{
  int iVar1;
  
  gp = 0x20004000;
  iVar1 = FUN_ram_0004332a();
  if ((iVar1 == 0) && (DAT_ram_200019d4 != (code *)0x0)) {
    if (param_3 == 1) {
      param_3 = *param_4 + 1 & 0xff;
    }
    (*DAT_ram_200019d4)(param_1,param_3);
  }
  return iVar1;
}

