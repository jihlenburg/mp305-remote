/* Address: ram:00053524; name: FUN_ram_00053524; body bytes: 474 */

undefined4 FUN_ram_00053524(int param_1)

{
  undefined1 uVar1;
  undefined2 uVar2;
  int iVar3;
  byte *pbVar4;
  undefined4 uVar5;
  int iVar6;
  byte bVar7;
  
  gp = 0x20004000;
  if (DAT_ram_20001e08 != (code *)0x0) {
    FUN_ram_00062262();
    (*DAT_ram_20001e08)();
    iVar3 = FUN_ram_00057ba2();
    if (iVar3 != 0) {
      pbVar4 = *(byte **)(param_1 + 0x50);
      *(undefined4 *)(iVar3 + 0x88) = *(undefined4 *)(param_1 + 0x24);
      if (*(char *)(param_1 + 0xb) == -0x66) {
        *(undefined1 *)(iVar3 + 0x140) = 1;
        uVar1 = *(undefined1 *)(param_1 + 99);
        *(undefined1 *)(iVar3 + 0x146) = uVar1;
        *(undefined1 *)(iVar3 + 0x147) = uVar1;
      }
      else if (DAT_ram_20001e28 << 0x11 < 0) {
        *(byte *)(iVar3 + 0x140) = (*pbVar4 & **(byte **)(param_1 + 0x4c)) >> 5 & 1;
      }
      *(uint *)(iVar3 + 0x98) =
           (uint)pbVar4[0xf] * 0x100 + (uint)pbVar4[0x10] * 0x10000 + (uint)pbVar4[0xe] +
           (uint)pbVar4[0x11] * 0x1000000;
      *(uint *)(iVar3 + 0x9c) =
           (uint)pbVar4[0x13] * 0x100 + (uint)pbVar4[0x14] * 0x10000 + (uint)pbVar4[0x12];
      *(byte *)(iVar3 + 0x35) = pbVar4[0x15];
      *(undefined2 *)(iVar3 + 0x36) = *(undefined2 *)(pbVar4 + 0x16);
      *(undefined2 *)(iVar3 + 0x38) = *(undefined2 *)(pbVar4 + 0x18);
      *(undefined2 *)(iVar3 + 0x3a) = *(undefined2 *)(pbVar4 + 0x1a);
      uVar2 = *(undefined2 *)(pbVar4 + 0x1c);
      *(undefined4 *)(iVar3 + 0x13c) = 0;
      *(undefined2 *)(iVar3 + 0x3c) = uVar2;
      *(undefined4 *)(iVar3 + 0x138) = 0;
      tmos_memcpy(iVar3 + 0x138,pbVar4 + 0x1e,5);
      iVar6 = *(int *)(param_1 + 0x50);
      bVar7 = *(byte *)(iVar6 + 0x23) & 0x1f;
      *(byte *)(iVar3 + 0x33) = bVar7;
      *(byte *)(iVar3 + 0x2f) = *(byte *)(iVar6 + 0x23) >> 5;
      if ((((0xb < (byte)(bVar7 - 5)) || (0xc7a < (ushort)(*(short *)(iVar3 + 0x38) - 6U))) ||
          (499 < *(ushort *)(iVar3 + 0x3a))) || (&timeh <= *(undefined **)(iVar3 + 0x3c))) {
        FUN_ram_00057d86(*(undefined2 *)(iVar3 + 8));
        gp = 0x20004000;
        return 0;
      }
      (*DAT_ram_20001e0c)(iVar3);
      uVar5 = 10;
      if ((DAT_ram_20001e30 & 0x200) == 0) {
        uVar5 = 1;
      }
      FUN_ram_0005d5f6(*(undefined2 *)(iVar3 + 8),0x80,uVar5);
      if (DAT_ram_20001e28 << 0x11 < 0) {
        FUN_ram_0005d5f6(*(undefined2 *)(iVar3 + 8),0x80,0x14);
      }
      if (*(int *)(DAT_ram_20001db4 + 0x54) << 4 < 0) {
        *(undefined1 *)(param_1 + 0x17) = 0;
        FUN_ram_0005d5f6(*(undefined1 *)(param_1 + 8),0x80,0x12);
      }
    }
  }
  return 1;
}

