/* Address: ram:000473e4; name: GAP_UpdateAdvertisingData; body bytes: 332 */

undefined4 GAP_UpdateAdvertisingData(undefined1 param_1,int param_2,uint param_3,undefined4 param_4)

{
  uint uVar1;
  int *piVar2;
  undefined4 uVar3;
  
  gp = 0x20004000;
  if ((DAT_ram_20001d50 & 5) != 0) {
    if (0x1cc < param_3) {
      return 2;
    }
    if ((DAT_ram_200019e4 != 0) && (DAT_ram_20001a0c == -2)) {
      uVar1 = param_3 + 8 & 0xffff;
      DAT_ram_20001a0c = param_1;
      if (param_2 == 0) {
        piVar2 = (int *)FUN_ram_20000040(uVar1,0x4715);
        if (piVar2 != (int *)0x0) {
          if (DAT_ram_20001a20 != (int *)0x0) {
            FUN_ram_20000104();
          }
          *piVar2 = (int)(piVar2 + 2);
          DAT_ram_20001a20 = piVar2;
          tmos_memset(piVar2 + 2,0,param_3);
          tmos_memcpy(*DAT_ram_20001a20,param_4,param_3);
          piVar2 = DAT_ram_20001a20;
          *(short *)(DAT_ram_20001a20 + 1) = (short)param_3;
          uVar3 = thunk_FUN_ram_00065864(1,3,1,param_3,*piVar2);
          return uVar3;
        }
      }
      else {
        piVar2 = (int *)FUN_ram_20000040(uVar1,0x4716);
        if (piVar2 != (int *)0x0) {
          if (DAT_ram_20001a18 != (int *)0x0) {
            FUN_ram_20000104();
          }
          *piVar2 = (int)(piVar2 + 2);
          DAT_ram_20001a18 = piVar2;
          tmos_memset(piVar2 + 2,0,param_3);
          tmos_memcpy(*DAT_ram_20001a18,param_4,param_3);
          piVar2 = DAT_ram_20001a18;
          *(short *)(DAT_ram_20001a18 + 1) = (short)param_3;
          uVar3 = thunk_FUN_ram_0006583e(1,3,1,param_3,*piVar2);
          return uVar3;
        }
      }
      return 2;
    }
  }
  return 0x12;
}

