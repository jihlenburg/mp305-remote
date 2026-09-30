/* Address: ram:0005d354; name: FUN_ram_0005d354; body bytes: 98 */

undefined4 FUN_ram_0005d354(undefined1 param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  gp = 0x20004000;
  iVar1 = FUN_ram_00054de4(param_1);
  if (iVar1 == 0) {
    uVar2 = 2;
  }
  else {
    if ((DAT_ram_20001e30 & 0x200) == 0) {
      FUN_ram_00068284(0x3c,0,1,*(undefined1 *)(iVar1 + 0x3d),iVar1 + 0x3e,0,0,0,0);
    }
    else {
      FUN_ram_000682aa(0x3c,0,1,0,0,0,0,0,0,0,0);
    }
    uVar2 = 0;
  }
  return uVar2;
}

