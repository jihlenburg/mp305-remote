/* Address: 000116a8; name: cmd_20; body bytes: 376 */

int cmd_20(int param_1,undefined1 *param_2,int param_3,undefined4 param_4)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  undefined1 uVar10;
  uint local_b8 [32];
  int local_38;
  int iStack_34;
  undefined1 *puStack_30;
  int local_2c;
  undefined4 uStack_28;
  
  iVar5 = DAT_1fffa0a0;
  uVar10 = 0;
  iVar9 = (uint)*(byte *)(param_1 + 5) + (uint)*(byte *)(param_1 + 6) * 0x100 +
          (uint)*(byte *)(param_1 + 7) * 0x10000 + (uint)*(byte *)(param_1 + 8) * 0x1000000;
  bVar1 = *(byte *)(param_1 + 9);
  bVar2 = *(byte *)(param_1 + 10);
  iVar8 = 0;
  bVar3 = *(byte *)(param_1 + 0xb);
  bVar4 = *(byte *)(param_1 + 0xc);
  local_2c = param_3;
  if (*(char *)(param_1 + 1) == '\x05') {
    iStack_34 = param_1;
    puStack_30 = param_2;
    uStack_28 = param_4;
    if (iVar9 == 0) {
      DAT_1fffa0a0 = 0;
      FUN_0001bdc6(0x100000);
      FUN_0001bdc6(0x110000);
      FUN_0001bdc6(0x120000);
      FUN_0001bdc6(0x130000);
    }
    if (((uint)bVar1 + (uint)bVar2 * 0x100 + (uint)bVar3 * 0x10000 + (uint)bVar4 * 0x1000000 == 0x80
        ) && (iVar9 + 0x1000U < 0x44000)) {
      uVar7 = 0;
      DAT_1fffa018 = DAT_1fffa018 + 0x80;
      FUN_0001049c(local_b8,0x80);
      local_38 = iVar9 + 0x100000;
      FUN_0001bf3a(local_38,param_1 + 0x1d,0x80);
      FUN_0001bef8(local_38,local_b8,0x80);
      do {
        uVar6 = local_b8[uVar7];
        DAT_1fffa0a0 = ((uVar6 & 0xffff) >> 8) +
                       DAT_1fffa0a0 + ((uVar6 & 0xffffff) >> 0x10) + (uVar6 >> 0x18) +
                       (uVar6 & 0xff);
        uVar7 = uVar7 + 1 & 0xffff;
      } while (uVar7 < 0x20);
    }
    else {
      uVar10 = 0xff;
    }
    *param_2 = 0x20;
    param_2[1] = *(undefined1 *)(param_1 + 1);
    param_2[2] = (char)iVar9;
    param_2[3] = (char)((uint)iVar9 >> 8);
    param_2[4] = (char)((uint)iVar9 >> 0x10);
    param_2[5] = (char)((uint)iVar9 >> 0x18);
    param_2[6] = uVar10;
    iVar8 = 7;
  }
  else if (*(char *)(param_1 + 1) == '\x06') {
    bVar1 = *(byte *)(param_1 + 0xd);
    bVar2 = *(byte *)(param_1 + 0xe);
    bVar3 = *(byte *)(param_1 + 0xf);
    bVar4 = *(byte *)(param_1 + 0x10);
    *param_2 = 0x20;
    if (iVar5 == (uint)bVar1 + (uint)bVar2 * 0x100 + (uint)bVar3 * 0x10000 + (uint)bVar4 * 0x1000000
       ) {
      param_2[1] = *(undefined1 *)(param_1 + 1);
    }
    else {
      param_2[1] = 0x86;
      DAT_1fffa018 = 0;
    }
    param_2[2] = (undefined1)DAT_1fffa0a0;
    param_2[3] = (char)((uint)DAT_1fffa0a0 >> 8);
    param_2[4] = (char)((uint)DAT_1fffa0a0 >> 0x10);
    param_2[5] = (char)((uint)DAT_1fffa0a0 >> 0x18);
    param_2[6] = 0;
    iVar8 = 7;
  }
  if (local_2c == 6) {
    param_2[iVar8] = 0x31;
    iVar8 = iVar8 + 1;
  }
  return iVar8;
}

