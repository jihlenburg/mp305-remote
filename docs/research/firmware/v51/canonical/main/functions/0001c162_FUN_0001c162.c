/* Address: 0001c162; name: FUN_0001c162; body bytes: 382 */

void FUN_0001c162(uint *param_1,int param_2,int param_3,uint param_4,uint param_5)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint local_48;
  uint local_40;
  uint local_3c;
  uint local_2c;
  
  local_40 = 0;
  local_3c = 0;
  local_2c = 0;
  bVar1 = true;
  iVar2 = 0;
  uVar3 = param_1[1];
  uVar5 = (param_1[3] & 3) + 1;
  uVar6 = param_1[6] & 0xf00;
  do {
    if (param_4 <= local_3c) {
LAB_0001c2be:
      if (((int)(param_1[1] << 0x1c) < 0) && (iVar2 == 0)) {
        FUN_0001c2e0(param_1,2,0,param_5);
        return;
      }
      return;
    }
    if ((local_40 < param_4) && (iVar2 = FUN_0001c2e0(param_1,0x20,0x20,0), iVar2 == 0)) {
      if ((uVar3 & 8) == 8) {
        if (bVar1) goto LAB_0001c1c2;
      }
      else if ((uVar3 & 8) == 0) {
LAB_0001c1c2:
        local_48 = 0;
        if (param_2 == 0) {
          for (; local_48 < uVar5; local_48 = local_48 + 1) {
            *param_1 = 0xffffffff;
            local_40 = local_40 + 1;
          }
        }
        else {
          for (; local_48 < uVar5; local_48 = local_48 + 1) {
            if (uVar6 < 0x401) {
              uVar4 = (uint)*(byte *)(param_2 + local_40);
            }
            else if (uVar6 < 0xc01) {
              uVar4 = (uint)*(ushort *)(param_2 + local_40 * 2);
            }
            else {
              uVar4 = *(uint *)(param_2 + local_40 * 4);
            }
            *param_1 = uVar4;
            local_40 = local_40 + 1;
          }
        }
        bVar1 = false;
      }
    }
    iVar2 = FUN_0001c2e0(param_1,0x80,0x80,0);
    if (iVar2 == 0) {
      if (param_3 == 0) {
        for (local_48 = 0; local_48 < uVar5; local_48 = local_48 + 1) {
          local_3c = local_3c + 1;
        }
      }
      else {
        for (local_48 = 0; local_48 < uVar5; local_48 = local_48 + 1) {
          uVar4 = *param_1;
          if (uVar6 < 0x401) {
            *(char *)(param_3 + local_3c) = (char)uVar4;
          }
          else if (uVar6 < 0xc01) {
            *(short *)(param_3 + local_3c * 2) = (short)uVar4;
          }
          else {
            *(uint *)(param_3 + local_3c * 4) = uVar4;
          }
          local_3c = local_3c + 1;
        }
      }
      local_2c = 0;
      bVar1 = true;
    }
    if (param_5 < local_2c) {
      iVar2 = -8;
      goto LAB_0001c2be;
    }
    local_2c = local_2c + 1;
  } while( true );
}

