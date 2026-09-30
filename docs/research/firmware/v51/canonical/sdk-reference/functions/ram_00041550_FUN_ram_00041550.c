/* Address: ram:00041550; name: FUN_ram_00041550; body bytes: 462 */

void FUN_ram_00041550(uint param_1,int param_2)

{
  uint *puVar1;
  byte *pbVar2;
  int iVar3;
  char *pcVar4;
  uint uVar5;
  int iVar6;
  ushort uVar7;
  char local_48 [48];
  
  gp = 0x20004000;
  *DAT_ram_20001e88 = *DAT_ram_20001e88 & 0xfffffe7f | 0x80;
  *(uint *)(DAT_ram_20001efc + 8) = *(uint *)(DAT_ram_20001efc + 8) & 0xffcdffff;
  *(undefined4 *)(DAT_ram_20001eb0 + 0x50) = 0x80;
  FUN_ram_00040484(local_48,0x81,0x28);
  (*(code *)&SUB_ram_e00a240c)();
  (*(code *)&SUB_ram_e00a24d2)();
  puVar1 = DAT_ram_20001e88;
  DAT_ram_20001e88[2] = 0;
  puVar1[4] = puVar1[4] | 0x3f;
  iVar3 = -0x7f;
  puVar1[0x17] = puVar1[0x17] & 0xfffffe00 | param_1 & 0x1ff;
  *puVar1 = *puVar1 & 0xffffcfff;
  *puVar1 = *puVar1 & 0xfffffe7f;
  *puVar1 = *puVar1 & 0xfffffe7f | 0x100;
  *(uint *)(DAT_ram_20001efc + 8) = *(uint *)(DAT_ram_20001efc + 8) | 0x330000;
  pcVar4 = local_48;
  *(undefined4 *)(DAT_ram_20001eb0 + 0x50) = 0xd9;
  uVar5 = 0;
  do {
    iVar6 = DAT_ram_20001efc;
    puVar1 = DAT_ram_20001e88;
    pbVar2 = (byte *)((uVar5 >> 3) + param_2);
    if (((int)(uint)*pbVar2 >> (uVar5 & 7) & 1U) != 0) {
      *(undefined2 *)(DAT_ram_20001e88 + 0x16) = 0;
      *(undefined2 *)(puVar1 + 0x18) = 0;
      *(uint *)(iVar6 + 0x2c) = *(uint *)(iVar6 + 0x2c) & 0xfffffffd;
      *puVar1 = *puVar1 & 0xffffff80 | uVar5 & 0x7f;
      puVar1[9] = puVar1[9] | 0x40000;
      iVar6 = DAT_ram_20001eb0;
      uVar7 = 0;
      do {
        *(undefined4 *)(iVar6 + 100) = 500;
        if (uVar7 != (ushort)puVar1[0x18]) {
          if (*pcVar4 < (char)(puVar1[0xc] >> 0xf)) {
            *pcVar4 = (char)(puVar1[0xc] >> 0xf);
          }
          uVar7 = (ushort)puVar1[0x18] & 0xff;
        }
      } while ((*(int *)(iVar6 + 100) != 0) && ((ushort)puVar1[0x16] < 5));
      puVar1[9] = puVar1[9] & 0xfffbffff;
      iVar6 = (int)*pcVar4;
      if ((int)param_1 < iVar6) {
        *pbVar2 = ~(byte)(1 << (uVar5 & 7)) & *pbVar2;
      }
      if (iVar6 < iVar3) {
        iVar6 = iVar3;
      }
      iVar3 = (int)(char)iVar6;
    }
    uVar5 = uVar5 + 1 & 0xff;
    pcVar4 = pcVar4 + 1;
  } while (uVar5 != 0x28);
  return;
}

