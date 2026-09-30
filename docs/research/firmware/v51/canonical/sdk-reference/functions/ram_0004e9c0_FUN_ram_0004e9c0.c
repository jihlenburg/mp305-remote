/* Address: ram:0004e9c0; name: FUN_ram_0004e9c0; body bytes: 280 */

undefined4 FUN_ram_0004e9c0(int param_1,byte *param_2)

{
  ushort uVar1;
  ushort uVar2;
  byte bVar3;
  byte bVar4;
  ushort uVar5;
  ushort uVar6;
  ushort uVar7;
  ushort uVar8;
  ushort uVar9;
  ushort uVar10;
  undefined4 uVar11;
  
  gp = 0x20004000;
  if ((param_1 != 0) && (param_2 != (byte *)0x0)) {
    *param_2 = *(byte *)(param_1 + 1);
    param_2[1] = *(byte *)(param_1 + 2);
    param_2[2] = *(byte *)(param_1 + 3);
    param_2[3] = *(byte *)(param_1 + 4);
    uVar5 = (*(byte *)(param_1 + 5) & 1) << 8;
    uVar1 = *(ushort *)(param_2 + 4);
    *(ushort *)(param_2 + 4) = uVar1 & 0xfeff | uVar5;
    uVar6 = (*(byte *)(param_1 + 5) & 2) << 8;
    *(ushort *)(param_2 + 4) = uVar6 | uVar1 & 0xfcff | uVar5;
    uVar9 = (*(byte *)(param_1 + 5) & 4) << 8;
    *(ushort *)(param_2 + 4) = uVar9 | uVar6 | uVar1 & 0xf8ff | uVar5;
    uVar2 = (ushort)(((int)(uint)*(byte *)(param_1 + 5) >> 3 & 1U) << 0xb);
    *(ushort *)(param_2 + 4) = uVar2 | uVar9 | uVar6 | uVar1 & 0xf0ff | uVar5;
    uVar7 = *(byte *)(param_1 + 6) & 1;
    *(ushort *)(param_2 + 4) = uVar7 | uVar2 | uVar9 | uVar6 | uVar1 & 0xf0fe | uVar5;
    uVar10 = *(byte *)(param_1 + 6) & 2;
    *(ushort *)(param_2 + 4) = uVar7 | uVar2 | uVar9 | uVar6 | uVar1 & 0xf0fc | uVar5 | uVar10;
    uVar8 = *(byte *)(param_1 + 6) & 4;
    *(ushort *)(param_2 + 4) =
         uVar7 | uVar2 | uVar9 | uVar6 | uVar1 & 0xf0f8 | uVar5 | uVar10 | uVar8;
    *(ushort *)(param_2 + 4) =
         uVar7 | uVar2 | uVar9 | uVar6 | uVar1 & 0xf0f0 | uVar5 | uVar10 | uVar8 |
         *(byte *)(param_1 + 6) & 8;
    bVar3 = GAP_GetParamValue(0x13);
    bVar4 = GAP_GetParamValue(0x14);
    uVar11 = 0x12;
    if ((((bVar3 <= param_2[3]) && (param_2[3] <= bVar4)) && (uVar11 = 0x18, *param_2 < 5)) &&
       (param_2[1] < 2)) {
      uVar11 = 0;
    }
    return uVar11;
  }
  return 2;
}

