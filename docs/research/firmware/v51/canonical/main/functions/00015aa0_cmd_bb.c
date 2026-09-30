/* Address: 00015aa0; name: cmd_bb; body bytes: 168 */

void cmd_bb(int param_1)

{
  int iVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  byte bVar6;
  byte bVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  
  FUN_0001049c(&DAT_1fff9a70,0xc4);
  DAT_1fff9a74 = *(byte *)(param_1 + 1);
  uVar9 = 2;
  for (uVar8 = 0; uVar8 < DAT_1fff9a74; uVar8 = uVar8 + 1 & 0xff) {
    bVar5 = *(byte *)(param_1 + uVar9);
    iVar1 = uVar8 * 0x26;
    uVar9 = uVar9 + 1 & 0xff;
    (&DAT_1fff9a76)[iVar1] = bVar5;
    bVar6 = *(byte *)(param_1 + uVar9);
    (&DAT_1fff9a77)[iVar1] = bVar6;
    uVar9 = uVar9 + 1 & 0xff;
    bVar7 = *(byte *)(param_1 + uVar9);
    uVar9 = uVar9 + 1 & 0xff;
    (&DAT_1fff9a78)[iVar1] = bVar7;
    bVar2 = *(byte *)(param_1 + uVar9);
    (&DAT_1fff9a79)[iVar1] = bVar2;
    uVar9 = uVar9 + 1 & 0xff;
    bVar3 = *(byte *)(param_1 + uVar9);
    (&DAT_1fff9a7a)[iVar1] = bVar3;
    uVar9 = uVar9 + 1 & 0xff;
    bVar4 = *(byte *)(param_1 + uVar9);
    (&DAT_1fff9a7b)[iVar1] = bVar4;
    uVar9 = uVar9 + 1 & 0xff;
    DAT_1fff9a70 = (uint)bVar4 + (uint)bVar3 + (uint)bVar2 + (uint)bVar7 + (uint)bVar6 + (uint)bVar5
                   + DAT_1fff9a70;
    bVar2 = *(byte *)(param_1 + uVar9);
    for (uVar10 = 0; uVar9 = uVar9 + 1 & 0xff, uVar10 < bVar2; uVar10 = uVar10 + 1 & 0xff) {
      (&DAT_1fff9a7c)[iVar1 + uVar10] = *(undefined1 *)(param_1 + uVar9);
    }
  }
  DAT_1fffab09 = 1;
  return;
}

