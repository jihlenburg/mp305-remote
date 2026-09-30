/* Address: ram:000590b8; name: FUN_ram_000590b8; body bytes: 320 */

undefined4 FUN_ram_000590b8(int param_1)

{
  byte bVar1;
  byte bVar2;
  byte *pbVar3;
  undefined4 uVar4;
  int iVar5;
  byte *pbVar6;
  byte *pbVar7;
  
  gp = 0x20004000;
  iVar5 = FUN_ram_20001120(*(undefined4 *)(param_1 + 0x98),0,0,0);
  if (iVar5 == 0) {
    pbVar3 = *(byte **)(param_1 + 0x98);
    bVar1 = *pbVar3;
    *(byte *)(param_1 + 9) = bVar1 & 0xf;
    bVar2 = pbVar3[1];
    *(byte *)(param_1 + 10) = bVar2;
    if ((bVar1 & 0xf) == 7) {
      if (*(byte *)(param_1 + 0x3d) == pbVar3[2] >> 6) {
        pbVar6 = pbVar3 + 4;
        if ((pbVar3[2] & 0x3f) < bVar2) {
          *(undefined1 *)(param_1 + 0x74) = 0;
          if ((pbVar3[3] & 1) != 0) {
            *(undefined1 *)(param_1 + 0x74) = 1;
            *(byte *)(param_1 + 0x75) = (byte)((int)(uint)*pbVar3 >> 6) & 1;
            tmos_memcpy(param_1 + 0x76,pbVar6,6);
            pbVar6 = pbVar3 + 10;
          }
          *(undefined1 *)(param_1 + 0x7c) = 0;
          pbVar7 = pbVar6;
          if ((pbVar3[3] & 2) != 0) {
            *(undefined1 *)(param_1 + 0x7c) = 1;
            pbVar7 = pbVar6 + 6;
            *(byte *)(param_1 + 0x7d) = **(byte **)(param_1 + 0x98) >> 7;
            tmos_memcpy(param_1 + 0x7e,pbVar6,6);
          }
          if (((pbVar3[3] & 8) == 0) || (*(byte *)(param_1 + 0x3f) == pbVar7[1] >> 4)) {
            iVar5 = FUN_ram_00058ee0(param_1);
            uVar4 = 0x7f;
            if (iVar5 == 1) {
              if (*(char *)(param_1 + 0x3e) == '\0') {
                if ((*(char *)(param_1 + 0x3c) == '\x02') && (DAT_ram_20001e9f != '\0')) {
                  *(undefined1 *)(param_1 + 0x3c) = 3;
                }
                uVar4 = FUN_ram_00059074(param_1);
                return uVar4;
              }
              *(char *)(param_1 + 0x3e) = *(char *)(param_1 + 0x3e) + -1;
              FUN_ram_00062262();
            }
          }
          else {
            uVar4 = 0x14;
          }
        }
        else {
          uVar4 = 3;
        }
      }
      else {
        uVar4 = 5;
      }
    }
    else {
      uVar4 = 7;
    }
  }
  else {
    uVar4 = 1;
  }
  return uVar4;
}

