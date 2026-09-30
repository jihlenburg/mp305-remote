/* Address: ram:00067fce; name: FUN_ram_00067fce; body bytes: 138 */

undefined4
FUN_ram_00067fce(undefined4 param_1,uint param_2,uint param_3,undefined1 param_4,uint param_5)

{
  int iVar1;
  undefined4 uVar2;
  
  gp = 0x20004000;
  iVar1 = FUN_ram_00054de4();
  if (iVar1 == 0) {
    uVar2 = 0x42;
  }
  else {
    uVar2 = 0xc;
    if ((*(uint *)(iVar1 + 0x54) & 0x200) == 0) {
      uVar2 = 0x11;
      if ((((param_2 <= DAT_ram_20001da9) &&
           (((int)(uint)*(byte *)(iVar1 + 0xa4) >> (param_3 & 0x1f) & 1U) != 0)) &&
          (DAT_ram_20001e28 << 0xc < 0)) && (param_5 <= DAT_ram_20001da8)) {
        *(char *)(iVar1 + 0xa6) = (char)param_3;
        *(char *)(iVar1 + 0xa5) = (char)param_2;
        *(undefined1 *)(iVar1 + 0xa7) = param_4;
        if (param_3 == 0) {
          param_5 = 0;
        }
        *(char *)(iVar1 + 0xa8) = (char)param_5;
        *(uint *)(iVar1 + 0x54) = *(uint *)(iVar1 + 0x54) | 0x100;
        uVar2 = 0;
      }
    }
  }
  return uVar2;
}

