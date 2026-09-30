/* Address: ram:000435c2; name: FUN_ram_000435c2; body bytes: 70 */

undefined4 FUN_ram_000435c2(undefined4 param_1,ushort *param_2)

{
  uint uVar1;
  undefined4 uVar2;
  
  gp = 0x20004000;
  if (*param_2 < 0x17) {
    return 2;
  }
  uVar1 = FUN_ram_0004c74c();
  if (*param_2 <= uVar1) {
    uVar2 = FUN_ram_0004332a(param_1,&LAB_ram_00043438,2,param_2,0);
    return uVar2;
  }
  return 2;
}

