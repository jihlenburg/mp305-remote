/* Address: ram:00044326; name: FUN_ram_00044326; body bytes: 40 */

undefined4 FUN_ram_00044326(int param_1,int param_2)

{
  byte bVar1;
  undefined4 uVar2;
  
  gp = 0x20004000;
  uVar2 = 0;
  if ((param_2 != 0) && (param_1 != 0)) {
    uVar2 = 1;
    bVar1 = *(byte *)(param_2 + 5) & 0xc0;
    if ((bVar1 != 0xc0) && (uVar2 = 3, bVar1 != 0x40)) {
      uVar2 = 2;
    }
  }
  return uVar2;
}

