/* Address: ram:00047750; name: FUN_ram_00047750; body bytes: 208 */

undefined4 FUN_ram_00047750(uint param_1,undefined4 param_2)

{
  int *piVar1;
  undefined4 uVar2;
  uint auStack_24 [4];
  
  gp = 0x20004000;
  if (0x1cc < param_1) {
    return 2;
  }
  if (param_1 != 0) {
    piVar1 = (int *)FUN_ram_20000040(param_1 + 8 & 0xffff,0x4717);
    if (piVar1 == (int *)0x0) {
      gp = 0x20004000;
      return 2;
    }
    if (DAT_ram_20001a1c != (int *)0x0) {
      FUN_ram_20000104();
    }
    *piVar1 = (int)(piVar1 + 2);
    DAT_ram_20001a1c = piVar1;
    tmos_memset(piVar1 + 2,0,param_1);
    tmos_memcpy(*DAT_ram_20001a1c,param_2,param_1);
    *(short *)(DAT_ram_20001a1c + 1) = (short)param_1;
  }
  uVar2 = 0;
  if ((DAT_ram_200019e4 != 0) && (uVar2 = 0x12, (DAT_ram_20001d50 & 5) != 0)) {
    GAPRole_GetParameter(0x30d,auStack_24);
    uVar2 = 0;
    if ((auStack_24[0] & 0xf0) != 0) {
      uVar2 = thunk_FUN_ram_000658d6(1,3,(short)DAT_ram_20001a1c[1],*DAT_ram_20001a1c);
    }
  }
  return uVar2;
}

