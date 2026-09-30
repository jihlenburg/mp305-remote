/* Address: ram:00048e32; name: FUN_ram_00048e32; body bytes: 212 */

undefined4 FUN_ram_00048e32(undefined2 *param_1,int param_2,int *param_3)

{
  int iVar1;
  int *piVar2;
  byte bVar3;
  undefined2 *puVar4;
  undefined1 auStack_14 [4];
  
  gp = 0x20004000;
  if ((((param_2 == 0x17) &&
       (piVar2 = (int *)(*(int *)(param_1 + 8) + (uint)*(byte *)((int)param_1 + 0x15) * 0xc),
       *piVar2 == *param_3)) && ((short)piVar2[1] == (short)param_3[1])) &&
     (iVar1 = tmos_memcmp(piVar2[2],param_3[2]), iVar1 != 0)) {
    bVar3 = *(char *)((int)param_1 + 0x15) + 1;
    *(byte *)((int)param_1 + 0x15) = bVar3;
    if ((uint)*(byte *)(param_1 + 10) <= (uint)bVar3) {
      auStack_14[0] = *(undefined1 *)(param_1 + 0xb);
      goto LAB_ram_00048e48;
    }
    puVar4 = (undefined2 *)((uint)bVar3 * 0xc + *(int *)(param_1 + 8));
    iVar1 = FUN_ram_00048dc4(*param_1,*puVar4,puVar4[1],puVar4[2],*(undefined4 *)(puVar4 + 4));
    if (iVar1 == 0) {
      FUN_ram_00042194(*(undefined1 *)(param_1 + 4),48000);
      gp = 0x20004000;
      return 0x16;
    }
  }
  auStack_14[0] = 0;
LAB_ram_00048e48:
  FUN_ram_000438e4(*param_1,auStack_14);
  if (param_2 != 1) {
    FUN_ram_00042194(*(undefined1 *)(param_1 + 4),48000);
    *(undefined1 *)(param_1 + 1) = 0x19;
    *(undefined1 **)(param_1 + 2) = &LAB_ram_000438da;
    return 0x16;
  }
  gp = 0x20004000;
  return 1;
}

