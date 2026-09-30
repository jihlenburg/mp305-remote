/* Address: ram:0000322a; name: FUN_ram_0000322a; body bytes: 140 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint FUN_ram_0000322a(undefined4 param_1,uint param_2,undefined4 param_3,undefined4 param_4,
                     undefined4 param_5)

{
  int iVar1;
  uint uVar2;
  undefined4 extraout_a3;
  undefined4 extraout_a4;
  
  gp = &DAT_ram_20002000;
  if ((short)param_2 < 0) {
    iVar1 = (*_DAT_ram_0004006c)();
    if (iVar1 != 0) {
      (*_DAT_ram_00040068)();
    }
    uVar2 = 0x8000;
  }
  else {
    if ((param_2 & 1) != 0) {
      gp = &DAT_ram_20002000;
      return param_2 ^ 1;
    }
    if ((int)(param_2 << 0x12) < 0) {
      (*_DAT_ram_000401ec)(param_2 ^ 1);
      FUN_ram_00003156();
      (*_DAT_ram_00040058)
                (DAT_ram_20002f74,0x2000,0x2ee00,extraout_a3,extraout_a4,_DAT_ram_00040058);
      uVar2 = 0x2000;
    }
    else {
      if (-1 < (int)(param_2 << 0x11)) {
        gp = &DAT_ram_20002000;
        return 0;
      }
      (*_DAT_ram_00040058)(DAT_ram_20002f74,0x4000,0x640,param_4,param_5,_DAT_ram_00040058);
      uVar2 = 0x4000;
    }
  }
  return uVar2 ^ param_2;
}

