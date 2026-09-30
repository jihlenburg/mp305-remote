/* Address: ram:00041e32; name: FUN_ram_00041e32; body bytes: 124 */

uint FUN_ram_00041e32(int param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  undefined4 *puVar4;
  
  gp = 0x20004000;
  if ((short)param_2 < 0) {
    iVar2 = tmos_msg_receive();
    if (iVar2 != 0) {
      tmos_msg_deallocate();
    }
    uVar1 = param_2 ^ 0x8000;
  }
  else {
    uVar1 = 0;
    if (param_2 != 0) {
      uVar3 = 0;
      do {
        if (((int)param_2 >> (uVar3 & 0x1f) & 1U) != 0) {
          uVar1 = 1 << (uVar3 & 0x1f) & 0xffff;
          puVar4 = (undefined4 *)(DAT_ram_20001bf8 + (param_1 * 0x10 + uVar3) * 0xc);
          (*(code *)*puVar4)(puVar4[1]);
          *puVar4 = 0;
          puVar4[1] = 0;
          goto LAB_ram_00041ea0;
        }
        uVar3 = uVar3 + 1;
      } while (uVar3 != 0x10);
      uVar1 = 0;
LAB_ram_00041ea0:
      uVar1 = param_2 ^ uVar1;
    }
  }
  return uVar1;
}

