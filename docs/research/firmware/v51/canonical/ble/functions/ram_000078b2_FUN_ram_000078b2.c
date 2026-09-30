/* Address: ram:000078b2; name: FUN_ram_000078b2; body bytes: 182 */

void FUN_ram_000078b2(undefined4 *param_1,undefined4 *param_2,uint param_3)

{
  undefined1 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  
  gp = &DAT_ram_20002000;
  puVar4 = (undefined4 *)((int)param_1 + param_3);
  if (((((uint)param_2 ^ (uint)param_1) & 3) == 0) && (3 < param_3)) {
    for (; ((uint)param_1 & 3) != 0; param_1 = (undefined4 *)((int)param_1 + 1)) {
      uVar1 = *(undefined1 *)param_2;
      param_2 = (undefined4 *)((int)param_2 + 1);
      *(undefined1 *)param_1 = uVar1;
    }
    for (; param_1 < (undefined4 *)((uint)puVar4 & 0xfffffffc) + -8; param_1 = param_1 + 9) {
      uVar2 = param_2[1];
      uVar11 = param_2[2];
      uVar10 = param_2[3];
      uVar9 = param_2[4];
      uVar8 = param_2[5];
      uVar3 = param_2[6];
      uVar7 = param_2[7];
      *param_1 = *param_2;
      uVar6 = param_2[8];
      param_1[1] = uVar2;
      param_1[2] = uVar11;
      param_1[3] = uVar10;
      param_1[4] = uVar9;
      param_1[5] = uVar8;
      param_1[6] = uVar3;
      param_1[7] = uVar7;
      param_1[8] = uVar6;
      param_2 = param_2 + 9;
    }
    for (; param_1 < (undefined4 *)((uint)puVar4 & 0xfffffffc); param_1 = param_1 + 1) {
      uVar2 = *param_2;
      param_2 = param_2 + 1;
      *param_1 = uVar2;
    }
  }
  if (puVar4 <= param_1) {
    return;
  }
  do {
    uVar1 = *(undefined1 *)param_2;
    puVar5 = (undefined4 *)((int)param_1 + 1);
    param_2 = (undefined4 *)((int)param_2 + 1);
    *(undefined1 *)param_1 = uVar1;
    param_1 = puVar5;
  } while (puVar5 < puVar4);
  return;
}

