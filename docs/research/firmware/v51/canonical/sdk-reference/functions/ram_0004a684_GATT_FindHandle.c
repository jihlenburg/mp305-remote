/* Address: ram:0004a684; name: GATT_FindHandle; body bytes: 76 */

int GATT_FindHandle(uint param_1,ushort *param_2)

{
  ushort uVar1;
  uint uVar2;
  int *piVar3;
  int iVar4;
  
  gp = 0x20004000;
  piVar3 = (int *)DAT_ram_20001a48;
  do {
    if (piVar3 == (int *)0x0) {
      return 0;
    }
    uVar1 = *(ushort *)(piVar3[2] + 10);
    if ((uVar1 <= param_1) && ((int)param_1 < (int)((uint)*(ushort *)(piVar3 + 1) + (uint)uVar1))) {
      iVar4 = piVar3[2];
      for (uVar2 = 0; uVar2 != *(ushort *)(piVar3 + 1); uVar2 = uVar2 + 1 & 0xffff) {
        if (*(ushort *)(iVar4 + 10) == param_1) {
          if (param_2 == (ushort *)0x0) {
            gp = 0x20004000;
            return iVar4;
          }
          *param_2 = uVar1;
          gp = 0x20004000;
          return iVar4;
        }
        iVar4 = iVar4 + 0x10;
      }
    }
    piVar3 = (int *)*piVar3;
  } while( true );
}

