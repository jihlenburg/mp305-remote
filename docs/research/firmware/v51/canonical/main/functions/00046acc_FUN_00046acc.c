/* Address: 00046acc; name: FUN_00046acc; body bytes: 166 */

/* Recovered from stored Thumb pointer at 0006a6dc; callback identification is inferred until
   reviewed. */

undefined4 FUN_00046acc(int param_1,int param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  uint *puVar3;
  undefined4 uVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  bool bVar8;
  
  bVar8 = param_3 == 9;
  if (bVar8) {
    param_3 = 0x20;
  }
  iVar6 = *(int *)(param_1 + 0x18);
  iVar1 = FUN_000372f4(param_1,param_3);
  uVar4 = 0;
  if (iVar1 != 0) {
    iVar7 = 0;
    if ((*(int *)(iVar6 + 0xc) != 0) && (iVar2 = FUN_000372f4(param_1,param_4), iVar2 != 0)) {
      iVar7 = FUN_00037460(param_1,iVar1);
    }
    puVar3 = (uint *)(*(int *)(iVar6 + 4) + iVar1 * 8);
    uVar5 = *puVar3 >> 0x14;
    if (bVar8) {
      uVar5 = uVar5 << 1;
    }
    *(short *)(param_2 + 4) =
         (short)(uVar5 + ((int)((uint)*(ushort *)(iVar6 + 0x10) * iVar7) >> 4) + 8 >> 4);
    *(ushort *)(param_2 + 8) = (ushort)*(byte *)((int)puVar3 + 5);
    uVar5 = puVar3[1];
    *(ushort *)(param_2 + 6) = (ushort)(byte)uVar5;
    *(short *)(param_2 + 10) = (short)*(char *)((int)puVar3 + 6);
    *(short *)(param_2 + 0xc) = (short)*(char *)((int)puVar3 + 7);
    *(byte *)(param_2 + 0xe) = (byte)(((uint)*(ushort *)(iVar6 + 0x12) << 0x13) >> 0x1c);
    *(undefined1 *)(param_2 + 0xf) = 0;
    *(int *)(param_2 + 0x10) = iVar1;
    if (bVar8) {
      *(ushort *)(param_2 + 6) = (ushort)(byte)uVar5 << 1;
    }
    uVar4 = 1;
  }
  return uVar4;
}

