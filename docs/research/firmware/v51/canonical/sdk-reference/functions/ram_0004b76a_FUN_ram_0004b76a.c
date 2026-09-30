/* Address: ram:0004b76a; name: FUN_ram_0004b76a; body bytes: 48 */

undefined4 FUN_ram_0004b76a(undefined4 param_1,undefined2 *param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined2 auStack_12 [5];
  
  gp = 0x20004000;
  iVar1 = GATT_FindHandle(*param_2,auStack_12);
  if (iVar1 == 0) {
    uVar2 = 1;
  }
  else {
    uVar2 = FUN_ram_0004b654(param_1,*(undefined1 *)(iVar1 + 8),auStack_12[0]);
  }
  return uVar2;
}

