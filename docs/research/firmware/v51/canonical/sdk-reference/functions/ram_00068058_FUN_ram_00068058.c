/* Address: ram:00068058; name: FUN_ram_00068058; body bytes: 52 */

undefined4 FUN_ram_00068058(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  
  gp = 0x20004000;
  iVar1 = FUN_ram_00054de4();
  uVar2 = 0x42;
  if (iVar1 != 0) {
    uVar3 = *(uint *)(iVar1 + 0x54);
    uVar2 = 0xc;
    if ((uVar3 & 2) != 0) {
      if (param_2 == 0) {
        uVar3 = uVar3 & 0xfffffdff;
      }
      else {
        uVar3 = uVar3 | 0x200;
      }
      *(uint *)(iVar1 + 0x54) = uVar3;
      uVar2 = 0;
    }
  }
  return uVar2;
}

