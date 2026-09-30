/* Address: ram:0004d7c8; name: FUN_ram_0004d7c8; body bytes: 264 */

int FUN_ram_0004d7c8(int param_1)

{
  ushort uVar1;
  short sVar2;
  uint uVar3;
  short *psVar4;
  uint uVar5;
  undefined1 *puVar6;
  int iVar7;
  short sStack_28;
  undefined2 uStack_26;
  undefined1 *puStack_24;
  
  gp = 0x20004000;
  psVar4 = *(short **)(param_1 + 0xc);
  uVar5 = (uint)DAT_ram_20001a5e;
  if ((uint)(ushort)psVar4[3] < (uint)DAT_ram_20001a5e) {
    uVar5 = (uint)(ushort)psVar4[3];
  }
  if ((ushort)psVar4[9] == 0) {
    iVar7 = 2;
  }
  else {
    iVar7 = -(uint)(ushort)psVar4[9];
  }
  uVar3 = uVar5;
  if ((int)((uint)(ushort)psVar4[8] + iVar7) < (int)uVar5) {
    uVar3 = (uint)(ushort)psVar4[8] + iVar7 & 0xffff;
  }
  puStack_24 = (undefined1 *)FUN_ram_0004c868(uVar3,2);
  iVar7 = 0x13;
  if (puStack_24 != (undefined1 *)0x0) {
    sStack_28 = psVar4[1];
    uStack_26 = (undefined2)uVar3;
    puVar6 = puStack_24;
    if (psVar4[9] == 0) {
      puVar6 = puStack_24 + 2;
      *puStack_24 = (char)psVar4[8];
      puStack_24[1] = (char)((ushort)psVar4[8] >> 8);
      if (uVar3 < uVar5) {
        uVar3 = (uint)(ushort)psVar4[8];
      }
      else {
        uVar3 = uVar3 - 2 & 0xffff;
      }
    }
    tmos_memcpy(puVar6,*(int *)(psVar4 + 6) + (uint)(ushort)psVar4[9],uVar3);
    iVar7 = FUN_ram_0004d656(*(undefined2 *)(param_1 + 6),&sStack_28);
    if (iVar7 == 0) {
      uVar1 = psVar4[9];
      sVar2 = *psVar4;
      *psVar4 = sVar2 + -1;
      psVar4[9] = (short)((uVar3 + uVar1) * 0x10000 >> 0x10);
      if ((uVar3 + uVar1 & 0xffff) < (uint)(ushort)psVar4[8]) {
        if ((short)(sVar2 + -1) == 0) {
          *(undefined1 *)((int)psVar4 + 0x1d) = 0xff;
        }
      }
      else {
        FUN_ram_0004d444(param_1,0);
      }
    }
    else {
      FUN_ram_20000104(puVar6);
    }
  }
  return iVar7;
}

