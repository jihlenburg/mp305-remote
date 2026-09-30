/* Address: 0001b740; name: FUN_0001b740; body bytes: 84 */

undefined4 FUN_0001b740(undefined1 *param_1,int param_2,undefined1 *param_3)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = 0xfffffffd;
  if (param_1 != (undefined1 *)0x0) {
    iVar2 = FUN_0001497c(0x100,(DAT_2003a60c >> ((DAT_40054020 & 0x7ffffff) >> 0x18)) / 20000);
    if (iVar2 == 0) {
      for (; param_2 != 0; param_2 = param_2 + -1) {
        *param_1 = *param_3;
        param_3 = param_3 + 1;
        param_1 = param_1 + 1;
      }
      return 0;
    }
    uVar1 = 0xfffffffb;
  }
  return uVar1;
}

