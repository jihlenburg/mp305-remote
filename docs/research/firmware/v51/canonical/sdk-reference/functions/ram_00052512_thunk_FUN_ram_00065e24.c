/* Address: ram:00052512; name: thunk_FUN_ram_00065e24; body bytes: 4 */

undefined4 thunk_FUN_ram_00065e24(undefined4 param_1,undefined4 param_2)

{
  undefined1 uVar1;
  int iVar2;
  undefined4 uVar3;
  
  gp = 0x20004000;
  iVar2 = FUN_ram_00057ba2();
  if (iVar2 == 0) {
    uVar3 = 0x12;
  }
  else {
    uVar1 = FUN_ram_00056968(iVar2,param_2);
    *(undefined1 *)(iVar2 + 0x2a) = uVar1;
    uVar3 = 0;
  }
  return uVar3;
}

