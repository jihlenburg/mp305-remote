/* Address: ram:00044162; name: FUN_ram_00044162; body bytes: 146 */

int FUN_ram_00044162(uint param_1,short *param_2,uint param_3,int param_4)

{
  byte bVar1;
  byte bVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  
  gp = 0x20004000;
  *param_2 = 0;
  if (param_4 == 0) {
    return 0;
  }
  uVar3 = 0;
  while( true ) {
    if (param_3 <= uVar3) {
      return 0;
    }
    bVar1 = *(byte *)(param_4 + uVar3);
    uVar5 = (uint)bVar1;
    uVar6 = uVar3 + 1 & 0xffff;
    if (uVar5 == 0) {
      gp = 0x20004000;
      return 0;
    }
    if ((int)param_3 < (int)(uVar5 + uVar6)) {
      gp = 0x20004000;
      return 0;
    }
    bVar2 = *(byte *)(param_4 + uVar6);
    iVar4 = FUN_ram_0004414c((uint)bVar2);
    if (iVar4 == 0) break;
    *param_2 = bVar1 - 1;
    if (bVar2 == param_1) {
      gp = 0x20004000;
      return uVar6 + 1 + param_4;
    }
    uVar3 = uVar3 + uVar5 & 0xffff;
  }
  gp = 0x20004000;
  return 0;
}

