/* Address: ram:0004e8b0; name: FUN_ram_0004e8b0; body bytes: 60 */

undefined1 FUN_ram_0004e8b0(int param_1)

{
  undefined1 uVar1;
  int iVar2;
  
  gp = 0x20004000;
  if (DAT_ram_20001f04 == 0) {
    return 1;
  }
  if (*(code **)(DAT_ram_20001f04 + 4) != (code *)0x0) {
    iVar2 = *(int *)(param_1 + 0x80);
    uVar1 = (**(code **)(DAT_ram_20001f04 + 4))(iVar2 + 0x40,iVar2 + 0x60,iVar2 + 0xc0,iVar2 + 0x20)
    ;
    return uVar1;
  }
  return 1;
}

