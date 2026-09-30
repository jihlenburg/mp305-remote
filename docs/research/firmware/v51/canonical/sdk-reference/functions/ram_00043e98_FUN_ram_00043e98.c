/* Address: ram:00043e98; name: FUN_ram_00043e98; body bytes: 34 */

undefined4 FUN_ram_00043e98(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  gp = 0x20004000;
  iVar1 = FUN_ram_0004e028();
  if (iVar1 != 0) {
    uVar2 = thunk_FUN_ram_0006512c(*(undefined2 *)(iVar1 + 2),param_2);
    return uVar2;
  }
  return 0x12;
}

