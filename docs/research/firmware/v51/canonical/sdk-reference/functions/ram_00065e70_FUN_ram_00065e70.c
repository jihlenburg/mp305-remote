/* Address: ram:00065e70; name: FUN_ram_00065e70; body bytes: 34 */

undefined4 FUN_ram_00065e70(undefined4 param_1,undefined1 *param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  gp = 0x20004000;
  iVar1 = FUN_ram_00057ba2();
  if (iVar1 == 0) {
    uVar2 = 2;
  }
  else {
    uVar2 = 0;
    *param_2 = *(undefined1 *)(iVar1 + 0x32);
  }
  return uVar2;
}

