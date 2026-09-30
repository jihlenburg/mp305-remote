/* Address: ram:00040374; name: FUN_ram_00040374; body bytes: 216 */

void FUN_ram_00040374(uint *param_1)

{
  uint *puVar1;
  uint *puVar2;
  uint *puVar3;
  uint *puVar4;
  uint uVar5;
  uint *puVar6;
  uint *puVar7;
  
  puVar4 = DAT_ram_20001b5c;
  puVar1 = DAT_ram_20001b54;
  gp = 0x20004000;
  if (param_1 != (uint *)0x0) {
    puVar2 = (uint *)0x0;
    puVar7 = DAT_ram_20001b5c;
    do {
      puVar6 = puVar7;
      puVar3 = puVar2;
      if (DAT_ram_20001b54 <= puVar6) {
        gp = 0x20004000;
        return;
      }
      puVar7 = (uint *)*puVar6;
      puVar2 = puVar6;
    } while ((param_1 < puVar6) || (puVar7 < param_1));
    if (puVar6 + 2 <= param_1) {
      if (*(short *)((int)puVar6 + 6) == -0x7fff) {
        DAT_ram_20001a64 = DAT_ram_20001a64 + '\x01';
      }
      uVar5 = puVar6[1];
      *(undefined2 *)((int)puVar6 + 6) = 0;
      DAT_ram_20001b6a = DAT_ram_20001b6a + (short)uVar5;
      if (((puVar6 != puVar4) && (DAT_ram_20001b58 != puVar6)) && (*(short *)((int)puVar3 + 6) == 0)
         ) {
        *puVar3 = (uint)puVar7;
        DAT_ram_20001b6a = DAT_ram_20001b6a + 8;
        *(short *)(puVar3 + 1) = (short)uVar5 + (short)puVar3[1] + 8;
        puVar6 = puVar3;
      }
      puVar4 = (uint *)*puVar6;
      if (((puVar4 != puVar1) && (puVar4 != DAT_ram_20001b58)) && (*(short *)((int)puVar4 + 6) == 0)
         ) {
        uVar5 = *puVar4;
        *(short *)(puVar6 + 1) = (short)puVar6[1] + 8 + (short)puVar4[1];
        *puVar6 = uVar5;
        DAT_ram_20001b6a = DAT_ram_20001b6a + 8;
        return;
      }
    }
  }
  return;
}

