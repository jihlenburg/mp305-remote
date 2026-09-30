/* Address: 00050c14; name: FUN_00050c14; body bytes: 44 */

undefined1 FUN_00050c14(uint param_1)

{
  undefined1 uVar1;
  undefined *puVar2;
  
  if (param_1 == 0xff) {
    uVar1 = 0x3f;
  }
  else {
    uVar1 = 0;
    if (param_1 != 0) {
      if (param_1 < 0x8d) {
        puVar2 = &DAT_0007a228;
      }
      else {
        param_1 = param_1 - 0x8d & 0xff;
        if ((DAT_2003a450 == (undefined *)0x0) || (puVar2 = DAT_2003a450, DAT_2003a448 <= param_1))
        {
          return 0;
        }
      }
      return puVar2[param_1];
    }
  }
  return uVar1;
}

