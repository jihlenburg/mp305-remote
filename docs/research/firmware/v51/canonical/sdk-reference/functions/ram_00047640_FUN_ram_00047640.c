/* Address: ram:00047640; name: FUN_ram_00047640; body bytes: 272 */

undefined4 FUN_ram_00047640(uint param_1,undefined4 param_2)

{
  int *piVar1;
  undefined4 uVar2;
  undefined2 uVar3;
  int iVar4;
  
  gp = 0x20004000;
  if (0x1cc < param_1) {
    return 2;
  }
  if (param_1 == 0) {
    if (DAT_ram_200019e4 == 0) {
      return 0;
    }
    if ((DAT_ram_20001d50 & 5) == 0) {
      return 0x12;
    }
    if (DAT_ram_20001a20 == (int *)0x0) {
      iVar4 = 0;
      uVar3 = 0;
    }
    else {
      iVar4 = *DAT_ram_20001a20;
      uVar3 = (undefined2)DAT_ram_20001a20[1];
    }
LAB_ram_00047702:
    uVar2 = thunk_FUN_ram_00065864(1,3,1,uVar3,iVar4);
    return uVar2;
  }
  piVar1 = (int *)FUN_ram_20000040(param_1 + 8 & 0xffff,0x4715);
  if (piVar1 == (int *)0x0) {
    uVar2 = 2;
  }
  else {
    if (DAT_ram_20001a20 != (int *)0x0) {
      FUN_ram_20000104();
    }
    *piVar1 = (int)(piVar1 + 2);
    DAT_ram_20001a20 = piVar1;
    tmos_memset(piVar1 + 2,0,param_1);
    tmos_memcpy(*DAT_ram_20001a20,param_2,param_1);
    *(short *)(DAT_ram_20001a20 + 1) = (short)param_1;
    if (DAT_ram_200019e4 == 0) {
      uVar2 = 0;
    }
    else {
      if ((DAT_ram_20001d50 & 5) != 0) {
        if (DAT_ram_20001a20 == (int *)0x0) {
          iVar4 = 0;
          uVar3 = 0;
        }
        else {
          iVar4 = *DAT_ram_20001a20;
          uVar3 = (undefined2)DAT_ram_20001a20[1];
        }
        goto LAB_ram_00047702;
      }
      uVar2 = 0x12;
    }
  }
  return uVar2;
}

