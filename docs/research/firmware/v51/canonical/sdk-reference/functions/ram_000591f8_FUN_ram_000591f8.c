/* Address: ram:000591f8; name: FUN_ram_000591f8; body bytes: 218 */

undefined1 FUN_ram_000591f8(int param_1)

{
  byte bVar1;
  byte bVar2;
  undefined1 uVar3;
  int iVar4;
  byte *pbVar5;
  
  gp = 0x20004000;
  iVar4 = FUN_ram_20001120(*(undefined4 *)(param_1 + 0x98),0,0,0);
  uVar3 = 1;
  if (iVar4 == 0) {
    pbVar5 = *(byte **)(param_1 + 0x98);
    bVar1 = *pbVar5;
    *(byte *)(param_1 + 9) = bVar1 & 0xf;
    bVar2 = pbVar5[1];
    *(byte *)(param_1 + 10) = bVar2;
    if ((bVar1 & 0xf) == 8) {
      bVar1 = pbVar5[2];
      if (bVar1 >> 6 == 0) {
        if ((uint)bVar2 == bVar1 + 1) {
          if (pbVar5[3] == 3) {
            *(byte *)(param_1 + 0x75) = (byte)((int)(uint)*pbVar5 >> 6) & 1;
            tmos_memcpy(param_1 + 0x76,pbVar5 + 4,6);
            *(undefined1 *)(param_1 + 0x7c) = 1;
            *(byte *)(param_1 + 0x7d) = **(byte **)(param_1 + 0x98) >> 7;
            tmos_memcpy(param_1 + 0x7e,pbVar5 + 10,6);
            if (bVar1 == 0xd) {
              iVar4 = FUN_ram_00058ee0(param_1);
              uVar3 = 8;
              if (iVar4 != 0) {
                FUN_ram_00058d92(param_1);
                uVar3 = 0;
              }
            }
            else {
              uVar3 = 0x18;
            }
          }
          else {
            uVar3 = 0x11;
          }
        }
        else {
          uVar3 = 0x19;
        }
      }
      else {
        uVar3 = 5;
      }
    }
    else {
      uVar3 = 7;
    }
  }
  return uVar3;
}

