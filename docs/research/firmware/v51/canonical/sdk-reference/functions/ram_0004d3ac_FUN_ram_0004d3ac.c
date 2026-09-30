/* Address: ram:0004d3ac; name: FUN_ram_0004d3ac; body bytes: 102 */

void FUN_ram_0004d3ac(byte *param_1,undefined4 param_2)

{
  byte bVar1;
  undefined4 uVar2;
  
  gp = 0x20004000;
  bVar1 = *param_1;
  if (bVar1 == 4) {
    FUN_ram_0004d1f6(param_1[8],*(undefined2 *)(param_1 + 6),param_2,0x13,0,0);
    uVar2 = 0x12;
  }
  else {
    if ((bVar1 & 0xfb) != 2) {
      if (bVar1 == 3) {
        FUN_ram_0004d36e(param_1,param_2,0);
        return;
      }
      return;
    }
    FUN_ram_0004d312(param_1,param_2,0);
    uVar2 = 0x14;
  }
  FUN_ram_0004c4c2(5,*(undefined2 *)(param_1 + 6),uVar2);
  return;
}

