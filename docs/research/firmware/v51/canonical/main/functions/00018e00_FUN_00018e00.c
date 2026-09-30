/* Address: 00018e00; name: FUN_00018e00; body bytes: 102 */

void FUN_00018e00(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_00015ee8();
  *(undefined4 *)(iVar1 + 0x20) = 0;
  FUN_00018c52(param_1);
  iVar2 = FUN_00015ee8(param_1);
  FUN_00018c52(param_1);
  *(undefined1 *)(iVar2 + 1) = 2;
  *(undefined1 *)(iVar2 + 2) = 2;
  *(undefined1 *)(iVar2 + 9) = 0x59;
  *(undefined1 *)(iVar2 + 3) = 0x59;
  FUN_00012cb0(param_1,0);
  FUN_00018e66(param_1);
  if (*(int *)(iVar1 + 0x20) == 0) {
    *(undefined1 *)(iVar1 + 4) = 1;
  }
  return;
}

